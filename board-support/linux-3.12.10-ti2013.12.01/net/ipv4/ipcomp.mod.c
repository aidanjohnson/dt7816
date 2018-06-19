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
	{ 0x9125c5cd, __VMLINUX_SYMBOL_STR(xfrm4_rcv) },
	{ 0xc90566ed, __VMLINUX_SYMBOL_STR(ipcomp_output) },
	{ 0xe290fc65, __VMLINUX_SYMBOL_STR(ipcomp_input) },
	{ 0x8aaa7470, __VMLINUX_SYMBOL_STR(ipcomp_destroy) },
	{ 0x1ecbb142, __VMLINUX_SYMBOL_STR(inet_del_protocol) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xfb5c58e, __VMLINUX_SYMBOL_STR(xfrm_unregister_type) },
	{ 0xf4406e45, __VMLINUX_SYMBOL_STR(inet_add_protocol) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x3cb3dd34, __VMLINUX_SYMBOL_STR(xfrm_register_type) },
	{ 0xbb2e061f, __VMLINUX_SYMBOL_STR(xfrm_state_insert) },
	{ 0x9ec0599f, __VMLINUX_SYMBOL_STR(xfrm_init_state) },
	{ 0x1c26a519, __VMLINUX_SYMBOL_STR(xfrm_state_alloc) },
	{ 0x92edb159, __VMLINUX_SYMBOL_STR(ipcomp_init_state) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x95c68e4a, __VMLINUX_SYMBOL_STR(__xfrm_state_destroy) },
	{ 0x4a6ac572, __VMLINUX_SYMBOL_STR(ipv4_redirect) },
	{ 0xe158c29e, __VMLINUX_SYMBOL_STR(ipv4_update_pmtu) },
	{ 0x643f723d, __VMLINUX_SYMBOL_STR(xfrm_state_lookup) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=xfrm_ipcomp";

