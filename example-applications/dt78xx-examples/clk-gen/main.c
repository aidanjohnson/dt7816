/* 
 * This is a simple test of counter timer in the DT78xx family. The example
 * opens file /dev/dt7837-ctr-tmr (or /dev/dt7816-ctr-tmr) and sends ioctls to 
 * configure the counter timer to generate an output clock from dividing either
 * the internal clock or an external clock.
 * Command line arguments configure the clock and gate source, the digital
 * input pins used for external clock and gate and the digital output pin used
 * to output the generated clock
 * 
 *  ===========================================================================
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed WITHOUT ANY WARRANTY; without the implied
 *  warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * ============================================================================
 * Usage : see msg[] below
 *  
 */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <getopt.h>

#include "dt78xx_ioctl.h"

#ifdef DT7837
#define CT_DEV_FILE     "/dev/dt7837-ctr-tmr"
#elif DT7816
#define CT_DEV_FILE     "/dev/dt7816-ctr-tmr"
#else
#error BOARD_TYPE not defined!!
#endif

static const char msg[]=
{
"Generate clock by dividing either the input 48MHz clock or an external clock\n"
"Usage : clkgen [options] -p|--period <number> -u|--pulse <number>\n"
"-p|--period <number> specifies output clock total period; number is 32-bit\n"
"-u|--pulse <number> specifies output clock active period, number is 32-bit\n"
"     duty-cyle=(pulse/period); hence pulse must be less than period\n"
"Options :\n"
"-x|--xclk : select external clock, default is internal 48MHz\n"
"-c|--clkin <number> : uses DIN <number> as external clock input, number is 0-7\n"
"-g|--gate lo|hi|no : selects external gate lo, external gate hi or no gate\n"
"     default is no gate\n"
"-i|--gatein <number> : uses DIN <number> as external gate, number is 0-7\n"
"-o|--clkout <number> uses DOUT <number> as clock output, number is 0-7\n"
"     default is DOUT0\n"
};

void print_usage() 
{
    printf(msg);
}

static void print_cfg(const dt78xx_ct_config_t *cfg)
{
    if (cfg->mode == ct_mode_divider)
    {
        printf("Clock divider mode, output DOUT%d\n", cfg->divider.out);
        if (!cfg->ext_clk)
            printf("Period %u pulse %u freq %.3f Hz Duty cycle %.2f\n", 
                   cfg->divider.period, cfg->divider.pulse,
                   (cfg->divider.period ? 
                       48000000.0f/cfg->divider.period : 0.0f),
                   (cfg->divider.period ?
                   (float)cfg->divider.pulse/cfg->divider.period :
                       0.0f));
        else
            printf("Period %u pulse %u Duty cycle %.2f\n", 
                   cfg->divider.period, cfg->divider.pulse,
                   (float)cfg->divider.pulse/cfg->divider.period);
    }
    else if (cfg->mode == ct_mode_counter)
        printf("Counter mode\n");
    else if (cfg->mode == ct_mode_1shot)
        printf("One shot mode\n");
    else if (cfg->mode == ct_mode_idle)
        printf("Counter/Timer idle !!\n");

    if ((cfg->gate==ct_gate_ext_hi)||
             (cfg->gate==ct_gate_ext_lo))
    {
        printf("Gate %s", (cfg->gate==ct_gate_ext_hi)?"gate hi":
                          "gate lo");
        printf(" on DIN%d\n",cfg->ext_gate_din);
    }
    
    if (cfg->ext_clk)
    {
        printf("Clock : external on DIN%d\n", cfg->ext_clk_din);
    }
    else
    {
        printf("Clock : internal\n");
    }
}

int main(int argc, char *argv[]) 
{
    int opt= 0;
    int ct_file = -1;
    dt78xx_ct_config_t ct_cfg;

    //Specifying the expected options
    static struct option long_options[] = 
    {
        {"xclk",        no_argument,        0,  'x' },
        {"gate",        required_argument,  0,  'g' },
        {"gatein",      required_argument,  0,  'i' },
        {"clkin",       required_argument,  0,  'c' },
        {"clkout",      required_argument,  0,  'o' },
        {"period",      required_argument,  0,  'p' },
        {"pulse",       required_argument,  0,  'u' },
        {0,             0,                 0,  0   }
    };

    ct_file = open(CT_DEV_FILE, O_RDWR);
    if (ct_file < 0)
    {
        perror("open ");
        return (EXIT_FAILURE);
    }

    //set the current configuration
    memset(&ct_cfg, 0, sizeof(ct_cfg));
    ct_cfg.mode = ct_mode_divider;
    ct_cfg.divider.period = 1000; //default
    ct_cfg.divider.pulse = 500; // default
    ct_cfg.divider.out_hi = 1; //active high
    
    int long_index =0;
    opterr = 0;
    while ((opt = getopt_long(argc, argv,"xg:i:c:o:p:u:", 
                   long_options, &long_index )) != -1) 
    {
        switch (opt) 
        {
             case 'x' : ct_cfg.ext_clk = 1;
                 break;
             case 'g' : ct_cfg.gate = !strcmp(optarg, "no")?ct_gate_none:
                                             !strcmp(optarg, "hi")?ct_gate_ext_hi:
                                             ct_gate_ext_lo;
                 break;
             case 'i' : ct_cfg.ext_gate_din = atoi(optarg); 
                 break;
             case 'c' : ct_cfg.ext_clk_din = atoi(optarg);
                 break;
             case 'o' : ct_cfg.divider.out = atoi(optarg);
                 break;
             case 'p' : ct_cfg.divider.period = strtoul(optarg, NULL, 10);
                 break;
             case 'u' : ct_cfg.divider.pulse = strtoul(optarg, NULL, 10);
                 break;
             default: 
                 print_usage(); 
                 exit(EXIT_FAILURE);
        }
    }
    
    if (ioctl(ct_file, IOCTL_CT_CFG_SET, &ct_cfg))
    {
        perror("IOCTL_CT_CFG_SET");    
        goto finish;
    }
    
    if (ioctl(ct_file, IOCTL_CT_CFG_GET, &ct_cfg))
    {
        perror("IOCTL_CT_CFG_GET");    
        goto finish;
    }
    print_cfg(&ct_cfg);
    
    //verify configuration
    if (ct_cfg.mode != ct_mode_divider)
    {
        printf("ERROR : Counter/Timer configuration\n");
        goto finish;
    }
    
    printf("Press s to start counter, p to stop counter, q to quit\n");
    if (ct_cfg.gate != ct_gate_none)
        printf("Gate='%d' on DIN%d enables counting\n", 
               (ct_cfg.gate==ct_gate_ext_hi)?1:0,
                ct_cfg.ext_gate_din);
    while (1)
    {
        int c = getchar();
        if ((c=='s')||(c=='S'))
        {
            if (ioctl(ct_file, IOCTL_START_SUBSYS, NULL))
            {
                perror("IOCTL_START_SUBSYS"); 
                break;
            }
        }
        else if ((c=='p')||(c=='P'))
        {
            if (ioctl(ct_file, IOCTL_STOP_SUBSYS, NULL))
            {
                perror("IOCTL_STOP_SUBSYS"); 
                break;
            }
        }
        else if ((c=='q')||(c=='Q'))
            break;
    }
    
finish: 
    if (ct_file > 0)
    {
        ioctl(ct_file, IOCTL_STOP_SUBSYS, NULL); //stop the counter on exiting
        close(ct_file);
    }
    return (EXIT_SUCCESS);
}
