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
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xa120d33c, __VMLINUX_SYMBOL_STR(tty_unregister_ldisc) },
	{ 0xadd8c681, __VMLINUX_SYMBOL_STR(tty_register_ldisc) },
	{ 0xd9b7516a, __VMLINUX_SYMBOL_STR(n_tty_inherit_ops) },
	{ 0xa50e253d, __VMLINUX_SYMBOL_STR(pps_event) },
	{ 0x46608fa0, __VMLINUX_SYMBOL_STR(getnstimeofday) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xede50073, __VMLINUX_SYMBOL_STR(pps_register_source) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x78a3b004, __VMLINUX_SYMBOL_STR(pps_unregister_source) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x42dcd705, __VMLINUX_SYMBOL_STR(pps_lookup_dev) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

