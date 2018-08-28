#
# Makefile for Data Translation DT78xx base module
# For details see Documentation/kbuild/modules.txt
MODULE_NAME := dt78xx
obj-m += $(MODULE_NAME).o
$(MODULE_NAME)-objs := dt78xx_main.o dt78xx_sysfs.o dt78xx_fops.o dt78xx_misc.o \
	dt78xx_pot.o

ccflags-$(CONFIG_DEBUG_DRIVER) := -DDEBUG
# Define _GPMC_DT_OVERRIDE_ to add functions that parse bindings in the device
# tree and directly configure the GPMC config registers
ccflags-y += -D_GPMC_DT_OVERRIDE_
# ccflags-y += -D_WARN_

# uncomment the following to get verbose output from make. Default V=0 
# See https://www.kernel.org/doc/linux/README	
# MAKE_VERBOSE := V=1
	
# To generate assembly listing for any source file, use this example
# CFLAGS_dt78xx_sysfs.o = -Wa,-adhln=$(obj)/dt78xx_sysfs.s -g -fverbose-asm 
    
all : kmodule dtbs
clean : kmodule_clean dtbs_clean

kmodule: 
	@echo ================================
	@echo  Building  $(MODULE_NAME) device driver
	@echo ================================
	$(MAKE) $(MAKE_VERBOSE) -j $(MAKE_JOBS) -C $(LINUXKERNEL_INSTALL_DIR) ARCH=arm \
	CROSS_COMPILE=$(CROSS_COMPILE) M=`pwd` modules

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

dtbs_clean:
	@rm -rf ./dtb/*.dtb ./dtb/.*.tmp
	
.PHONY: all install clean kmodule kmodule_clean dtbs dtbs_clean
	