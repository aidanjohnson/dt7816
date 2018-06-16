/*****************************************************************************
 * DT78xx USB host application. This host application communicates with a
 * corresponding application in the DT78xx board over USB. This application
 * merely sends a block of data through an OUT USB pipe which the board 
 * application loops back through an IN USB pipe.
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
 * PREREQUISITES :
 * The program requires libusb. libusb is a C library that gives applications
 * easy access to USB devices on many different operating systems. libusb is
 * an open source project, the code is licensed under the ​GNU Lesser General
 * Public License version 2.1 or later. If libusb is not already installed, 
 * please see http://www.libusb.org/ to download and install libusb.
 * 
 * USAGE :
 * 1) Build both host and device USB applications.
 * 2) Copy the USB device application to the board.
 * 2) Execute the device application specifying the length of data to loopback
 *      and the USB pipes to use. See command line arguments for device app.
 * 3) Execute the host application specifying the length of data to write and
 *      read back.
 * 4) If the test succeeds, the CRC32 of date written will match that of data
 *      looped back from device to host.
 */
#include <libusb.h>
#include <stdio.h>
#include <unistd.h> //getopt())
#include <stdlib.h>
#include <string.h>
#include <signal.h>

#define DEFAULT_LOOP_LEN (4096)

//Command line args, see usage
struct cmdline_args
{
    uint16_t    vid;        
    uint16_t    pid;
    uint8_t     ep_in;
    uint8_t     ep_out;
    uint32_t    loop_len;
};

extern unsigned int xcrc32 (const unsigned char *buf, int len, 
                                unsigned int init);
static void printdev(libusb_device *dev); //prototype of the function
static int  parse_args(int argc, char *argv[], struct cmdline_args *args);
static int  match_device(libusb_device *dev, int vid, int pid);
static void print_str_descriptors(libusb_device_handle* dev_handle);
static int  loopback(libusb_device_handle* dev_handle, 
                     const struct cmdline_args *args);
static void print_usage(const char *prog);

int main(int argc, char *argv[]) 
{
    struct cmdline_args args;
    if (parse_args(argc, argv, &args))
    {
        return EXIT_FAILURE;
    }
    
	libusb_context *ctx = NULL; //a libusb session
    if (libusb_init(&ctx) < 0) //initialize a library session
    {
		printf("Init Error\n"); //there was an error
        return EXIT_FAILURE;
	}
    libusb_set_debug(ctx, 3); //set verbosity level to 3, as per documentation
    
    libusb_device_handle* dev_handle;
    dev_handle = libusb_open_device_with_vid_pid(ctx, args.vid, args.pid);
    if (!dev_handle) //device not found
    {
        printf("USB device vid %#04x pid %#04x not found\n", args.vid, args.pid);
        libusb_exit(ctx); //close the session
        return EXIT_FAILURE;
    }
    
    loopback(dev_handle, &args);
                
    libusb_close(dev_handle);
    libusb_exit(ctx); //close the session
    return 0;
}

static void printdev(libusb_device *dev) 
{
	struct libusb_device_descriptor desc;
	int r = libusb_get_device_descriptor(dev, &desc);
	if (r < 0) 
    {
		printf("failed to get device descriptor\n");
		return;
	}
    printf("\n");
	printf("VendorID %#04x ProductID %#04x\n", desc.idVendor, desc.idProduct);
	printf("Number of possible configurations:%d Device Class:%#02x\n",
           (int)desc.bNumConfigurations, (int)desc.bDeviceClass);
	
    struct libusb_config_descriptor *config;
	libusb_get_config_descriptor(dev, 0, &config);
	printf("Interfaces %d\n",(int)config->bNumInterfaces);
	
    const struct libusb_interface *inter;
	const struct libusb_interface_descriptor *interdesc;
	const struct libusb_endpoint_descriptor *epdesc;
    int i;
	for(i=0; i<(int)config->bNumInterfaces; i++) 
    {
		inter = &config->interface[i];
		printf("Number of alternate settings: %d\n", inter->num_altsetting);
        int j;
		for(j=0; j<inter->num_altsetting; j++) 
        {
			interdesc = &inter->altsetting[j];
			printf("\tInterface Number: %d",(int)interdesc->bInterfaceNumber);
			printf(" Number of endpoints: %d\n", (int)interdesc->bNumEndpoints);;
			int k;
            for(k=0; k<(int)interdesc->bNumEndpoints; k++) 
            {
				epdesc = &interdesc->endpoint[k];
				printf("\t\tDescriptor Type: %d",(int)epdesc->bDescriptorType);
				printf(" EP Address: %#02x\n", (int)epdesc->bEndpointAddress);
			}
		}
	}
	libusb_free_config_descriptor(config);
}

