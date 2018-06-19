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
	{ 0x6eb85693, __VMLINUX_SYMBOL_STR(nf_defrag_ipv6_enable) },
	{ 0x6b6c3d10, __VMLINUX_SYMBOL_STR(nf_defrag_ipv4_enable) },
	{ 0xf2e295ed, __VMLINUX_SYMBOL_STR(__inet_lookup_listener) },
	{ 0xfcb56d2a, __VMLINUX_SYMBOL_STR(udp4_lib_lookup) },
	{ 0xa624c2a0, __VMLINUX_SYMBOL_STR(__inet_lookup_established) },
	{ 0x57e82f57, __VMLINUX_SYMBOL_STR(tcp_death_row) },
	{ 0xf265ac6, __VMLINUX_SYMBOL_STR(tcp_hashinfo) },
	{ 0x1ad320f4, __VMLINUX_SYMBOL_STR(inet_twsk_deschedule) },
	{ 0x96645a56, __VMLINUX_SYMBOL_STR(inet6_lookup_listener) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x7a984958, __VMLINUX_SYMBOL_STR(udp6_lib_lookup) },
	{ 0xb044ede7, __VMLINUX_SYMBOL_STR(__inet6_lookup_established) },
	{ 0xff924d9c, __VMLINUX_SYMBOL_STR(skb_copy_bits) },
	{ 0xd4182c5e, __VMLINUX_SYMBOL_STR(ipv6_find_hdr) },
	{ 0x9f1ec650, __VMLINUX_SYMBOL_STR(inet_twsk_put) },
	{ 0xaa0675de, __VMLINUX_SYMBOL_STR(sk_free) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x47fee741, __VMLINUX_SYMBOL_STR(sock_edemux) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=x_tables,nf_defrag_ipv6,nf_defrag_ipv4";

