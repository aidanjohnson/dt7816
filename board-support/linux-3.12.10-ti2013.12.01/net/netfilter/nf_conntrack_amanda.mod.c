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
	{ 0x75288bf1, __VMLINUX_SYMBOL_STR(nf_conntrack_helper_register) },
	{ 0xacf3e3d1, __VMLINUX_SYMBOL_STR(__nf_ct_refresh_acct) },
	{ 0xa6bbcbae, __VMLINUX_SYMBOL_STR(nf_conntrack_helper_unregister) },
	{ 0x20000329, __VMLINUX_SYMBOL_STR(simple_strtoul) },
	{ 0x4f6f139b, __VMLINUX_SYMBOL_STR(nf_ct_expect_init) },
	{ 0xa814bd1d, __VMLINUX_SYMBOL_STR(textsearch_prepare) },
	{ 0x289f03ae, __VMLINUX_SYMBOL_STR(skb_find_text) },
	{ 0x5d41c87c, __VMLINUX_SYMBOL_STR(param_ops_charp) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xac7f0706, __VMLINUX_SYMBOL_STR(nf_ct_expect_put) },
	{ 0xe949bfe9, __VMLINUX_SYMBOL_STR(nf_ct_expect_alloc) },
	{ 0xc7be16d9, __VMLINUX_SYMBOL_STR(nf_ct_expect_related_report) },
	{ 0xe43ae2a2, __VMLINUX_SYMBOL_STR(nf_ct_helper_log) },
	{ 0x454ba61e, __VMLINUX_SYMBOL_STR(textsearch_destroy) },
	{ 0xf6ebc03b, __VMLINUX_SYMBOL_STR(net_ratelimit) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x47c8baf4, __VMLINUX_SYMBOL_STR(param_ops_uint) },
	{ 0xff924d9c, __VMLINUX_SYMBOL_STR(skb_copy_bits) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=nf_conntrack";

