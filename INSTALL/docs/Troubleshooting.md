## Notes

1. If when the `dt7816-calibration` example is being built you get an error about not finding `libusb.h` in `/usr/local/include/libusb-1.0`, create a link of `/usr/include/libusb-1.0/libusb.h` in that directory. That is:
   ```
   sudo mkdir /usr/local/include/libusb-1.0
   sudo ln -s /usr/include/libusb-1.0/libusb.h /usr/local/include/libusb-1.0
   ```
2. Called by `build_dev.sh`, `build_examples.py` is a Python script that builds each of the [example applications](https://github.com/aidanjohnson/dt7816/tree/master/example-applications/dt78xx-examples/) according to the manufacturer's instructions. See the installation directory for information on what each of these do. The script also creates a NetBeans project for each. It builds:
   * examples: `aio-in`, `aio-out`, `aout-single`, `clk-gen`, `digio`, `dt7816-calibration`, `event-counter`, `fir-filter`, `function-gen`, `sig-analyzer`, `usb-loopback`, `web-server`
   * [`recorder`](https://github.com/aidanjohnson/dt7816/tree/master/example-applications/dt78xx-examples/recorder) ([**WIP**](https://github.com/aidanjohnson/dt7816/projects/1#card-10768858): this is the custom built ADC recording program for the DAQ; samples recorded in the `.aiff` format using with a standardised file naming convention.)

3. For an unknown reason, the example C-language code applications contains an include header for a differently named directories. To remedy this, create a link like so:
   ```
   sudo ln -s <target directory or file> <destination directory>
   ```
   You may have to reparse the project after the linkages, and there could be more broken include header links besides these above. For example, you may need to link from the header files in `linux-devkit/sysroots/cortexa8hf-vfp-neon-3.8-oe-linux-gnueabi/usr/include` and `board-support/u-boot-2013.10-ti2013.12.01/include` (targets) to `board-support/linux-3.12.10-ti2013.12.01/include/linux` (destination). After enquiring further, the `build_dev.sh` script now tries to mend this issue by creating these links.

4. In these instructions the superuser `sudo` command program for elevating security privileges has been included for redundancy. Moreover, these instructions will *only* work properly on Linux. These files were developed and tested on a machine running [Ubuntu 18.04 LTS](http://releases.ubuntu.com/18.04/). Although, after technical issues with the hardware of the laptop used (read: driver bug), the OS was switched to [Ubuntu Budgie 18.04 LTS](https://ubuntubudgie.org).

5. For connecting to the DAQ, consult these for assistance:
   * https://askubuntu.com/questions/22835/how-to-network-two-ubuntu-computers-using-ethernet-without-a-router
   * https://www.garron.me/en/linux/add-secondary-ip-linux.html
   * https://access.redhat.com/sites/default/files/attachments/rh_ip_command_cheatsheet_1214_jcs_print.pdf

6. Reset the board by pressing the reset button (a soft reset) or by unplugging DC power (a hard reset). Additionally, it is advisable to let the board warm-up for at least 10 minutes; there seems to be better performance in operation and sampling after warming up.

7. Not entirely sure why this fixes the 'cannot resolve syscall' warning in NetBeans, but for each NetBeans project, right click to access the 'Properties' menu. Then under 'C Compiler'->'C Standard' set to C11, and under 'C++ compiler'->'C++ Standard' set to C++11. See this Stack Overflow [post](https://stackoverflow.com/questions/30686264/erroneous-unable-to-resolve-identifier-in-netbeans/35025731) for more information and discussion.