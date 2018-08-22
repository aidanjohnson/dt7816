## Running C Programs on the DT7816

This document intends to simplify the connecting and operating instructions for the DT7816. These instructions are fairly complicated and tedious. With this in consideration, the following simplified steps should guide a novice and developer users alike with connecting to the DT7816 client to a Linux host computer via Serial-to-USB and Ethernet.

Additionally, these are not meant to be thorough and rigorous. Rather they are meant to be concise and most importantly assume that the setup process described in depth on the [wiki page](https://github.com/aidanjohnson/dt7816/wiki/Connecting:-Setup) has been successful. Lastly, these instructions will briefly explain how to run C programs and applications compiled and built on a host computer in the NetBeans IDE. 

### Pre-Operation Instructions

1. Connect the DT7816 (henceforth referred to as the board) client to the host computer. Do this by plugging in the:

   1.1. Serial-to-USB cable in the J10 pins (the center most column in the cluster of three columns adjacent to the DC voltage input;

   1.2. Ethernet cable between the host and client.

2. Turn on the board by powering the board with the 5 Vdc power supply.

3. Open the command-line terminal on the host computer and run the command `screen /dev/ttyUSB0 115200` with elevated privileges. This will open a serial terminal for the board.

4. Wait for the board to finish the boot-up process. If the process takes longer than 5 min and/or is hung-up on initialising NFS or the Apache web server (you’ll get a message about connecting timed out), then the setup process failed. When directed to, enter the username `root` and password `root`. 

5. Check that the setup process was successful again by pinging:

   5.1. The host from the client with `ping 10.0.0.1`.

   5.2. The client from the host with `ping 10.0.0.2`.

   These will print a success message that all sent packets were received.

6. If the above step succeeds, then we need to check that the NFS server has successfully been established. To do this, on the client, run the command `ls -l /nfs/dt7816` to confirm that all the files in the host development directory (`/opt/ti-sdk-am335x-evm-07.00.00.00`) are listed.

7. Now that we know that the local network has be created and the files on the host can be copied to the client, synchronise the client clock with the NIST time server. The board will access this NTP server using the Internet connection shared by host. Do this by running the commands:

   7.1. `service ntp stop`

   7.2. `ntpdate 10.0.0.1`

   7.3. `service ntp start`

   You may have to run `ntpdate time.nist.gov` in lieu off `ntpdate 10.0.0.1` if the host is not properly configured as an NTP server. This alternative will only work if the host Internet connection is shared (you can check this with ping).

8. If a failure message is returned then likely the NTP server on the client is not running. Start it with `/etc/init.d/ntp start`. Confirm that the time has been updated and synchronised by running the command `date`. The current date and time will be returned.

9. Now that all the configuration steps have been completed, the next steps will outline how to copy and run a desired program. Do this by:

   9.1. Moving to the NFS server directory with the development files with `cd /nfs/dt7816`.

   9.2. To copy: Change to the directory with the developed programs with `cd /example-applications/dt78xx-examples` and copy the entire desired program directory to a desired location on the client (e.g., `recorder` with `cp recorder /`).

10. To run: Change to the desired directory of the program (e.g., `/example-applications/dt78xx-examples/recorder` with `cd /example-applications/dt78xx-examples/recorder`).

    10.1. On the host computer make any last changes to the Macros of your C-program and then build and compile, as usual (e.g., for `recorder` you should change the file path for writing the AIFF files to a desired and existing directory on the client).

    10.2. Run the desired program by executing the C-object file (e.g., `recorder` with `./release/recorder`).

    10.3. Include all the required parameters listed by the `--help` flag. For example, with `recorder` you at least must run the command `./release/recorder <ID>`, where `<ID>` is some identifier.

    10.4. The program should then run as programmed.
