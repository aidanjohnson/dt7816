cmd_arch/arm/boot/compressed/head.o := /opt/ti-sdk-am335x-evm-07.00.00.00/linux-devkit/sysroots/i686-arago-linux/usr/bin/arm-linux-gnueabihf-gcc -Wp,-MD,arch/arm/boot/compressed/.head.o.d  -nostdinc -isystem /opt/ti-sdk-am335x-evm-07.00.00.00/linux-devkit/sysroots/i686-arago-linux/usr/bin/../lib/gcc/arm-linux-gnueabihf/4.7.3/include -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/arch/arm/include -Iarch/arm/include/generated  -Iinclude -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/arch/arm/include/uapi -Iarch/arm/include/generated/uapi -I/opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/uapi -Iinclude/generated/uapi -include /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/include/linux/kconfig.h -D__KERNEL__ -mlittle-endian -Iarch/arm/mach-omap2/include -Iarch/arm/plat-omap/include  -D__ASSEMBLY__ -mabi=aapcs-linux -mno-thumb-interwork -funwind-tables -marm -D__LINUX_ARM_ARCH__=7 -march=armv7-a  -include asm/unified.h -msoft-float     -DZIMAGE  -DTEXT_OFFSET=0x00008000   -c -o arch/arm/boot/compressed/head.o arch/arm/boot/compressed/head.S

source_arch/arm/boot/compressed/head.o := arch/arm/boot/compressed/head.S

deps_arch/arm/boot/compressed/head.o := \
    $(wildcard include/config/debug/icedcc.h) \
    $(wildcard include/config/cpu/v6.h) \
    $(wildcard include/config/cpu/v6k.h) \
    $(wildcard include/config/cpu/v7.h) \
    $(wildcard include/config/cpu/xscale.h) \
    $(wildcard include/config/debug/ll/include.h) \
    $(wildcard include/config/arch/sa1100.h) \
    $(wildcard include/config/debug/ll/ser3.h) \
    $(wildcard include/config/arch/s3c24xx.h) \
    $(wildcard include/config/s3c/lowlevel/uart/port.h) \
    $(wildcard include/config/cpu/cp15.h) \
    $(wildcard include/config/arm/virt/ext.h) \
    $(wildcard include/config/auto/zreladdr.h) \
    $(wildcard include/config/zboot/rom.h) \
    $(wildcard include/config/arm/appended/dtb.h) \
    $(wildcard include/config/arm/atag/dtb/compat.h) \
    $(wildcard include/config/arch/rpc.h) \
    $(wildcard include/config/cpu/dcache/writethrough.h) \
    $(wildcard include/config/mmu.h) \
    $(wildcard include/config/cpu/endian/be8.h) \
    $(wildcard include/config/thumb2/kernel.h) \
    $(wildcard include/config/processor/id.h) \
    $(wildcard include/config/cpu/feroceon/old/id.h) \
  /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/arch/arm/include/asm/unified.h \
    $(wildcard include/config/arm/asm/unified.h) \
  include/linux/linkage.h \
  include/linux/compiler.h \
    $(wildcard include/config/sparse/rcu/pointer.h) \
    $(wildcard include/config/trace/branch/profiling.h) \
    $(wildcard include/config/profile/all/branches.h) \
    $(wildcard include/config/enable/must/check.h) \
    $(wildcard include/config/enable/warn/deprecated.h) \
    $(wildcard include/config/kprobes.h) \
  include/linux/stringify.h \
  include/linux/export.h \
    $(wildcard include/config/have/underscore/symbol/prefix.h) \
    $(wildcard include/config/modules.h) \
    $(wildcard include/config/modversions.h) \
    $(wildcard include/config/unused/symbols.h) \
  /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/arch/arm/include/asm/linkage.h \
  /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/arch/arm/include/asm/assembler.h \
    $(wildcard include/config/cpu/feroceon.h) \
    $(wildcard include/config/trace/irqflags.h) \
    $(wildcard include/config/cpu/v7m.h) \
    $(wildcard include/config/smp.h) \
    $(wildcard include/config/cpu/use/domains.h) \
  /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/arch/arm/include/asm/ptrace.h \
    $(wildcard include/config/arm/thumb.h) \
  /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/arch/arm/include/uapi/asm/ptrace.h \
  /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/arch/arm/include/asm/hwcap.h \
  /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/arch/arm/include/uapi/asm/hwcap.h \
  /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/arch/arm/include/asm/domain.h \
    $(wildcard include/config/io/36.h) \
  /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/arch/arm/include/asm/opcodes-virt.h \
  /opt/ti-sdk-am335x-evm-07.00.00.00/board-support/linux-3.12.10-ti2013.12.01/arch/arm/include/asm/opcodes.h \
    $(wildcard include/config/cpu/endian/be32.h) \

arch/arm/boot/compressed/head.o: $(deps_arch/arm/boot/compressed/head.o)

$(deps_arch/arm/boot/compressed/head.o):
