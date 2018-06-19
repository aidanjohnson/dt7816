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
	{ 0xeb408310, __VMLINUX_SYMBOL_STR(wlcore_boot_upload_nvs) },
	{ 0x53dff67d, __VMLINUX_SYMBOL_STR(wl12xx_debug_level) },
	{ 0x6f218aa2, __VMLINUX_SYMBOL_STR(wlcore_set_key) },
	{ 0xdd9201e2, __VMLINUX_SYMBOL_STR(wl1271_acx_init_mem_config) },
	{ 0x84439fcd, __VMLINUX_SYMBOL_STR(generic_file_llseek) },
	{ 0xa70dcea1, __VMLINUX_SYMBOL_STR(debugfs_create_dir) },
	{ 0x76b99b02, __VMLINUX_SYMBOL_STR(wlcore_event_beacon_loss) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xe5d5ee62, __VMLINUX_SYMBOL_STR(wlcore_event_dummy_packet) },
	{ 0x54e9895c, __VMLINUX_SYMBOL_STR(wlcore_event_inactive_sta) },
	{ 0xc44e2808, __VMLINUX_SYMBOL_STR(wlcore_event_ba_rx_constraint) },
	{ 0xfb396d3e, __VMLINUX_SYMBOL_STR(wl1271_acx_pm_config) },
	{ 0xb54533f7, __VMLINUX_SYMBOL_STR(usecs_to_jiffies) },
	{ 0x5e8e8bdd, __VMLINUX_SYMBOL_STR(wlcore_calc_packet_alignment) },
	{ 0x52a36f42, __VMLINUX_SYMBOL_STR(wlcore_event_rssi_trigger) },
	{ 0x68f9960b, __VMLINUX_SYMBOL_STR(wlcore_cmd_wait_for_event_or_timeout) },
	{ 0x85b9b20a, __VMLINUX_SYMBOL_STR(wlcore_probe) },
	{ 0x14e73749, __VMLINUX_SYMBOL_STR(wlcore_alloc_hw) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xbdfc0bc0, __VMLINUX_SYMBOL_STR(debugfs_create_file) },
	{ 0xe86463d7, __VMLINUX_SYMBOL_STR(wl1271_acx_set_ht_capabilities) },
	{ 0x7781b4da, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0xb61a9ae3, __VMLINUX_SYMBOL_STR(wl1271_cmd_configure) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x5d41c87c, __VMLINUX_SYMBOL_STR(param_ops_charp) },
	{ 0xabea4eab, __VMLINUX_SYMBOL_STR(wl1271_cmd_data_path) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xc9ed2989, __VMLINUX_SYMBOL_STR(wl12xx_acx_mem_cfg) },
	{ 0x8f045d1c, __VMLINUX_SYMBOL_STR(cancel_delayed_work) },
	{ 0x37ed4593, __VMLINUX_SYMBOL_STR(wlcore_event_sched_scan_completed) },
	{ 0xe36f62e6, __VMLINUX_SYMBOL_STR(wlcore_boot_upload_firmware) },
	{ 0x9e19d978, __VMLINUX_SYMBOL_STR(wl1271_acx_sleep_auth) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xc5cdab5a, __VMLINUX_SYMBOL_STR(wlcore_set_partition) },
	{ 0x5315c422, __VMLINUX_SYMBOL_STR(wlcore_enable_interrupts) },
	{ 0xb4fdb4dd, __VMLINUX_SYMBOL_STR(wl1271_cmd_test) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0xdae7127e, __VMLINUX_SYMBOL_STR(simple_open) },
	{ 0x1d4cdb6d, __VMLINUX_SYMBOL_STR(ieee80211_queue_delayed_work) },
	{ 0x4059792f, __VMLINUX_SYMBOL_STR(print_hex_dump) },
	{ 0x2c470f86, __VMLINUX_SYMBOL_STR(wlcore_event_channel_switch) },
	{ 0x3bd1b1f6, __VMLINUX_SYMBOL_STR(msecs_to_jiffies) },
	{ 0x750ced5c, __VMLINUX_SYMBOL_STR(wlcore_disable_interrupts) },
	{ 0x1b7c551f, __VMLINUX_SYMBOL_STR(wlcore_remove) },
	{ 0x3746d19, __VMLINUX_SYMBOL_STR(wlcore_event_max_tx_failure) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9adb5343, __VMLINUX_SYMBOL_STR(wlcore_scan_sched_scan_results) },
	{ 0xd0d1bee4, __VMLINUX_SYMBOL_STR(wlcore_event_soft_gemini_sense) },
	{ 0x30b49ae7, __VMLINUX_SYMBOL_STR(wlcore_free_hw) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xf58cf1eb, __VMLINUX_SYMBOL_STR(wlcore_tx_complete) },
	{ 0x5294fba, __VMLINUX_SYMBOL_STR(wl1271_format_buffer) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x3ae6c4bf, __VMLINUX_SYMBOL_STR(wl1271_debugfs_update_stats) },
	{ 0xccd8f2c9, __VMLINUX_SYMBOL_STR(wlcore_set_scan_chan_params) },
	{ 0x6ec99d5c, __VMLINUX_SYMBOL_STR(wlcore_boot_run_firmware) },
	{ 0x6dc40d2, __VMLINUX_SYMBOL_STR(wlcore_translate_addr) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x48dff28b, __VMLINUX_SYMBOL_STR(wlcore_scan_sched_scan_ssid_list) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xfea172ba, __VMLINUX_SYMBOL_STR(wlcore_event_roc_complete) },
	{ 0x35c39aa9, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0xf17c7616, __VMLINUX_SYMBOL_STR(wl1271_cmd_send) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x1965690, __VMLINUX_SYMBOL_STR(wl1271_tx_min_rate_get) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=wlcore,mac80211";

MODULE_ALIAS("platform:wl12xx");
