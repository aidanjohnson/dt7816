## Installation Instructions

1. Download the four following files. Save each in your OS `~/Downloads` directory.
   * http://software-dl.ti.com/sitara_linux/esd/AM335xSDK/07_00_00_00/exports/ti-sdk-am335x-evm-07.00.00.00-Linux-x86-Install.bin
   * ftp://ftp.mccdaq.com/downloads/DTSoftware/DT78XX_ARM/DT78XX-setup-3.2.bz2.run
   * https://cfhcable.dl.sourceforge.net/project/aifftools/libaiff/LibAiff%205.0/libaiff-5.0-release.tar.gz
   * ftp://ftp.fftw.org/pub/fftw/fftw-3.3.8.tar.gz

2. Download the compressed directories in `INSTALL`. Uncompress [`INSTALL.tar.gz`](https://github.com/aidanjohnson/dt7816/tree/master/INSTALL/INSTALL.tar.gz), which is formed with the script `INSTALL_tar.sh`, using the command:
   ```
   tar -xzvf INSTALL.tar.gz
   ```

   Save these (a shell script, a Python executable program, the `recorder` program files, and a directory containing the NetBeans IDE project templates) in `~/Downloads`.
   * `build_dev.sh`
   * `build_examples.py`
   * `main.c`, `recorder_helpers.c`, `Makefile`, etc.
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

6. Complete the last step of https://www.mccdaq.com/PDFs/Manuals/DT7816_WebHelp/Build_the_Drivers_.htm. This step is optional.
