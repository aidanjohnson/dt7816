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
	{ 0x38e10b5b, __VMLINUX_SYMBOL_STR(tcf_em_unregister) },
	{ 0xdeb65109, __VMLINUX_SYMBOL_STR(tcf_em_register) },
	{ 0xe2fae716, __VMLINUX_SYMBOL_STR(kmemdup) },
	{ 0xc3b062db, __VMLINUX_SYMBOL_STR(ip_set_nfnl_get_byindex) },
	{ 0x5515ca7f, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0x62013789, __VMLINUX_SYMBOL_STR(ip_set_test) },
	{ 0xe937e5af, __VMLINUX_SYMBOL_STR(dev_get_by_index_rcu) },
	{ 0xe40dc473, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0x71bc64b4, __VMLINUX_SYMBOL_STR(__pskb_pull_tail) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x7762965e, __VMLINUX_SYMBOL_STR(ip_set_nfnl_put) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=ip_set";

