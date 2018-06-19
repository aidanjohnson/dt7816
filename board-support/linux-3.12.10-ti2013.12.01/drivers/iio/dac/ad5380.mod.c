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
	{ 0x2f088f2e, __VMLINUX_SYMBOL_STR(iio_enum_available_read) },
	{ 0x4862ff8a, __VMLINUX_SYMBOL_STR(iio_enum_write) },
	{ 0x441347fd, __VMLINUX_SYMBOL_STR(iio_enum_read) },
	{ 0xa731ccf6, __VMLINUX_SYMBOL_STR(i2c_del_driver) },
	{ 0x1f05bf4a, __VMLINUX_SYMBOL_STR(driver_unregister) },
	{ 0xe25a742c, __VMLINUX_SYMBOL_STR(i2c_register_driver) },
	{ 0xbdf61e00, __VMLINUX_SYMBOL_STR(spi_register_driver) },
	{ 0xa7993bd5, __VMLINUX_SYMBOL_STR(devm_regmap_init_spi) },
	{ 0x2a52919e, __VMLINUX_SYMBOL_STR(spi_get_device_id) },
	{ 0x642dd311, __VMLINUX_SYMBOL_STR(devm_regmap_init_i2c) },
	{ 0xd8a93efc, __VMLINUX_SYMBOL_STR(iio_device_register) },
	{ 0x698be398, __VMLINUX_SYMBOL_STR(regulator_get_voltage) },
	{ 0xca16dbe7, __VMLINUX_SYMBOL_STR(regulator_enable) },
	{ 0xb1ad5f39, __VMLINUX_SYMBOL_STR(devm_regulator_get) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xb12e51ef, __VMLINUX_SYMBOL_STR(devm_iio_device_alloc) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xa8232c78, __VMLINUX_SYMBOL_STR(strtobool) },
	{ 0x2b2e801c, __VMLINUX_SYMBOL_STR(regmap_update_bits) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x11612e0e, __VMLINUX_SYMBOL_STR(regmap_read) },
	{ 0xe440f76f, __VMLINUX_SYMBOL_STR(regmap_write) },
	{ 0x1258d9d9, __VMLINUX_SYMBOL_STR(regulator_disable) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x17bcfee8, __VMLINUX_SYMBOL_STR(iio_device_unregister) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=industrialio";

MODULE_ALIAS("i2c:ad5380-3");
MODULE_ALIAS("i2c:ad5380-5");
MODULE_ALIAS("i2c:ad5381-3");
MODULE_ALIAS("i2c:ad5381-5");
MODULE_ALIAS("i2c:ad5382-3");
MODULE_ALIAS("i2c:ad5382-5");
MODULE_ALIAS("i2c:ad5383-3");
MODULE_ALIAS("i2c:ad5383-5");
MODULE_ALIAS("i2c:ad5384-3");
MODULE_ALIAS("i2c:ad5384-5");
MODULE_ALIAS("i2c:ad5390-3");
MODULE_ALIAS("i2c:ad5390-5");
MODULE_ALIAS("i2c:ad5391-3");
MODULE_ALIAS("i2c:ad5391-5");
MODULE_ALIAS("i2c:ad5392-3");
MODULE_ALIAS("i2c:ad5392-5");
MODULE_ALIAS("spi:ad5380-3");
MODULE_ALIAS("spi:ad5380-5");
MODULE_ALIAS("spi:ad5381-3");
MODULE_ALIAS("spi:ad5381-5");
MODULE_ALIAS("spi:ad5382-3");
MODULE_ALIAS("spi:ad5382-5");
MODULE_ALIAS("spi:ad5383-3");
MODULE_ALIAS("spi:ad5383-5");
MODULE_ALIAS("spi:ad5384-3");
MODULE_ALIAS("spi:ad5384-5");
MODULE_ALIAS("spi:ad5390-3");
MODULE_ALIAS("spi:ad5390-5");
MODULE_ALIAS("spi:ad5391-3");
MODULE_ALIAS("spi:ad5391-5");
MODULE_ALIAS("spi:ad5392-3");
MODULE_ALIAS("spi:ad5392-5");
