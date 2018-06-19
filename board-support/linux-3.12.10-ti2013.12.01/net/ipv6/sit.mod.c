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
	{ 0x33ba5cd4, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0xe7ea71ad, __VMLINUX_SYMBOL_STR(ip_tunnel_get_stats64) },
	{ 0x1ac8eab4, __VMLINUX_SYMBOL_STR(rtnl_link_register) },
	{ 0x95ae0601, __VMLINUX_SYMBOL_STR(xfrm4_tunnel_register) },
	{ 0x74e0edeb, __VMLINUX_SYMBOL_STR(register_pernet_device) },
	{ 0x60a13e90, __VMLINUX_SYMBOL_STR(rcu_barrier) },
	{ 0x7fa72395, __VMLINUX_SYMBOL_STR(unregister_pernet_device) },
	{ 0xd22151d5, __VMLINUX_SYMBOL_STR(xfrm4_tunnel_deregister) },
	{ 0xab4aa62b, __VMLINUX_SYMBOL_STR(rtnl_link_unregister) },
	{ 0x9c273b30, __VMLINUX_SYMBOL_STR(sock_wfree) },
	{ 0x3d55ba8b, __VMLINUX_SYMBOL_STR(iptunnel_xmit) },
	{ 0x50d6202a, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0x3474c0aa, __VMLINUX_SYMBOL_STR(skb_realloc_headroom) },
	{ 0x5262efe, __VMLINUX_SYMBOL_STR(icmpv6_send) },
	{ 0xd116b762, __VMLINUX_SYMBOL_STR(neigh_destroy) },
	{ 0xd542439, __VMLINUX_SYMBOL_STR(__ipv6_addr_type) },
	{ 0x240eefdf, __VMLINUX_SYMBOL_STR(ip_tunnel_xmit) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xc6cbbc89, __VMLINUX_SYMBOL_STR(capable) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xbc10dd97, __VMLINUX_SYMBOL_STR(__put_user_4) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xd2936c14, __VMLINUX_SYMBOL_STR(ns_capable) },
	{ 0x67c2fa54, __VMLINUX_SYMBOL_STR(__copy_to_user) },
	{ 0xfbc74f64, __VMLINUX_SYMBOL_STR(__copy_from_user) },
	{ 0xa75312bc, __VMLINUX_SYMBOL_STR(call_rcu_sched) },
	{ 0x9469482, __VMLINUX_SYMBOL_STR(kfree_call_rcu) },
	{ 0x6b2dc060, __VMLINUX_SYMBOL_STR(dump_stack) },
	{ 0x85670f1d, __VMLINUX_SYMBOL_STR(rtnl_is_locked) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0xc24d24cf, __VMLINUX_SYMBOL_STR(register_netdevice) },
	{ 0xd87c2198, __VMLINUX_SYMBOL_STR(register_netdev) },
	{ 0x50c89f23, __VMLINUX_SYMBOL_STR(__alloc_percpu) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
	{ 0xfb4628f9, __VMLINUX_SYMBOL_STR(alloc_netdev_mqs) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xf1db1704, __VMLINUX_SYMBOL_STR(nla_memcpy) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x6aa0ac2d, __VMLINUX_SYMBOL_STR(netdev_state_change) },
	{ 0x609f1c7e, __VMLINUX_SYMBOL_STR(synchronize_net) },
	{ 0x5fe006df, __VMLINUX_SYMBOL_STR(__dev_get_by_index) },
	{ 0x9700966d, __VMLINUX_SYMBOL_STR(dst_release) },
	{ 0xddde3c32, __VMLINUX_SYMBOL_STR(ip_route_output_flow) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x63096cbc, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0xfcd5641, __VMLINUX_SYMBOL_STR(netif_rx) },
	{ 0xcdf70e4c, __VMLINUX_SYMBOL_STR(skb_scrub_packet) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x7210b37c, __VMLINUX_SYMBOL_STR(ipv6_chk_custom_prefix) },
	{ 0xf6ebc03b, __VMLINUX_SYMBOL_STR(net_ratelimit) },
	{ 0x2a644546, __VMLINUX_SYMBOL_STR(ipv6_chk_prefix) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x4a6ac572, __VMLINUX_SYMBOL_STR(ipv4_redirect) },
	{ 0xe158c29e, __VMLINUX_SYMBOL_STR(ipv4_update_pmtu) },
	{ 0x6599a5b, __VMLINUX_SYMBOL_STR(iptunnel_pull_header) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0xf93f1ccc, __VMLINUX_SYMBOL_STR(ip_tunnel_rcv) },
	{ 0x275de30d, __VMLINUX_SYMBOL_STR(__xfrm_policy_check) },
	{ 0xe94f1e83, __VMLINUX_SYMBOL_STR(free_netdev) },
	{ 0xc9ec4e21, __VMLINUX_SYMBOL_STR(free_percpu) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x6e720ff2, __VMLINUX_SYMBOL_STR(rtnl_unlock) },
	{ 0x9fdecc31, __VMLINUX_SYMBOL_STR(unregister_netdevice_many) },
	{ 0xfb3dec2b, __VMLINUX_SYMBOL_STR(unregister_netdevice_queue) },
	{ 0xc7a4fbed, __VMLINUX_SYMBOL_STR(rtnl_lock) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=ip_tunnel,tunnel4";

