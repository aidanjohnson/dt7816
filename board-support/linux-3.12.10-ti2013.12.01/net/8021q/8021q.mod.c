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
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xfbc74f64, __VMLINUX_SYMBOL_STR(__copy_from_user) },
	{ 0xe36951f4, __VMLINUX_SYMBOL_STR(mrp_uninit_applicant) },
	{ 0x8d176d46, __VMLINUX_SYMBOL_STR(dev_change_flags) },
	{ 0xe15601dc, __VMLINUX_SYMBOL_STR(dev_mc_unsync) },
	{ 0x3e7e1d90, __VMLINUX_SYMBOL_STR(mrp_request_leave) },
	{ 0xf88dd612, __VMLINUX_SYMBOL_STR(single_open) },
	{ 0x67c2fa54, __VMLINUX_SYMBOL_STR(__copy_to_user) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x60a13e90, __VMLINUX_SYMBOL_STR(rcu_barrier) },
	{ 0xec684743, __VMLINUX_SYMBOL_STR(garp_uninit_applicant) },
	{ 0xc5e99c21, __VMLINUX_SYMBOL_STR(vlan_dev_vlan_id) },
	{ 0x110807ba, __VMLINUX_SYMBOL_STR(dev_uc_add) },
	{ 0x4cd9d440, __VMLINUX_SYMBOL_STR(single_release) },
	{ 0xd2ce469a, __VMLINUX_SYMBOL_STR(seq_puts) },
	{ 0x3eebe54f, __VMLINUX_SYMBOL_STR(garp_request_join) },
	{ 0xc7a4fbed, __VMLINUX_SYMBOL_STR(rtnl_lock) },
	{ 0x53f648e, __VMLINUX_SYMBOL_STR(vlan_uses_dev) },
	{ 0x4a8342f8, __VMLINUX_SYMBOL_STR(netif_carrier_on) },
	{ 0xd3f57a2, __VMLINUX_SYMBOL_STR(_find_next_bit_le) },
	{ 0x2247cba2, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0xd2da1048, __VMLINUX_SYMBOL_STR(register_netdevice_notifier) },
	{ 0x94ee05c8, __VMLINUX_SYMBOL_STR(netif_carrier_off) },
	{ 0x688c3c76, __VMLINUX_SYMBOL_STR(remove_proc_entry) },
	{ 0x50c89f23, __VMLINUX_SYMBOL_STR(__alloc_percpu) },
	{ 0x15cf087c, __VMLINUX_SYMBOL_STR(dev_set_allmulti) },
	{ 0x22f5a257, __VMLINUX_SYMBOL_STR(vlan_vid_del) },
	{ 0x2bf817b8, __VMLINUX_SYMBOL_STR(call_netdevice_notifiers) },
	{ 0x8d5c7f3b, __VMLINUX_SYMBOL_STR(linkwatch_fire_event) },
	{ 0xfd838173, __VMLINUX_SYMBOL_STR(vlan_vid_add) },
	{ 0xeb2e3f9b, __VMLINUX_SYMBOL_STR(__netpoll_setup) },
	{ 0xba52cf62, __VMLINUX_SYMBOL_STR(garp_init_applicant) },
	{ 0x92c80041, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0xc9ec4e21, __VMLINUX_SYMBOL_STR(free_percpu) },
	{ 0x9d0d6206, __VMLINUX_SYMBOL_STR(unregister_netdevice_notifier) },
	{ 0xfba197b8, __VMLINUX_SYMBOL_STR(proc_remove) },
	{ 0x458d2aad, __VMLINUX_SYMBOL_STR(vlan_ioctl_set) },
	{ 0xad01eef1, __VMLINUX_SYMBOL_STR(netpoll_send_skb_on_dev) },
	{ 0xbbcbd046, __VMLINUX_SYMBOL_STR(PDE_DATA) },
	{ 0xfe7c4287, __VMLINUX_SYMBOL_STR(nr_cpu_ids) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xdc8cb9d7, __VMLINUX_SYMBOL_STR(unregister_pernet_subsys) },
	{ 0x9fdecc31, __VMLINUX_SYMBOL_STR(unregister_netdevice_many) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xa4c7fa32, __VMLINUX_SYMBOL_STR(ethtool_op_get_link) },
	{ 0xd2936c14, __VMLINUX_SYMBOL_STR(ns_capable) },
	{ 0x128e7aa8, __VMLINUX_SYMBOL_STR(__netpoll_free_async) },
	{ 0xf005d30, __VMLINUX_SYMBOL_STR(__ethtool_get_settings) },
	{ 0xe94f1e83, __VMLINUX_SYMBOL_STR(free_netdev) },
	{ 0x328a05f1, __VMLINUX_SYMBOL_STR(strncpy) },
	{ 0x290bc3c3, __VMLINUX_SYMBOL_STR(garp_register_application) },
	{ 0x63096cbc, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0xab71cad5, __VMLINUX_SYMBOL_STR(netdev_upper_dev_unlink) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0x5515ca7f, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0x3834b570, __VMLINUX_SYMBOL_STR(proc_mkdir_data) },
	{ 0x1118ff8b, __VMLINUX_SYMBOL_STR(seq_release_net) },
	{ 0x3248534f, __VMLINUX_SYMBOL_STR(netif_stacked_transfer_operstate) },
	{ 0xab4aa62b, __VMLINUX_SYMBOL_STR(rtnl_link_unregister) },
	{ 0x5fe006df, __VMLINUX_SYMBOL_STR(__dev_get_by_index) },
	{ 0x2c20f97d, __VMLINUX_SYMBOL_STR(garp_request_leave) },
	{ 0x347013de, __VMLINUX_SYMBOL_STR(nla_validate) },
	{ 0x4ca3136c, __VMLINUX_SYMBOL_STR(arp_find) },
	{ 0x7c62d042, __VMLINUX_SYMBOL_STR(cpu_possible_mask) },
	{ 0x34fc4f97, __VMLINUX_SYMBOL_STR(eth_header_parse) },
	{ 0x6b2dc060, __VMLINUX_SYMBOL_STR(dump_stack) },
	{ 0xfb4628f9, __VMLINUX_SYMBOL_STR(alloc_netdev_mqs) },
	{ 0xd7cb77a9, __VMLINUX_SYMBOL_STR(register_pernet_subsys) },
	{ 0x2b70666e, __VMLINUX_SYMBOL_STR(mrp_init_applicant) },
	{ 0xbd9d4f1f, __VMLINUX_SYMBOL_STR(netdev_upper_dev_link) },
	{ 0xf1ef0fc0, __VMLINUX_SYMBOL_STR(ether_setup) },
	{ 0x7be7ccf, __VMLINUX_SYMBOL_STR(dev_uc_unsync) },
	{ 0x7d79ede0, __VMLINUX_SYMBOL_STR(__dev_get_by_name) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x20a5d12a, __VMLINUX_SYMBOL_STR(garp_unregister_application) },
	{ 0x1176e07f, __VMLINUX_SYMBOL_STR(__per_cpu_offset) },
	{ 0xfb3dec2b, __VMLINUX_SYMBOL_STR(unregister_netdevice_queue) },
	{ 0xf9141363, __VMLINUX_SYMBOL_STR(proc_create_data) },
	{ 0xd63271fb, __VMLINUX_SYMBOL_STR(eth_validate_addr) },
	{ 0x94b932f1, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0x9cd59c9d, __VMLINUX_SYMBOL_STR(dev_set_promiscuity) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xbd084931, __VMLINUX_SYMBOL_STR(seq_open_net) },
	{ 0xd638c632, __VMLINUX_SYMBOL_STR(mrp_register_application) },
	{ 0x1ac8eab4, __VMLINUX_SYMBOL_STR(rtnl_link_register) },
	{ 0xef84e783, __VMLINUX_SYMBOL_STR(dev_uc_del) },
	{ 0xeef0a7b4, __VMLINUX_SYMBOL_STR(dev_uc_sync) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xf3f92cf8, __VMLINUX_SYMBOL_STR(netdev_update_features) },
	{ 0x85670f1d, __VMLINUX_SYMBOL_STR(rtnl_is_locked) },
	{ 0xc11126ee, __VMLINUX_SYMBOL_STR(dev_queue_xmit) },
	{ 0xb8ccc45b, __VMLINUX_SYMBOL_STR(mrp_unregister_application) },
	{ 0xa7c7592f, __VMLINUX_SYMBOL_STR(mrp_request_join) },
	{ 0x715a02ee, __VMLINUX_SYMBOL_STR(dev_mc_sync) },
	{ 0x6e720ff2, __VMLINUX_SYMBOL_STR(rtnl_unlock) },
	{ 0x5124353d, __VMLINUX_SYMBOL_STR(dev_get_stats) },
	{ 0xf724ee1, __VMLINUX_SYMBOL_STR(dev_set_mtu) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=mrp,garp";


MODULE_INFO(srcversion, "020C6DD9318B31414F09D20");
