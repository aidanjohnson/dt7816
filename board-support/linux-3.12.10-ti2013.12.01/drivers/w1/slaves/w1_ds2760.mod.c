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
	{ 0x2c997392, __VMLINUX_SYMBOL_STR(w1_reset_select_slave) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x5b72009f, __VMLINUX_SYMBOL_STR(ida_simple_get) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x20df2681, __VMLINUX_SYMBOL_STR(ida_simple_remove) },
	{ 0xd727a63c, __VMLINUX_SYMBOL_STR(platform_device_alloc) },
	{ 0x4fb7d5a2, __VMLINUX_SYMBOL_STR(platform_device_add) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xbadfd0e, __VMLINUX_SYMBOL_STR(platform_device_unregister) },
	{ 0xd932221c, __VMLINUX_SYMBOL_STR(w1_write_block) },
	{ 0xe9e89624, __VMLINUX_SYMBOL_STR(w1_write_8) },
	{ 0xe1d05a93, __VMLINUX_SYMBOL_STR(w1_read_block) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x8e5c580a, __VMLINUX_SYMBOL_STR(ida_init) },
	{ 0xeb9e7cdd, __VMLINUX_SYMBOL_STR(ida_destroy) },
	{ 0x9fb12980, __VMLINUX_SYMBOL_STR(w1_register_family) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0xb3f38dbc, __VMLINUX_SYMBOL_STR(platform_device_put) },
	{ 0x47581c02, __VMLINUX_SYMBOL_STR(w1_unregister_family) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=wire";

