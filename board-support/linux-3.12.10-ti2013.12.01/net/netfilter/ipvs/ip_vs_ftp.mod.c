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
	{ 0xafad493b, __VMLINUX_SYMBOL_STR(param_ops_ushort) },
	{ 0x20b2bb2d, __VMLINUX_SYMBOL_STR(param_array_ops) },
	{ 0xdc8cb9d7, __VMLINUX_SYMBOL_STR(unregister_pernet_subsys) },
	{ 0xd7cb77a9, __VMLINUX_SYMBOL_STR(register_pernet_subsys) },
	{ 0x926d1fa3, __VMLINUX_SYMBOL_STR(ip_vs_conn_in_get) },
	{ 0x7ddf8682, __VMLINUX_SYMBOL_STR(skb_make_writable) },
	{ 0x31979b4f, __VMLINUX_SYMBOL_STR(ip_vs_conn_put) },
	{ 0x2ebfdb7c, __VMLINUX_SYMBOL_STR(ip_vs_tcp_conn_listen) },
	{ 0x41dc5c2a, __VMLINUX_SYMBOL_STR(ip_vs_nfct_expect_related) },
	{ 0xc3e403ed, __VMLINUX_SYMBOL_STR(__nf_nat_mangle_tcp_packet) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xd157f4b9, __VMLINUX_SYMBOL_STR(ip_vs_conn_new) },
	{ 0x6feb5387, __VMLINUX_SYMBOL_STR(ip_vs_conn_out_get) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x4e830a3e, __VMLINUX_SYMBOL_STR(strnicmp) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x8a466b54, __VMLINUX_SYMBOL_STR(register_ip_vs_app_inc) },
	{ 0x52ab3f2d, __VMLINUX_SYMBOL_STR(register_ip_vs_app) },
	{ 0x2875c6fb, __VMLINUX_SYMBOL_STR(unregister_ip_vs_app) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=ip_vs,nf_nat";

