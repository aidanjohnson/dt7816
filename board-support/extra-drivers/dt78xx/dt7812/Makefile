#
# Makefile for Data Translation DT7816 board
# For details see Documentation/kbuild/modules.txt
MODULE_NAME := dt7816

# Module will be named $(MODULE_NAME).ko
obj-m += $(MODULE_NAME).o
$(MODULE_NAME)-objs := dt7816_main.o dt7816_sysfs.o  dt7816_din.o dt7816_dout.o \
	dt7816_ct.o dt7816_common.o dt7816_ain.o dt7816_stream_in.o \
	dt7816_measure.o dt7816_tach.o dt7816_misc.o dt7816_aout.o \
	dt7816_stream_out.o

ccflags-y += -I$(DT78xx_INC_DIR)
ccflags-$(CONFIG_DEBUG_DRIVER) += -DDEBUG
#ccflags-y += -D_WARN_

# If VFP h/w is enabled, perform hardware floating point using the soft 
# floating point ABI
ifeq ($(CONFIG_KERNEL_MODE_NEON),y)
  NEON_FLAGS			:= -mfloat-abi=softfp -mfpu=neon
  CFLAGS_dt7816_misc.o		+= $(NEON_FLAGS)
endif

# exported symbols from the dt78xx base driver used by modpost	
KBUILD_EXTRA_SYMBOLS= $(DT78xx_DIR)/Module.symvers 

all : kmodule dtbs
clean : kmodule_clean dtbs_clean

kmodule: 
	@echo ================================
	@echo  Building $(MODULE_NAME) kernel load module
	@echo ================================
	$(MAKE) $(MAKE_VERBOSE) -j $(MAKE_JOBS) -C $(LINUXKERNEL_INSTALL_DIR) ARCH=arm \
	CROSS_COMPILE=$(CROSS_COMPILE)  M=`pwd` modules

kmodule_clean: 
	$(MAKE) -C $(LINUXKERNEL_INSTALL_DIR) M=`pwd` clean

install:
	@echo ================================
	@echo  Installing DT78xx driver
	@echo ================================
	$(MAKE) -j $(MAKE_JOBS) -C $(LINUXKERNEL_INSTALL_DIR) ARCH=arm \
	CROSS_COMPILE=$(CROSS_COMPILE) INSTALL_MOD_PATH=$(FILESYS) \
	M=`pwd` modules_install

dtbs:
	@echo =====================================
	@echo     Building the $(MODULE_NAME) DTBs
	@echo =====================================
	@mkdir -p ./dtb
	@rm -rf ./dtb/.*.tmp
	@$(CC) -E -Wp,-MD,./dtb/.dt78xx.dtb.d.pre.tmp -nostdinc \
	-I$(LINUXKERNEL_INSTALL_DIR)/arch/arm/boot/dts \
	-I$(LINUXKERNEL_INSTALL_DIR)/arch/arm/boot/dts/include \
	-I$(DT78xx_INC_DIR) \
	-undef -D__DTS__ -D_GPMC_DT_OVERRIDE_ \
	-x assembler-with-cpp -o ./dtb/.dt78xx.dtb.dts.tmp ./$(MODULE_NAME).dts
	@$(LINUXKERNEL_INSTALL_DIR)/scripts/dtc/dtc -O dtb \
	-o ./dtb/$(MODULE_NAME).dtb -b 0 \
	-i $(LINUXKERNEL_INSTALL_DIR)/arch/arm/boot/dts  \
	-d ./dtb/.dt78xx.dtb.d.dtc.tmp ./dtb/.dt78xx.dtb.dts.tmp

dtbs_clean:
	@rm -rf ./dtb/*.dtb ./dtb/.*.tmp
	
.PHONY: all install clean kmodule kmodule_clean dtbs dtbs_clean
	
