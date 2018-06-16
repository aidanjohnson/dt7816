-include Rules.make

MAKE_JOBS ?= 1

all: linux matrix-gui arm-benchmarks am-sysinfo matrix-gui-browser refresh-screen qt-tstat oprofile-example u-boot-spl quick-playground ti-crypto-examples linux-dtbs wireless cryptodev 
clean: linux_clean matrix-gui_clean arm-benchmarks_clean am-sysinfo_clean matrix-gui-browser_clean refresh-screen_clean qt-tstat_clean oprofile-example_clean u-boot-spl_clean quick-playground_clean ti-crypto-examples_clean linux-dtbs_clean wireless_clean cryptodev_clean 
install: linux_install matrix-gui_install arm-benchmarks_install am-sysinfo_install matrix-gui-browser_install refresh-screen_install qt-tstat_install oprofile-example_install u-boot-spl_install quick-playground_install ti-crypto-examples_install linux-dtbs_install wireless_install cryptodev_install 
# Kernel build targets
linux: linux-dtbs
	@echo =================================
	@echo     Building the Linux Kernel
	@echo =================================
	$(MAKE) -C $(LINUXKERNEL_INSTALL_DIR) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) tisdk_$(PLATFORM)_defconfig
	$(MAKE) -j $(MAKE_JOBS) -C $(LINUXKERNEL_INSTALL_DIR) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) zImage
	$(MAKE) -j $(MAKE_JOBS) -C $(LINUXKERNEL_INSTALL_DIR) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) modules

linux_install: linux-dtbs_install
	@echo ===================================
	@echo     Installing the Linux Kernel
	@echo ===================================
	@if [ ! -d $(DESTDIR) ] ; then \
		echo "The extracted target filesystem directory doesn't exist."; \
		echo "Please run setup.sh in the SDK's root directory and then try again."; \
		exit 1; \
	fi
	install -d $(DESTDIR)/boot
	install $(LINUXKERNEL_INSTALL_DIR)/arch/arm/boot/zImage $(DESTDIR)/boot
	install $(LINUXKERNEL_INSTALL_DIR)/vmlinux $(DESTDIR)/boot
	install $(LINUXKERNEL_INSTALL_DIR)/System.map $(DESTDIR)/boot
	$(MAKE) -C $(LINUXKERNEL_INSTALL_DIR) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) INSTALL_MOD_PATH=$(DESTDIR) modules_install

linux_clean:
	@echo =================================
	@echo     Cleaning the Linux Kernel
	@echo =================================
	$(MAKE) -C $(LINUXKERNEL_INSTALL_DIR) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) mrproper
# Make Rules for matrix-gui project
matrix-gui:
	@echo =============================
	@echo      Building Matrix GUI
	@echo =============================
	@echo    NOTHING TO DO.  COMPILATION NOT REQUIRED

matrix-gui_clean:
	@echo =============================
	@echo      Cleaning Matrix GUI
	@echo =============================
	@echo    NOTHING TO DO.

matrix-gui_install:
	@echo =============================
	@echo     Installing Matrix GUI
	@echo =============================
	@cd example-applications; cd `find . -name "*matrix-gui-2.0*"`; make install
# arm-benchmarks build targets
arm-benchmarks:
	@echo =============================
	@echo    Building ARM Benchmarks
	@echo =============================
	@cd example-applications; cd `find . -name "*arm-benchmarks*"`; make

arm-benchmarks_clean:
	@echo =============================
	@echo    Cleaning ARM Benchmarks
	@echo =============================
	@cd example-applications; cd `find . -name "*arm-benchmarks*"`; make clean

arm-benchmarks_install:
	@echo ==============================================
	@echo   Installing ARM Benchmarks - Release version
	@echo ==============================================
	@cd example-applications; cd `find . -name "*arm-benchmarks*"`; make install

arm-benchmarks_install_debug:
	@echo ============================================
	@echo   Installing ARM Benchmarks - Debug Version
	@echo ============================================
	@cd example-applications; cd `find . -name "*arm-benchmarks*"`; make install_debug
# am-sysinfo build targets
am-sysinfo:
	@echo =============================
	@echo    Building AM Sysinfo
	@echo =============================
	@cd example-applications; cd `find . -name "*am-sysinfo*"`; make

am-sysinfo_clean:
	@echo =============================
	@echo    Cleaning AM Sysinfo
	@echo =============================
	@cd example-applications; cd `find . -name "*am-sysinfo*"`; make clean

am-sysinfo_install:
	@echo ===============================================
	@echo     Installing AM Sysinfo - Release version
	@echo ===============================================
	@cd example-applications; cd `find . -name "*am-sysinfo*"`; make install

am-sysinfo_install_debug:
	@echo =============================================
	@echo     Installing AM Sysinfo - Debug version
	@echo =============================================
	@cd example-applications; cd `find . -name "*am-sysinfo*"`; make install_debug
