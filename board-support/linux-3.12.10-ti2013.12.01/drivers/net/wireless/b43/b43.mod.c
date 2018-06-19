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
	{ 0xfd128d57, __VMLINUX_SYMBOL_STR(skb_queue_head) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0x31405c41, __VMLINUX_SYMBOL_STR(ssb_dma_translation) },
	{ 0xc2290b94, __VMLINUX_SYMBOL_STR(device_remove_file) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0xff178f6, __VMLINUX_SYMBOL_STR(__aeabi_idivmod) },
	{ 0xe52e3763, __VMLINUX_SYMBOL_STR(mem_map) },
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x91eb9b4, __VMLINUX_SYMBOL_STR(round_jiffies) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x3250d522, __VMLINUX_SYMBOL_STR(ieee80211_queue_work) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x80d216b9, __VMLINUX_SYMBOL_STR(led_classdev_register) },
	{ 0x655b8063, __VMLINUX_SYMBOL_STR(arm_dma_ops) },
	{ 0x151e56a5, __VMLINUX_SYMBOL_STR(sdio_enable_func) },
	{ 0x9df247a9, __VMLINUX_SYMBOL_STR(sdio_claim_irq) },
	{ 0x81164600, __VMLINUX_SYMBOL_STR(ieee80211_rts_get) },
	{ 0x7ef39823, __VMLINUX_SYMBOL_STR(ieee80211_hdrlen) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0x6b06fdce, __VMLINUX_SYMBOL_STR(delayed_work_timer_fn) },
	{ 0xe49e7ea0, __VMLINUX_SYMBOL_STR(ssb_commit_settings) },
	{ 0xd439b33c, __VMLINUX_SYMBOL_STR(ieee80211_beacon_get_tim) },
	{ 0x76cf47f6, __VMLINUX_SYMBOL_STR(__aeabi_llsl) },
	{ 0x4205ad24, __VMLINUX_SYMBOL_STR(cancel_work_sync) },
	{ 0xe2fae716, __VMLINUX_SYMBOL_STR(kmemdup) },
	{ 0x62b0cbf8, __VMLINUX_SYMBOL_STR(ieee80211_unregister_hw) },
	{ 0x593a99b, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0x24d7b4eb, __VMLINUX_SYMBOL_STR(cancel_delayed_work_sync) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x8109fbd5, __VMLINUX_SYMBOL_STR(ssb_bus_powerup) },
	{ 0x9c315bca, __VMLINUX_SYMBOL_STR(ssb_bus_sdiobus_register) },
	{ 0x4790699f, __VMLINUX_SYMBOL_STR(wiphy_rfkill_start_polling) },
	{ 0x9db99b06, __VMLINUX_SYMBOL_STR(__ieee80211_get_assoc_led_name) },
	{ 0x6ccf7bd7, __VMLINUX_SYMBOL_STR(__pv_phys_offset) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x784f2433, __VMLINUX_SYMBOL_STR(__ssb_driver_register) },
	{ 0xaa9087c0, __VMLINUX_SYMBOL_STR(param_ops_string) },
	{ 0x63a326ef, __VMLINUX_SYMBOL_STR(__netdev_alloc_skb) },
	{ 0xb36d73f1, __VMLINUX_SYMBOL_STR(ieee80211_stop_queue) },
	{ 0x1071bf3d, __VMLINUX_SYMBOL_STR(ieee80211_tx_status) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x1fab5905, __VMLINUX_SYMBOL_STR(wait_for_completion) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xbcf4bf9b, __VMLINUX_SYMBOL_STR(ssb_driver_unregister) },
	{ 0x712849ff, __VMLINUX_SYMBOL_STR(ssb_chipco_gpio_control) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x145a37ca, __VMLINUX_SYMBOL_STR(ieee80211_free_txskb) },
	{ 0x4bd83a6d, __VMLINUX_SYMBOL_STR(ieee80211_wake_queues) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0x328a05f1, __VMLINUX_SYMBOL_STR(strncpy) },
	{ 0x3e8c2cba, __VMLINUX_SYMBOL_STR(ssb_device_enable) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x9a0156f5, __VMLINUX_SYMBOL_STR(ieee80211_rx) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xd6b8e852, __VMLINUX_SYMBOL_STR(request_threaded_irq) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0xe40dc473, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0xb7fabbc2, __VMLINUX_SYMBOL_STR(ieee80211_ctstoself_get) },
	{ 0x2607e1cb, __VMLINUX_SYMBOL_STR(request_firmware_nowait) },
	{ 0x4c759827, __VMLINUX_SYMBOL_STR(byte_rev_table) },
	{ 0x1d4cdb6d, __VMLINUX_SYMBOL_STR(ieee80211_queue_delayed_work) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0xe2ea17e8, __VMLINUX_SYMBOL_STR(dev_kfree_skb_any) },
	{ 0xe523ad75, __VMLINUX_SYMBOL_STR(synchronize_irq) },
	{ 0xfc27bfdd, __VMLINUX_SYMBOL_STR(device_create_file) },
	{ 0xd6f52eb1, __VMLINUX_SYMBOL_STR(sdio_unregister_driver) },
	{ 0x7783bae2, __VMLINUX_SYMBOL_STR(skb_queue_tail) },
	{ 0xc6cbbc89, __VMLINUX_SYMBOL_STR(capable) },
	{ 0x3ff62317, __VMLINUX_SYMBOL_STR(local_bh_disable) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x11b29ff9, __VMLINUX_SYMBOL_STR(__ieee80211_get_rx_led_name) },
	{ 0x350bb8ab, __VMLINUX_SYMBOL_STR(ssb_pmu_set_ldo_voltage) },
	{ 0x5e379ed1, __VMLINUX_SYMBOL_STR(ssb_device_disable) },
	{ 0x37e33744, __VMLINUX_SYMBOL_STR(sdio_release_irq) },
	{ 0x863f4559, __VMLINUX_SYMBOL_STR(wiphy_rfkill_set_hw_state) },
	{ 0x3507a132, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irq) },
	{ 0x799aca4, __VMLINUX_SYMBOL_STR(local_bh_enable) },
	{ 0xb678366f, __VMLINUX_SYMBOL_STR(int_sqrt) },
	{ 0x624a6406, __VMLINUX_SYMBOL_STR(hwrng_register) },
	{ 0x96026d3c, __VMLINUX_SYMBOL_STR(__ieee80211_get_tx_led_name) },
	{ 0xc66b0d41, __VMLINUX_SYMBOL_STR(ssb_set_devtypedata) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x640ac329, __VMLINUX_SYMBOL_STR(ieee80211_wake_queue) },
	{ 0x27eccfde, __VMLINUX_SYMBOL_STR(ieee80211_generic_frame_duration) },
	{ 0x1a5e4640, __VMLINUX_SYMBOL_STR(__ieee80211_get_radio_led_name) },
	{ 0xf6ebc03b, __VMLINUX_SYMBOL_STR(net_ratelimit) },
	{ 0x80fcfdaf, __VMLINUX_SYMBOL_STR(ssb_bus_unregister) },
	{ 0xee2f25c1, __VMLINUX_SYMBOL_STR(ieee80211_register_hw) },
	{ 0xc91156f9, __VMLINUX_SYMBOL_STR(led_classdev_unregister) },
	{ 0x1e047854, __VMLINUX_SYMBOL_STR(warn_slowpath_fmt) },
	{ 0x1eb9516e, __VMLINUX_SYMBOL_STR(round_jiffies_relative) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x9388074f, __VMLINUX_SYMBOL_STR(ieee80211_alloc_hw) },
	{ 0x5353a8a0, __VMLINUX_SYMBOL_STR(dma_supported) },
	{ 0x155a3d9f, __VMLINUX_SYMBOL_STR(request_firmware) },
	{ 0x74c134b9, __VMLINUX_SYMBOL_STR(__sw_hweight32) },
	{ 0x6a8d8061, __VMLINUX_SYMBOL_STR(ieee80211_free_hw) },
	{ 0xfc624459, __VMLINUX_SYMBOL_STR(ssb_bus_may_powerdown) },
	{ 0x1cff016, __VMLINUX_SYMBOL_STR(skb_dequeue) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xb742fd7, __VMLINUX_SYMBOL_STR(simple_strtol) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0xd4669fad, __VMLINUX_SYMBOL_STR(complete) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x99bb8806, __VMLINUX_SYMBOL_STR(memmove) },
	{ 0x377db316, __VMLINUX_SYMBOL_STR(sdio_register_driver) },
	{ 0x8106da78, __VMLINUX_SYMBOL_STR(ssb_pcicore_dev_irqvecs_enable) },
	{ 0x8a4fa83b, __VMLINUX_SYMBOL_STR(__aeabi_llsr) },
	{ 0x50d6202a, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0x44a17998, __VMLINUX_SYMBOL_STR(sdio_claim_host) },
	{ 0x3c06cf54, __VMLINUX_SYMBOL_STR(ssb_pmu_set_ldo_paref) },
	{ 0x7267db00, __VMLINUX_SYMBOL_STR(hwrng_unregister) },
	{ 0x70b60936, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0xa4a33d9, __VMLINUX_SYMBOL_STR(ssb_device_is_enabled) },
	{ 0xac8f37b2, __VMLINUX_SYMBOL_STR(outer_cache) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x69c15397, __VMLINUX_SYMBOL_STR(sdio_set_block_size) },
	{ 0x8b5187c3, __VMLINUX_SYMBOL_STR(release_firmware) },
	{ 0xcb1356a2, __VMLINUX_SYMBOL_STR(ssb_pmu_spuravoid_pllupdate) },
	{ 0x5c28cca5, __VMLINUX_SYMBOL_STR(ieee80211_get_tkip_p1k_iv) },
	{ 0x4c3b5878, __VMLINUX_SYMBOL_STR(ieee80211_get_response_rate) },
	{ 0x161a8033, __VMLINUX_SYMBOL_STR(sdio_disable_func) },
	{ 0xf20dabd8, __VMLINUX_SYMBOL_STR(free_irq) },
	{ 0x2407dc39, __VMLINUX_SYMBOL_STR(sdio_release_host) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=ssb,mac80211,cfg80211";

MODULE_ALIAS("ssb:v4243id0812rev05*");
MODULE_ALIAS("ssb:v4243id0812rev06*");
MODULE_ALIAS("ssb:v4243id0812rev07*");
MODULE_ALIAS("ssb:v4243id0812rev09*");
MODULE_ALIAS("ssb:v4243id0812rev0A*");
MODULE_ALIAS("ssb:v4243id0812rev0B*");
MODULE_ALIAS("ssb:v4243id0812rev0C*");
MODULE_ALIAS("ssb:v4243id0812rev0D*");
MODULE_ALIAS("ssb:v4243id0812rev0F*");
MODULE_ALIAS("ssb:v4243id0812rev10*");
