cmd_drivers/tty/serial/built-in.o :=  /opt/ti-sdk-am335x-evm-07.00.00.00/linux-devkit/sysroots/i686-arago-linux/usr/bin/arm-linux-gnueabihf-ld -EL    -r -o drivers/tty/serial/built-in.o drivers/tty/serial/serial_core.o drivers/tty/serial/8250/built-in.o drivers/tty/serial/of_serial.o drivers/tty/serial/omap-serial.o drivers/tty/serial/kgdboc.o 