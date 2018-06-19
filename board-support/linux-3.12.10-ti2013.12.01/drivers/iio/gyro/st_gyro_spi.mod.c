#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

MODULE_INFO(intree, "Y");

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xb5c97a0d, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x1f05bf4a, __VMLINUX_SYMBOL_STR(driver_unregister) },
	{ 0xbdf61e00, __VMLINUX_SYMBOL_STR(spi_register_driver) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x32f3fee1, __VMLINUX_SYMBOL_STR(st_gyro_common_probe) },
	{ 0xfe3060da, __VMLINUX_SYMBOL_STR(st_sensors_spi_configure) },
	{ 0xb12e51ef, __VMLINUX_SYMBOL_STR(devm_iio_device_alloc) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x9a11102b, __VMLINUX_SYMBOL_STR(st_gyro_common_remove) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=st_gyro,st_sensors_spi,industrialio";

MODULE_ALIAS("spi:l3g4200d");
MODULE_ALIAS("spi:lsm330d_gyro");
MODULE_ALIAS("spi:lsm330dl_gyro");
MODULE_ALIAS("spi:lsm330dlc_gyro");
MODULE_ALIAS("spi:l3gd20");
MODULE_ALIAS("spi:l3gd20h");
MODULE_ALIAS("spi:l3g4is_ui");
MODULE_ALIAS("spi:lsm330_gyro");
