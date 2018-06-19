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
	{ 0x511e82ae, __VMLINUX_SYMBOL_STR(nf_nat_amanda_hook) },
	{ 0xc2cdbf1, __VMLINUX_SYMBOL_STR(synchronize_sched) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x8f6a03a2, __VMLINUX_SYMBOL_STR(nf_nat_follow_master) },
	{ 0xff544df7, __VMLINUX_SYMBOL_STR(nf_nat_mangle_udp_packet) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x8eb03d78, __VMLINUX_SYMBOL_STR(nf_ct_unexpect_related) },
	{ 0xe43ae2a2, __VMLINUX_SYMBOL_STR(nf_ct_helper_log) },
	{ 0xc7be16d9, __VMLINUX_SYMBOL_STR(nf_ct_expect_related_report) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=nf_conntrack_amanda,nf_nat,nf_conntrack";

