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
	{ 0x1a0c7788, __VMLINUX_SYMBOL_STR(xt_unregister_matches) },
	{ 0xd55169c1, __VMLINUX_SYMBOL_STR(xt_register_matches) },
	{ 0x6eb85693, __VMLINUX_SYMBOL_STR(nf_defrag_ipv6_enable) },
	{ 0x6b6c3d10, __VMLINUX_SYMBOL_STR(nf_defrag_ipv4_enable) },
	{ 0xfcb56d2a, __VMLINUX_SYMBOL_STR(udp4_lib_lookup) },
	{ 0xf2e295ed, __VMLINUX_SYMBOL_STR(__inet_lookup_listener) },
	{ 0xa624c2a0, __VMLINUX_SYMBOL_STR(__inet_lookup_established) },
	{ 0xf265ac6, __VMLINUX_SYMBOL_STR(tcp_hashinfo) },
	{ 0x7a984958, __VMLINUX_SYMBOL_STR(udp6_lib_lookup) },
	{ 0x7ad402ee, __VMLINUX_SYMBOL_STR(inet6_lookup) },
	{ 0x508cd864, __VMLINUX_SYMBOL_STR(ipv6_skip_exthdr) },
	{ 0xff924d9c, __VMLINUX_SYMBOL_STR(skb_copy_bits) },
	{ 0xd4182c5e, __VMLINUX_SYMBOL_STR(ipv6_find_hdr) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xaa0675de, __VMLINUX_SYMBOL_STR(sk_free) },
	{ 0x9f1ec650, __VMLINUX_SYMBOL_STR(inet_twsk_put) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=x_tables,nf_defrag_ipv6,nf_defrag_ipv4";

