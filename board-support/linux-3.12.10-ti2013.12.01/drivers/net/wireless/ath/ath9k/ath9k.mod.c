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
	{ 0x11e7095c, __VMLINUX_SYMBOL_STR(ar9003_paprd_is_done) },
	{ 0x126b9872, __VMLINUX_SYMBOL_STR(ath9k_hw_set_txq_props) },
	{ 0x41459e94, __VMLINUX_SYMBOL_STR(ieee80211_csa_finish) },
	{ 0xa55e61f2, __VMLINUX_SYMBOL_STR(ath9k_hw_init) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xe6a70a87, __VMLINUX_SYMBOL_STR(pci_bus_read_config_byte) },
	{ 0xff178f6, __VMLINUX_SYMBOL_STR(__aeabi_idivmod) },
	{ 0x6ae4d81d, __VMLINUX_SYMBOL_STR(ath9k_hw_deinit) },
	{ 0x3d30175d, __VMLINUX_SYMBOL_STR(ath9k_hw_cfg_output) },
	{ 0xe52e3763, __VMLINUX_SYMBOL_STR(mem_map) },
	{ 0x3e162649, __VMLINUX_SYMBOL_STR(ar9003_mci_send_wlan_channels) },
	{ 0xa5b889c2, __VMLINUX_SYMBOL_STR(pcim_enable_device) },
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0xc28d205d, __VMLINUX_SYMBOL_STR(ath9k_hw_setantenna) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x8e1b028d, __VMLINUX_SYMBOL_STR(ath9k_hw_gen_timer_start) },
	{ 0x87594321, __VMLINUX_SYMBOL_STR(ath9k_hw_set_gpio) },
	{ 0xe093bb43, __VMLINUX_SYMBOL_STR(ath9k_cmn_init_crypto) },
	{ 0x3250d522, __VMLINUX_SYMBOL_STR(ieee80211_queue_work) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x80d216b9, __VMLINUX_SYMBOL_STR(led_classdev_register) },
	{ 0x32f3cd32, __VMLINUX_SYMBOL_STR(pcim_iomap_table) },
	{ 0xb9932c50, __VMLINUX_SYMBOL_STR(ieee80211_csa_is_complete) },
	{ 0x3d268c44, __VMLINUX_SYMBOL_STR(devm_kzalloc) },
	{ 0x971247a3, __VMLINUX_SYMBOL_STR(ath9k_hw_numtxpending) },
	{ 0x655b8063, __VMLINUX_SYMBOL_STR(arm_dma_ops) },
	{ 0x950e8c15, __VMLINUX_SYMBOL_STR(ar9003_paprd_setup_gain_table) },
	{ 0xf90b7504, __VMLINUX_SYMBOL_STR(ath9k_hw_btcoex_enable) },
	{ 0xc13f4274, __VMLINUX_SYMBOL_STR(ath9k_hw_wait) },
	{ 0xb67590ee, __VMLINUX_SYMBOL_STR(ath9k_hw_set_interrupts) },
	{ 0x4fbf8b5, __VMLINUX_SYMBOL_STR(ath9k_cmn_get_hw_crypto_keytype) },
	{ 0xedd096e9, __VMLINUX_SYMBOL_STR(ath9k_hw_stopdmarecv) },
	{ 0x3f9eb5c8, __VMLINUX_SYMBOL_STR(ath9k_hw_btcoex_init_mci) },
	{ 0xc15c8611, __VMLINUX_SYMBOL_STR(cfg80211_chandef_create) },
	{ 0xee83d268, __VMLINUX_SYMBOL_STR(ar9003_paprd_enable) },
	{ 0xa41d5b09, __VMLINUX_SYMBOL_STR(ath9k_hw_getchan_noise) },
	{ 0x3a7431ca, __VMLINUX_SYMBOL_STR(ath_key_delete) },
	{ 0xaf23595f, __VMLINUX_SYMBOL_STR(ath9k_cmn_update_txpow) },
	{ 0xa886e8c5, __VMLINUX_SYMBOL_STR(ath9k_hw_computetxtime) },
	{ 0xa1d55e90, __VMLINUX_SYMBOL_STR(_raw_spin_lock_bh) },
	{ 0xe3d8b4d1, __VMLINUX_SYMBOL_STR(ath9k_hw_disable_interrupts) },
	{ 0x7ef39823, __VMLINUX_SYMBOL_STR(ieee80211_hdrlen) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0x6b06fdce, __VMLINUX_SYMBOL_STR(delayed_work_timer_fn) },
	{ 0x22f2a3ad, __VMLINUX_SYMBOL_STR(ath9k_hw_bstuck_nfcal) },
	{ 0xd439b33c, __VMLINUX_SYMBOL_STR(ieee80211_beacon_get_tim) },
	{ 0x30ca5954, __VMLINUX_SYMBOL_STR(ath9k_hw_gpio_get) },
	{ 0x3c8911de, __VMLINUX_SYMBOL_STR(ath_regd_init) },
	{ 0x4205ad24, __VMLINUX_SYMBOL_STR(cancel_work_sync) },
	{ 0xf9152eed, __VMLINUX_SYMBOL_STR(ath9k_hw_gettxbuf) },
	{ 0xa89ab226, __VMLINUX_SYMBOL_STR(ath9k_cmn_get_curchannel) },
	{ 0x62b0cbf8, __VMLINUX_SYMBOL_STR(ieee80211_unregister_hw) },
	{ 0x593a99b, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0xd225aeb5, __VMLINUX_SYMBOL_STR(pcie_capability_clear_and_set_word) },
	{ 0x24d7b4eb, __VMLINUX_SYMBOL_STR(cancel_delayed_work_sync) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x59e31c01, __VMLINUX_SYMBOL_STR(ieee80211_iterate_active_interfaces_atomic) },
	{ 0xd0ca0983, __VMLINUX_SYMBOL_STR(ath_gen_timer_free) },
	{ 0xcdc46118, __VMLINUX_SYMBOL_STR(ath9k_hw_setrxfilter) },
	{ 0x55d19853, __VMLINUX_SYMBOL_STR(ath9k_hw_get_txq_props) },
	{ 0xe1a14159, __VMLINUX_SYMBOL_STR(ath9k_hw_releasetxqueue) },
	{ 0xfff317b5, __VMLINUX_SYMBOL_STR(ath9k_hw_reset_tsf) },
	{ 0x4790699f, __VMLINUX_SYMBOL_STR(wiphy_rfkill_start_polling) },
	{ 0x733072bc, __VMLINUX_SYMBOL_STR(ath9k_hw_cfg_gpio_input) },
	{ 0x2e0066d7, __VMLINUX_SYMBOL_STR(ath9k_hw_kill_interrupts) },
	{ 0x6ccf7bd7, __VMLINUX_SYMBOL_STR(__pv_phys_offset) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x594ff15d, __VMLINUX_SYMBOL_STR(skb_trim) },
	{ 0xd05ce766, __VMLINUX_SYMBOL_STR(ieee80211_stop_queues) },
	{ 0xb36d73f1, __VMLINUX_SYMBOL_STR(ieee80211_stop_queue) },
	{ 0x1071bf3d, __VMLINUX_SYMBOL_STR(ieee80211_tx_status) },
	{ 0xde4c398f, __VMLINUX_SYMBOL_STR(ath_printk) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xa2bcaba8, __VMLINUX_SYMBOL_STR(ath9k_hw_process_rxdesc_edma) },
	{ 0x576ebe46, __VMLINUX_SYMBOL_STR(ar9003_paprd_populate_single_table) },
	{ 0xf04a4650, __VMLINUX_SYMBOL_STR(ath9k_hw_setopmode) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x1fab5905, __VMLINUX_SYMBOL_STR(wait_for_completion) },
	{ 0x527e74c1, __VMLINUX_SYMBOL_STR(pci_set_master) },
	{ 0x382c8a1c, __VMLINUX_SYMBOL_STR(ath9k_hw_disable) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xd5f2172f, __VMLINUX_SYMBOL_STR(del_timer_sync) },
	{ 0x3ee4e71d, __VMLINUX_SYMBOL_STR(ath9k_hw_resettxqueue) },
	{ 0xf33e0f00, __VMLINUX_SYMBOL_STR(ath_gen_timer_isr) },
	{ 0xc9c872a5, __VMLINUX_SYMBOL_STR(ath9k_hw_rxprocdesc) },
	{ 0x99dc2dde, __VMLINUX_SYMBOL_STR(ath9k_hw_gettsf64) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x26cd8b4, __VMLINUX_SYMBOL_STR(ath9k_hw_btcoex_init_2wire) },
	{ 0x37befc70, __VMLINUX_SYMBOL_STR(jiffies_to_msecs) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x145a37ca, __VMLINUX_SYMBOL_STR(ieee80211_free_txskb) },
	{ 0x6728a483, __VMLINUX_SYMBOL_STR(ath9k_hw_set_sta_beacon_timers) },
	{ 0x4fde0a11, __VMLINUX_SYMBOL_STR(ar9003_hw_bb_watchdog_dbg_info) },
	{ 0xcc42f5d4, __VMLINUX_SYMBOL_STR(ar9003_paprd_create_curve) },
	{ 0x67da9868, __VMLINUX_SYMBOL_STR(ath9k_hw_set_tsfadjust) },
	{ 0x4bd83a6d, __VMLINUX_SYMBOL_STR(ieee80211_wake_queues) },
	{ 0xfaef0ed, __VMLINUX_SYMBOL_STR(__tasklet_schedule) },
	{ 0xe52aa1c8, __VMLINUX_SYMBOL_STR(ath9k_hw_btcoex_disable) },
	{ 0xf8bfa36d, __VMLINUX_SYMBOL_STR(ath9k_hw_getrxfilter) },
	{ 0x91caa576, __VMLINUX_SYMBOL_STR(ath9k_hw_ani_monitor) },
	{ 0x2998fa98, __VMLINUX_SYMBOL_STR(ath9k_hw_gen_timer_stop) },
	{ 0x4e2481d5, __VMLINUX_SYMBOL_STR(ath_is_world_regd) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x521934aa, __VMLINUX_SYMBOL_STR(pci_bus_write_config_dword) },
	{ 0x9a0156f5, __VMLINUX_SYMBOL_STR(ieee80211_rx) },
	{ 0x5515ca7f, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xdf9abc15, __VMLINUX_SYMBOL_STR(ath9k_hw_addrxbuf_edma) },
	{ 0x8f05a105, __VMLINUX_SYMBOL_STR(ieee80211_find_sta_by_ifaddr) },
	{ 0x9545af6d, __VMLINUX_SYMBOL_STR(tasklet_init) },
	{ 0x8834396c, __VMLINUX_SYMBOL_STR(mod_timer) },
	{ 0x3b87af96, __VMLINUX_SYMBOL_STR(ath9k_hw_setup_statusring) },
	{ 0xd6b8e852, __VMLINUX_SYMBOL_STR(request_threaded_irq) },
	{ 0xe40dc473, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0x7ee11bc1, __VMLINUX_SYMBOL_STR(device_init_wakeup) },
	{ 0x44710d5d, __VMLINUX_SYMBOL_STR(wiphy_rfkill_stop_polling) },
	{ 0x2607e1cb, __VMLINUX_SYMBOL_STR(request_firmware_nowait) },
	{ 0xe753488f, __VMLINUX_SYMBOL_STR(ar9003_mci_get_next_gpm_offset) },
	{ 0x625c9f80, __VMLINUX_SYMBOL_STR(ath9k_cmn_update_ichannel) },
	{ 0x73936f0c, __VMLINUX_SYMBOL_STR(ath9k_hw_write_associd) },
	{ 0x1d4cdb6d, __VMLINUX_SYMBOL_STR(ieee80211_queue_delayed_work) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0xe2ea17e8, __VMLINUX_SYMBOL_STR(dev_kfree_skb_any) },
	{ 0x8b5505b2, __VMLINUX_SYMBOL_STR(pcim_iomap_regions) },
	{ 0xe523ad75, __VMLINUX_SYMBOL_STR(synchronize_irq) },
	{ 0xd2400912, __VMLINUX_SYMBOL_STR(ath_reg_notifier_apply) },
	{ 0x177527db, __VMLINUX_SYMBOL_STR(ath9k_hw_puttxbuf) },
	{ 0x4739dd03, __VMLINUX_SYMBOL_STR(wiphy_to_ieee80211_hw) },
	{ 0x82072614, __VMLINUX_SYMBOL_STR(tasklet_kill) },
	{ 0xbd3310fc, __VMLINUX_SYMBOL_STR(ar9003_mci_state) },
	{ 0xa78564cd, __VMLINUX_SYMBOL_STR(ath9k_hw_btcoex_init_scheme) },
	{ 0x6d4d016a, __VMLINUX_SYMBOL_STR(ath9k_hw_init_btcoex_hw) },
	{ 0x3527d183, __VMLINUX_SYMBOL_STR(ieee80211_stop_tx_ba_cb_irqsafe) },
	{ 0x2f172c4f, __VMLINUX_SYMBOL_STR(ath9k_hw_beaconq_setup) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0xf8879b07, __VMLINUX_SYMBOL_STR(ath9k_hw_name) },
	{ 0x45d0f44e, __VMLINUX_SYMBOL_STR(ath9k_hw_abortpcurecv) },
	{ 0x417db5e0, __VMLINUX_SYMBOL_STR(ath9k_hw_init_global_settings) },
	{ 0xc3e596f0, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0xd2981357, __VMLINUX_SYMBOL_STR(ath9k_cmn_count_streams) },
	{ 0x12a38747, __VMLINUX_SYMBOL_STR(usleep_range) },
	{ 0x14cd8ec1, __VMLINUX_SYMBOL_STR(pci_bus_read_config_dword) },
	{ 0xabcdf206, __VMLINUX_SYMBOL_STR(ath9k_hw_settsf64) },
	{ 0xdd3916ac, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_bh) },
	{ 0x863f4559, __VMLINUX_SYMBOL_STR(wiphy_rfkill_set_hw_state) },
	{ 0x3bd1b1f6, __VMLINUX_SYMBOL_STR(msecs_to_jiffies) },
	{ 0xbd48f270, __VMLINUX_SYMBOL_STR(ieee80211_sta_set_buffered) },
	{ 0x8dce7e7b, __VMLINUX_SYMBOL_STR(ar9003_mci_get_interrupt) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x297aa450, __VMLINUX_SYMBOL_STR(ath9k_hw_beaconinit) },
	{ 0x3a6590da, __VMLINUX_SYMBOL_STR(ieee80211_send_bar) },
	{ 0x350d44cd, __VMLINUX_SYMBOL_STR(ath9k_hw_updatetxtriglevel) },
	{ 0x74a84ccf, __VMLINUX_SYMBOL_STR(ath_hw_cycle_counters_update) },
	{ 0xc978e6c5, __VMLINUX_SYMBOL_STR(ar9003_mci_set_bt_version) },
	{ 0x473e5374, __VMLINUX_SYMBOL_STR(ath9k_hw_set_rx_bufsize) },
	{ 0xa7a8b320, __VMLINUX_SYMBOL_STR(ieee80211_get_tx_rates) },
	{ 0xd77000a9, __VMLINUX_SYMBOL_STR(ar9003_is_paprd_enabled) },
	{ 0x27e185e3, __VMLINUX_SYMBOL_STR(ar9003_get_pll_sqsum_dvc) },
	{ 0xea802da5, __VMLINUX_SYMBOL_STR(ar9003_mci_send_message) },
	{ 0x39d3dc37, __VMLINUX_SYMBOL_STR(ieee80211_get_buffered_bc) },
	{ 0x28fae1ba, __VMLINUX_SYMBOL_STR(ar9003_mci_cleanup) },
	{ 0xd796878f, __VMLINUX_SYMBOL_STR(pskb_expand_head) },
	{ 0x82a23040, __VMLINUX_SYMBOL_STR(ath9k_hw_btcoex_bt_stomp) },
	{ 0x82753f4, __VMLINUX_SYMBOL_STR(ath9k_hw_txstart) },
	{ 0xc3ed664f, __VMLINUX_SYMBOL_STR(ath9k_hw_setrxabort) },
	{ 0x2fcf877f, __VMLINUX_SYMBOL_STR(ath9k_hw_check_alive) },
	{ 0xcd3f5e8a, __VMLINUX_SYMBOL_STR(pci_unregister_driver) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x2f39312e, __VMLINUX_SYMBOL_STR(ath9k_hw_btcoex_set_concur_txprio) },
	{ 0x998078a9, __VMLINUX_SYMBOL_STR(ath_hw_setbssidmask) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x640ac329, __VMLINUX_SYMBOL_STR(ieee80211_wake_queue) },
	{ 0x3370e514, __VMLINUX_SYMBOL_STR(ath9k_hw_phy_disable) },
	{ 0x1a5e4640, __VMLINUX_SYMBOL_STR(__ieee80211_get_radio_led_name) },
	{ 0x547ee0c2, __VMLINUX_SYMBOL_STR(ar9003_mci_setup) },
	{ 0x9a272542, __VMLINUX_SYMBOL_STR(ieee80211_get_hdrlen_from_skb) },
	{ 0xeb862f4e, __VMLINUX_SYMBOL_STR(ath9k_hw_setpower) },
	{ 0x2c0c788d, __VMLINUX_SYMBOL_STR(ieee80211_sta_eosp) },
	{ 0xc45b0685, __VMLINUX_SYMBOL_STR(__ieee80211_create_tpt_led_trigger) },
	{ 0x93e135e0, __VMLINUX_SYMBOL_STR(pci_bus_write_config_byte) },
	{ 0xc91156f9, __VMLINUX_SYMBOL_STR(led_classdev_unregister) },
	{ 0xee2f25c1, __VMLINUX_SYMBOL_STR(ieee80211_register_hw) },
	{ 0x5c5257fb, __VMLINUX_SYMBOL_STR(ath9k_hw_btcoex_set_weight) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x92b1d32e, __VMLINUX_SYMBOL_STR(regulatory_hint) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x741036dc, __VMLINUX_SYMBOL_STR(ath9k_hw_setmcastfilter) },
	{ 0x9388074f, __VMLINUX_SYMBOL_STR(ieee80211_alloc_hw) },
	{ 0x223d16e9, __VMLINUX_SYMBOL_STR(ath9k_hw_putrxbuf) },
	{ 0x5353a8a0, __VMLINUX_SYMBOL_STR(dma_supported) },
	{ 0x88ea2095, __VMLINUX_SYMBOL_STR(ath_rxbuf_alloc) },
	{ 0xf02ec43b, __VMLINUX_SYMBOL_STR(ar9003_paprd_init_table) },
	{ 0x2a6ee38b, __VMLINUX_SYMBOL_STR(__pci_register_driver) },
	{ 0x601a892e, __VMLINUX_SYMBOL_STR(ath9k_hw_startpcureceive) },
	{ 0x77430c30, __VMLINUX_SYMBOL_STR(ath9k_hw_setuprxdesc) },
	{ 0xac46860d, __VMLINUX_SYMBOL_STR(ath9k_hw_setuptxqueue) },
	{ 0xfe735b52, __VMLINUX_SYMBOL_STR(ath9k_hw_abort_tx_dma) },
	{ 0x7048a42c, __VMLINUX_SYMBOL_STR(ath9k_hw_reset) },
	{ 0x6a8d8061, __VMLINUX_SYMBOL_STR(ieee80211_free_hw) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xd4669fad, __VMLINUX_SYMBOL_STR(complete) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0x99bb8806, __VMLINUX_SYMBOL_STR(memmove) },
	{ 0xf922c09f, __VMLINUX_SYMBOL_STR(ath_gen_timer_alloc) },
	{ 0xdf2fc8cb, __VMLINUX_SYMBOL_STR(ath9k_hw_btcoex_init_3wire) },
	{ 0x50d6202a, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0x5dc6f856, __VMLINUX_SYMBOL_STR(ath_key_config) },
	{ 0x921e6f99, __VMLINUX_SYMBOL_STR(ath9k_hw_enable_interrupts) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x70b60936, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0x7cf9099, __VMLINUX_SYMBOL_STR(wait_for_completion_timeout) },
	{ 0x8bc33b85, __VMLINUX_SYMBOL_STR(ath9k_hw_intrpend) },
	{ 0x47c8baf4, __VMLINUX_SYMBOL_STR(param_ops_uint) },
	{ 0xac8f37b2, __VMLINUX_SYMBOL_STR(outer_cache) },
	{ 0x994c1a5e, __VMLINUX_SYMBOL_STR(ath9k_hw_reset_calvalid) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x8b5187c3, __VMLINUX_SYMBOL_STR(release_firmware) },
	{ 0x8d3abe0e, __VMLINUX_SYMBOL_STR(ieee80211_start_tx_ba_cb_irqsafe) },
	{ 0x536adad4, __VMLINUX_SYMBOL_STR(device_set_wakeup_enable) },
	{ 0xba3c6226, __VMLINUX_SYMBOL_STR(pcie_capability_read_word) },
	{ 0xf20dabd8, __VMLINUX_SYMBOL_STR(free_irq) },
	{ 0x4ff6ad97, __VMLINUX_SYMBOL_STR(dmam_alloc_coherent) },
	{ 0x3c5bbd8e, __VMLINUX_SYMBOL_STR(ath9k_hw_set_txpowerlimit) },
	{ 0x41967229, __VMLINUX_SYMBOL_STR(ath9k_hw_stop_dma_queue) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=ath9k_hw,mac80211,ath9k_common,cfg80211,ath";

MODULE_ALIAS("pci:v0000168Cd00000023sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000024sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000027sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000029sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd0000002Asv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd0000002Asv00001A3Bsd00001C71bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd0000002Asv0000105Bsd0000E01Fbc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd0000002Asv000011ADsd00006632bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd0000002Asv000011ADsd00006642bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd0000002Asv00001A32sd00000306bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd0000002Asv0000185Fsd0000309Dbc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd0000002Asv000010CFsd0000147Cbc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd0000002Asv000010CFsd0000147Dbc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd0000002Asv000010CFsd00001536bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd0000002Bsv00001A3Bsd00002C37bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd0000002Bsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd0000002Csv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd0000002Dsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd0000002Esv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000030sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000032sv00001A3Bsd00002086bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000032sv00001A3Bsd00001237bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000032sv00001A3Bsd00002126bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000032sv00001A3Bsd0000126Abc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000032sv00001A3Bsd00002152bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000032sv0000105Bsd0000E075bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000032sv0000168Csd00003119bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000032sv0000168Csd00003122bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000032sv0000185Fsd00003119bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000032sv0000185Fsd00003027bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000032sv0000144Dsd00004105bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000032sv0000144Dsd00004106bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000032sv0000144Dsd0000410Dbc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000032sv0000144Dsd0000410Ebc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000032sv0000144Dsd0000410Fbc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000032sv0000144Dsd0000C706bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000032sv0000144Dsd0000C680bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000032sv0000144Dsd0000C708bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000032sv000017AAsd00003218bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000032sv000017AAsd00003219bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000032sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000033sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000034sv00001A3Bsd00002116bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000034sv000011ADsd00006661bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000034sv0000168Csd00003117bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000034sv000017AAsd00003214bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000034sv00001969sd00000091bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000034sv00001A3Bsd00002110bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000034sv00001043sd0000850Ebc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000034sv000011ADsd00006631bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000034sv000011ADsd00006641bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000034sv0000103Csd00001864bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000034sv000014CDsd00000063bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000034sv000014CDsd00000064bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000034sv000010CFsd00001783bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000034sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000037sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v0000168Cd00000036sv*sd*bc*sc*i*");
