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
	{ 0x1e75f0d, __VMLINUX_SYMBOL_STR(pmbus_do_remove) },
	{ 0xa731ccf6, __VMLINUX_SYMBOL_STR(i2c_del_driver) },
	{ 0xe25a742c, __VMLINUX_SYMBOL_STR(i2c_register_driver) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x792af75f, __VMLINUX_SYMBOL_STR(pmbus_read_byte_data) },
	{ 0xd3a7e7ea, __VMLINUX_SYMBOL_STR(pmbus_read_word_data) },
	{ 0x23d59fd7, __VMLINUX_SYMBOL_STR(pmbus_get_driver_info) },
	{ 0x9f2c9cc6, __VMLINUX_SYMBOL_STR(pmbus_write_byte) },
	{ 0x2b9f9d6d, __VMLINUX_SYMBOL_STR(pmbus_clear_cache) },
	{ 0x386efbb8, __VMLINUX_SYMBOL_STR(pmbus_write_word_data) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xaa6a392f, __VMLINUX_SYMBOL_STR(pmbus_do_probe) },
	{ 0xdd384ca3, __VMLINUX_SYMBOL_STR(i2c_smbus_read_byte_data) },
	{ 0x3d268c44, __VMLINUX_SYMBOL_STR(devm_kzalloc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=pmbus_core";

MODULE_ALIAS("i2c:lm25056");
MODULE_ALIAS("i2c:lm25066");
MODULE_ALIAS("i2c:lm5064");
MODULE_ALIAS("i2c:lm5066");
