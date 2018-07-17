#!/bin/sh

cd ~/Downloads
sudo chmod +x ti-sdk-am335x-evm-07.00.00.00-Linux-x86-Install.bin
sudo ./ti-sdk-am335x-evm-07.00.00.00-Linux-x86-Install.bin

sudo apt-get install libusb-1.0-0-dev
sudo apt-get install build-essential gcc make linux-headers-$(uname -r)

sudo chmod +x DT78XX-setup-3.2.bz2.run
sudo ./DT78XX-setup-3.2.bz2.run --target /opt/ti-sdk-am335x-evm-07.00.00.00/

sudo mv fftw-3.3.8.tar.gz /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications
cd /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications
tar -xzvf fftw-3.3.8.tar.gz
cd fftw-3.3.8/
sudo ./configure --with-slow-timer --host=arm-linux-gnueabi --enable-single --enable-neon CFLAGS="-march=armv7-a -marm -mthumb-interwork -mfloat-abi=hard -mfpu=neon -mtune=cortex-a8 -O4 -Wall" CC="/opt/ti-sdk-am335x-evm-07.00.00.00/linux-devkit/sysroots/i686-arago-linux/usr/bin/arm-linux-gnueabihf-gcc"
sudo make 

cd ~/Downloads
sudo cp build_examples.py /opt/ti-sdk-am335x-evm-07.00.00.00/
sudo cp -r nbproject /opt/ti-sdk-am335x-evm-07.00.00.00/
cd /opt/ti-sdk-am335x-evm-07.00.00.00/
sudo chmod +x build_examples.py
sudo ./build_examples.py

sudo make -f dt78xx.mak linux
sudo make -f dt78xx.mak dtmods_clean
sudo make -f dt78xx.mak dtmods

sudo ln -sf /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/extra-drivers/dt78xx/dt78xx_ioctl.h /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/common
sudo ln -sf /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/asm-generic /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/asm
sudo ln -sf /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/acpi/processor.h /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/asm
sudo ln -sf /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux/acpi.h /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/asm
sudo ln -sf /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux/thread_info.h /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/asm

cd /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/asm
sudo ln -sf ../../../u-boot-2013.10-ti2013.12.01/include/errno.h 
sudo ln -sf ../../../../linux-devkit/sysroots/cortexa8hf-vfp-neon-3.8-oe-linux-gnueabi/usr/include/fcntl.h 

cd /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/asm/
sudo sed -i 3c"#include <uapi/asm-generic/errno.h>" errno.h
cd /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/uapi/asm-generic/errno.h
sudo sed -i 4c"#include <uapi/asm-generic/errno-base.h>" errno.h

sudo ln -sf /opt/ti-sdk-am335x-evm-07.00.00.00/linux-devkit/sysroots/cortexa8hf-vfp-neon-3.8-oe-linux-gnueabi/usr/include/fcntl.h /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux/
sudo ln -sf /opt/ti-sdk-am335x-evm-07.00.00.00/linux-devkit/sysroots/cortexa8hf-vfp-neon-3.8-oe-linux-gnueabi/usr/include/errno.h /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux/
sudo ln -sf /opt/ti-sdk-am335x-evm-07.00.00.00/linux-devkit/sysroots/cortexa8hf-vfp-neon-3.8-oe-linux-gnueabi/usr/include/getopt.h /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux/
sudo ln -sf /opt/ti-sdk-am335x-evm-07.00.00.00/linux-devkit/sysroots/cortexa8hf-vfp-neon-3.8-oe-linux-gnueabi/usr/include/stdlib.h /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux/
sudo ln -sf /opt/ti-sdk-am335x-evm-07.00.00.00/linux-devkit/sysroots/cortexa8hf-vfp-neon-3.8-oe-linux-gnueabi/usr/include/unistd.h /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux/
sudo ln -sf /opt/ti-sdk-am335x-evm-07.00.00.00/linux-devkit/sysroots/cortexa8hf-vfp-neon-3.8-oe-linux-gnueabi/usr/include/features.h /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux/
sudo ln -sf /opt/ti-sdk-am335x-evm-07.00.00.00/linux-devkit/sysroots/cortexa8hf-vfp-neon-3.8-oe-linux-gnueabi/usr/include/string.h /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux/
sudo ln -sf /opt/ti-sdk-am335x-evm-07.00.00.00/linux-devkit/sysroots/cortexa8hf-vfp-neon-3.8-oe-linux-gnueabi/usr/include/stdio.h /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux/
sudo ln -sf /opt/ti-sdk-am335x-evm-07.00.00.00/linux-devkit/sysroots/cortexa8hf-vfp-neon-3.8-oe-linux-gnueabi/usr/include/stdint.h /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux/
sudo ln -sf /opt/ti-sdk-am335x-evm-07.00.00.00/linux-devkit/sysroots/cortexa8hf-vfp-neon-3.8-oe-linux-gnueabi/usr/include/bits /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux/
sudo ln -sf /opt/ti-sdk-am335x-evm-07.00.00.00/linux-devkit/sysroots/cortexa8hf-vfp-neon-3.8-oe-linux-gnueabi/usr/include/xlocale.h /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux/
sudo ln -sf /opt/ti-sdk-am335x-evm-07.00.00.00/linux-devkit/sysroots/cortexa8hf-vfp-neon-3.8-oe-linux-gnueabi/usr/include/assert.h /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux/
sudo ln -s /opt/ti-sdk-am335x-evm-07.00.00.00/linux-devkit/sysroots/i686-arago-linux/usr/lib/gcc/arm-linux-gnueabihf/4.7.3/include-fixed/syslimits.h /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux/
sudo ln -sf /opt/ti-sdk-am335x-evm-07.00.00.00/linux-devkit/sysroots/i686-arago-linux/usr/lib/gcc/arm-linux-gnueabihf/4.7.3/include/stdbool.h /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux/

sudo mv ~/Downloads/libaiff-5.0-release.tar.gz /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications
cd /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications
sudo tar -xzvf libaiff-5.0-release.tar.gz
cd libaiff-5.0
sudo ./configure --prefix=/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01
sudo make
sudo make install
sudo ln -sf /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/libaiff-5.0/libaiff.* /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/lib/
