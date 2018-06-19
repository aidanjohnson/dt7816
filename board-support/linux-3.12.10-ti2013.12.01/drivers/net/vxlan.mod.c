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
	{ 0xcf369001, __VMLINUX_SYMBOL_STR(release_sock) },
	{ 0x7cd15b70, __VMLINUX_SYMBOL_STR(neigh_lookup) },
	{ 0x78bc26d7, __VMLINUX_SYMBOL_STR(netdev_info) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x74e0edeb, __VMLINUX_SYMBOL_STR(register_pernet_device) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x60a13e90, __VMLINUX_SYMBOL_STR(rcu_barrier) },
	{ 0xe7ea71ad, __VMLINUX_SYMBOL_STR(ip_tunnel_get_stats64) },
	{ 0x43a53735, __VMLINUX_SYMBOL_STR(__alloc_workqueue_key) },
	{ 0x9469482, __VMLINUX_SYMBOL_STR(kfree_call_rcu) },
	{ 0x79aa04a2, __VMLINUX_SYMBOL_STR(get_random_bytes) },
	{ 0x11382f3c, __VMLINUX_SYMBOL_STR(ip_mc_leave_group) },
	{ 0xc7a4fbed, __VMLINUX_SYMBOL_STR(rtnl_lock) },
	{ 0xefe8af4d, __VMLINUX_SYMBOL_STR(arp_tbl) },
	{ 0x4d763937, __VMLINUX_SYMBOL_STR(eth_change_mtu) },
	{ 0x9700966d, __VMLINUX_SYMBOL_STR(dst_release) },
	{ 0xa1d55e90, __VMLINUX_SYMBOL_STR(_raw_spin_lock_bh) },
	{ 0xb2038f57, __VMLINUX_SYMBOL_STR(skb_clone) },
	{ 0x172af66b, __VMLINUX_SYMBOL_STR(rtnl_notify) },
	{ 0x50c89f23, __VMLINUX_SYMBOL_STR(__alloc_percpu) },
	{ 0x33ba5cd4, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0x593a99b, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0x39a6a2b9, __VMLINUX_SYMBOL_STR(sock_create_kern) },
	{ 0xd116b762, __VMLINUX_SYMBOL_STR(neigh_destroy) },
	{ 0x53b86f03, __VMLINUX_SYMBOL_STR(__put_net) },
	{ 0xcdf70e4c, __VMLINUX_SYMBOL_STR(skb_scrub_packet) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0xc9ec4e21, __VMLINUX_SYMBOL_STR(free_percpu) },
	{ 0x594ff15d, __VMLINUX_SYMBOL_STR(skb_trim) },
	{ 0xfcd5641, __VMLINUX_SYMBOL_STR(netif_rx) },
	{ 0x71bc64b4, __VMLINUX_SYMBOL_STR(__pskb_pull_tail) },
	{ 0xf1db1704, __VMLINUX_SYMBOL_STR(nla_memcpy) },
	{ 0x96d24144, __VMLINUX_SYMBOL_STR(kernel_setsockopt) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xd5f2172f, __VMLINUX_SYMBOL_STR(del_timer_sync) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x5bc60d2f, __VMLINUX_SYMBOL_STR(netif_rx_ni) },
	{ 0xa0658c45, __VMLINUX_SYMBOL_STR(skb_checksum) },
	{ 0x9fdecc31, __VMLINUX_SYMBOL_STR(unregister_netdevice_many) },
	{ 0xf6388c56, __VMLINUX_SYMBOL_STR(sysctl_ip_default_ttl) },
	{ 0x1c0027b2, __VMLINUX_SYMBOL_STR(arp_create) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xa4c7fa32, __VMLINUX_SYMBOL_STR(ethtool_op_get_link) },
	{ 0x285cbdae, __VMLINUX_SYMBOL_STR(lock_sock_nested) },
	{ 0x7fa72395, __VMLINUX_SYMBOL_STR(unregister_pernet_device) },
	{ 0x1b828557, __VMLINUX_SYMBOL_STR(ip_mc_join_group) },
	{ 0xe94f1e83, __VMLINUX_SYMBOL_STR(free_netdev) },
	{ 0x63096cbc, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0x38a9f7c5, __VMLINUX_SYMBOL_STR(in6addr_loopback) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x5515ca7f, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0x3d55ba8b, __VMLINUX_SYMBOL_STR(iptunnel_xmit) },
	{ 0x8c03d20c, __VMLINUX_SYMBOL_STR(destroy_workqueue) },
	{ 0x99517682, __VMLINUX_SYMBOL_STR(udp_encap_enable) },
	{ 0xc668ae36, __VMLINUX_SYMBOL_STR(__skb_get_rxhash) },
	{ 0xaa0675de, __VMLINUX_SYMBOL_STR(sk_free) },
	{ 0x17a66c39, __VMLINUX_SYMBOL_STR(dev_get_by_index) },
	{ 0x8834396c, __VMLINUX_SYMBOL_STR(mod_timer) },
	{ 0xfd760d4f, __VMLINUX_SYMBOL_STR(ipv6_stub) },
	{ 0xab4aa62b, __VMLINUX_SYMBOL_STR(rtnl_link_unregister) },
	{ 0x5fe006df, __VMLINUX_SYMBOL_STR(__dev_get_by_index) },
	{ 0x8766a38f, __VMLINUX_SYMBOL_STR(rtnl_set_sk_err) },
	{ 0xc3e596f0, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0xdf82a3b4, __VMLINUX_SYMBOL_STR(sk_release_kernel) },
	{ 0xdd3916ac, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_bh) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x746f15cf, __VMLINUX_SYMBOL_STR(eth_type_trans) },
	{ 0xd796878f, __VMLINUX_SYMBOL_STR(pskb_expand_head) },
	{ 0xf1ef0fc0, __VMLINUX_SYMBOL_STR(ether_setup) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0xfb3dec2b, __VMLINUX_SYMBOL_STR(unregister_netdevice_queue) },
	{ 0xddde3c32, __VMLINUX_SYMBOL_STR(ip_route_output_flow) },
	{ 0xf6ebc03b, __VMLINUX_SYMBOL_STR(net_ratelimit) },
	{ 0xd63271fb, __VMLINUX_SYMBOL_STR(eth_validate_addr) },
	{ 0x44da5d0f, __VMLINUX_SYMBOL_STR(__csum_ipv6_magic) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xa75312bc, __VMLINUX_SYMBOL_STR(call_rcu_sched) },
	{ 0x69fadbe6, __VMLINUX_SYMBOL_STR(kernel_bind) },
	{ 0x1ac8eab4, __VMLINUX_SYMBOL_STR(rtnl_link_register) },
	{ 0x6599a5b, __VMLINUX_SYMBOL_STR(iptunnel_pull_header) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x7d0db45c, __VMLINUX_SYMBOL_STR(jiffies_to_clock_t) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x99bb8806, __VMLINUX_SYMBOL_STR(memmove) },
	{ 0x1c7674e8, __VMLINUX_SYMBOL_STR(ip6_local_out) },
	{ 0x50d6202a, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0xafad493b, __VMLINUX_SYMBOL_STR(param_ops_ushort) },
	{ 0x2f512d52, __VMLINUX_SYMBOL_STR(ip6_dst_hoplimit) },
	{ 0x5471c290, __VMLINUX_SYMBOL_STR(eth_mac_addr) },
	{ 0x8dd61422, __VMLINUX_SYMBOL_STR(__nlmsg_put) },
	{ 0x475100c2, __VMLINUX_SYMBOL_STR(inet_get_local_port_range) },
	{ 0x6e720ff2, __VMLINUX_SYMBOL_STR(rtnl_unlock) },
	{ 0x200b2041, __VMLINUX_SYMBOL_STR(in6addr_any) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=ip_tunnel";


MODULE_INFO(srcversion, "7F7133CAB4A75E9892C3228");
