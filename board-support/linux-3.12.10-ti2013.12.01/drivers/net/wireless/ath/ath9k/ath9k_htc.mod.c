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
	{ 0x126b9872, __VMLINUX_SYMBOL_STR(ath9k_hw_set_txq_props) },
	{ 0xa55e61f2, __VMLINUX_SYMBOL_STR(ath9k_hw_init) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xff178f6, __VMLINUX_SYMBOL_STR(__aeabi_idivmod) },
	{ 0x6ae4d81d, __VMLINUX_SYMBOL_STR(ath9k_hw_deinit) },
	{ 0x3d30175d, __VMLINUX_SYMBOL_STR(ath9k_hw_cfg_output) },
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xcd63ab3c, __VMLINUX_SYMBOL_STR(device_release_driver) },
	{ 0x87594321, __VMLINUX_SYMBOL_STR(ath9k_hw_set_gpio) },
	{ 0xe093bb43, __VMLINUX_SYMBOL_STR(ath9k_cmn_init_crypto) },
	{ 0x3250d522, __VMLINUX_SYMBOL_STR(ieee80211_queue_work) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x80d216b9, __VMLINUX_SYMBOL_STR(led_classdev_register) },
	{ 0xd3dbfbc4, __VMLINUX_SYMBOL_STR(_find_first_zero_bit_le) },
	{ 0xf90b7504, __VMLINUX_SYMBOL_STR(ath9k_hw_btcoex_enable) },
	{ 0xc13f4274, __VMLINUX_SYMBOL_STR(ath9k_hw_wait) },
	{ 0x4fbf8b5, __VMLINUX_SYMBOL_STR(ath9k_cmn_get_hw_crypto_keytype) },
	{ 0xedd096e9, __VMLINUX_SYMBOL_STR(ath9k_hw_stopdmarecv) },
	{ 0x3a7431ca, __VMLINUX_SYMBOL_STR(ath_key_delete) },
	{ 0xaf23595f, __VMLINUX_SYMBOL_STR(ath9k_cmn_update_txpow) },
	{ 0xa1d55e90, __VMLINUX_SYMBOL_STR(_raw_spin_lock_bh) },
	{ 0x7ef39823, __VMLINUX_SYMBOL_STR(ieee80211_hdrlen) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0x6b06fdce, __VMLINUX_SYMBOL_STR(delayed_work_timer_fn) },
	{ 0xd439b33c, __VMLINUX_SYMBOL_STR(ieee80211_beacon_get_tim) },
	{ 0x30ca5954, __VMLINUX_SYMBOL_STR(ath9k_hw_gpio_get) },
	{ 0x3c8911de, __VMLINUX_SYMBOL_STR(ath_regd_init) },
	{ 0x4205ad24, __VMLINUX_SYMBOL_STR(cancel_work_sync) },
	{ 0x68913526, __VMLINUX_SYMBOL_STR(usb_kill_urb) },
	{ 0xe2fae716, __VMLINUX_SYMBOL_STR(kmemdup) },
	{ 0xa89ab226, __VMLINUX_SYMBOL_STR(ath9k_cmn_get_curchannel) },
	{ 0x62b0cbf8, __VMLINUX_SYMBOL_STR(ieee80211_unregister_hw) },
	{ 0x593a99b, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0x24d7b4eb, __VMLINUX_SYMBOL_STR(cancel_delayed_work_sync) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x59e31c01, __VMLINUX_SYMBOL_STR(ieee80211_iterate_active_interfaces_atomic) },
	{ 0xcdc46118, __VMLINUX_SYMBOL_STR(ath9k_hw_setrxfilter) },
	{ 0x55d19853, __VMLINUX_SYMBOL_STR(ath9k_hw_get_txq_props) },
	{ 0xe1a14159, __VMLINUX_SYMBOL_STR(ath9k_hw_releasetxqueue) },
	{ 0xfff317b5, __VMLINUX_SYMBOL_STR(ath9k_hw_reset_tsf) },
	{ 0x4790699f, __VMLINUX_SYMBOL_STR(wiphy_rfkill_start_polling) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x594ff15d, __VMLINUX_SYMBOL_STR(skb_trim) },
	{ 0xd05ce766, __VMLINUX_SYMBOL_STR(ieee80211_stop_queues) },
	{ 0x64bd2bb4, __VMLINUX_SYMBOL_STR(usb_unanchor_urb) },
	{ 0x81f3afb, __VMLINUX_SYMBOL_STR(complete_all) },
	{ 0x63a326ef, __VMLINUX_SYMBOL_STR(__netdev_alloc_skb) },
	{ 0x1071bf3d, __VMLINUX_SYMBOL_STR(ieee80211_tx_status) },
	{ 0xde4c398f, __VMLINUX_SYMBOL_STR(ath_printk) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xf04a4650, __VMLINUX_SYMBOL_STR(ath9k_hw_setopmode) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x1fab5905, __VMLINUX_SYMBOL_STR(wait_for_completion) },
	{ 0x382c8a1c, __VMLINUX_SYMBOL_STR(ath9k_hw_disable) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xd5f2172f, __VMLINUX_SYMBOL_STR(del_timer_sync) },
	{ 0x3ee4e71d, __VMLINUX_SYMBOL_STR(ath9k_hw_resettxqueue) },
	{ 0x99dc2dde, __VMLINUX_SYMBOL_STR(ath9k_hw_gettsf64) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x37befc70, __VMLINUX_SYMBOL_STR(jiffies_to_msecs) },
	{ 0xb223f9fb, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x6728a483, __VMLINUX_SYMBOL_STR(ath9k_hw_set_sta_beacon_timers) },
	{ 0x67da9868, __VMLINUX_SYMBOL_STR(ath9k_hw_set_tsfadjust) },
	{ 0x4bd83a6d, __VMLINUX_SYMBOL_STR(ieee80211_wake_queues) },
	{ 0xfaef0ed, __VMLINUX_SYMBOL_STR(__tasklet_schedule) },
	{ 0xe52aa1c8, __VMLINUX_SYMBOL_STR(ath9k_hw_btcoex_disable) },
	{ 0xf8bfa36d, __VMLINUX_SYMBOL_STR(ath9k_hw_getrxfilter) },
	{ 0x91caa576, __VMLINUX_SYMBOL_STR(ath9k_hw_ani_monitor) },
	{ 0x1049b573, __VMLINUX_SYMBOL_STR(usb_control_msg) },
	{ 0x84b183ae, __VMLINUX_SYMBOL_STR(strncmp) },
	{ 0x4e2481d5, __VMLINUX_SYMBOL_STR(ath_is_world_regd) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x9a0156f5, __VMLINUX_SYMBOL_STR(ieee80211_rx) },
	{ 0x5515ca7f, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x9545af6d, __VMLINUX_SYMBOL_STR(tasklet_init) },
	{ 0x8834396c, __VMLINUX_SYMBOL_STR(mod_timer) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0xe40dc473, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0x44710d5d, __VMLINUX_SYMBOL_STR(wiphy_rfkill_stop_polling) },
	{ 0x2607e1cb, __VMLINUX_SYMBOL_STR(request_firmware_nowait) },
	{ 0x625c9f80, __VMLINUX_SYMBOL_STR(ath9k_cmn_update_ichannel) },
	{ 0x73936f0c, __VMLINUX_SYMBOL_STR(ath9k_hw_write_associd) },
	{ 0x1d4cdb6d, __VMLINUX_SYMBOL_STR(ieee80211_queue_delayed_work) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0xe2ea17e8, __VMLINUX_SYMBOL_STR(dev_kfree_skb_any) },
	{ 0xd2400912, __VMLINUX_SYMBOL_STR(ath_reg_notifier_apply) },
	{ 0x4739dd03, __VMLINUX_SYMBOL_STR(wiphy_to_ieee80211_hw) },
	{ 0x82072614, __VMLINUX_SYMBOL_STR(tasklet_kill) },
	{ 0x6d4d016a, __VMLINUX_SYMBOL_STR(ath9k_hw_init_btcoex_hw) },
	{ 0x3527d183, __VMLINUX_SYMBOL_STR(ieee80211_stop_tx_ba_cb_irqsafe) },
	{ 0x7783bae2, __VMLINUX_SYMBOL_STR(skb_queue_tail) },
	{ 0x2f172c4f, __VMLINUX_SYMBOL_STR(ath9k_hw_beaconq_setup) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0xa97c342f, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0xf8879b07, __VMLINUX_SYMBOL_STR(ath9k_hw_name) },
	{ 0x417db5e0, __VMLINUX_SYMBOL_STR(ath9k_hw_init_global_settings) },
	{ 0xc3e596f0, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0x7bd3b321, __VMLINUX_SYMBOL_STR(usb_get_dev) },
	{ 0x78cf4589, __VMLINUX_SYMBOL_STR(usb_kill_anchored_urbs) },
	{ 0xd2981357, __VMLINUX_SYMBOL_STR(ath9k_cmn_count_streams) },
	{ 0xabcdf206, __VMLINUX_SYMBOL_STR(ath9k_hw_settsf64) },
	{ 0xdd3916ac, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_bh) },
	{ 0x863f4559, __VMLINUX_SYMBOL_STR(wiphy_rfkill_set_hw_state) },
	{ 0x3bd1b1f6, __VMLINUX_SYMBOL_STR(msecs_to_jiffies) },
	{ 0x11b78479, __VMLINUX_SYMBOL_STR(usb_bulk_msg) },
	{ 0xbb9e326a, __VMLINUX_SYMBOL_STR(usb_put_dev) },
	{ 0x86a4889a, __VMLINUX_SYMBOL_STR(kmalloc_order_trace) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x297aa450, __VMLINUX_SYMBOL_STR(ath9k_hw_beaconinit) },
	{ 0x2940c7a5, __VMLINUX_SYMBOL_STR(ieee80211_find_sta) },
	{ 0x39d3dc37, __VMLINUX_SYMBOL_STR(ieee80211_get_buffered_bc) },
	{ 0x14ef5d2c, __VMLINUX_SYMBOL_STR(usb_interrupt_msg) },
	{ 0x82a23040, __VMLINUX_SYMBOL_STR(ath9k_hw_btcoex_bt_stomp) },
	{ 0xc3ed664f, __VMLINUX_SYMBOL_STR(ath9k_hw_setrxabort) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x998078a9, __VMLINUX_SYMBOL_STR(ath_hw_setbssidmask) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x3370e514, __VMLINUX_SYMBOL_STR(ath9k_hw_phy_disable) },
	{ 0x9a272542, __VMLINUX_SYMBOL_STR(ieee80211_get_hdrlen_from_skb) },
	{ 0xeb862f4e, __VMLINUX_SYMBOL_STR(ath9k_hw_setpower) },
	{ 0xc45b0685, __VMLINUX_SYMBOL_STR(__ieee80211_create_tpt_led_trigger) },
	{ 0xee2f25c1, __VMLINUX_SYMBOL_STR(ieee80211_register_hw) },
	{ 0xc91156f9, __VMLINUX_SYMBOL_STR(led_classdev_unregister) },
	{ 0x5c5257fb, __VMLINUX_SYMBOL_STR(ath9k_hw_btcoex_set_weight) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x92b1d32e, __VMLINUX_SYMBOL_STR(regulatory_hint) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x741036dc, __VMLINUX_SYMBOL_STR(ath9k_hw_setmcastfilter) },
	{ 0xc7a00bf1, __VMLINUX_SYMBOL_STR(ieee80211_start_tx_ba_session) },
	{ 0x9388074f, __VMLINUX_SYMBOL_STR(ieee80211_alloc_hw) },
	{ 0x601a892e, __VMLINUX_SYMBOL_STR(ath9k_hw_startpcureceive) },
	{ 0xac46860d, __VMLINUX_SYMBOL_STR(ath9k_hw_setuptxqueue) },
	{ 0xa3e8bb7a, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0x155a3d9f, __VMLINUX_SYMBOL_STR(request_firmware) },
	{ 0x7048a42c, __VMLINUX_SYMBOL_STR(ath9k_hw_reset) },
	{ 0x6a8d8061, __VMLINUX_SYMBOL_STR(ieee80211_free_hw) },
	{ 0x1cff016, __VMLINUX_SYMBOL_STR(skb_dequeue) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xc2d63bc1, __VMLINUX_SYMBOL_STR(usb_ifnum_to_if) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xd4669fad, __VMLINUX_SYMBOL_STR(complete) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0x99bb8806, __VMLINUX_SYMBOL_STR(memmove) },
	{ 0xdf2fc8cb, __VMLINUX_SYMBOL_STR(ath9k_hw_btcoex_init_3wire) },
	{ 0x5dc6f856, __VMLINUX_SYMBOL_STR(ath_key_config) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x70b60936, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0x7cf9099, __VMLINUX_SYMBOL_STR(wait_for_completion_timeout) },
	{ 0x47c8baf4, __VMLINUX_SYMBOL_STR(param_ops_uint) },
	{ 0x994c1a5e, __VMLINUX_SYMBOL_STR(ath9k_hw_reset_calvalid) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x4b9ab611, __VMLINUX_SYMBOL_STR(usb_free_urb) },
	{ 0x8b5187c3, __VMLINUX_SYMBOL_STR(release_firmware) },
	{ 0x8d3abe0e, __VMLINUX_SYMBOL_STR(ieee80211_start_tx_ba_cb_irqsafe) },
	{ 0x8be2d05b, __VMLINUX_SYMBOL_STR(usb_anchor_urb) },
	{ 0x148c8de9, __VMLINUX_SYMBOL_STR(usb_alloc_urb) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=ath9k_hw,ath9k_common,mac80211,ath,cfg80211";

MODULE_ALIAS("usb:v0CF3p9271d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0CF3p1006d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0846p9030d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v07D1p3A10d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v13D3p3327d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v13D3p3328d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v13D3p3346d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v13D3p3348d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v13D3p3349d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v13D3p3350d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v04CAp4605d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v040Dp3801d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0CF3pB003d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0CF3pB002d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v057Cp8403d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0CF3p7015d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1668p1200d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0CF3p7010d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0846p9018d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v083ApA704d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0411p017Fd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v04DAp3904d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0CF3p20FFd*dc*dsc*dp*ic*isc*ip*in*");
