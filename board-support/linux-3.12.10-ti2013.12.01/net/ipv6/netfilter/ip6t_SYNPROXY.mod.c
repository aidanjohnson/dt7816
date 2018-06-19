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
	{ 0x69ba683, __VMLINUX_SYMBOL_STR(xt_unregister_target) },
	{ 0x3b79fa87, __VMLINUX_SYMBOL_STR(nf_unregister_hooks) },
	{ 0x5882e4bf, __VMLINUX_SYMBOL_STR(xt_register_target) },
	{ 0xad44eec5, __VMLINUX_SYMBOL_STR(nf_register_hooks) },
	{ 0x1ce85ab0, __VMLINUX_SYMBOL_STR(synproxy_tstamp_adjust) },
	{ 0x50d6202a, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0xb33c2561, __VMLINUX_SYMBOL_STR(nf_ct_seqadj_init) },
	{ 0x508cd864, __VMLINUX_SYMBOL_STR(ipv6_skip_exthdr) },
	{ 0xef7db50c, __VMLINUX_SYMBOL_STR(synproxy_net_id) },
	{ 0x883c2740, __VMLINUX_SYMBOL_STR(__cookie_v6_init_sequence) },
	{ 0x90298227, __VMLINUX_SYMBOL_STR(synproxy_init_timestamp_cookie) },
	{ 0xfbb9fbe9, __VMLINUX_SYMBOL_STR(synproxy_parse_options) },
	{ 0xff924d9c, __VMLINUX_SYMBOL_STR(skb_copy_bits) },
	{ 0x92819969, __VMLINUX_SYMBOL_STR(nf_ip6_checksum) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x8841d39b, __VMLINUX_SYMBOL_STR(synproxy_build_options) },
	{ 0xc3e596f0, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0xb42e336a, __VMLINUX_SYMBOL_STR(synproxy_options_size) },
	{ 0x11a006b5, __VMLINUX_SYMBOL_STR(synproxy_check_timestamp_cookie) },
	{ 0x9973add9, __VMLINUX_SYMBOL_STR(__cookie_v6_check) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x1c7674e8, __VMLINUX_SYMBOL_STR(ip6_local_out) },
	{ 0x50fd4505, __VMLINUX_SYMBOL_STR(xfrm_lookup) },
	{ 0x9700966d, __VMLINUX_SYMBOL_STR(dst_release) },
	{ 0x25f1c0bb, __VMLINUX_SYMBOL_STR(ip6_route_output) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x44da5d0f, __VMLINUX_SYMBOL_STR(__csum_ipv6_magic) },
	{ 0x78f9b710, __VMLINUX_SYMBOL_STR(nf_ct_l3proto_try_module_get) },
	{ 0xb602c57e, __VMLINUX_SYMBOL_STR(nf_ct_l3proto_module_put) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x70b60936, __VMLINUX_SYMBOL_STR(skb_put) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=x_tables,nf_synproxy_core,nf_conntrack";

