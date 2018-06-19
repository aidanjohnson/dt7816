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
	{ 0x33ba5cd4, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0x8729b095, __VMLINUX_SYMBOL_STR(rt2x00usb_resume) },
	{ 0xf6660c3c, __VMLINUX_SYMBOL_STR(rt2x00usb_suspend) },
	{ 0x5cef648c, __VMLINUX_SYMBOL_STR(rt2x00usb_disconnect) },
	{ 0x229a2951, __VMLINUX_SYMBOL_STR(rt2x00mac_tx_frames_pending) },
	{ 0x20ec59d7, __VMLINUX_SYMBOL_STR(rt2x00mac_get_ringparam) },
	{ 0x83c616e2, __VMLINUX_SYMBOL_STR(rt2x00mac_get_antenna) },
	{ 0xe2be7746, __VMLINUX_SYMBOL_STR(rt2x00mac_set_antenna) },
	{ 0xe4a2bda, __VMLINUX_SYMBOL_STR(rt2x00mac_flush) },
	{ 0xa075ed2b, __VMLINUX_SYMBOL_STR(rt2x00mac_rfkill_poll) },
	{ 0x2a1895a8, __VMLINUX_SYMBOL_STR(rt2x00mac_conf_tx) },
	{ 0xb4e014ce, __VMLINUX_SYMBOL_STR(rt2x00mac_get_stats) },
	{ 0xb54e2d95, __VMLINUX_SYMBOL_STR(rt2x00mac_sw_scan_complete) },
	{ 0xe4594a76, __VMLINUX_SYMBOL_STR(rt2x00mac_sw_scan_start) },
	{ 0x70db0a4d, __VMLINUX_SYMBOL_STR(rt2x00mac_set_key) },
	{ 0xf177b5cf, __VMLINUX_SYMBOL_STR(rt2x00mac_set_tim) },
	{ 0x289658b1, __VMLINUX_SYMBOL_STR(rt2x00mac_configure_filter) },
	{ 0xa1806128, __VMLINUX_SYMBOL_STR(rt2x00mac_bss_info_changed) },
	{ 0xf753dce9, __VMLINUX_SYMBOL_STR(rt2x00mac_config) },
	{ 0x629b20d1, __VMLINUX_SYMBOL_STR(rt2x00mac_remove_interface) },
	{ 0x22f2f30d, __VMLINUX_SYMBOL_STR(rt2x00mac_add_interface) },
	{ 0x4e47e1e0, __VMLINUX_SYMBOL_STR(rt2x00mac_stop) },
	{ 0x928be96e, __VMLINUX_SYMBOL_STR(rt2x00mac_start) },
	{ 0x9f0698a4, __VMLINUX_SYMBOL_STR(rt2x00mac_tx) },
	{ 0xfd54476e, __VMLINUX_SYMBOL_STR(rt2x00usb_flush_queue) },
	{ 0x626de67c, __VMLINUX_SYMBOL_STR(rt2x00usb_kick_queue) },
	{ 0x243f5c23, __VMLINUX_SYMBOL_STR(rt2x00usb_watchdog) },
	{ 0xb28f6ce8, __VMLINUX_SYMBOL_STR(rt2x00usb_clear_entry) },
	{ 0x396f32e7, __VMLINUX_SYMBOL_STR(rt2x00usb_uninitialize) },
	{ 0x6b689f79, __VMLINUX_SYMBOL_STR(rt2x00usb_initialize) },
	{ 0xb223f9fb, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0xa3e8bb7a, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x79aa04a2, __VMLINUX_SYMBOL_STR(get_random_bytes) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x955f173f, __VMLINUX_SYMBOL_STR(rt2x00usb_disable_radio) },
	{ 0xe29fcb1, __VMLINUX_SYMBOL_STR(rt2x00usb_vendor_request) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x51ebdf6c, __VMLINUX_SYMBOL_STR(rt2x00usb_vendor_req_buff_lock) },
	{ 0x50d6202a, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0xa97c342f, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5515ca7f, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0x594ff15d, __VMLINUX_SYMBOL_STR(skb_trim) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x6f7e68c8, __VMLINUX_SYMBOL_STR(rt2x00usb_vendor_request_buff) },
	{ 0x610e528a, __VMLINUX_SYMBOL_STR(rt2x00usb_probe) },
	{ 0xff178f6, __VMLINUX_SYMBOL_STR(__aeabi_idivmod) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=rt2x00usb,rt2x00lib";

MODULE_ALIAS("usb:v0B05p1706d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0B05p1707d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v050Dp7050d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v050Dp7051d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v13B1p000Dd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v13B1p0011d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v13B1p001Ad*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v14B2p3C02d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2001p3C00d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1044p8001d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1044p8007d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v06F8pE000d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0411p005Ed*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0411p0066d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0411p0067d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0411p008Bd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0411p0097d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0DB0p6861d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0DB0p6865d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0DB0p6869d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v148Fp1706d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v148Fp2570d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v148Fp9020d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v079Bp004Bd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0681p3C06d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0707pEE13d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v114Bp0110d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0769p11F3d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0EB0p9020d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0F88p3012d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v5A57p0260d*dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "6BD63200B7209622E2ACCE8");
