cmd_firmware/keyspan/usa28xa.fw.gen.o := /opt/ti-sdk-am335x-evm-07.00.00.00/linux-devkit/sysroots/i686-arago-linux/usr/bin/arm-linux-gnueabihf-gcc -Wp,-MD,firmware/keyspan/.usa28xa.fw.gen.o.d  -nostdinc -isystem /opt/ti-sdk-am335x-evm-07.00.00.00/linux-devkit/sysroots/i686-arago-linux/usr/bin/../lib/gcc/arm-linux-gnueabihf/4.7.3/include -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/arch/arm/include -Iarch/arm/include/generated  -Iinclude -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/arch/arm/include/uapi -Iarch/arm/include/generated/uapi -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/uapi -Iinclude/generated/uapi -include /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-omap2/include -Iarch/arm/plat-omap/include  -D__ASSEMBLY__ -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables -marm -D__LINUX_ARM_ARCH__=7 -march=armv7-a  -include asm/unified.h -msoft-float         -c -o firmware/keyspan/usa28xa.fw.gen.o firmware/keyspan/usa28xa.fw.gen.S

source_firmware/keyspan/usa28xa.fw.gen.o := firmware/keyspan/usa28xa.fw.gen.S

deps_firmware/keyspan/usa28xa.fw.gen.o := \
  /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \
    $(wildcard include/config/thumb2/kernel.h) \

firmware/keyspan/usa28xa.fw.gen.o: $(deps_firmware/keyspan/usa28xa.fw.gen.o)

$(deps_firmware/keyspan/usa28xa.fw.gen.o):
