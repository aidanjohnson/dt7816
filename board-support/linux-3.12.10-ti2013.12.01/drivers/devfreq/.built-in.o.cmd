cmd_drivers/devfreq/built-in.o :=  /opt/ti-sdk-am335x-evm-07.00.00.00/linux-devkit/sysroots/i686-arago-linux/usr/bin/arm-linux-gnueabihf-ld -EL    -r -o drivers/devfreq/built-in.o drivers/devfreq/devfreq.o drivers/devfreq/governor_simpleondemand.o drivers/devfreq/governor_performance.o drivers/devfreq/governor_powersave.o drivers/devfreq/governor_userspace.o 