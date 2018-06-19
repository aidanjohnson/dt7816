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
	{ 0xf9163322, __VMLINUX_SYMBOL_STR(nf_ct_helper_expectfn_register) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x7d8d03b0, __VMLINUX_SYMBOL_STR(nf_nat_sdp_media_hook) },
	{ 0xa22b8e45, __VMLINUX_SYMBOL_STR(nf_nat_sdp_session_hook) },
	{ 0xfbf0fe85, __VMLINUX_SYMBOL_STR(nf_nat_sdp_port_hook) },
	{ 0xda13a7e0, __VMLINUX_SYMBOL_STR(nf_nat_sdp_addr_hook) },
	{ 0xba8e6225, __VMLINUX_SYMBOL_STR(nf_nat_sip_expect_hook) },
	{ 0x227366a3, __VMLINUX_SYMBOL_STR(nf_nat_sip_seq_adjust_hook) },
	{ 0xb6c2efd9, __VMLINUX_SYMBOL_STR(nf_nat_sip_hook) },
	{ 0xc2cdbf1, __VMLINUX_SYMBOL_STR(synchronize_sched) },
	{ 0xb7e0c036, __VMLINUX_SYMBOL_STR(nf_ct_helper_expectfn_unregister) },
	{ 0x7ddf8682, __VMLINUX_SYMBOL_STR(skb_make_writable) },
	{ 0xd6284541, __VMLINUX_SYMBOL_STR(ct_sip_parse_numerical_param) },
	{ 0x636bb445, __VMLINUX_SYMBOL_STR(ct_sip_parse_address_param) },
	{ 0xca6de3f4, __VMLINUX_SYMBOL_STR(ct_sip_parse_request) },
	{ 0x4e830a3e, __VMLINUX_SYMBOL_STR(strnicmp) },
	{ 0x8e2c7ce7, __VMLINUX_SYMBOL_STR(ct_sip_parse_header_uri) },
	{ 0xff692410, __VMLINUX_SYMBOL_STR(nf_ct_seqadj_set) },
	{ 0xe43ae2a2, __VMLINUX_SYMBOL_STR(nf_ct_helper_log) },
	{ 0x8eb03d78, __VMLINUX_SYMBOL_STR(nf_ct_unexpect_related) },
	{ 0xc7be16d9, __VMLINUX_SYMBOL_STR(nf_ct_expect_related_report) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x1acc741c, __VMLINUX_SYMBOL_STR(ct_sip_get_header) },
	{ 0x96ef52b1, __VMLINUX_SYMBOL_STR(ct_sip_get_sdp_header) },
	{ 0xff544df7, __VMLINUX_SYMBOL_STR(nf_nat_mangle_udp_packet) },
	{ 0xc3e403ed, __VMLINUX_SYMBOL_STR(__nf_nat_mangle_tcp_packet) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x2f2af5fb, __VMLINUX_SYMBOL_STR(nf_nat_setup_info) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=nf_conntrack,nf_conntrack_sip,nf_nat";

