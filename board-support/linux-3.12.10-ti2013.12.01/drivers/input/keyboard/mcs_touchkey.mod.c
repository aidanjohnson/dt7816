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
	{ 0xa731ccf6, __VMLINUX_SYMBOL_STR(i2c_del_driver) },
	{ 0xe25a742c, __VMLINUX_SYMBOL_STR(i2c_register_driver) },
	{ 0xb79a5aed, __VMLINUX_SYMBOL_STR(input_event) },
	{ 0x55e25a41, __VMLINUX_SYMBOL_STR(input_free_device) },
	{ 0xaa58a0ae, __VMLINUX_SYMBOL_STR(input_register_device) },
	{ 0xd6b8e852, __VMLINUX_SYMBOL_STR(request_threaded_irq) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0xfc88fbae, __VMLINUX_SYMBOL_STR(input_set_capability) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0xdd384ca3, __VMLINUX_SYMBOL_STR(i2c_smbus_read_byte_data) },
	{ 0x26a6901f, __VMLINUX_SYMBOL_STR(input_allocate_device) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x657c72c4, __VMLINUX_SYMBOL_STR(input_unregister_device) },
	{ 0xf20dabd8, __VMLINUX_SYMBOL_STR(free_irq) },
	{ 0x3ce4ca6f, __VMLINUX_SYMBOL_STR(disable_irq) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xfcec0987, __VMLINUX_SYMBOL_STR(enable_irq) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("i2c:mcs5000_touchkey");
MODULE_ALIAS("i2c:mcs5080_touchkey");
