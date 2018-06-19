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
	{ 0xf56e3d8a, __VMLINUX_SYMBOL_STR(wl12xx_cmd_build_probe_req) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x53dff67d, __VMLINUX_SYMBOL_STR(wl12xx_debug_level) },
	{ 0xff178f6, __VMLINUX_SYMBOL_STR(__aeabi_idivmod) },
	{ 0x6f218aa2, __VMLINUX_SYMBOL_STR(wlcore_set_key) },
	{ 0x528c709d, __VMLINUX_SYMBOL_STR(simple_read_from_buffer) },
	{ 0x84439fcd, __VMLINUX_SYMBOL_STR(generic_file_llseek) },
	{ 0xa70dcea1, __VMLINUX_SYMBOL_STR(debugfs_create_dir) },
	{ 0x76b99b02, __VMLINUX_SYMBOL_STR(wlcore_event_beacon_loss) },
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x79aa04a2, __VMLINUX_SYMBOL_STR(get_random_bytes) },
	{ 0xe5d5ee62, __VMLINUX_SYMBOL_STR(wlcore_event_dummy_packet) },
	{ 0x54e9895c, __VMLINUX_SYMBOL_STR(wlcore_event_inactive_sta) },
	{ 0xc44e2808, __VMLINUX_SYMBOL_STR(wlcore_event_ba_rx_constraint) },
	{ 0xe3dd8efa, __VMLINUX_SYMBOL_STR(wlcore_rx_ba_max_subframes) },
	{ 0x52a36f42, __VMLINUX_SYMBOL_STR(wlcore_event_rssi_trigger) },
	{ 0xe2fae716, __VMLINUX_SYMBOL_STR(kmemdup) },
	{ 0x68f9960b, __VMLINUX_SYMBOL_STR(wlcore_cmd_wait_for_event_or_timeout) },
	{ 0x85b9b20a, __VMLINUX_SYMBOL_STR(wlcore_probe) },
	{ 0x33ba5cd4, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0x14e73749, __VMLINUX_SYMBOL_STR(wlcore_alloc_hw) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xbdfc0bc0, __VMLINUX_SYMBOL_STR(debugfs_create_file) },
	{ 0x7781b4da, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x37744b53, __VMLINUX_SYMBOL_STR(ieee80211_change_rx_ba_max_subframes) },
	{ 0xb61a9ae3, __VMLINUX_SYMBOL_STR(wl1271_cmd_configure) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x5d41c87c, __VMLINUX_SYMBOL_STR(param_ops_charp) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x8f045d1c, __VMLINUX_SYMBOL_STR(cancel_delayed_work) },
	{ 0x7a2d97, __VMLINUX_SYMBOL_STR(default_llseek) },
	{ 0x37ed4593, __VMLINUX_SYMBOL_STR(wlcore_event_sched_scan_completed) },
	{ 0xe36f62e6, __VMLINUX_SYMBOL_STR(wlcore_boot_upload_firmware) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xc5cdab5a, __VMLINUX_SYMBOL_STR(wlcore_set_partition) },
	{ 0x328a05f1, __VMLINUX_SYMBOL_STR(strncpy) },
	{ 0x5315c422, __VMLINUX_SYMBOL_STR(wlcore_enable_interrupts) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0xe40dc473, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0xdae7127e, __VMLINUX_SYMBOL_STR(simple_open) },
	{ 0x1d4cdb6d, __VMLINUX_SYMBOL_STR(ieee80211_queue_delayed_work) },
	{ 0x4059792f, __VMLINUX_SYMBOL_STR(print_hex_dump) },
	{ 0x7783bae2, __VMLINUX_SYMBOL_STR(skb_queue_tail) },
	{ 0x2c470f86, __VMLINUX_SYMBOL_STR(wlcore_event_channel_switch) },
	{ 0x12a38747, __VMLINUX_SYMBOL_STR(usleep_range) },
	{ 0x3bd1b1f6, __VMLINUX_SYMBOL_STR(msecs_to_jiffies) },
	{ 0x750ced5c, __VMLINUX_SYMBOL_STR(wlcore_disable_interrupts) },
	{ 0x1b7c551f, __VMLINUX_SYMBOL_STR(wlcore_remove) },
	{ 0x3746d19, __VMLINUX_SYMBOL_STR(wlcore_event_max_tx_failure) },
	{ 0x491f37bf, __VMLINUX_SYMBOL_STR(wl1271_free_tx_id) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9adb5343, __VMLINUX_SYMBOL_STR(wlcore_scan_sched_scan_results) },
	{ 0x9a272542, __VMLINUX_SYMBOL_STR(ieee80211_get_hdrlen_from_skb) },
	{ 0x30b49ae7, __VMLINUX_SYMBOL_STR(wlcore_free_hw) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x5294fba, __VMLINUX_SYMBOL_STR(wl1271_format_buffer) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x20b2bb2d, __VMLINUX_SYMBOL_STR(param_array_ops) },
	{ 0x3ae6c4bf, __VMLINUX_SYMBOL_STR(wl1271_debugfs_update_stats) },
	{ 0xccd8f2c9, __VMLINUX_SYMBOL_STR(wlcore_set_scan_chan_params) },
	{ 0x155a3d9f, __VMLINUX_SYMBOL_STR(request_firmware) },
	{ 0x6ec99d5c, __VMLINUX_SYMBOL_STR(wlcore_boot_run_firmware) },
	{ 0x6dc40d2, __VMLINUX_SYMBOL_STR(wlcore_translate_addr) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x48dff28b, __VMLINUX_SYMBOL_STR(wlcore_scan_sched_scan_ssid_list) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xfea172ba, __VMLINUX_SYMBOL_STR(wlcore_event_roc_complete) },
	{ 0x99bb8806, __VMLINUX_SYMBOL_STR(memmove) },
	{ 0xdd8bcd1d, __VMLINUX_SYMBOL_STR(wl12xx_is_dummy_packet) },
	{ 0x35c39aa9, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0xf17c7616, __VMLINUX_SYMBOL_STR(wl1271_cmd_send) },
	{ 0x8b5187c3, __VMLINUX_SYMBOL_STR(release_firmware) },
	{ 0x85b01abe, __VMLINUX_SYMBOL_STR(ieee80211_connection_loss) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=wlcore,mac80211,cfg80211";

MODULE_ALIAS("platform:wl18xx");
