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
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x8bf50106, __VMLINUX_SYMBOL_STR(tcp_register_congestion_control) },
	{ 0x63096cbc, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0xb7787265, __VMLINUX_SYMBOL_STR(tcp_unregister_congestion_control) },
	{ 0xf668acb6, __VMLINUX_SYMBOL_STR(tcp_reno_ssthresh) },
	{ 0x70e6dc21, __VMLINUX_SYMBOL_STR(tcp_reno_min_cwnd) },
	{ 0x208c51a1, __VMLINUX_SYMBOL_STR(tcp_slow_start) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x6968bbe6, __VMLINUX_SYMBOL_STR(tcp_reno_cong_avoid) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

