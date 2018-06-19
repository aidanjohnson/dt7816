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
	{ 0xc2cdbf1, __VMLINUX_SYMBOL_STR(synchronize_sched) },
	{ 0xb7e0c036, __VMLINUX_SYMBOL_STR(nf_ct_helper_expectfn_unregister) },
	{ 0x5e305428, __VMLINUX_SYMBOL_STR(nat_q931_hook) },
	{ 0xfa12779b, __VMLINUX_SYMBOL_STR(nat_callforwarding_hook) },
	{ 0x7a340bc4, __VMLINUX_SYMBOL_STR(nat_h245_hook) },
	{ 0x8014586e, __VMLINUX_SYMBOL_STR(nat_t120_hook) },
	{ 0x7da1df5, __VMLINUX_SYMBOL_STR(nat_rtp_rtcp_hook) },
	{ 0xf29b5363, __VMLINUX_SYMBOL_STR(set_ras_addr_hook) },
	{ 0x1a3a54e6, __VMLINUX_SYMBOL_STR(set_sig_addr_hook) },
	{ 0xd935cd0c, __VMLINUX_SYMBOL_STR(set_h225_addr_hook) },
	{ 0x58567ae9, __VMLINUX_SYMBOL_STR(set_h245_addr_hook) },
	{ 0xf9163322, __VMLINUX_SYMBOL_STR(nf_ct_helper_expectfn_register) },
	{ 0x8eb03d78, __VMLINUX_SYMBOL_STR(nf_ct_unexpect_related) },
	{ 0x4b3926a0, __VMLINUX_SYMBOL_STR(get_h225_addr) },
	{ 0xc7be16d9, __VMLINUX_SYMBOL_STR(nf_ct_expect_related_report) },
	{ 0xff544df7, __VMLINUX_SYMBOL_STR(nf_nat_mangle_udp_packet) },
	{ 0xff924d9c, __VMLINUX_SYMBOL_STR(skb_copy_bits) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xf6ebc03b, __VMLINUX_SYMBOL_STR(net_ratelimit) },
	{ 0xc3e403ed, __VMLINUX_SYMBOL_STR(__nf_nat_mangle_tcp_packet) },
	{ 0x8f6a03a2, __VMLINUX_SYMBOL_STR(nf_nat_follow_master) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x2f2af5fb, __VMLINUX_SYMBOL_STR(nf_nat_setup_info) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=nf_conntrack,nf_conntrack_h323,nf_nat";

