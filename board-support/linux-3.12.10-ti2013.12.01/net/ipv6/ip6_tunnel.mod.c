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
	{ 0xc24d24cf, __VMLINUX_SYMBOL_STR(register_netdevice) },
	{ 0x609f1c7e, __VMLINUX_SYMBOL_STR(synchronize_net) },
	{ 0x5262efe, __VMLINUX_SYMBOL_STR(icmpv6_send) },
	{ 0x2d497b73, __VMLINUX_SYMBOL_STR(xfrm6_tunnel_deregister) },
	{ 0x74e0edeb, __VMLINUX_SYMBOL_STR(register_pernet_device) },
	{ 0xfbc74f64, __VMLINUX_SYMBOL_STR(__copy_from_user) },
	{ 0x67c2fa54, __VMLINUX_SYMBOL_STR(__copy_to_user) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x369de012, __VMLINUX_SYMBOL_STR(ipv6_chk_addr) },
	{ 0x79aa04a2, __VMLINUX_SYMBOL_STR(get_random_bytes) },
	{ 0xc7a4fbed, __VMLINUX_SYMBOL_STR(rtnl_lock) },
	{ 0xad6d6409, __VMLINUX_SYMBOL_STR(__skb_dst_set_noref) },
	{ 0x9700966d, __VMLINUX_SYMBOL_STR(dst_release) },
	{ 0xaa51f5a3, __VMLINUX_SYMBOL_STR(icmp_send) },
	{ 0xb2038f57, __VMLINUX_SYMBOL_STR(skb_clone) },
	{ 0xd3f57a2, __VMLINUX_SYMBOL_STR(_find_next_bit_le) },
	{ 0x50c89f23, __VMLINUX_SYMBOL_STR(__alloc_percpu) },
	{ 0x33ba5cd4, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x3474c0aa, __VMLINUX_SYMBOL_STR(skb_realloc_headroom) },
	{ 0xcdf70e4c, __VMLINUX_SYMBOL_STR(skb_scrub_packet) },
	{ 0xc9ec4e21, __VMLINUX_SYMBOL_STR(free_percpu) },
	{ 0xfcd5641, __VMLINUX_SYMBOL_STR(netif_rx) },
	{ 0x71bc64b4, __VMLINUX_SYMBOL_STR(__pskb_pull_tail) },
	{ 0xfe7c4287, __VMLINUX_SYMBOL_STR(nr_cpu_ids) },
	{ 0xf1db1704, __VMLINUX_SYMBOL_STR(nla_memcpy) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x9fdecc31, __VMLINUX_SYMBOL_STR(unregister_netdevice_many) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x7fa72395, __VMLINUX_SYMBOL_STR(unregister_pernet_device) },
	{ 0x99591a7a, __VMLINUX_SYMBOL_STR(ipv6_ext_hdr) },
	{ 0xd2936c14, __VMLINUX_SYMBOL_STR(ns_capable) },
	{ 0xe94f1e83, __VMLINUX_SYMBOL_STR(free_netdev) },
	{ 0xd87c2198, __VMLINUX_SYMBOL_STR(register_netdev) },
	{ 0x63096cbc, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0x5515ca7f, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0xe937e5af, __VMLINUX_SYMBOL_STR(dev_get_by_index_rcu) },
	{ 0xe40dc473, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0xab4aa62b, __VMLINUX_SYMBOL_STR(rtnl_link_unregister) },
	{ 0x25f1c0bb, __VMLINUX_SYMBOL_STR(ip6_route_output) },
	{ 0xc8353381, __VMLINUX_SYMBOL_STR(ipv6_push_nfrag_opts) },
	{ 0xd61d3802, __VMLINUX_SYMBOL_STR(ip_route_input_noref) },
	{ 0x7c62d042, __VMLINUX_SYMBOL_STR(cpu_possible_mask) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0xfb4628f9, __VMLINUX_SYMBOL_STR(alloc_netdev_mqs) },
	{ 0x6aa0ac2d, __VMLINUX_SYMBOL_STR(netdev_state_change) },
	{ 0x1176e07f, __VMLINUX_SYMBOL_STR(__per_cpu_offset) },
	{ 0xfb3dec2b, __VMLINUX_SYMBOL_STR(unregister_netdevice_queue) },
	{ 0xddde3c32, __VMLINUX_SYMBOL_STR(ip_route_output_flow) },
	{ 0xf6ebc03b, __VMLINUX_SYMBOL_STR(net_ratelimit) },
	{ 0x275de30d, __VMLINUX_SYMBOL_STR(__xfrm_policy_check) },
	{ 0xbd6dff84, __VMLINUX_SYMBOL_STR(rt6_lookup) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x1ac8eab4, __VMLINUX_SYMBOL_STR(rtnl_link_register) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x1c7674e8, __VMLINUX_SYMBOL_STR(ip6_local_out) },
	{ 0x50d6202a, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0x9c273b30, __VMLINUX_SYMBOL_STR(sock_wfree) },
	{ 0x39885d11, __VMLINUX_SYMBOL_STR(xfrm6_tunnel_register) },
	{ 0x50fd4505, __VMLINUX_SYMBOL_STR(xfrm_lookup) },
	{ 0xd542439, __VMLINUX_SYMBOL_STR(__ipv6_addr_type) },
	{ 0x6e720ff2, __VMLINUX_SYMBOL_STR(rtnl_unlock) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=tunnel6";

