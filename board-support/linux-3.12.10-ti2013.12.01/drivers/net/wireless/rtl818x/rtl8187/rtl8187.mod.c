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
	{ 0xc848caf8, __VMLINUX_SYMBOL_STR(ieee80211_rts_duration) },
	{ 0x98bb5a22, __VMLINUX_SYMBOL_STR(eeprom_93cx6_read) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0xe75a96c5, __VMLINUX_SYMBOL_STR(ieee80211_rx_irqsafe) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x80d216b9, __VMLINUX_SYMBOL_STR(led_classdev_register) },
	{ 0x9c64fbd, __VMLINUX_SYMBOL_STR(ieee80211_frequency_to_channel) },
	{ 0x79aa04a2, __VMLINUX_SYMBOL_STR(get_random_bytes) },
	{ 0xb54533f7, __VMLINUX_SYMBOL_STR(usecs_to_jiffies) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0x6b06fdce, __VMLINUX_SYMBOL_STR(delayed_work_timer_fn) },
	{ 0xd439b33c, __VMLINUX_SYMBOL_STR(ieee80211_beacon_get_tim) },
	{ 0x62b0cbf8, __VMLINUX_SYMBOL_STR(ieee80211_unregister_hw) },
	{ 0x593a99b, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0x24d7b4eb, __VMLINUX_SYMBOL_STR(cancel_delayed_work_sync) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x4790699f, __VMLINUX_SYMBOL_STR(wiphy_rfkill_start_polling) },
	{ 0x9ad01724, __VMLINUX_SYMBOL_STR(skb_unlink) },
	{ 0x594ff15d, __VMLINUX_SYMBOL_STR(skb_trim) },
	{ 0x64bd2bb4, __VMLINUX_SYMBOL_STR(usb_unanchor_urb) },
	{ 0x63a326ef, __VMLINUX_SYMBOL_STR(__netdev_alloc_skb) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x8f045d1c, __VMLINUX_SYMBOL_STR(cancel_delayed_work) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0xb223f9fb, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x27cb133b, __VMLINUX_SYMBOL_STR(eeprom_93cx6_multiread) },
	{ 0x328a05f1, __VMLINUX_SYMBOL_STR(strncpy) },
	{ 0x1049b573, __VMLINUX_SYMBOL_STR(usb_control_msg) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x5515ca7f, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0xe40dc473, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0x44710d5d, __VMLINUX_SYMBOL_STR(wiphy_rfkill_stop_polling) },
	{ 0x1d4cdb6d, __VMLINUX_SYMBOL_STR(ieee80211_queue_delayed_work) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0xe2ea17e8, __VMLINUX_SYMBOL_STR(dev_kfree_skb_any) },
	{ 0x80dddc87, __VMLINUX_SYMBOL_STR(dev_kfree_skb_irq) },
	{ 0x7783bae2, __VMLINUX_SYMBOL_STR(skb_queue_tail) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0xa97c342f, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0x11b29ff9, __VMLINUX_SYMBOL_STR(__ieee80211_get_rx_led_name) },
	{ 0x7bd3b321, __VMLINUX_SYMBOL_STR(usb_get_dev) },
	{ 0x78cf4589, __VMLINUX_SYMBOL_STR(usb_kill_anchored_urbs) },
	{ 0xe851bb05, __VMLINUX_SYMBOL_STR(queue_delayed_work_on) },
	{ 0xe72ae005, __VMLINUX_SYMBOL_STR(usb_reset_device) },
	{ 0x863f4559, __VMLINUX_SYMBOL_STR(wiphy_rfkill_set_hw_state) },
	{ 0xbb9e326a, __VMLINUX_SYMBOL_STR(usb_put_dev) },
	{ 0x28558c71, __VMLINUX_SYMBOL_STR(ieee80211_tx_status_irqsafe) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x74ce05b8, __VMLINUX_SYMBOL_STR(flush_delayed_work) },
	{ 0x96026d3c, __VMLINUX_SYMBOL_STR(__ieee80211_get_tx_led_name) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x27eccfde, __VMLINUX_SYMBOL_STR(ieee80211_generic_frame_duration) },
	{ 0x1a5e4640, __VMLINUX_SYMBOL_STR(__ieee80211_get_radio_led_name) },
	{ 0xee2f25c1, __VMLINUX_SYMBOL_STR(ieee80211_register_hw) },
	{ 0xc91156f9, __VMLINUX_SYMBOL_STR(led_classdev_unregister) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x9388074f, __VMLINUX_SYMBOL_STR(ieee80211_alloc_hw) },
	{ 0xa3e8bb7a, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0x6a8d8061, __VMLINUX_SYMBOL_STR(ieee80211_free_hw) },
	{ 0x1cff016, __VMLINUX_SYMBOL_STR(skb_dequeue) },
	{ 0xbf670952, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x70b60936, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x4b9ab611, __VMLINUX_SYMBOL_STR(usb_free_urb) },
	{ 0x8be2d05b, __VMLINUX_SYMBOL_STR(usb_anchor_urb) },
	{ 0x148c8de9, __VMLINUX_SYMBOL_STR(usb_alloc_urb) },
	{ 0x4662282f, __VMLINUX_SYMBOL_STR(ieee80211_queue_stopped) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=mac80211,cfg80211";

MODULE_ALIAS("usb:v0B05p171Dd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v050Dp705Ed*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BDAp8187d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BDAp8189d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BDAp8197d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BDAp8198d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0769p11F2d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0789p010Cd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0846p6100d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0846p6A00d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0846p4260d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v03F0pCA02d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0DF6p000Dd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0DF6p0028d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0DF6p0029d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v114Bp0150d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1371p9401d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v13D1pABE6d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v18E8p6232d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1B75p8187d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1737p0073d*dc*dsc*dp*ic*isc*ip*in*");
