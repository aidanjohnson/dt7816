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
	{ 0x6217213b, __VMLINUX_SYMBOL_STR(adt7x10_dev_pm_ops) },
	{ 0xa731ccf6, __VMLINUX_SYMBOL_STR(i2c_del_driver) },
	{ 0xe25a742c, __VMLINUX_SYMBOL_STR(i2c_register_driver) },
	{ 0xdd384ca3, __VMLINUX_SYMBOL_STR(i2c_smbus_read_byte_data) },
	{ 0x69d0f0ae, __VMLINUX_SYMBOL_STR(i2c_smbus_write_byte_data) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x50a418b, __VMLINUX_SYMBOL_STR(i2c_smbus_read_word_data) },
	{ 0xb4cd6ce6, __VMLINUX_SYMBOL_STR(i2c_smbus_write_word_data) },
	{ 0xe2495feb, __VMLINUX_SYMBOL_STR(adt7x10_probe) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xbd79287d, __VMLINUX_SYMBOL_STR(adt7x10_remove) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=adt7x10";

MODULE_ALIAS("i2c:adt7410");
MODULE_ALIAS("i2c:adt7420");
