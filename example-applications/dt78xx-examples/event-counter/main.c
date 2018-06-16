/* 
 * This is a simple test of counter timer in the DT78xx family. The example
 * opens file /dev/dt78xx-ctr-tmr, sends ioctls to configure the counter
 * timer to count events and reads the counter
 * Command line arguments configure the clock and gate source, the digital
 * input pins used for external clock and gate 
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
"Application to count pulses on external clock input or internal clock.\n"
"Uses either external gate or software to start and stop counting\n"
"Usage : evt-counter [options]\n"
"Options :\n"
"-x|--xclk selects external clock, default is internal 48MHz\n"
"-g|--gate <lo|hi|no> : selects external gate lo,hi or no gate, i.e software\n"
"-i|--gatein <number> selects DIN used as external gate, number is 0-7\n"
"-c|--clkin <number> selects DIN used as external clock input, number is 0-7\n"
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
        printf("Period %u pulse %u freq %.3f Hz Duty cycle %.2f\n", 
               cfg->divider.period, cfg->divider.pulse,
               (cfg->divider.period ? 
                   48000000.0f/cfg->divider.period : 0.0f),
               (cfg->divider.period ?
               (float)cfg->divider.pulse/cfg->divider.period :
                   0.0f));
        printf("Period %u pulse %u Duty cycle %.2f\n", 
               cfg->divider.period, cfg->divider.pulse,
               (float)cfg->divider.pulse/cfg->divider.period);
    }
    else if (cfg->mode == ct_mode_divider)
        printf("Counter mode\n");

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
        {0,             0,                 0,  0   }
    };

    memset(&ct_cfg, 0, sizeof(ct_cfg));
    ct_cfg.mode = ct_mode_counter;
    
    opterr = 0;
    while ((opt = getopt_long(argc, argv,"xg:i:c:", long_options, NULL)) != -1) 
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
             default: 
                 print_usage(); 
                 exit(EXIT_FAILURE);
        }
    }

    ct_file = open(CT_DEV_FILE, O_RDWR);
    if (ct_file < 0)
    {
        perror("open ");
        return (EXIT_FAILURE);
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
    
    if (ct_cfg.gate != ct_gate_none)
        printf("Gate='%d' on DIN%d enables counting\n", 
               (ct_cfg.gate==ct_gate_ext_hi)?1:0,
                ct_cfg.ext_gate_din);
    printf("Press s/p/r to start/stop/read counter, q to quit\n");
   
    int err = 0;
    while (!err)
    {
        int c = getchar();
        if ((c=='s')||(c=='S'))
        {
            err = ioctl(ct_file, IOCTL_START_SUBSYS, NULL);
            if (err)
                perror("IOCTL_START_SUBSYS"); 
        }
        else if ((c=='p')||(c=='P'))
        {
            err = ioctl(ct_file, IOCTL_STOP_SUBSYS, NULL);
            if (err)
                perror("IOCTL_STOP_SUBSYS"); 
        }
        else if ((c=='r')||(c=='R'))
        {
            uint32_t count;
            err = read(ct_file, &count, sizeof(count));
            if (err < 0)
                perror("read"); 
            else if (err == sizeof(count)) //#of bytes read
            {
                printf("%u (%#08x)\n", count,count);
                err = 0; //reset since no errors
            }
            else
                printf("Got only %d bytes\n", err);
        }
        else if ((c=='q')||(c=='Q'))
            break;
    }
    
finish:    
    if (ct_file > 0)
    {
        ioctl(ct_file, IOCTL_STOP_SUBSYS, NULL);
        close(ct_file);
    }
    return (EXIT_SUCCESS);
}