# matrix-gui-browser build targets
matrix-gui-browser:
	@echo =================================
	@echo    Building Matrix GUI Browser
	@echo =================================
	@cd example-applications; cd `find . -name "*matrix-gui-browser*"`; make -f Makefile.build release

matrix-gui-browser_clean:
	@echo =================================
	@echo    Cleaning Matrix GUI Browser
	@echo =================================
	@cd example-applications; cd `find . -name "*matrix-gui-browser*"`; make -f Makefile.build clean

matrix-gui-browser_install:
	@echo ===================================================
	@echo   Installing Matrix GUI Browser - Release version
	@echo ===================================================
	@cd example-applications; cd `find . -name "*matrix-gui-browser*"`; make -f Makefile.build install

matrix-gui-browser_install_debug:
	@echo =================================================
	@echo   Installing Matrix GUI Browser - Debug Version
	@echo =================================================
	@cd example-applications; cd `find . -name "*matrix-gui-browser*"`; make -f Makefile.build install_debug
# refresh-screen build targets
refresh-screen:
	@echo =============================
	@echo    Building Refresh Screen
	@echo =============================
	@cd example-applications; cd `find . -name "*refresh-screen*"`; make -f Makefile.build release

refresh-screen_clean:
	@echo =============================
	@echo    Cleaning Refresh Screen
	@echo =============================
	@cd example-applications; cd `find . -name "*refresh-screen*"`; make -f Makefile.build clean

refresh-screen_install:
	@echo ================================================
	@echo   Installing Refresh Screen - Release version
	@echo ================================================
	@cd example-applications; cd `find . -name "*refresh-screen*"`; make -f Makefile.build install

refresh-screen_install_debug:
	@echo ==============================================
	@echo   Installing Refresh Screen - Debug Version
	@echo ==============================================
	@cd example-applications; cd `find . -name "*refresh-screen*"`; make -f Makefile.build install_debug
# QT Thermostat build targets
qt-tstat:
	@echo ================================
	@echo    Building QT Thermostat App
	@echo ================================
	@cd example-applications; cd `find . -name "*qt-tstat*"`; make -f Makefile.build release

qt-tstat_clean:
	@echo ================================
	@echo    Cleaning QT Thermostat App
	@echo ================================
	@cd example-applications; cd `find . -name "*qt-tstat*"`; make -f Makefile.build clean

qt-tstat_install:
	@echo ===================================================
	@echo   Installing QT Thermostat App - Release version
	@echo ===================================================
	@cd example-applications; cd `find . -name "*qt-tstat*"`; make -f Makefile.build install

qt-tstat_install_debug:
	@echo =================================================
	@echo   Installing QT Thermostat App - Debug version
	@echo =================================================
	@cd example-applications; cd `find . -name "*qt-tstat*"`; make -f Makefile.build install_debug
# oprofile-example build targets
oprofile-example:
	@echo =============================
	@echo    Building OProfile Example
	@echo =============================
	@cd example-applications; cd `find . -name "*oprofile-example*"`; make

oprofile-example_clean:
	@echo =============================
	@echo    Cleaning OProfile Example
	@echo =============================
	@cd example-applications; cd `find . -name "*oprofile-example*"`; make clean

oprofile-example_install:
	@echo =============================================
	@echo     Installing OProfile Example - Debug version
	@echo =============================================
	@cd example-applications; cd `find . -name "*oprofile-example*"`; make install
# u-boot build targets
u-boot-spl: u-boot
u-boot-spl_clean: u-boot_clean
u-boot-spl_install: u-boot_install

u-boot:
	@echo ===================================
	@echo    Building U-boot
	@echo ===================================
	$(MAKE) -j $(MAKE_JOBS) -C $(TI_SDK_PATH)/board-support/u-boot-* CROSS_COMPILE=$(CROSS_COMPILE) $(UBOOT_MACHINE)
	$(MAKE) -j $(MAKE_JOBS) -C $(TI_SDK_PATH)/board-support/u-boot-* CROSS_COMPILE=$(CROSS_COMPILE)

u-boot_clean:
	@echo ===================================
	@echo    Cleaining U-boot
	@echo ===================================
	$(MAKE) -C $(TI_SDK_PATH)/board-support/u-boot-* CROSS_COMPILE=$(CROSS_COMPILE) distclean

u-boot_install:
	@echo ===================================
	@echo    Installing U-boot
	@echo ===================================
	@echo "Nothing to do"
# Quick Playground build targets
quick-playground:
	@echo =================================
	@echo    Building Quick Playground App
	@echo =================================
	@cd example-applications; cd `find . -name "*quick-playground*"`; make -f Makefile.build

