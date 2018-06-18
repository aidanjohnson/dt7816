#!/bin/sh

cd ~/Downloads
sudo chmod +x ti-sdk-am335x-evm-07.00.00.00-Linux-x86-Install.bin
sudo ./ti-sdk-am335x-evm-07.00.00.00-Linux-x86-Install.bin

sudo apt-get install build-essential gcc make linux-headers-$(uname -r)

sudo chmod +x DT78XX-setup-3.2.bz2.run
sudo ./DT78XX-setup-3.2.bz2.run --target /opt/ti-sdk-am335x-evm-07.00.00.00/

cd /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications
tar -xzvf ~/Downloads/fftw-3.3.4.tar.gz
cd fftw-3.3.4/
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

sudo ln -s /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/extra-drivers/dt78xx/dt78xx_ioctl.h /opt/ti-sdk-am335x-evm-07.00.00.00/example-applications/dt78xx-examples/common
sudo ln -s /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/asm-generic /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/asm
sudo ln -s /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/acpi/processor.h /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/asm
sudo ln -s /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux/acpi.h /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/asm
sudo ln -s /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux/thread_info.h /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/asm

sudo tar -xzvf ~/Downloads/libxml2-2.9.8.tar.gz
cd libxml2-2.9.8
sudo ./configure --prefix=/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/ --without-python
sudo make
sudo make install