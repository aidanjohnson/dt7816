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
	{ 0xe5e0ca4a, __VMLINUX_SYMBOL_STR(xt_register_targets) },
	{ 0xe113bbbc, __VMLINUX_SYMBOL_STR(csum_partial) },
	{ 0x508cd864, __VMLINUX_SYMBOL_STR(ipv6_skip_exthdr) },
	{ 0x99d704, __VMLINUX_SYMBOL_STR(inet_proto_csum_replace4) },
	{ 0x99bb8806, __VMLINUX_SYMBOL_STR(memmove) },
	{ 0x70b60936, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0xd796878f, __VMLINUX_SYMBOL_STR(pskb_expand_head) },
	{ 0xf6ebc03b, __VMLINUX_SYMBOL_STR(net_ratelimit) },
	{ 0x7ddf8682, __VMLINUX_SYMBOL_STR(skb_make_writable) },
	{ 0xfc8b84a4, __VMLINUX_SYMBOL_STR(init_net) },
	{ 0x6697b84c, __VMLINUX_SYMBOL_STR(nf_afinfo) },
	{ 0x9700966d, __VMLINUX_SYMBOL_STR(dst_release) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=x_tables";

