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
	{ 0x2124474, __VMLINUX_SYMBOL_STR(ip_send_check) },
	{ 0x7f76fdb, __VMLINUX_SYMBOL_STR(ip_defrag) },
	{ 0x3b79fa87, __VMLINUX_SYMBOL_STR(nf_unregister_hooks) },
	{ 0x3ff62317, __VMLINUX_SYMBOL_STR(local_bh_disable) },
	{ 0x799aca4, __VMLINUX_SYMBOL_STR(local_bh_enable) },
	{ 0xad44eec5, __VMLINUX_SYMBOL_STR(nf_register_hooks) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

