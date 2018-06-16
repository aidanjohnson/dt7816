# MCC DT7816

See the [manufacturer guide](https://www.mccdaq.com/PDFs/Manuals/DT7816_WebHelp/DT7816_Getting_Started.htm) for the [DT7816](https://www.mccdaq.com/Products/ARM-DAQ/DT7816) if you want a more thorough guide necessary for manual setup and building. This repository is intended to make the building process easier and faster by automating it through a script. Download/clone this repository for already built code for this DAQ, saving it in the directory: `/opt/ti-sdk-am335x-evm-07.00.00.00/`. Note that, if built from scratch, the directory would not contain `INSTALL`, `UM7816.pdf`, and `libuldaq-1.0.0`; these have been only included for convenience. Otherwise, and preferably, follow the instructions below to build it all from scratch.

## Instructions

1. Download the three following files. Save each in your OS `~/Downloads` directory.
  * http://software-dl.ti.com/sitara_linux/esd/AM335xSDK/07_00_00_00/exports/ti-sdk-am335x-evm-07.00.00.00-Linux-x86-Install.bin
  * ftp://ftp.mccdaq.com/downloads/DTSoftware/DT78XX_ARM/DT78XX-setup-3.2.bz2.run
  * http://www.fftw.org/fftw-3.3.4.tar.gz

2. Download the three directories in [`INSTALL`](/INSTALL). Save these (a shell script, a Python executable program, and a directory containing the NetBeans IDE project templates) in `~/Downloads`.
  * `build_dev.sh`
  * `build_examples.py`
  * `nbproject`

3. Run in terminal the command:
   ```
   chmod +x build_dev.sh
   sudo ./build_dev.sh
   ```
   The files required for the System on Module (SoM), TI Sitara AM3352, will then be installed automatically. The example programs provided will be built for NetBeans IDE.

4. Follow steps on your screen and terminal; watch for any errors (especially fatal).

5. Download and install Oracle's NetBeans 8.2. (Recommended instead of TI's Code Composer Studio because the manufacturer's guide assumes NetBeans 8.1.) Create a project for the example applications by following these instructions:
  * https://www.mccdaq.com/PDFs/Manuals/DT7816_WebHelp/Creating_Projects_in_Netbeans.htm
  * https://www.mccdaq.com/PDFs/Manuals/DT7816_WebHelp/Configuring_the_Resources_for_Netbeans_Code_Assistance.htm

6. Complete the last step of: https://www.mccdaq.com/PDFs/Manuals/DT7816_WebHelp/Build_the_Drivers_.htm

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
  * `bat-array` (**WIP**: this is the custom built ADC recording program for the DAQ)

3. For an unknown reason, the example C-language code conapplicationstains an header include for a differently named directory. To remedy this, create a link like so:
   ```
   sudo ln -s <target directory or file> <destination directory>
   ```
   You may have to reparse the project after the linkages, and there could be more broken include header links besides these above.

4. In these instructions the superuser `sudo` command program for elevating security privelages has been included for redundancy. Moreover, these instructions will *only* work properly on Linux. These files were developed and tested on a machine running Ubuntu 18.04 LTS.
