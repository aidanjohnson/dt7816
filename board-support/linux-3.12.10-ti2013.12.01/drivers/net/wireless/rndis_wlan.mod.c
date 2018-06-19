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
	{ 0xaa9087c0, __VMLINUX_SYMBOL_STR(param_ops_string) },
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0xe8abd28b, __VMLINUX_SYMBOL_STR(usbnet_resume) },
	{ 0x3f97822e, __VMLINUX_SYMBOL_STR(usbnet_suspend) },
	{ 0xcebe8978, __VMLINUX_SYMBOL_STR(usbnet_disconnect) },
	{ 0x1ea0d766, __VMLINUX_SYMBOL_STR(usbnet_probe) },
	{ 0x21068fee, __VMLINUX_SYMBOL_STR(rndis_tx_fixup) },
	{ 0x333b0efc, __VMLINUX_SYMBOL_STR(rndis_rx_fixup) },
	{ 0x159dbf22, __VMLINUX_SYMBOL_STR(rndis_status) },
	{ 0x1879316f, __VMLINUX_SYMBOL_STR(usbnet_tx_timeout) },
	{ 0xd63271fb, __VMLINUX_SYMBOL_STR(eth_validate_addr) },
	{ 0x5471c290, __VMLINUX_SYMBOL_STR(eth_mac_addr) },
	{ 0xd25bbb0, __VMLINUX_SYMBOL_STR(usbnet_start_xmit) },
	{ 0xbff95b28, __VMLINUX_SYMBOL_STR(usbnet_stop) },
	{ 0x42ee5024, __VMLINUX_SYMBOL_STR(usbnet_open) },
	{ 0xb223f9fb, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0xa3e8bb7a, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0x3bd1b1f6, __VMLINUX_SYMBOL_STR(msecs_to_jiffies) },
	{ 0xbce51d1a, __VMLINUX_SYMBOL_STR(cfg80211_cqm_rssi_notify) },
	{ 0x6b06fdce, __VMLINUX_SYMBOL_STR(delayed_work_timer_fn) },
	{ 0xa7d0b6b4, __VMLINUX_SYMBOL_STR(wiphy_register) },
	{ 0xe3a126e6, __VMLINUX_SYMBOL_STR(generic_rndis_bind) },
	{ 0x593a99b, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0x43a53735, __VMLINUX_SYMBOL_STR(__alloc_workqueue_key) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x14dce37f, __VMLINUX_SYMBOL_STR(wiphy_new) },
	{ 0x31d9a4bc, __VMLINUX_SYMBOL_STR(usbnet_purge_paused_rxq) },
	{ 0xbc35e3cc, __VMLINUX_SYMBOL_STR(netdev_err) },
	{ 0x9c64fbd, __VMLINUX_SYMBOL_STR(ieee80211_frequency_to_channel) },
	{ 0x81f095d2, __VMLINUX_SYMBOL_STR(wiphy_free) },
	{ 0x81dc345a, __VMLINUX_SYMBOL_STR(wiphy_unregister) },
	{ 0x388cfd12, __VMLINUX_SYMBOL_STR(rndis_unbind) },
	{ 0x8c03d20c, __VMLINUX_SYMBOL_STR(destroy_workqueue) },
	{ 0x42160169, __VMLINUX_SYMBOL_STR(flush_workqueue) },
	{ 0x4205ad24, __VMLINUX_SYMBOL_STR(cancel_work_sync) },
	{ 0x24d7b4eb, __VMLINUX_SYMBOL_STR(cancel_delayed_work_sync) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x94ee05c8, __VMLINUX_SYMBOL_STR(netif_carrier_off) },
	{ 0xb4a28b85, __VMLINUX_SYMBOL_STR(cfg80211_disconnected) },
	{ 0x4a8342f8, __VMLINUX_SYMBOL_STR(netif_carrier_on) },
	{ 0x3ba27386, __VMLINUX_SYMBOL_STR(usbnet_resume_rx) },
	{ 0xd8e55a7d, __VMLINUX_SYMBOL_STR(cfg80211_ibss_joined) },
	{ 0x2a408677, __VMLINUX_SYMBOL_STR(cfg80211_roamed) },
	{ 0x5ad2bca9, __VMLINUX_SYMBOL_STR(cfg80211_connect_result) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x2a3aa678, __VMLINUX_SYMBOL_STR(_test_and_clear_bit) },
	{ 0xe851bb05, __VMLINUX_SYMBOL_STR(queue_delayed_work_on) },
	{ 0x1eb9516e, __VMLINUX_SYMBOL_STR(round_jiffies_relative) },
	{ 0xff178f6, __VMLINUX_SYMBOL_STR(__aeabi_idivmod) },
	{ 0x79aa04a2, __VMLINUX_SYMBOL_STR(get_random_bytes) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xdd3916ac, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_bh) },
	{ 0xa1d55e90, __VMLINUX_SYMBOL_STR(_raw_spin_lock_bh) },
	{ 0x18b61eb6, __VMLINUX_SYMBOL_STR(netdev_warn) },
	{ 0xb859f38b, __VMLINUX_SYMBOL_STR(krealloc) },
	{ 0x4a2ab51e, __VMLINUX_SYMBOL_STR(cfg80211_scan_done) },
	{ 0x48f98dce, __VMLINUX_SYMBOL_STR(cfg80211_put_bss) },
	{ 0xfb835d67, __VMLINUX_SYMBOL_STR(cfg80211_inform_bss_width) },
	{ 0x713641e, __VMLINUX_SYMBOL_STR(__ieee80211_get_channel) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x8833e4ab, __VMLINUX_SYMBOL_STR(rndis_command) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x90cab3f3, __VMLINUX_SYMBOL_STR(cfg80211_pmksa_candidate_notify) },
	{ 0x44f5ed0e, __VMLINUX_SYMBOL_STR(cfg80211_michael_mic_failure) },
	{ 0x78bc26d7, __VMLINUX_SYMBOL_STR(netdev_info) },
	{ 0xcbb99977, __VMLINUX_SYMBOL_STR(usbnet_pause_rx) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x11089ac7, __VMLINUX_SYMBOL_STR(_ctype) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=usbnet,rndis_host,cfg80211";

MODULE_ALIAS("usb:v0411p00BCd*dc*dsc*dp*ic02isc02ipFFin*");
MODULE_ALIAS("usb:v0BAFp011Bd*dc*dsc*dp*ic02isc02ipFFin*");
MODULE_ALIAS("usb:v050Dp011Bd*dc*dsc*dp*ic02isc02ipFFin*");
MODULE_ALIAS("usb:v1799p011Bd*dc*dsc*dp*ic02isc02ipFFin*");
MODULE_ALIAS("usb:v13B1p0014d*dc*dsc*dp*ic02isc02ipFFin*");
MODULE_ALIAS("usb:v13B1p0026d*dc*dsc*dp*ic02isc02ipFFin*");
MODULE_ALIAS("usb:v0B05p1717d*dc*dsc*dp*ic02isc02ipFFin*");
MODULE_ALIAS("usb:v0A5CpD11Bd*dc*dsc*dp*ic02isc02ipFFin*");
MODULE_ALIAS("usb:v1690p0715d*dc*dsc*dp*ic02isc02ipFFin*");
MODULE_ALIAS("usb:v13B1p000Ed*dc*dsc*dp*ic02isc02ipFFin*");
MODULE_ALIAS("usb:v0BAFp0111d*dc*dsc*dp*ic02isc02ipFFin*");
MODULE_ALIAS("usb:v0411p004Bd*dc*dsc*dp*ic02isc02ipFFin*");
MODULE_ALIAS("usb:v*p*d*dc*dsc*dp*ic02isc02ipFFin*");
MODULE_ALIAS("usb:v*p*d*dc*dsc*dp*icEFisc01ip01in*");
