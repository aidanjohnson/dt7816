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
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0xb223f9fb, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0xa3e8bb7a, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x74ee9098, __VMLINUX_SYMBOL_STR(sms_board_load_modules) },
	{ 0x8b5187c3, __VMLINUX_SYMBOL_STR(release_firmware) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x155a3d9f, __VMLINUX_SYMBOL_STR(request_firmware) },
	{ 0x21e36bf2, __VMLINUX_SYMBOL_STR(smscore_registry_getmode) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xbdaa8393, __VMLINUX_SYMBOL_STR(smscore_start_device) },
	{ 0x84edca2d, __VMLINUX_SYMBOL_STR(usb_init_urb) },
	{ 0x96a10e54, __VMLINUX_SYMBOL_STR(smscore_set_board_id) },
	{ 0x807fec50, __VMLINUX_SYMBOL_STR(smscore_register_device) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x844539ae, __VMLINUX_SYMBOL_STR(sms_get_board) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x3704802d, __VMLINUX_SYMBOL_STR(usb_set_interface) },
	{ 0x34bc973b, __VMLINUX_SYMBOL_STR(usb_clear_halt) },
	{ 0x59c7dbbc, __VMLINUX_SYMBOL_STR(smscore_onresponse) },
	{ 0x45284ae9, __VMLINUX_SYMBOL_STR(smsendian_handle_rx_message) },
	{ 0xa97c342f, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0x62e6752e, __VMLINUX_SYMBOL_STR(smscore_getbuffer) },
	{ 0x1e6d26a8, __VMLINUX_SYMBOL_STR(strstr) },
	{ 0x11b78479, __VMLINUX_SYMBOL_STR(usb_bulk_msg) },
	{ 0x7c576277, __VMLINUX_SYMBOL_STR(smsendian_handle_message_header) },
	{ 0x37d91069, __VMLINUX_SYMBOL_STR(smsendian_handle_tx_message) },
	{ 0x9c2225ed, __VMLINUX_SYMBOL_STR(smscore_translate_msg) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x33ed1caf, __VMLINUX_SYMBOL_STR(smscore_unregister_device) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xdc3f3281, __VMLINUX_SYMBOL_STR(smscore_putbuffer) },
	{ 0x68913526, __VMLINUX_SYMBOL_STR(usb_kill_urb) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=smsmdtv";

MODULE_ALIAS("usb:v187Fp0010d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v187Fp0100d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v187Fp0200d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v187Fp0201d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v187Fp0300d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p1700d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p1800d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p1801d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p2000d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p2009d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p200Ad*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p2010d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p2011d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p2019d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p5500d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p5510d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p5520d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p5530d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p5580d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p5590d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v187Fp0202d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v187Fp0301d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040pB900d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040pB910d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040pB980d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040pB990d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040pC000d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040pC010d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040pC080d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040pC090d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040pC0A0d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040pF5A0d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v187Fp0202d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v187Fp0301d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v187Fp0302d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v187Fp0310d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v187Fp0500d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v187Fp0600d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v187Fp0700d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v187Fp0800d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v19D2p0086d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v19D2p0078d*dc*dsc*dp*ic*isc*ip*in*");
