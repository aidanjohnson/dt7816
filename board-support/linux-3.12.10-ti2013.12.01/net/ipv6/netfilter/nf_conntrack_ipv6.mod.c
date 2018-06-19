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
	{ 0x609f1c7e, __VMLINUX_SYMBOL_STR(synchronize_net) },
	{ 0x9e5f3375, __VMLINUX_SYMBOL_STR(nf_conntrack_in) },
	{ 0x67c2fa54, __VMLINUX_SYMBOL_STR(__copy_to_user) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xacf3e3d1, __VMLINUX_SYMBOL_STR(__nf_ct_refresh_acct) },
	{ 0xc781a541, __VMLINUX_SYMBOL_STR(nf_ct_l4proto_pernet_register) },
	{ 0x500718de, __VMLINUX_SYMBOL_STR(nf_ct_get_tuplepr) },
	{ 0x6eb85693, __VMLINUX_SYMBOL_STR(nf_defrag_ipv6_enable) },
	{ 0x2247cba2, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0xe2fae716, __VMLINUX_SYMBOL_STR(kmemdup) },
	{ 0x6fa9fb8, __VMLINUX_SYMBOL_STR(nf_ct_deliver_cached_events) },
	{ 0xea054b22, __VMLINUX_SYMBOL_STR(nla_policy_len) },
	{ 0x92e7a4b1, __VMLINUX_SYMBOL_STR(nf_log_packet) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x56111996, __VMLINUX_SYMBOL_STR(nf_ct_l4proto_unregister) },
	{ 0xdc8cb9d7, __VMLINUX_SYMBOL_STR(unregister_pernet_subsys) },
	{ 0xde9b0f19, __VMLINUX_SYMBOL_STR(nf_ct_invert_tuple) },
	{ 0x128179d3, __VMLINUX_SYMBOL_STR(__nf_conntrack_confirm) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x2398a526, __VMLINUX_SYMBOL_STR(nf_ct_l4proto_pernet_unregister) },
	{ 0x63096cbc, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0xec44c5ae, __VMLINUX_SYMBOL_STR(nf_ct_l4proto_register) },
	{ 0x29759942, __VMLINUX_SYMBOL_STR(nf_ct_l3proto_unregister) },
	{ 0x3b79fa87, __VMLINUX_SYMBOL_STR(nf_unregister_hooks) },
	{ 0x508cd864, __VMLINUX_SYMBOL_STR(ipv6_skip_exthdr) },
	{ 0x6e224a7a, __VMLINUX_SYMBOL_STR(need_conntrack) },
	{ 0xa45fc51b, __VMLINUX_SYMBOL_STR(nf_unregister_sockopt) },
	{ 0x5ad2863d, __VMLINUX_SYMBOL_STR(nf_conntrack_l4proto_tcp6) },
	{ 0xaabc8dc9, __VMLINUX_SYMBOL_STR(nf_ct_l3proto_pernet_register) },
	{ 0xd7cb77a9, __VMLINUX_SYMBOL_STR(register_pernet_subsys) },
	{ 0x2a18c74, __VMLINUX_SYMBOL_STR(nf_conntrack_destroy) },
	{ 0xa33f3090, __VMLINUX_SYMBOL_STR(nf_ct_seq_adjust) },
	{ 0xf6ebc03b, __VMLINUX_SYMBOL_STR(net_ratelimit) },
	{ 0x7cf6ca92, __VMLINUX_SYMBOL_STR(nf_conntrack_untracked) },
	{ 0xad44eec5, __VMLINUX_SYMBOL_STR(nf_register_hooks) },
	{ 0x438b9f22, __VMLINUX_SYMBOL_STR(nf_ct_l3proto_pernet_unregister) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x39888fb2, __VMLINUX_SYMBOL_STR(nf_register_sockopt) },
	{ 0x9ae13ada, __VMLINUX_SYMBOL_STR(nf_conntrack_l4proto_udp6) },
	{ 0x9cf1b46, __VMLINUX_SYMBOL_STR(proc_dointvec_jiffies) },
	{ 0xff924d9c, __VMLINUX_SYMBOL_STR(skb_copy_bits) },
	{ 0x92819969, __VMLINUX_SYMBOL_STR(nf_ip6_checksum) },
	{ 0xd542439, __VMLINUX_SYMBOL_STR(__ipv6_addr_type) },
	{ 0x784749d4, __VMLINUX_SYMBOL_STR(nf_ct_l3proto_register) },
	{ 0xbc9a4f1, __VMLINUX_SYMBOL_STR(nf_conntrack_find_get) },
	{ 0x6fd2e9c, __VMLINUX_SYMBOL_STR(__nf_ct_l4proto_find) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=nf_conntrack,nf_defrag_ipv6";