static void print_usage(const char *prog)
{
    printf("Usage: %s -v <vid> -p <pid> [-i <in> -o <out> <len>]\n",prog?"":prog);
    printf("vid is a hex 16-bit USB vendor id\n");
    printf("pid is a hex 16-bit product id\n");
    printf("in is a hex 8-bit IN USB endpoint to read data from device\n");
    printf("out is a hex 8-bit OUT USB endpoint to write data to device\n");
    printf("len is the number of bytes to write and read back\n");
}
/**
 * Parse the command line args 
 * 
 * Returns :
 *  -1 on error
 *  On success, 0
 */
static int  parse_args(int argc, char *argv[], struct cmdline_args *args)
{
    int opt;
    memset(args, 0, sizeof(struct cmdline_args));
    while ((opt = getopt(argc, argv, "v:p:i:o:")) != -1) 
    {
        switch (opt) 
        {
        case 'v':
            args->vid = (uint16_t)strtoul(optarg, NULL, 16);
            break;
        case 'p':
            args->pid = (uint16_t)strtoul(optarg, NULL, 16);
            break;
        case 'i':
            args->ep_in = (uint8_t)strtoul(optarg, NULL, 16);
            break;
        case 'o':
            args->ep_out = (uint8_t)strtoul(optarg, NULL, 16);
            break;
        default:
            print_usage(argv[0]);
            return -1;
        }
    } 
    //Vid and Pid are mandatory
    if (!args->vid || !args->pid)
    {
        print_usage(argv[0]);
        return -1;
    }
    
    //if epin and epout are specified then len is mandatory
    if (args->ep_in && args->ep_out)
    {
        if ((optind < argc) && argv[optind])
        {
            args->loop_len = strtoul(argv[optind], NULL, 10);
            return 0;
        }
        else
        {
            print_usage(argv[0]);
            return -1;
        }
    }
    return 0;
}
#if 0
/*
 * Match the specified vendor and product id in the given device
 * Params :
 *  dev : device to check for match
 *  vid : vendor ID to match
 *  pid : product id to match
 * Returns :
 *  0 : match found
 *  non-zero : no match
 */
static int match_device(libusb_device *dev, int vid, int pid)
{
    int match;
	libusb_device_descriptor desc;
	match = libusb_get_device_descriptor(dev, &desc);
	if (match < 0) 
    {
		printf("Failed to get device descriptor\n");
	}
    else if ((vid == desc.idVendor)&&(pid == desc.idProduct))
    {
        match = 0;
    }
    else
    {
        match = -1;
    }
    return match;
}
#endif
/**
 * Print all string decriptors
 * @param dev_handle : device handle
 */
static void print_str_descriptors(libusb_device_handle* dev_handle)
{
    struct libusb_device *dev =libusb_get_device(dev_handle);
                
    struct libusb_device_descriptor desc;
    int ret = libusb_get_device_descriptor(dev, &desc);
    if (ret < 0) 
    {
        printf("failed to get device descriptor\n");
        return;
    }
    
    unsigned char buff[64];
    //show the manufacturer string descriptors
    ret = libusb_get_string_descriptor_ascii(dev_handle, desc.iManufacturer, 
                                             buff, sizeof(buff));
    if ((ret>0) && (ret< sizeof(buff)))
    {
        buff[ret]= '\0';
        printf("Manufacturer : %s\n",buff);
    }
    
    ret = libusb_get_string_descriptor_ascii(dev_handle, desc.iProduct, 
                                             buff, sizeof(buff));
    if ((ret>0) && (ret< sizeof(buff)))
    {
        buff[ret]= '\0';
        printf("Product : %s\n",buff);
    }
    //show the serial number
    ret = libusb_get_string_descriptor_ascii(dev_handle, desc.iSerialNumber, 
                                             buff, sizeof(buff));
    if ((ret>0) && (ret< sizeof(buff)))
    {
        buff[ret]= '\0';
        printf("Serial : %s\n",buff);
    }
    
    //active configuration descriptor's string
    struct libusb_config_descriptor *config;
    ret = libusb_get_active_config_descriptor (dev, &config);
    if (ret == 0)
    {
        ret = libusb_get_string_descriptor_ascii(dev_handle, 
                                                 config->iConfiguration, 
                                                 buff,
                                                 sizeof(buff));
        if ((ret>0) && (ret< sizeof(buff)))
        {
            buff[ret]= '\0';
            printf("Active configuration : %s\n",buff);
        }
        libusb_free_config_descriptor(config);
    }
}

static int g_abort = 0;
/*
 * Signal handler for ctrl-C does nothing. It prevents the process from 
 * terminating so that io_getevents() can be interrupted and return
 */
