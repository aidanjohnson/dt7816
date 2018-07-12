# Bat Array: MCC DT7816

***—Work in Progress (WIP)—***

This is a custom application for DT7816 autonomous asynchronous I/O sampling that configures the board's analog inputs. The sampled data is read [asynchronously](https://msdn.microsoft.com/en-us/library/windows/desktop/aa365683(v=vs.85).aspx) from the input stream and written to a AIFF file. The following documentation provides a step-by-step guide to using this software.

See the [manufacturer guide](https://www.mccdaq.com/PDFs/Manuals/DT7816_WebHelp/DT7816_Getting_Started.htm) for the [DT7816](https://www.mccdaq.com/Products/ARM-DAQ/DT7816) if you want a more thorough guide necessary for manual setup and building. This repository is intended to make the building process easier and faster by automating it through a script. Download the tarball in [`INSTALL`](/INSTALL) to build all the code for this DAQ, which is installed to the directory: `/opt/ti-sdk-am335x-evm-07.00.00.00/`. Note that, if built from scratch, the directory would not contain `INSTALL`, [`UM7816.pdf`](/DT7816/UM7816.pdf), and [`DT7816-Programming.pdf`](/DT7816-Programming.pdf); these have been only included for convenience. Follow the instructions below to build it all from scratch.

## Installation Instructions

1. Download the three following files. Save each in your OS `~/Downloads` directory.
   * http://software-dl.ti.com/sitara_linux/esd/AM335xSDK/07_00_00_00/exports/ti-sdk-am335x-evm-07.00.00.00-Linux-x86-Install.bin
   * ftp://ftp.mccdaq.com/downloads/DTSoftware/DT78XX_ARM/DT78XX-setup-3.2.bz2.run
   * https://cfhcable.dl.sourceforge.net/project/aifftools/libaiff/LibAiff%205.0/libaiff-5.0-release.tar.gz

2. Download the compressed directories in `INSTALL`. Uncompress each [`INSTALL.tar.gz`](/INSTALL/INSTALL.tar.gz), which is formed with the script `INSTALL_tar.sh`, using the command:
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

5. Download and install NetBeans 8.2. (Recommended instead of TI's Code Composer Studio because the manufacturer's guide assumes NetBeans 8.1.) If for some reason you decide not use the Python script `build_examples.py` to create a project for each of the example applications, follow these instructions:
   * https://www.mccdaq.com/PDFs/Manuals/DT7816_WebHelp/Creating_Projects_in_Netbeans.htm
   * https://www.mccdaq.com/PDFs/Manuals/DT7816_WebHelp/Configuring_the_Resources_for_Netbeans_Code_Assistance.htm

6. Complete the last step of https://www.mccdaq.com/PDFs/Manuals/DT7816_WebHelp/Build_the_Drivers_.htm. This requires the following set of instructions, which pertain to establishing a connection between the DT7816 DAQ module and a Unix-based, specifically Linux, PC.

## Connection Instructions

There are two ways for a user to connect the host computer (PC) to the client computer (the DT7816). The first, which is documented at length in the Getting Started guide from the manufacturer, relies on using the `web-server` example application. In this method the client and host are connected to the same network and the terminal of the client can be accessed from the host via an serial console application like [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html) or even in the Unix shell (e.g., the GNOME Terminal). However, this is cumbersome in the field and in general, especially when transfering or copying files (e.g., custom programs). 

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

11. Now we will set up the NFS client. In the serial console terminal, once booted up and logged in on the DT7816 using a baud rate of 115200 and at the USB-Serial port `/dev/ttyUSB0`, install `apt-get install nfs-common` and make a directory with `mkdir /usr/local/dt7816-nfs`. Then mount the NFS server with `mount -t nfs 10.0.0.10:/export/DT7816-NFS /usr/local/dt7816-nfs`.

12. Edit the file `sudo nano /etc/fstab` to have the lines
    ```
    # nfs mount development PC mapped directory 
    10.0.0.10:/export/DT7816-NFS /usr/local/dt7816-nfs nfs rw,hard,intr 0 0
    ```
    To check all the directories on the server are accesible by the client, run `ls -l /usr/local/dt7816-nfs`

## Operation Instructions

1. Assuming the above installation and connection instructions were performed successfully, connect a Linux PC to the DT7816 board via the USB-Serial cable. On the serial end, connect the female header to the J10 pins (the centre row of the parallel row pin trio). Have the black lead attach to pin 1 (the pin closest to the J10 label and microSD card reader. Pair the PC and board with a male-to-male Ethernet cable, as described in the above instructions. Plug the DC power cable to the board so it boots up.

2. In Terminal on the PC, run the command `screen /dev/ttyUSB0 115200` to connect to the serial console of the DAQ. The terminal console will initially be blank; be patient and after a few moments press the 'return' carriage key. Now some boot messages should be displayed. When it asks for a username, type `root` and type `root` for the password. You now are accessing the serial console.

3. To check that the NFS server is functioning, type the command `ls -l /usr/local/dt7816-nfs`. You should then see a list of all the files in the `/opt/ti-sdk-am335x-evm-07.00.00.00/` directory on the PC. 

4. Now that we are confident that the preliminary steps are functioning correctly, we can then access the programs or applications that we've written in C. For our purposes we will be running the `bat-array` program such that the board will autonomously sample and record the soundscape. ***—more to be added later on mounting a local storage device (e.g., HDD for lower cost per GB or SSD for lower Watt consumption) at a predefined file structure location—***

5. Inconveniently, the board's local time clock needs to be set and synchronised to a common time so the `aiff` files can be properly time-stamped in their file name. We can synchronise the board's clock to a local clock that *must* be used for both boards—I would use my digital wristwatch or computer's time when the time was exactly zero seconds (HH:MM:00). Specifically run the commands (following [ISO 8601](https://en.wikipedia.org/wiki/ISO_8601) standards):
   * `date --set YYYY-MM-DD` where YYYY is the year, MM is the month and DD is the day.
   * `date --set HH:mm:ss` where HH is hours in 24-hour time, mm is minutes and ss is seconds.
   * ` hwclock --systohc` to set current time to the hardware clock in order for the time to be recoverable after reboots.
   ***—more on a common external clock that is described in the [User Manual](/UM7816.pdf) on pp. 35-39 and p. 48 as it is implemented—***
6. Since we want to run the `bat-array` program without the PC connected to the board, we will need to copy the program over to local, on-board memory. To do so, run the command `cp -r /usr/local/dt7816-nfs/example-applications/dt78xx-examples/bat-array/ /usr/local/`. Then change directories to that location with `cd /usr/local/bat-array`.

7. Now we can run the program. To do so, run the command `./release/bat-array <identifier> [options]` on the serial console (via Terminal) where `<identifier>` is a identifier of your choosing for the board's recordings (e.g., N for North), and `[options]` is the set of optional command line parameters (note that the board will run with the default values predefined in the source C code). The "help" display describes the options available. It is reproduced below for convenience.
   ```text
   Samples AINx (where AINx is a combination of AIN0/1/2/3/4/5/6/7 and at most 8
   simultaneous channels) and writes data to timestamped file in AIFF format files 
   saved to a predefined storage path. All options below are not required, only 
   the file identifier is required. The files are saved to 
   <path>/<prefix>_<YYYY-DD-MMTHHmmssuuuuuuZ>.aiff

   Usage        : ./release/bat-array <identifier prefix> [options]

   Required     : a file or location identifier prefix, such as NORTH or 1.

   Options
   -i|--inputs  : 8-bit binary string to enable and disable analog input channels
                  A channel is on if its bit is 1 and off if its bit is 0. Bit 
                  positions 0/1/2/3/4/5/6/7 correspond to channels 
                  AIN0/1/2/3/4/5/6/7. For example, 10101001 enables AIN0/2/4/7 
                  and disables AIN1/3/5/6. By default, only channel AIN0 is 
                  enabled (i.e., 10000000).  
   -s|--samples : number of samples per channel, defaults 65536. Note that you are
                  limited to 2^(16-bits) = 65536 samples >= (samples per channel)
                  (channels per buffer)(buffers)
   -c|--clk     : sampling rate in Hz, defaults 400000 Hz.
   -b|--buffers : number of buffers per file written, defaults 1.
   -d|--dur     : fixed duration of sampling period in days at night as
                  determined by sunset and sunrise times, defaults 7 days.
   -r|--run     : runs this application as a daemon process, defaults off.
   -t|--trig    : when the voltage on either AIN crosses 0.0 V rising (threshold)
                  acquisition is triggered. By default, acquisition is triggered
                  when you start the analog input operation using the ioct.
   ```
   If all user input parameters are okay, a console message will appear waiting for the user to start data recording. At the console message, type 's' and then press 'return' key. The program will now automatically run saving the recordings to the local storage directory as `.aiff` files. The console will print information about the written files as it records and saves to the storage directory predefined in the C code `main.c`.

   **Sunrise and Sunset Times**

   Restraining from making a *Fiddler on the Roof* reference, ~~the program is fed a `.txt` file coining the sunset times interleaved with the sunrise times of a location determined by its latitude and longitude coordinates. The [US Naval Observatory](http://aa.usno.navy.mil/data/docs/RS_OneDay.php) has a database of these times accesible using a [JSON API](http://aa.usno.navy.mil/data/docs/api.php). The Jupyter Notebook [`navy_json_sunsight_sunclipse.ipynb`](/navy_json_sunsight_sunclipse.ipynb) contains a script that writes the sunset and sunrise times (indicating the time of dusk and dawn) for given range of days to the file [`sunup_sundown.txt`](/sunup_sundown.txt) in ISO 8601 format. These dates and times are read by the `bat-array` program so that the data sampling and recording only occurs when the bats are out foraging (i.e., at night).~~ the `bat-array` program is given a latitude and longitude coordinate pair for the location of the recording site in order to calculate the sunset and sunrise times for each day in the set duration in days. The sampling regime begins immediately after starting through the command line. 

   **Debug LEDs**
   
   The LEDs (LEDx) on the board below the debug pins will light up to indicate whether the channels are being read and recorded (written).
   * 8 LEDs in total.
   * LEDx ON (1) := channel (AINx) is currently reading/writing (R/W) the input.

   **Indicator LED Locations**

   Viewing the DT7816 such that the debug pin row is above the user LEDs, i.e. the DC in, USB, Ethernet, etc. are at the bottom), the LEDs are located and orientated like so:

   |  **PIN1** |  **PIN2** |  **PIN3** |  **PIN4** |  **PIN5** |  **PIN6** |  **PIN7** |  **PIN8** |  **PIN9** | **PIN10** |
   |-----------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|-----------|
   |           |  **LED7** |  **LED6** |  **LED5** |  **LED4** |  **LED3** |  **LED2** |  **LED1** |  **LED0** |           |

   where each LED is defined by the state (R/W or not R/W) of its respective analog input:
   * LED0 := AIN0
   * LED1 := AIN1
   * LED2 := AIN2
   * LED3 := AIN3
   * LED4 := AIN4
   * LED5 := AIN5
   * LED6 := AIN6
   * LED7 := AIN7

   The analog input channels have the following bit coding returned by `IOCTL_CHAN_MASK_GET`, which enables/disables the LEDs debug indicators (where `0x` indicates a hexadecimal number):
   * AIN0 = 0x01
   * AIN1 = 0x02
   * AIN2 = 0x04
   * AIN3 = 0x08
   * AIN4 = 0x10
   * AIN5 = 0x20
   * AIN6 = 0x40
   * AIN7 = 0x80

   **Analog Inputs Locations**

   For the input header pins (J16), i.e. the right header at the top of the board when viewed from the same perspective as before, is grouped like this where the topmost row is the topmost row of the header:

   |  **2** |  **4** |  **6** |  **8** | **10** | **12** | **14** | **16** | **18** | **20** |
   |--------|--------|--------|--------|--------|--------|--------|--------|--------|--------|
   |  **1** |  **3** |  **5** |  **7** |  **9** | **11** | **13** | **15** | **17** | **19** |

   The analog inputs (AINs, or AINx) are defined as:
   * PIN5 := AIN0
   * PIN7 := AIN1
   * PIN9 := AIN2
   * PIN11 := AIN3
   * PIN13 := AIN4
   * PIN15 := AIN5
   * PIN17 := AIN6
   * PIN19 := AIN7

   and their corresponding analog grounds (AGRDs, AGRDx) are defined as:
   * PIN6 := AGRD0
   * PIN8 := AGRD1
   * PIN10 := AGRD2
   * PIN12 := AGRD3
   * PIN14 := AGRD4
   * PIN16 := AGRD5
   * PIN18 := AGRD6
   * PIN20 := AGRD7

## Troubleshooting

1. If when the `dt7816-calibration` example is being built you get an error about not finding `libusb.h` in `/usr/local/include/libusb-1.0`, create a link of `/usr/include/libusb-1.0/libusb.h` in that directory. That is:
   ```
   sudo mkdir /usr/local/include/libusb-1.0
   sudo ln -s /usr/include/libusb-1.0/libusb.h /usr/local/include/libusb-1.0
   ```
2. Called by `build_dev.sh`, `build_examples.py` is a Python script that builds each of the [example applications](/example-applications/dt78xx-examples/) according to the manufacturer's instructions. See the installation directory for information on what each of these do. The script also creates a NetBeans project for each. It builds:
   * examples: `aio-in`, `aio-out`, `aout-single`, `clk-gen`, `digio`, `dt7816-calibration`, `event-counter`, `fir-filter`, `function-gen`, `sig-analyzer`, `usb-loopback`, `web-server`
   * [`bat-array`](/example-applications/dt78xx-examples/bat-array) ([**WIP**](https://github.com/aidanjohnson/dt7816/projects/1#card-10768858): this is the custom built ADC recording program for the DAQ; samples recorded in the `.aiff` format using with a standardised file naming convention.)

3. For an unknown reason, the example C-language code applications contains an include header for a differently named directories. To remedy this, create a link like so:
   ```
   sudo ln -s <target directory or file> <destination directory>
   ```
   You may have to reparse the project after the linkages, and there could be more broken include header links besides these above. For example, you may need to link from the header files in `linux-devkit/sysroots/cortexa8hf-vfp-neon-3.8-oe-linux-gnueabi/usr/include` and `board-support/u-boot-2013.10-ti2013.12.01/include` (targets) to `board-support/linux-3.12.10-ti2013.12.01/include/linux` (desitination). After enquiring further, the `build_dev.sh` script now tries to mend this issue by creating these links.

4. In these instructions the superuser `sudo` command program for elevating security privelages has been included for redundancy. Moreover, these instructions will *only* work properly on Linux. These files were developed and tested on a machine running [Ubuntu 18.04 LTS](http://releases.ubuntu.com/18.04/).

5. For connecting to the DAQ, consult these for assistance:
   * https://askubuntu.com/questions/22835/how-to-network-two-ubuntu-computers-using-ethernet-without-a-router
   * https://www.garron.me/en/linux/add-secondary-ip-linux.html
   * https://access.redhat.com/sites/default/files/attachments/rh_ip_command_cheatsheet_1214_jcs_print.pdf

6. Reset the board by pressing the reset button (a soft reset) or by unpluging DC power (a hard reset). Additionally, it is advisable to let the board warm-up for at least 10 minutes; there seems to be better performance in operation and sampling after warming up.

7. Not entirely sure why this fixes the 'cannot resolve syscall' warning in NetBeans, but for each NetBeans project, right click to access the 'Properties' menu. Then under 'C Compiler'->'C Standard' set to C11, and under 'C++ compiler'->'C++ Standard' set to C++11. See this Stack Overflow [post](https://stackoverflow.com/questions/30686264/erroneous-unable-to-resolve-identifier-in-netbeans/35025731) for more information and discussion.

8. To synchronise the board's clock to official US (NIST) time, after the Operation Instructions, follow the steps at this [wiki page](https://wiki.archlinux.org/index.php/Internet_sharing), substituting `enp4s0f1` for `net0` and `wlp3s0` for `internet0` in addition to substituting the arbitrary IP addresses of `192.168.123.0` with `10.0.0.0`, `192.168.123.100` with `10.0.0.1` and `192.168.123.201` with `10.0.0.2`. After this process shares the internet connection of the host computer to the client board, set up the NTP server and client by running the command `ntpdate time.nist.gov` on the server host and `ntpdate 10.0.0.1` on the server client (consult [this page](http://www.ubuntugeek.com/network-time-protocol-ntp-server-and-clients-setup-in-ubuntu.html) for assistance). On the client you likely will have to run these commands in the following order: `service ntp stop`, `ntpdate 10.0.0.1`, `service ntp start`. This should update the local time on the client/board. You can check that it is the case by running the command `date` on the client.

## Acknowledgements
Thank you to the [Applied Physics Laboratory](http://www.apl.washington.edu/) at the University of Washington and the [UW Institute for Neuroengineering](http://uwin.washington.edu/) for funding and support, and to the [Union Bay Natural Area](https://botanicgardens.uw.edu/center-for-urban-horticulture/visit/union-bay-natural-area/) for support. This project was funded by the UW Institute for Neuroengineering and the Washington Research Foundation Funds for Innovation in Neuroengineering and **<2nd funding source goes here: NIFTI?>**. Contact: [Wu-Jung Lee](https://leewujung.github.io/) at wjlee@apl.washington.edu and [Aidan Johnson](https://aidanjohnson.github.io/) at johnsj96@uw.edu.

This project uses the open source libraries:
* [LibAiff](http://aifftools.sourceforge.net/libaiff/) by Marco Trillo ([MIT License](https://opensource.org/licenses/mit-license.php))
* [ArduinoRingBuffer](https://github.com/wizard97/ArduinoRingBuffer) by Aaron Wisner ([MIT License](https://opensource.org/licenses/MIT))
* [DT78xx software](https://www.mccdaq.com/Products/ARM-DAQ/DT7816) by Data Translation Inc ([GPLv2](https://opensource.org/licenses/gpl-2.0.php))
* [Free C source for computing sunrise/set times](http://stjarnhimlen.se/english.html) by Paul Schlyter ([Public Domain](http://stjarnhimlen.se/snippets/snippets.(c)))
