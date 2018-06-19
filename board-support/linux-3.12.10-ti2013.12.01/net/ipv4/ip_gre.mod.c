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
	{ 0xe13b800c, __VMLINUX_SYMBOL_STR(ip_tunnel_dellink) },
	{ 0x33ba5cd4, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0xd63271fb, __VMLINUX_SYMBOL_STR(eth_validate_addr) },
	{ 0x5471c290, __VMLINUX_SYMBOL_STR(eth_mac_addr) },
	{ 0xe7ea71ad, __VMLINUX_SYMBOL_STR(ip_tunnel_get_stats64) },
	{ 0x50de6e5f, __VMLINUX_SYMBOL_STR(ip_tunnel_change_mtu) },
	{ 0xa32220b8, __VMLINUX_SYMBOL_STR(ip_tunnel_uninit) },
	{ 0x7fa72395, __VMLINUX_SYMBOL_STR(unregister_pernet_device) },
	{ 0xbf74f2af, __VMLINUX_SYMBOL_STR(gre_cisco_unregister) },
	{ 0xab4aa62b, __VMLINUX_SYMBOL_STR(rtnl_link_unregister) },
	{ 0x1ac8eab4, __VMLINUX_SYMBOL_STR(rtnl_link_register) },
	{ 0x37464ff4, __VMLINUX_SYMBOL_STR(gre_cisco_register) },
	{ 0x74e0edeb, __VMLINUX_SYMBOL_STR(register_pernet_device) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x8f8dce73, __VMLINUX_SYMBOL_STR(ip_mc_dec_group) },
	{ 0x6592469f, __VMLINUX_SYMBOL_STR(inetdev_by_index) },
	{ 0x808001dc, __VMLINUX_SYMBOL_STR(ip_tunnel_newlink) },
	{ 0xaf56f3c1, __VMLINUX_SYMBOL_STR(ip_tunnel_changelink) },
	{ 0xc4f6646f, __VMLINUX_SYMBOL_STR(ip_tunnel_delete_net) },
	{ 0xf1ef0fc0, __VMLINUX_SYMBOL_STR(ether_setup) },
	{ 0x63096cbc, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0x5515ca7f, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0x37e693b1, __VMLINUX_SYMBOL_STR(ip_tunnel_init) },
	{ 0xa67be3d2, __VMLINUX_SYMBOL_STR(ip_mc_inc_group) },
	{ 0x9700966d, __VMLINUX_SYMBOL_STR(dst_release) },
	{ 0xddde3c32, __VMLINUX_SYMBOL_STR(ip_route_output_flow) },
	{ 0x50d6202a, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0xd796878f, __VMLINUX_SYMBOL_STR(pskb_expand_head) },
	{ 0xe40dc473, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0xd013e0bb, __VMLINUX_SYMBOL_STR(gre_handle_offloads) },
	{ 0x240eefdf, __VMLINUX_SYMBOL_STR(ip_tunnel_xmit) },
	{ 0x1863813f, __VMLINUX_SYMBOL_STR(gre_build_header) },
	{ 0x67c2fa54, __VMLINUX_SYMBOL_STR(__copy_to_user) },
	{ 0x4c174417, __VMLINUX_SYMBOL_STR(ip_tunnel_ioctl) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xfbc74f64, __VMLINUX_SYMBOL_STR(__copy_from_user) },
	{ 0xc2ad9134, __VMLINUX_SYMBOL_STR(ip_tunnel_setup) },
	{ 0xf93f1ccc, __VMLINUX_SYMBOL_STR(ip_tunnel_rcv) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x44dfd99f, __VMLINUX_SYMBOL_STR(ip_tunnel_lookup) },
	{ 0x91e5ce7c, __VMLINUX_SYMBOL_STR(ip_tunnel_init_net) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=ip_tunnel,gre";

