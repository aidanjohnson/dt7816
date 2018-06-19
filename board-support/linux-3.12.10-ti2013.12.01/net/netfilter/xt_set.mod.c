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
	{ 0xea2f6e60, __VMLINUX_SYMBOL_STR(xt_unregister_targets) },
	{ 0x1a0c7788, __VMLINUX_SYMBOL_STR(xt_unregister_matches) },
	{ 0xe5e0ca4a, __VMLINUX_SYMBOL_STR(xt_register_targets) },
	{ 0xd55169c1, __VMLINUX_SYMBOL_STR(xt_register_matches) },
	{ 0x62013789, __VMLINUX_SYMBOL_STR(ip_set_test) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xc3b062db, __VMLINUX_SYMBOL_STR(ip_set_nfnl_get_byindex) },
	{ 0x7762965e, __VMLINUX_SYMBOL_STR(ip_set_nfnl_put) },
	{ 0xc4634db4, __VMLINUX_SYMBOL_STR(ip_set_del) },
	{ 0x27b659a5, __VMLINUX_SYMBOL_STR(ip_set_add) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=x_tables,ip_set";

