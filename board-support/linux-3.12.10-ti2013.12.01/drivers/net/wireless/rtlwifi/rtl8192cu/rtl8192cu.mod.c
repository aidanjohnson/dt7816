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
	{ 0x26896080, __VMLINUX_SYMBOL_STR(rtl_cam_delete_one_entry) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0x75ec9595, __VMLINUX_SYMBOL_STR(rtl_fw_cb) },
	{ 0xf8e51de9, __VMLINUX_SYMBOL_STR(rtl_cam_get_free_entry) },
	{ 0x8743008a, __VMLINUX_SYMBOL_STR(rtl92c_phy_set_rfpath_switch) },
	{ 0x29774356, __VMLINUX_SYMBOL_STR(rtl_usb_disconnect) },
	{ 0xb774d936, __VMLINUX_SYMBOL_STR(_rtl92c_phy_fw_rf_serial_read) },
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x65bf9b80, __VMLINUX_SYMBOL_STR(rtl92c_phy_set_txpower_level) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x1eae696d, __VMLINUX_SYMBOL_STR(rtl92c_set_fw_rsvdpagepkt) },
	{ 0xbaef7de6, __VMLINUX_SYMBOL_STR(rtl92c_dm_check_txpower_tracking) },
	{ 0x290f8f9b, __VMLINUX_SYMBOL_STR(rtl_ps_disable_nic) },
	{ 0x87c9b6f2, __VMLINUX_SYMBOL_STR(rtl92c_dm_watchdog) },
	{ 0xe7690366, __VMLINUX_SYMBOL_STR(_rtl92c_phy_init_bb_rf_register_definition) },
	{ 0xde8c96aa, __VMLINUX_SYMBOL_STR(_rtl92c_phy_rf_serial_write) },
	{ 0xfd2700da, __VMLINUX_SYMBOL_STR(rtl_get_tcb_desc) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0x6f198a61, __VMLINUX_SYMBOL_STR(_rtl92c_phy_rf_serial_read) },
	{ 0xeb955666, __VMLINUX_SYMBOL_STR(rtl92c_phy_set_bw_mode) },
	{ 0xa9e36acf, __VMLINUX_SYMBOL_STR(rtl92c_phy_lc_calibrate) },
	{ 0xb3314d48, __VMLINUX_SYMBOL_STR(_rtl92c_phy_calculate_bit_shift) },
	{ 0x7be4dc0d, __VMLINUX_SYMBOL_STR(rtl_efuse_shadow_map_update) },
	{ 0x33ba5cd4, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xcce1689e, __VMLINUX_SYMBOL_STR(rtl_cam_add_one_entry) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0xfeac6c4, __VMLINUX_SYMBOL_STR(rtl92c_dm_init_edca_turbo) },
	{ 0x50ee3b2c, __VMLINUX_SYMBOL_STR(rtl92c_phy_iq_calibrate) },
	{ 0xfe21cff8, __VMLINUX_SYMBOL_STR(rtl92c_dm_init) },
	{ 0x2336330f, __VMLINUX_SYMBOL_STR(rtl_usb_probe) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x1d17a690, __VMLINUX_SYMBOL_STR(rtl92c_phy_set_bb_reg) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xd00ef43, __VMLINUX_SYMBOL_STR(rtl_ps_enable_nic) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x37befc70, __VMLINUX_SYMBOL_STR(jiffies_to_msecs) },
	{ 0xb223f9fb, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x34eae2fb, __VMLINUX_SYMBOL_STR(rtl92c_dm_rf_saving) },
	{ 0x91cc45f0, __VMLINUX_SYMBOL_STR(rtl92c_set_fw_pwrmode_cmd) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x9a0156f5, __VMLINUX_SYMBOL_STR(ieee80211_rx) },
	{ 0xd3b4647, __VMLINUX_SYMBOL_STR(dm_writepowerindex) },
	{ 0x5515ca7f, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x7ac1dda4, __VMLINUX_SYMBOL_STR(_rtl92c_phy_fw_rf_serial_write) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0xe40dc473, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0xa481ebe7, __VMLINUX_SYMBOL_STR(_rtl92c_phy_set_rf_sleep) },
	{ 0x2607e1cb, __VMLINUX_SYMBOL_STR(request_firmware_nowait) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0xea823942, __VMLINUX_SYMBOL_STR(rtlwifi_rate_mapping) },
	{ 0x5f84268c, __VMLINUX_SYMBOL_STR(rtl92c_set_fw_joinbss_report_cmd) },
	{ 0x532519af, __VMLINUX_SYMBOL_STR(rtl92c_download_fw) },
	{ 0x40a9b349, __VMLINUX_SYMBOL_STR(vzalloc) },
	{ 0x7b0dced6, __VMLINUX_SYMBOL_STR(rtl92c_phy_set_io_cmd) },
	{ 0x2940c7a5, __VMLINUX_SYMBOL_STR(ieee80211_find_sta) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0xab3b1178, __VMLINUX_SYMBOL_STR(rtl_cam_mark_invalid) },
	{ 0xc635a700, __VMLINUX_SYMBOL_STR(rtl92c_phy_rf_config) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x8f85b322, __VMLINUX_SYMBOL_STR(rtl_cam_del_entry) },
	{ 0xbb44bd01, __VMLINUX_SYMBOL_STR(rtl92c_phy_scan_operation_backup) },
	{ 0xf5121e87, __VMLINUX_SYMBOL_STR(rtl_cam_empty_entry) },
	{ 0x4cab1ded, __VMLINUX_SYMBOL_STR(rtl8192_phy_check_is_legal_rfpath) },
	{ 0xc0652164, __VMLINUX_SYMBOL_STR(rtl92ce_phy_set_rf_on) },
	{ 0xa3e8bb7a, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0x657a720, __VMLINUX_SYMBOL_STR(rtl92c_phy_query_bb_reg) },
	{ 0x48df8bfb, __VMLINUX_SYMBOL_STR(_rtl92c_store_pwrIndex_diffrate_offset) },
	{ 0x1cff016, __VMLINUX_SYMBOL_STR(skb_dequeue) },
	{ 0xe57e9860, __VMLINUX_SYMBOL_STR(rtl_cam_reset_all_entry) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x20459d8a, __VMLINUX_SYMBOL_STR(dm_restorepowerindex) },
	{ 0x247d46ab, __VMLINUX_SYMBOL_STR(efuse_read_1byte) },
	{ 0x4ea83d8d, __VMLINUX_SYMBOL_STR(_rtl92c_phy_bb8192c_config_parafile) },
	{ 0x6fcc849b, __VMLINUX_SYMBOL_STR(rtl92c_fill_h2c_cmd) },
	{ 0x391298a3, __VMLINUX_SYMBOL_STR(rtl92c_phy_sw_chnl) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=rtlwifi,rtl8192c-common,rtl_usb,mac80211";

MODULE_ALIAS("usb:v0BDAp8191d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BDAp018Ad*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BDAp8170d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BDAp8176d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BDAp8177d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BDAp817Ad*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BDAp817Bd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BDAp817Dd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BDAp817Ed*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BDAp817Fd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BDAp818Ad*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BDAp819Ad*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BDAp8754d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BDAp8178d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BDAp817Cd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v050Dp1102d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v050Dp11F2d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v06F8pE033d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v07B8p8188d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v07B8p8189d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0846p9041d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BDAp5088d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0DF6p0052d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0DF6p005Cd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0DF6p0077d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0EB0p9071d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v4856p0091d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v103Cp1629d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v13D3p3357d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2001p3308d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2019p4902d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2019pAB2Ad*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2019pAB2Ed*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2019pED17d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v20F4p648Bd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v7392p7811d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v13D3p3358d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v13D3p3359d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v4855p0090d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v4855p0091d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v9846p9041d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BDAp317Fd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v04F2pAFF7d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v04F2pAFF9d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v04F2pAFFAd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v04F2pAFF8d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v04F2pAFFBd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v04F2pAFFCd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2019p1201d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v050Dp1004d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v050Dp2102d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v050Dp2103d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0586p341Fd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v07AAp0056d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v07B8p8178d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0846p9021d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0846pF001d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0B05p17ABd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BDAp8186d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0DF6p0061d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0E66p0019d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2001p3307d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2001p3309d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2001p330Ad*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2019pAB2Bd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v20F4p624Dd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2357p0100d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v7392p7822d*dc*dsc*dp*ic*isc*ip*in*");
