/*****************************************************************************
 * DT78xx USB client application. This  application communicates with a
 * corresponding host application over USB. 
 * Specifically, this application does a  blocking read on an OUT endpoint 
 * followed by blocking write to an IN endpoint. The data read from the host
 * application's  OUT endpoint is looped back to the IN endpoint
 *
 * Copyright (C) 2014 Data Translation Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 ***************************************************************************** 
 *
 *         PC                       DT78xx     
 * =====================   ================================= 
 *   
 *   +--------------+          +-----------------------+       
 *   | USB host app |          |  Client  application  |     
 *   +------+-------+          +-------+---------------+
 *          :                          :                      
 *          :                          :                          
 *   +------+-------+                  :                          
 *   |   libusb     |                  :                          
 *   +------+-------+                  :                          
 *          :                          :                          
 *          :                +---------+---------+      
 *   +------+---------+      |     g_dt78xx      |      
 *   |USB host driver |      | USB gadget driver |         
 *   +------+---------+      +---------+---------+      
 *          :                          :                          
 *          :                          :                          
 *          :......... USB ............:                      
 * 
 * USAGE :
 * 1) Build both host and device USB applications.
 * 2) Copy this application to the board.
 * 2) Execute this application specifying the length of data to loopback
 *      and the USB pipes to use. See command line arguments below.
 * 3) Execute the host application specifying the length of data to write and
 *      read back.
 * 4) If the test succeeds, the CRC32 of date written will match that of data
 *      looped back from device to host.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h> //getopt())
#include <stdlib.h>
#include <string.h>

/*
 * Command line arguments
 */
static void usage(const char *filename)
{
    fprintf(stderr,"Synchronous read/write test\n");
    fprintf(stderr,"Usage\n%s -l len -i epin -o epout\n", filename);
    fprintf(stderr,"\tlen is the length in bytes to read from host and write back\n");
    fprintf(stderr,"\tepin is the input endpoint, e.g. /dev/dt78xx_ep1in\n");
    fprintf(stderr,"\tepout is the output endpoint, e.g. /dev/dt78xx_ep1out\n");
    fprintf(stderr,"\tData read through epout will be written to epin\n");
}

/*
 * main
 */
int main (int argc, char** argv)
{
    unsigned char *buff;
    int fd_out; //out endpoint file
    int fd_in;  //in endpoint
    int opt;
    int total_len = 0;
    const char *epin = NULL;
    const char *epout = NULL;
    
    //Get command line args and validate them
    while ((opt = getopt(argc, argv, "l:b:i:o:")) != -1) 
    {
        switch (opt) 
        {
            case 'l':
            total_len = strtoul(optarg, NULL, 10);
            break;
            
            case 'i':
            epin = optarg;
            break;
            
            case 'o':
            epout = optarg;
            break;
        }
    } 
    if (!epin || !epout || (total_len <=0))
    {
        usage(argv[0]);
        return (EXIT_FAILURE);
    }
    
    //Buffer to read data sent from host
    buff = malloc(total_len);
    if (!buff)
    {
        printf("ERROR malloc %d bytes\n",total_len);
        return (EXIT_FAILURE);
    }
    
    //Output USB pipe to read data from host. NOTE : output from host
    fd_out = open(epout, O_RDONLY);
    if (fd_out < 0)
    {
        free(buff);
        perror("open ");
        return (EXIT_FAILURE);
    }
    //Input USB pipe to write data to host
    fd_in = open(epin, O_WRONLY);
    if (fd_in < 0)
    {
        free(buff);
        close (fd_out);
        perror("open ");
        return (EXIT_FAILURE);
    }
    
    printf("read %d bytes from %s and write to %s\n", 
           total_len, epout, epin);
    
    //blocking read from host
    int read_len = read(fd_out, buff, total_len);
    if (read_len < total_len)
    {
        perror(" read\n");
    }
    else
    {
        printf("read %d\n", read_len);
        
        //blocking write to host
        int write_len = write(fd_in, buff, total_len);
        if (write_len < total_len)
        {
            perror(" write\n");
        }
        else
        {
            printf(" write %d\n", write_len);
        }
        if (write_len != read_len)
        {
            printf("ERROR wrote %d read %d\n", write_len, read_len);
        }
    }
    
    //As usual, need to clean up
    close(fd_in);
    close(fd_out);
    free(buff);
    return (EXIT_SUCCESS);
}

