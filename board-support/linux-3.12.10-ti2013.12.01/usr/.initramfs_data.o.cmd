cmd_usr/initramfs_data.o := /opt/ti-sdk-am335x-evm-07.00.00.00/linux-devkit/sysroots/i686-arago-linux/usr/bin/arm-linux-gnueabihf-gcc -Wp,-MD,usr/.initramfs_data.o.d  -nostdinc -isystem /opt/ti-sdk-am335x-evm-07.00.00.00/linux-devkit/sysroots/i686-arago-linux/usr/bin/../lib/gcc/arm-linux-gnueabihf/4.7.3/include -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/arch/arm/include -Iarch/arm/include/generated  -Iinclude -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/arch/arm/include/uapi -Iarch/arm/include/generated/uapi -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/uapi -Iinclude/generated/uapi -include /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-omap2/include -Iarch/arm/plat-omap/include  -D__ASSEMBLY__ -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables -marm -D__LINUX_ARM_ARCH__=7 -march=armv7-a  -include asm/unified.h -msoft-float      -DINITRAMFS_IMAGE="usr/initramfs_data.cpio"   -c -o usr/initramfs_data.o usr/initramfs_data.S

source_usr/initramfs_data.o := usr/initramfs_data.S

deps_usr/initramfs_data.o := \
    $(wildcard include/config/64bit.h) \
  /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \
    $(wildcard include/config/thumb2/kernel.h) \
  include/linux/stringify.h \
  include/asm-generic/vmlinux.lds.h \
    $(wildcard include/config/hotplug/cpu.h) \
    $(wildcard include/config/memory/hotplug.h) \
    $(wildcard include/config/ftrace/mcount/record.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/event/tracing.h) \
    $(wildcard include/config/tracing.h) \
    $(wildcard include/config/ftrace/syscalls.h) \
    $(wildcard include/config/clksrc/of.h) \
    $(wildcard include/config/irqchip.h) \
    $(wildcard include/config/common/clk.h) \
    $(wildcard include/config/function/graph/tracer.h) \
    $(wildcard include/config/constructors.h) \
    $(wildcard include/config/generic/bug.h) \
    $(wildcard include/config/pm/trace.h) \
    $(wildcard include/config/blk/dev/initrd.h) \
  include/linux/export.h \
    $(wildcard include/config/have/underscore/symbol/prefix.h) \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/unused/symbols.h) \

usr/initramfs_data.o: $(deps_usr/initramfs_data.o)

$(deps_usr/initramfs_data.o):