# Makefile for USB gadget driver for Data Translation DT78xx board 
g_dt78xx-objs = dt78xx_gadget.o	
obj-m += g_dt78xx.o

ccflags-$(CONFIG_DEBUG_DRIVER) := -DDEBUG
# ccflags-y += -D_WARN_

dt78xx-usbg: 
	@echo ================================
	@echo  Building DT78xx USB gadget driver
	@echo ================================
	$(MAKE) -j $(MAKE_JOBS) -C $(LINUXKERNEL_INSTALL_DIR) ARCH=arm \
	CROSS_COMPILE=$(CROSS_COMPILE) M=`pwd` modules

install:
	@echo ================================
	@echo  Installing DT78xx USB gadget driver
	@echo ================================
	$(MAKE) -j $(MAKE_JOBS) -C $(LINUXKERNEL_INSTALL_DIR) ARCH=arm \
	CROSS_COMPILE=$(CROSS_COMPILE) INSTALL_MOD_PATH=$(FILESYS) \
	M=`pwd` modules_install

clean:
	@echo ================================
	@echo  Cleaning DT78xx USB gadget driver
	@echo ================================
	$(MAKE) -C $(LINUXKERNEL_INSTALL_DIR) M=`pwd` clean
