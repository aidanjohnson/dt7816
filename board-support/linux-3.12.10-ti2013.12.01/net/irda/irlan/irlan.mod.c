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
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xb9394173, __VMLINUX_SYMBOL_STR(irias_delete_value) },
	{ 0x5bb37498, __VMLINUX_SYMBOL_STR(irttp_udata_request) },
	{ 0x9ffda243, __VMLINUX_SYMBOL_STR(irias_add_string_attrib) },
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xc996d097, __VMLINUX_SYMBOL_STR(del_timer) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0xdde0b0af, __VMLINUX_SYMBOL_STR(seq_open) },
	{ 0xc8b57c27, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0x79aa04a2, __VMLINUX_SYMBOL_STR(get_random_bytes) },
	{ 0x763e54a4, __VMLINUX_SYMBOL_STR(irlmp_unregister_client) },
	{ 0x6a3ee58, __VMLINUX_SYMBOL_STR(irias_new_integer_value) },
	{ 0x33cbe2c6, __VMLINUX_SYMBOL_STR(proc_irda) },
	{ 0xd2ce469a, __VMLINUX_SYMBOL_STR(seq_puts) },
	{ 0xa168d066, __VMLINUX_SYMBOL_STR(irttp_close_tsap) },
	{ 0xc7a4fbed, __VMLINUX_SYMBOL_STR(rtnl_lock) },
	{ 0x4d763937, __VMLINUX_SYMBOL_STR(eth_change_mtu) },
	{ 0x2a3aa678, __VMLINUX_SYMBOL_STR(_test_and_clear_bit) },
	{ 0x2247cba2, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0x7dca54b6, __VMLINUX_SYMBOL_STR(irttp_connect_request) },
	{ 0x688c3c76, __VMLINUX_SYMBOL_STR(remove_proc_entry) },
	{ 0x8a805e82, __VMLINUX_SYMBOL_STR(irttp_data_request) },
	{ 0x33ba5cd4, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0x593a99b, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0x3474c0aa, __VMLINUX_SYMBOL_STR(skb_realloc_headroom) },
	{ 0x92c80041, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0xf199cba4, __VMLINUX_SYMBOL_STR(irias_insert_object) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x57657d9b, __VMLINUX_SYMBOL_STR(iriap_getvaluebyclass_request) },
	{ 0xfcd5641, __VMLINUX_SYMBOL_STR(netif_rx) },
	{ 0x7042bc54, __VMLINUX_SYMBOL_STR(irlmp_register_client) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xd5f2172f, __VMLINUX_SYMBOL_STR(del_timer_sync) },
	{ 0xa4efed60, __VMLINUX_SYMBOL_STR(skb_queue_purge) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x1fe2d205, __VMLINUX_SYMBOL_STR(irttp_disconnect_request) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xe94f1e83, __VMLINUX_SYMBOL_STR(free_netdev) },
	{ 0xd87c2198, __VMLINUX_SYMBOL_STR(register_netdev) },
	{ 0xf29942b3, __VMLINUX_SYMBOL_STR(seq_putc) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x8834396c, __VMLINUX_SYMBOL_STR(mod_timer) },
	{ 0x7d3647c, __VMLINUX_SYMBOL_STR(irlmp_register_service) },
	{ 0x7783bae2, __VMLINUX_SYMBOL_STR(skb_queue_tail) },
	{ 0x2740cd3, __VMLINUX_SYMBOL_STR(irttp_connect_response) },
	{ 0xc3e596f0, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0xb3c13d7f, __VMLINUX_SYMBOL_STR(irias_add_integer_attrib) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0xae405457, __VMLINUX_SYMBOL_STR(iriap_close) },
	{ 0x6b2dc060, __VMLINUX_SYMBOL_STR(dump_stack) },
	{ 0xbe40ace9, __VMLINUX_SYMBOL_STR(irlmp_discovery_request) },
	{ 0xbcd3ef13, __VMLINUX_SYMBOL_STR(irias_object_change_attribute) },
	{ 0xfb4628f9, __VMLINUX_SYMBOL_STR(alloc_netdev_mqs) },
	{ 0x746f15cf, __VMLINUX_SYMBOL_STR(eth_type_trans) },
	{ 0xefa1f5e4, __VMLINUX_SYMBOL_STR(irda_notify_init) },
	{ 0xf1ef0fc0, __VMLINUX_SYMBOL_STR(ether_setup) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xfb3dec2b, __VMLINUX_SYMBOL_STR(unregister_netdevice_queue) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0xf6ebc03b, __VMLINUX_SYMBOL_STR(net_ratelimit) },
	{ 0xf9141363, __VMLINUX_SYMBOL_STR(proc_create_data) },
	{ 0xd63271fb, __VMLINUX_SYMBOL_STR(eth_validate_addr) },
	{ 0x94b932f1, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0x3d4f38c4, __VMLINUX_SYMBOL_STR(iriap_open) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x4c83bdcd, __VMLINUX_SYMBOL_STR(irttp_open_tsap) },
	{ 0x499cb58c, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0x1cfb04fa, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x1cff016, __VMLINUX_SYMBOL_STR(skb_dequeue) },
	{ 0xf346231f, __VMLINUX_SYMBOL_STR(seq_list_start_head) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0x46c1c4a2, __VMLINUX_SYMBOL_STR(irlmp_unregister_service) },
	{ 0xb9c81fa6, __VMLINUX_SYMBOL_STR(seq_release) },
	{ 0x36026fb7, __VMLINUX_SYMBOL_STR(__netif_schedule) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0x7e67ca6e, __VMLINUX_SYMBOL_STR(irias_new_object) },
	{ 0xe7d4daac, __VMLINUX_SYMBOL_STR(seq_list_next) },
	{ 0xc477368d, __VMLINUX_SYMBOL_STR(irias_find_object) },
	{ 0x50d6202a, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0x85670f1d, __VMLINUX_SYMBOL_STR(rtnl_is_locked) },
	{ 0xde4c6b3c, __VMLINUX_SYMBOL_STR(irlmp_service_to_hint) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x70b60936, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0x6e720ff2, __VMLINUX_SYMBOL_STR(rtnl_unlock) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=irda";