quick-playground_clean:
	@echo =================================
	@echo    Cleaning Quick Playground App
	@echo =================================
	@cd example-applications; cd `find . -name "*quick-playground*"`; make -f Makefile.build clean

quick-playground_install:
	@echo ====================================================
	@echo   Installing Quick Playground App - Release version
	@echo ====================================================
	@cd example-applications; cd `find . -name "*quick-playground*"`; make -f Makefile.build install

quick-playground_install_debug:
	@echo ==================================================
	@echo   Installing Quick Playground App - Debug version
	@echo ==================================================
	@cd example-applications; cd `find . -name "*quick-playground*"`; make -f Makefile.build install_debug
# ti-crypto-examples build targets
ti-crypto-examples:
	@echo =================================
	@echo    Building TI Crypto Examples
	@echo =================================
	@cd example-applications; cd `find . -name "*ti-crypto-examples*"`; make release

ti-crypto-examples_clean:
	@echo =================================
	@echo    Cleaning TI Crypto Examples
	@echo =================================
	@cd example-applications; cd `find . -name "*ti-crypto-examples*"`; make clean

ti-crypto-examples_install:
	@echo ===================================================
	@echo   Installing TI Crypto Examples - Release version
	@echo ===================================================
	@cd example-applications; cd `find . -name "*ti-crypto-examples*"`; make install

ti-crypto-examples_install_debug:
	@echo =================================================
	@echo   Installing TI Crypto Examples - Debug Version
	@echo =================================================
	@cd example-applications; cd `find . -name "*ti-crypto-examples*"`; make install_debug
# Kernel DTB build targets
linux-dtbs:
	@echo =====================================
	@echo     Building the Linux Kernel DTBs
	@echo =====================================
	$(MAKE) -C $(LINUXKERNEL_INSTALL_DIR) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) tisdk_$(PLATFORM)_defconfig
	$(MAKE) -j $(MAKE_JOBS) -C $(LINUXKERNEL_INSTALL_DIR) ARCH=arm CROSS_COMPILE=$(CROSS_COMPILE) am335x-evm.dtb am335x-evmsk.dtb am335x-bone.dtb am335x-boneblack.dtb

linux-dtbs_install:
	@echo =======================================
	@echo     Installing the Linux Kernel DTBs
	@echo =======================================
	@if [ ! -d $(DESTDIR) ] ; then \
		echo "The extracted target filesystem directory doesn't exist."; \
		echo "Please run setup.sh in the SDK's root directory and then try again."; \
		exit 1; \
	fi
	install -d $(DESTDIR)/boot
	@cp -f $(LINUXKERNEL_INSTALL_DIR)/arch/arm/boot/dts/*.dtb $(DESTDIR)/boot/

linux-dtbs_clean:
	@echo =======================================
	@echo     Cleaning the Linux Kernel DTBs
	@echo =======================================
	@echo "Nothing to do"

# Wireless build targets
wireless: wifi-firmware
wireless_install: wifi-firmware_install
wireless_clean: wifi-firmware_clean

wifi-firmware:
	@echo ================================
	@echo      Building wifi firmware
	@echo ================================
	@echo "Nothing to do"

wifi-firmware_install:
	@echo ==================================
	@echo      Installing wifi firmware
	@echo ==================================
	@cd board-support/extra-drivers; \
	cd `find . -maxdepth 1 -name "wl18xx-firmware*"`; \
	make DEST_DIR=${DESTDIR} install

wifi-firmware_clean:
	@echo ================================
	@echo      Cleaning wifi firmware
	@echo ================================
	@echo "Nothing to do" 
cryptodev: linux
	@echo ================================
	@echo      Building cryptodev-linux
	@echo ================================
	@cd board-support/extra-drivers; \
	cd `find . -maxdepth 1 -name "cryptodev*"`; \
	make ARCH=arm KERNEL_DIR=$(LINUXKERNEL_INSTALL_DIR)

cryptodev_clean:
	@echo ================================
	@echo      Cleaning cryptodev-linux
	@echo ================================
	@cd board-support/extra-drivers; \
	cd `find . -maxdepth 1 -name "cryptodev*"`; \
	make clean

cryptodev_install:
	@echo ================================
	@echo      Installing cryptodev-linux
	@echo ================================
	@if [ ! -d $(DESTDIR) ] ; then \
		echo "The extracted target filesystem directory doesn't exist."; \
		echo "Please run setup.sh in the SDK's root directory and then try again."; \
		exit 1; \
	fi
	@cd board-support/extra-drivers; \
	cd `find . -maxdepth 1 -name "cryptodev*"`; \
	make ARCH=arm  KERNEL_DIR=$(LINUXKERNEL_INSTALL_DIR)  INSTALL_MOD_PATH=$(DESTDIR) PREFIX=$(SDK_PATH_TARGET)  install
