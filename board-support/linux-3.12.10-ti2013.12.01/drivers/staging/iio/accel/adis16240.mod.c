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

MODULE_INFO(staging, "Y");

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xb5c97a0d, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x28e44a8b, __VMLINUX_SYMBOL_STR(adis_update_scan_mode) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0xd4c463a9, __VMLINUX_SYMBOL_STR(iio_read_const_attr) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xd8a93efc, __VMLINUX_SYMBOL_STR(iio_device_register) },
	{ 0x8a905b84, __VMLINUX_SYMBOL_STR(adis_initial_startup) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x17bcfee8, __VMLINUX_SYMBOL_STR(iio_device_unregister) },
	{ 0xb12e51ef, __VMLINUX_SYMBOL_STR(devm_iio_device_alloc) },
	{ 0x71a81793, __VMLINUX_SYMBOL_STR(adis_init) },
	{ 0x1f05bf4a, __VMLINUX_SYMBOL_STR(driver_unregister) },
	{ 0xd577fb9c, __VMLINUX_SYMBOL_STR(adis_check_status) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x86288e06, __VMLINUX_SYMBOL_STR(adis_write_reg) },
	{ 0x490be6f2, __VMLINUX_SYMBOL_STR(adis_cleanup_buffer_and_trigger) },
	{ 0x714f148c, __VMLINUX_SYMBOL_STR(adis_setup_buffer_and_trigger) },
	{ 0xa66d6cf4, __VMLINUX_SYMBOL_STR(adis_read_reg) },
	{ 0x370158d2, __VMLINUX_SYMBOL_STR(adis_single_conversion) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xbdf61e00, __VMLINUX_SYMBOL_STR(spi_register_driver) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=adis_lib,industrialio";

