cmd_net/phonet/phonet.ko := /opt/ti-sdk-am335x-evm-07.00.00.00/linux-devkit/sysroots/i686-arago-linux/usr/bin/arm-linux-gnueabihf-ld -EL -r  -T /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/scripts/module-common.lds --build-id  -o net/phonet/phonet.ko net/phonet/phonet.o net/phonet/phonet.mod.o