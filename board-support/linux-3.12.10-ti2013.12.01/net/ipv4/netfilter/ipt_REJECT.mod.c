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
	{ 0x69ba683, __VMLINUX_SYMBOL_STR(xt_unregister_target) },
	{ 0x5882e4bf, __VMLINUX_SYMBOL_STR(xt_register_target) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xf6388c56, __VMLINUX_SYMBOL_STR(sysctl_ip_default_ttl) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x83e60378, __VMLINUX_SYMBOL_STR(ip_local_out) },
	{ 0xc11126ee, __VMLINUX_SYMBOL_STR(dev_queue_xmit) },
	{ 0x2124474, __VMLINUX_SYMBOL_STR(ip_send_check) },
	{ 0x8503b735, __VMLINUX_SYMBOL_STR(nf_ct_attach) },
	{ 0xa06af5d5, __VMLINUX_SYMBOL_STR(ip_route_me_harder) },
	{ 0xad6d6409, __VMLINUX_SYMBOL_STR(__skb_dst_set_noref) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x70b60936, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0xc3e596f0, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0x5ddfd92b, __VMLINUX_SYMBOL_STR(nf_ip_checksum) },
	{ 0xff924d9c, __VMLINUX_SYMBOL_STR(skb_copy_bits) },
	{ 0xaa51f5a3, __VMLINUX_SYMBOL_STR(icmp_send) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=x_tables";

