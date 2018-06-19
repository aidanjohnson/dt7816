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
	{ 0x4d763937, __VMLINUX_SYMBOL_STR(eth_change_mtu) },
	{ 0xd63271fb, __VMLINUX_SYMBOL_STR(eth_validate_addr) },
	{ 0xb223f9fb, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0xa3e8bb7a, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x6b06fdce, __VMLINUX_SYMBOL_STR(delayed_work_timer_fn) },
	{ 0xd87c2198, __VMLINUX_SYMBOL_STR(register_netdev) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x148c8de9, __VMLINUX_SYMBOL_STR(usb_alloc_urb) },
	{ 0x593a99b, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0x9545af6d, __VMLINUX_SYMBOL_STR(tasklet_init) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xcf636b9e, __VMLINUX_SYMBOL_STR(alloc_etherdev_mqs) },
	{ 0xa36a8566, __VMLINUX_SYMBOL_STR(usb_driver_set_configuration) },
	{ 0x57feb1f2, __VMLINUX_SYMBOL_STR(netif_device_attach) },
	{ 0xc6cbbc89, __VMLINUX_SYMBOL_STR(capable) },
	{ 0x36026fb7, __VMLINUX_SYMBOL_STR(__netif_schedule) },
	{ 0x2a3aa678, __VMLINUX_SYMBOL_STR(_test_and_clear_bit) },
	{ 0xfaf98462, __VMLINUX_SYMBOL_STR(bitrev32) },
	{ 0xa34f1ef5, __VMLINUX_SYMBOL_STR(crc32_le) },
	{ 0xd35bd828, __VMLINUX_SYMBOL_STR(netdev_notice) },
	{ 0x94ee05c8, __VMLINUX_SYMBOL_STR(netif_carrier_off) },
	{ 0x4a8342f8, __VMLINUX_SYMBOL_STR(netif_carrier_on) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x24d7b4eb, __VMLINUX_SYMBOL_STR(cancel_delayed_work_sync) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x68913526, __VMLINUX_SYMBOL_STR(usb_kill_urb) },
	{ 0x50d6202a, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0xfd128d57, __VMLINUX_SYMBOL_STR(skb_queue_head) },
	{ 0x1cff016, __VMLINUX_SYMBOL_STR(skb_dequeue) },
	{ 0xfcd5641, __VMLINUX_SYMBOL_STR(netif_rx) },
	{ 0x746f15cf, __VMLINUX_SYMBOL_STR(eth_type_trans) },
	{ 0x70b60936, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0x63a326ef, __VMLINUX_SYMBOL_STR(__netdev_alloc_skb) },
	{ 0xe2ea17e8, __VMLINUX_SYMBOL_STR(dev_kfree_skb_any) },
	{ 0x7783bae2, __VMLINUX_SYMBOL_STR(skb_queue_tail) },
	{ 0xe91528c7, __VMLINUX_SYMBOL_STR(skb_tstamp_tx) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xfaef0ed, __VMLINUX_SYMBOL_STR(__tasklet_schedule) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x72350130, __VMLINUX_SYMBOL_STR(___ratelimit) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0xbc35e3cc, __VMLINUX_SYMBOL_STR(netdev_err) },
	{ 0xfba0a21b, __VMLINUX_SYMBOL_STR(netif_device_detach) },
	{ 0xe851bb05, __VMLINUX_SYMBOL_STR(queue_delayed_work_on) },
	{ 0x78bc26d7, __VMLINUX_SYMBOL_STR(netdev_info) },
	{ 0xe039aeb4, __VMLINUX_SYMBOL_STR(usb_unlink_urb) },
	{ 0x18b61eb6, __VMLINUX_SYMBOL_STR(netdev_warn) },
	{ 0xc9bf8bed, __VMLINUX_SYMBOL_STR(mii_ethtool_gset) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x328a05f1, __VMLINUX_SYMBOL_STR(strncpy) },
	{ 0xe94f1e83, __VMLINUX_SYMBOL_STR(free_netdev) },
	{ 0xf680cb71, __VMLINUX_SYMBOL_STR(unregister_netdev) },
	{ 0x82072614, __VMLINUX_SYMBOL_STR(tasklet_kill) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x4b9ab611, __VMLINUX_SYMBOL_STR(usb_free_urb) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x1049b573, __VMLINUX_SYMBOL_STR(usb_control_msg) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xa97c342f, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("usb:v0BDAp8152d*dc*dsc*dp*ic*isc*ip*in*");
