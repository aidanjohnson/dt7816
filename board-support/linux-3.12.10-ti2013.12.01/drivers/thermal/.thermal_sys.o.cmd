cmd_drivers/thermal/thermal_sys.o := /opt/ti-sdk-am335x-evm-07.00.00.00/linux-devkit/sysroots/i686-arago-linux/usr/bin/arm-linux-gnueabihf-ld -EL    -r -o drivers/thermal/thermal_sys.o drivers/thermal/thermal_core.o drivers/thermal/thermal_hwmon.o drivers/thermal/fair_share.o drivers/thermal/step_wise.o drivers/thermal/user_space.o drivers/thermal/cpu_cooling.o 