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
	{ 0xa4c7fa32, __VMLINUX_SYMBOL_STR(ethtool_op_get_link) },
	{ 0x5471c290, __VMLINUX_SYMBOL_STR(eth_mac_addr) },
	{ 0xab4aa62b, __VMLINUX_SYMBOL_STR(rtnl_link_unregister) },
	{ 0x1ac8eab4, __VMLINUX_SYMBOL_STR(rtnl_link_register) },
	{ 0xc9ec4e21, __VMLINUX_SYMBOL_STR(free_percpu) },
	{ 0x50c89f23, __VMLINUX_SYMBOL_STR(__alloc_percpu) },
	{ 0x4a8342f8, __VMLINUX_SYMBOL_STR(netif_carrier_on) },
	{ 0x99f7a74d, __VMLINUX_SYMBOL_STR(dev_forward_skb) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x1176e07f, __VMLINUX_SYMBOL_STR(__per_cpu_offset) },
	{ 0xfe7c4287, __VMLINUX_SYMBOL_STR(nr_cpu_ids) },
	{ 0x7c62d042, __VMLINUX_SYMBOL_STR(cpu_possible_mask) },
	{ 0xd3f57a2, __VMLINUX_SYMBOL_STR(_find_next_bit_le) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0xf1ef0fc0, __VMLINUX_SYMBOL_STR(ether_setup) },
	{ 0xd8c72cf0, __VMLINUX_SYMBOL_STR(ifla_policy) },
	{ 0xe94f1e83, __VMLINUX_SYMBOL_STR(free_netdev) },
	{ 0x56bc9ee5, __VMLINUX_SYMBOL_STR(rtnl_configure_link) },
	{ 0xc24d24cf, __VMLINUX_SYMBOL_STR(register_netdevice) },
	{ 0x79aa04a2, __VMLINUX_SYMBOL_STR(get_random_bytes) },
	{ 0x53b86f03, __VMLINUX_SYMBOL_STR(__put_net) },
	{ 0x66779563, __VMLINUX_SYMBOL_STR(rtnl_create_link) },
	{ 0xb807ac7, __VMLINUX_SYMBOL_STR(rtnl_link_get_net) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x6cdc5c6b, __VMLINUX_SYMBOL_STR(nla_strlcpy) },
	{ 0x4f391d0e, __VMLINUX_SYMBOL_STR(nla_parse) },
	{ 0x94ee05c8, __VMLINUX_SYMBOL_STR(netif_carrier_off) },
	{ 0xfb3dec2b, __VMLINUX_SYMBOL_STR(unregister_netdevice_queue) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