static void intHandler(int i) 
{
    g_abort = 1;
}
/**
 * Perform a loopback test between the first OUT endpoint and first IN endpoints
 * in the device's active configuration
 * @return 0 : success <0 on failure
 */
static int loopback(libusb_device_handle* dev_handle, 
                    const struct cmdline_args *args)
{
    int err = 0;
    libusb_device *dev =libusb_get_device(dev_handle);
    
    //get the active USB config descriptor
    struct libusb_config_descriptor *config = NULL;
    err = libusb_get_active_config_descriptor (dev, &config);
    if (err < 0)
    {
        libusb_free_config_descriptor(config);
        printf("ERROR libusb_get_active_config_descriptor\n");
        return -1;
    }
   
    //Get the interface descriptor and validate the endpoints
    const struct libusb_interface *inter;
    const struct libusb_interface_descriptor *interdesc;
	int i, ep_match;
    for(i=0, ep_match=0; i<(int)config->bNumInterfaces; i++) 
    {
		inter = &config->interface[i];
        int j;
		for(j=0; j<inter->num_altsetting; j++) 
        {
			interdesc = &inter->altsetting[j];
            int k;
            for(k=0; k<(int)interdesc->bNumEndpoints; k++) 
            {
                const struct libusb_endpoint_descriptor *epdesc;
                epdesc = &interdesc->endpoint[k];
                if (epdesc->bEndpointAddress == args->ep_in)
                {
                    ++ep_match;
                }
                if (epdesc->bEndpointAddress == args->ep_out)
                {
                    ++ep_match;
                }
            }
        }
    }
    
    libusb_free_config_descriptor(config);
    
    if (ep_match !=2) //must have a pair of endpoints
    {
        //print specs of this device
        print_str_descriptors (dev_handle);               
        libusb_device *dev =libusb_get_device(dev_handle);
        printdev(dev); 
        
        print_usage(NULL);
        return -1;
    }
    
    printf("ep_out %#02x ep_in %#02x \n", args->ep_out,args->ep_in);
   
    //Set up ctrl-C handler to terminate infinite wait in io_getevents()
    g_abort = 0;
    struct sigaction act;
    act.sa_handler = intHandler;
    sigaction(SIGINT, &act, NULL);
 
    unsigned char * buff = (unsigned char *)malloc(args->loop_len);
    if (!buff)
    {
        printf("ERROR failed to alloc %d bytes\n", args->loop_len);
        return (-1);
    }
        
    int len, len_out, len_in;
    
    //Initialize buffer to send
    srand(time(NULL));
    for (len=0; len < args->loop_len; ++len)
    {
        buff[len] = (char)rand();
    }
    
    //write this out
    err = libusb_bulk_transfer(dev_handle, args->ep_out, buff, args->loop_len,
                               &len_out, 1000);
    if (err)
    {
        printf("ERROR \"%s\" libusb_bulk_transfer(%#02x) write %d\n",  
                libusb_error_name(err), args->ep_out, len_out);
        goto done;;
    }
    if (len_out != args->loop_len)
    {
        printf("ERROR wrote %d of %d bytes\n", len_out, args->loop_len);
        goto done;
    }
    //Initialize and calculate the CRC of the data sent
    uint32_t crc32_out = xcrc32 (buff, args->loop_len,0);   
    printf("Wrote %d bytes xcrc32 %#x\n", len_out, crc32_out);
     
    printf("Waiting to read %d bytes, press ctrl-C to abort\n", len_out);
    memset(buff, 0, args->loop_len);
    len_in = 0;
    while (len_in < len_out)
    {
        int read;
        err = libusb_bulk_transfer(dev_handle, args->ep_in, buff+len_in, 
                                   args->loop_len - len_in,
                                   &read, 1000);
        if (err && (err != LIBUSB_ERROR_TIMEOUT))
        {
            printf("ERROR %d libusb_bulk_transfer(%#02x)\n", err, args->ep_in);
            goto done;
        }
        
        if (read)
        {
            len_in += read;
            printf("Read %d bytes remain %d\n", read, (len_out-len_in));
        }
        
        if (g_abort)
        {
            break;
        }
    }   
    
    if (len_in != args->loop_len)
    {
        printf("ERROR read %d of %d bytes\n", len_in, args->loop_len);
    }
    
    uint32_t crc32_in = xcrc32 (buff, len_in,0);   
    printf("Read %d bytes xcrc32 %#x\n", len_in, crc32_in);
    
    if (crc32_in != crc32_out)
    {
        printf("CRC error\n");
    }
done:    
    free (buff);

    return err;
}



