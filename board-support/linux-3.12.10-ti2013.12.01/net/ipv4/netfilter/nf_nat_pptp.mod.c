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
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x3ce79294, __VMLINUX_SYMBOL_STR(nf_nat_pptp_hook_expectfn) },
	{ 0xe3947383, __VMLINUX_SYMBOL_STR(nf_nat_pptp_hook_exp_gre) },
	{ 0xbd659da2, __VMLINUX_SYMBOL_STR(nf_nat_pptp_hook_inbound) },
	{ 0x3b8aa562, __VMLINUX_SYMBOL_STR(nf_nat_pptp_hook_outbound) },
	{ 0x636b12c8, __VMLINUX_SYMBOL_STR(nf_nat_need_gre) },
	{ 0xc3e403ed, __VMLINUX_SYMBOL_STR(__nf_nat_mangle_tcp_packet) },
	{ 0x2f2af5fb, __VMLINUX_SYMBOL_STR(nf_nat_setup_info) },
	{ 0xac7f0706, __VMLINUX_SYMBOL_STR(nf_ct_expect_put) },
	{ 0x8eb03d78, __VMLINUX_SYMBOL_STR(nf_ct_unexpect_related) },
	{ 0x648f39c1, __VMLINUX_SYMBOL_STR(nf_ct_expect_find_get) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=nf_conntrack_pptp,nf_nat_proto_gre,nf_nat,nf_conntrack";

