#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.arch = MODULE_ARCH_INIT,
};

MODULE_INFO(intree, "Y");

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xb5c97a0d, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xb524263f, __VMLINUX_SYMBOL_STR(rtl_deinit_deferred_work) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0xe0798f45, __VMLINUX_SYMBOL_STR(rtl_deinit_core) },
	{ 0xcc5c0060, __VMLINUX_SYMBOL_STR(usb_get_from_anchor) },
	{ 0x4205ad24, __VMLINUX_SYMBOL_STR(cancel_work_sync) },
	{ 0xe2fae716, __VMLINUX_SYMBOL_STR(kmemdup) },
	{ 0x62b0cbf8, __VMLINUX_SYMBOL_STR(ieee80211_unregister_hw) },
	{ 0x64bd2bb4, __VMLINUX_SYMBOL_STR(usb_unanchor_urb) },
	{ 0x63a326ef, __VMLINUX_SYMBOL_STR(__netdev_alloc_skb) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0x1fab5905, __VMLINUX_SYMBOL_STR(wait_for_completion) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xa4efed60, __VMLINUX_SYMBOL_STR(skb_queue_purge) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x2d75417a, __VMLINUX_SYMBOL_STR(rtl_init_core) },
	{ 0xfaef0ed, __VMLINUX_SYMBOL_STR(__tasklet_schedule) },
	{ 0xcbfd1640, __VMLINUX_SYMBOL_STR(rtl_action_proc) },
	{ 0x4c4b31af, __VMLINUX_SYMBOL_STR(rtl_dbgp_flag_init) },
	{ 0x1049b573, __VMLINUX_SYMBOL_STR(usb_control_msg) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x9a0156f5, __VMLINUX_SYMBOL_STR(ieee80211_rx) },
	{ 0xf8ff6add, __VMLINUX_SYMBOL_STR(rtl_lps_change_work_callback) },
	{ 0xa9145cad, __VMLINUX_SYMBOL_STR(rtl_init_rx_config) },
	{ 0xe40dc473, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0x9f038e56, __VMLINUX_SYMBOL_STR(usb_free_coherent) },
	{ 0xe2ea17e8, __VMLINUX_SYMBOL_STR(dev_kfree_skb_any) },
	{ 0x82072614, __VMLINUX_SYMBOL_STR(tasklet_kill) },
	{ 0x7783bae2, __VMLINUX_SYMBOL_STR(skb_queue_tail) },
	{ 0xa97c342f, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0x7bd3b321, __VMLINUX_SYMBOL_STR(usb_get_dev) },
	{ 0x78cf4589, __VMLINUX_SYMBOL_STR(usb_kill_anchored_urbs) },
	{ 0xbb9e326a, __VMLINUX_SYMBOL_STR(usb_put_dev) },
	{ 0x28558c71, __VMLINUX_SYMBOL_STR(ieee80211_tx_status_irqsafe) },
	{ 0x69ebeee8, __VMLINUX_SYMBOL_STR(rtl_ops) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x2c55ec3d, __VMLINUX_SYMBOL_STR(rtl_ips_nic_on) },
	{ 0x9388074f, __VMLINUX_SYMBOL_STR(ieee80211_alloc_hw) },
	{ 0x3baf6ea4, __VMLINUX_SYMBOL_STR(rtl_is_special_data) },
	{ 0x6a8d8061, __VMLINUX_SYMBOL_STR(ieee80211_free_hw) },
	{ 0x1cff016, __VMLINUX_SYMBOL_STR(skb_dequeue) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xd4669fad, __VMLINUX_SYMBOL_STR(complete) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0x82925eed, __VMLINUX_SYMBOL_STR(usb_alloc_coherent) },
	{ 0x70b60936, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x4b9ab611, __VMLINUX_SYMBOL_STR(usb_free_urb) },
	{ 0x8a9175a, __VMLINUX_SYMBOL_STR(rtl_beacon_statistic) },
	{ 0x8be2d05b, __VMLINUX_SYMBOL_STR(usb_anchor_urb) },
	{ 0x148c8de9, __VMLINUX_SYMBOL_STR(usb_alloc_urb) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=rtlwifi,mac80211";

