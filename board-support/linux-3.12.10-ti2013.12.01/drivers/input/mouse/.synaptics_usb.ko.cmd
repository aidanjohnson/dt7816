cmd_drivers/input/mouse/synaptics_usb.ko := /opt/ti-sdk-am335x-evm-07.00.00.00/linux-devkit/sysroots/i686-arago-linux/usr/bin/arm-linux-gnueabihf-ld -EL -r  -T /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/scripts/module-common.lds --build-id  -o drivers/input/mouse/synaptics_usb.ko drivers/input/mouse/synaptics_usb.o drivers/input/mouse/synaptics_usb.mod.o