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
	{ 0xd4c463a9, __VMLINUX_SYMBOL_STR(iio_read_const_attr) },
	{ 0xb361f9ce, __VMLINUX_SYMBOL_STR(ad_sd_validate_trigger) },
	{ 0x1f05bf4a, __VMLINUX_SYMBOL_STR(driver_unregister) },
	{ 0xbdf61e00, __VMLINUX_SYMBOL_STR(spi_register_driver) },
	{ 0xd8a93efc, __VMLINUX_SYMBOL_STR(iio_device_register) },
	{ 0xad920b1f, __VMLINUX_SYMBOL_STR(ad_sd_setup_buffer_and_trigger) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x910a0970, __VMLINUX_SYMBOL_STR(ad_sd_init) },
	{ 0x2a52919e, __VMLINUX_SYMBOL_STR(spi_get_device_id) },
	{ 0xca16dbe7, __VMLINUX_SYMBOL_STR(regulator_enable) },
	{ 0xb1ad5f39, __VMLINUX_SYMBOL_STR(devm_regulator_get) },
	{ 0xb12e51ef, __VMLINUX_SYMBOL_STR(devm_iio_device_alloc) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x82f324b7, __VMLINUX_SYMBOL_STR(ad_sd_set_comm) },
	{ 0x698be398, __VMLINUX_SYMBOL_STR(regulator_get_voltage) },
	{ 0xcd75ee80, __VMLINUX_SYMBOL_STR(ad_sigma_delta_single_conversion) },
	{ 0x8a4fa83b, __VMLINUX_SYMBOL_STR(__aeabi_llsr) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x938485e6, __VMLINUX_SYMBOL_STR(ad_sd_write_reg) },
	{ 0x222e7ce2, __VMLINUX_SYMBOL_STR(sysfs_streq) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x1258d9d9, __VMLINUX_SYMBOL_STR(regulator_disable) },
	{ 0xdef635c0, __VMLINUX_SYMBOL_STR(ad_sd_cleanup_buffer_and_trigger) },
	{ 0x17bcfee8, __VMLINUX_SYMBOL_STR(iio_device_unregister) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=industrialio,ad_sigma_delta";

MODULE_ALIAS("spi:ad7787");
MODULE_ALIAS("spi:ad7788");
MODULE_ALIAS("spi:ad7789");
MODULE_ALIAS("spi:ad7790");
MODULE_ALIAS("spi:ad7791");
