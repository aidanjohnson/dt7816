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
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x72f74d23, __VMLINUX_SYMBOL_STR(mwifiex_cancel_hs) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0x1afae5e7, __VMLINUX_SYMBOL_STR(down_interruptible) },
	{ 0x68913526, __VMLINUX_SYMBOL_STR(usb_kill_urb) },
	{ 0x98d154fc, __VMLINUX_SYMBOL_STR(mwifiex_write_data_complete) },
	{ 0xdd9cf2f5, __VMLINUX_SYMBOL_STR(mwifiex_process_sleep_confirm_resp) },
	{ 0x7bc70252, __VMLINUX_SYMBOL_STR(usb_disable_autosuspend) },
	{ 0x594ff15d, __VMLINUX_SYMBOL_STR(skb_trim) },
	{ 0x63a326ef, __VMLINUX_SYMBOL_STR(__netdev_alloc_skb) },
	{ 0x1fab5905, __VMLINUX_SYMBOL_STR(wait_for_completion) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xc04f4044, __VMLINUX_SYMBOL_STR(mwifiex_add_card) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xb223f9fb, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x62893466, __VMLINUX_SYMBOL_STR(mwifiex_deauthenticate) },
	{ 0x5515ca7f, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0xe40dc473, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0xe2ea17e8, __VMLINUX_SYMBOL_STR(dev_kfree_skb_any) },
	{ 0x7783bae2, __VMLINUX_SYMBOL_STR(skb_queue_tail) },
	{ 0xa97c342f, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0x7bd3b321, __VMLINUX_SYMBOL_STR(usb_get_dev) },
	{ 0xe72ae005, __VMLINUX_SYMBOL_STR(usb_reset_device) },
	{ 0x11b78479, __VMLINUX_SYMBOL_STR(usb_bulk_msg) },
	{ 0xbb9e326a, __VMLINUX_SYMBOL_STR(usb_put_dev) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x2950baa8, __VMLINUX_SYMBOL_STR(mwifiex_process_hs_config) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x4be7fb63, __VMLINUX_SYMBOL_STR(up) },
	{ 0xa3e8bb7a, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0xbf670952, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0xa761cf1d, __VMLINUX_SYMBOL_STR(mwifiex_remove_card) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x7370cd14, __VMLINUX_SYMBOL_STR(mwifiex_enable_hs) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x70b60936, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0xa66bea15, __VMLINUX_SYMBOL_STR(mwifiex_init_shutdown_fw) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x4b9ab611, __VMLINUX_SYMBOL_STR(usb_free_urb) },
	{ 0x148c8de9, __VMLINUX_SYMBOL_STR(usb_alloc_urb) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=mwifiex";

MODULE_ALIAS("usb:v1286p2043d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1286p2044d*dc*dsc*dp*icFFiscFFipFFin*");

MODULE_INFO(srcversion, "B1F3728BFB6F302735DC6E6");
