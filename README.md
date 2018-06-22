# Bat Array: MCC DT7816

See the [manufacturer guide](https://www.mccdaq.com/PDFs/Manuals/DT7816_WebHelp/DT7816_Getting_Started.htm) for the [DT7816](https://www.mccdaq.com/Products/ARM-DAQ/DT7816) if you want a more thorough guide necessary for manual setup and building. This repository is intended to make the building process easier and faster by automating it through a script. Download the tarball in `INSTALL` to build all the code for this DAQ, which is installed to the directory: `/opt/ti-sdk-am335x-evm-07.00.00.00/`. Note that, if built from scratch, the directory would not contain `INSTALL`, [`UM7816.pdf`](/UM7816.pdf), [`DT7816-Programming.pdf`](/DT7816-Programming.pdf) and `libuldaq-1.0.0`; these have been only included for convenience. Follow the instructions below to build it all from scratch.

## Installation Instructions

1. Download the four following files. Save each in your OS `~/Downloads` directory.
   * http://software-dl.ti.com/sitara_linux/esd/AM335xSDK/07_00_00_00/exports/ti-sdk-am335x-evm-07.00.00.00-Linux-x86-Install.bin
   * ftp://ftp.mccdaq.com/downloads/DTSoftware/DT78XX_ARM/DT78XX-setup-3.2.bz2.run
   * http://www.fftw.org/fftw-3.3.4.tar.gz
   * ftp://xmlsoft.org/libxml2/libxml2-2.9.8.tar.gz

2. Download the compressed directories in [`INSTALL`](/INSTALL). Uncompress `INSTALL.tar.gz` with the command:
   ```
   tar -xzvf INSTALL.tar.gz
   ```

   Save these (a shell script, a Python executable program, the `bat-array` program files, and a directory containing the NetBeans IDE project templates) in `~/Downloads`.
   * `build_dev.sh`
   * `build_examples.py`
   * `main.c`, `Makefile`, `README.md`
   * `nbproject`

3. Run in terminal the command:
   ```
   chmod +x build_dev.sh
   sudo ./build_dev.sh
   ```
   The files required for the System on Module (SoM), [TI Sitara AM3352](http://www.ti.com/product/AM3352), will then be installed automatically. The example programs provided will be built for [Oracle's NetBeans 8.2 IDE](https://netbeans.org/downloads/).

4. Follow steps on your screen and terminal; watch for any errors (especially fatal) and refer to the Troubleshooting section below for assistance.

5. Download and install NetBeans 8.2. (Recommended instead of TI's Code Composer Studio because the manufacturer's guide assumes NetBeans 8.1.) Create a project for the example applications by following these instructions:
   * https://www.mccdaq.com/PDFs/Manuals/DT7816_WebHelp/Creating_Projects_in_Netbeans.htm
   * https://www.mccdaq.com/PDFs/Manuals/DT7816_WebHelp/Configuring_the_Resources_for_Netbeans_Code_Assistance.htm

6. Complete the last step of https://www.mccdaq.com/PDFs/Manuals/DT7816_WebHelp/Build_the_Drivers_.htm. This requires the following set of instructions, which pertain to establishing a connection between the DT7816 DAQ module and a Unix-based, specifically Linux, PC.

## Connection Instructions

There are two ways for a user to connect the host computer (PC) to the client computer (the DT7816). The first, which is documented at length in the Getting Started guide from the manufacturer, relies on using the `web-server` example application. In this method the client and host are connected to the same network and the terminal of the client can be accessed from the host via an serial console application like [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html) or even in the Unix terminal. However, this is cumbersome in the field and in general, especially when transfering or copying files (e.g., custom programs). 

The second and alternative method is to locally network the client and host. This is achieved by using the host as a NFS server and the client a NFS client. The Serial-USB cable allows the host to connect to the board so the user can access the terminal interface necessary to perform any and all operations on the DT7816 module, again using a serial console terminal. The conduit for the transfer of data is an Ethernet cable that creates the local network (LAN). (Note: older PCs may require a crossover Ethernet cable, although most modern do not.) This section will provide a step-by-step guide to setting up the LAN and NFS mounting.
  
1. On the host computer, run the `ifconfig` command to find the MAC address. Likely, you will have to instead use the `ip a l` command if you are using a newer Linux version. Under `wl*` (where * are wild-card characters) copy the MAC address following `link/ether` (it looks like \*\*:\*\*:\*\*:\*\*:\*\*:\*\*). Before closing, make sure the automatically connect box is checked. Alternatively this can be done as a command line `sudo ip ad add 10.0.0.10/24 dev enp4sof1`. (Note: `enp4sof1` can differ; use the Ethernet port name from running `ifconfig`.)

2. Open up the host computer networking setting and create a new wired connection. Enter a name and the MAC address. Under the IPv4 tab, select manual. Then add the IP address and netmask: 10.0.0.1 and 255.255.255.0. Leave the gateway empty/blank.

3. Differently, for the client computer (the DAQ board) we will set similar settings in its terminal through a serial console (see https://learn.adafruit.com/welcome-to-circuitpython/advanced-serial-console-on-mac-and-linux for instructions how; alternatively, via PuTTY). In short, you can connect to the client terminal via the serial console by running the command `screen /dev/ttyUSB0 115200`. You may have to run `sudo apt-get install screen` first.

   Log into the system with `root` as both the username and password. After running the command `ip ad`, we see that the Ethernet port is referred to as `eth0`.  Run the command `ip ad add 10.0.0.20/24 dev eth0 valid_lft forever preferred_lft forever`.

4. Making sure the server and client are connected via Ethernet, test that the connection is functioning by pinging each other. Do this on the server's terminal with `ping 10.0.0.2` and on the client's terminal with `ping 10.0.0.1`. These ping tests will both be successful (no losses) if all is correct.

5. Now we need to set up the NFS server. First, make sure NFS is installed on the Linux host computer by running `sudo apt-get install nfs-kernel-server`. Then create a directory to house the server contents that will be accessed when mounted. Do this with `sudo mkdir -p /export/DT7816-NFS`. 

   Next, give permissions to this directory with `sudo chmod 777 /export/DT7816-NFS`. Lastly, mount the directory with `mount --bind /opt/ti-sdk-am335x-evm-07.00.00.00/ /export/DT7816-NFS`

6. Now we will continue to set up the NFS server. Edit the file `sudo nano /etc/default/nfs-kernel-server` to have the line `NEED_SVCGSSD="no"`. Then edit the file `sudo nano /etc/idmapd.conf` to have the lines:
   ```
   Nobody-User = nobody
   Nobody-Group = nogroup
   ```
  
7. Restart the NFS server with `/etc/init.d/nfs-kernel-server restart`. 

8. Edit the file `sudo nano /etc/hosts` to have the line `rcpbind mountd nfsd statd lockd rquotad : 10.0.0.0/255.255.255.0 127.0.0.1`. Repeat step 7.

9. Edit the file `sudo nano /etc/fstab` to have the lines 
   ```
   # DT78xx examples mapped for NFS
   /opt/ti-sdk-am335x-evm-07.00.00.00/ /export/DT7816-NFS none bind 0 0
   ```
   so the NFS server starts automatically on boot-up. Check that the NFS has the folder we want with `showmount -e`.

10. Then, to ensure all is set up correctly, run `sudo nano /etc/network/interfaces` and add the lines:
    ```
    auto eth0:1
    iface eth0:1 inet static
    address 10.0.0.20
    gateway 0.0.0.0
    netmask 255.255.255.0
     ```
    and write that to disk.

11. Now we will set up the NFS client. In the serial console terminal, once booted up and logged in on the DT7816 using a baud rate of 115200 and at the USB-serial port `/dev/ttyUSB0`, install `apt-get install nfs-common` and make a directory with `mkdir /usr/local/dt7816-nfs`. Then mount the NFS server with `mount -t nfs 10.0.0.10:/export/DT7816-NFS /usr/local/dt7816-nfs`.

12. Edit the file `sudo nano /etc/fstab` to have the lines
    ```
    # nfs mount development PC mapped directory 
    10.0.0.10:/export/DT7816-NFS /usr/local/dt7816-nfs nfs rw,hard,intr 0 0
    ```
    To check all the directories on the server are accesible by the client, run `ls -l /usr/local/dt7816-nfs`

## Troubleshooting

1. If when the `dt7816-calibration` example is being built you get an error about not finding `libusb.h` in `/usr/local/include/libusb-1.0`, create a link of `/usr/include/libusb-1.0/libusb.h` in that directory. That is:
   ```
   sudo mkdir /usr/local/include/libusb-1.0
   sudo ln -s /usr/include/libusb-1.0/libusb.h /usr/local/include/libusb-1.0
   ```
2. `build_examples.py` is a Python script that builds each of the [example applications](/example-applications/dt78xx-examples/) according to the manufacturer's instructions. See the installation directory for information on what each of these do. The script also creates a NetBeans project for each. It builds:
   * `aio-in`
   * `aio-out`
   * `aout-single`
   * `clk-gen`
   * `digio`
   * `dt7816-calibration`
   * `event-counter`
   * `fir-filter`
   * `function-gen`
   * `sig-analyzer`
   * `usb-loopback`
   * `web-server`
   * `bat-array` ([**WIP**](https://github.com/aidanjohnson/dt7816/projects/1#card-10768858): this is the custom built ADC recording program for the DAQ; samples recorded in the `.wav` format using [TinyWav](https://github.com/mhroth/tinywav) with a standardised file naming convention.)

3. For an unknown reason, the example C-language code applications contains an include header for a differently named directories. To remedy this, create a link like so:
   ```
   sudo ln -s <target directory or file> <destination directory>
   ```
   You may have to reparse the project after the linkages, and there could be more broken include header links besides these above. For example, you may need to link from the header files in `linux-devkit/sysroots/cortexa8hf-vfp-neon-3.8-oe-linux-gnueabi/usr/include` and `board-support/u-boot-2013.10-ti2013.12.01/include` (targets) to `board-support/linux-3.12.10-ti2013.12.01/include/linux` (desitination). The `build_dev.sh` script tries to mend this issue.

4. In these instructions the superuser `sudo` command program for elevating security privelages has been included for redundancy. Moreover, these instructions will *only* work properly on Linux. These files were developed and tested on a machine running [Ubuntu 18.04 LTS](http://releases.ubuntu.com/18.04/).

5. Consult the following docs for help with `libxml`:
   * http://xmlsoft.org/html/libxml-lib.html
   * http://xmlsoft.org/examples/index.html

6. For connecting to the DAQ, consult these for assistance:
   * https://askubuntu.com/questions/22835/how-to-network-two-ubuntu-computers-using-ethernet-without-a-router
   * https://www.garron.me/en/linux/add-secondary-ip-linux.html
   * https://access.redhat.com/sites/default/files/attachments/rh_ip_command_cheatsheet_1214_jcs_print.pdf

7. See https://msdn.microsoft.com/en-us/library/windows/desktop/aa365683(v=vs.85).aspx for an explanation of synchronous and asynchronous input/output (I/O) synchronisation.

## Acknowledgements
Thank you to the [Applied Physics Laboratory](http://www.apl.washington.edu/) at the University of Washington, the [UW Institute for Neuroengineering](http://uwin.washington.edu/), and the [Union Bay Natural Area](https://botanicgardens.uw.edu/center-for-urban-horticulture/visit/union-bay-natural-area/) for funding and support. Contact: [Wu-Jung Lee](https://leewujung.github.io/) at wjlee@apl.washington.edu and [Aidan Johnson](https://aidanjohnson.github.io/) at johnsj96@uw.edu.
