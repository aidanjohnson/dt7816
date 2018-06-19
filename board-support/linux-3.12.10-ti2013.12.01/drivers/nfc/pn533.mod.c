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
	{ 0xb223f9fb, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0xa3e8bb7a, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0x868b0fb4, __VMLINUX_SYMBOL_STR(nfc_get_local_general_bytes) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x8834396c, __VMLINUX_SYMBOL_STR(mod_timer) },
	{ 0x79aa04a2, __VMLINUX_SYMBOL_STR(get_random_bytes) },
	{ 0x6b06fdce, __VMLINUX_SYMBOL_STR(delayed_work_timer_fn) },
	{ 0xbb9e326a, __VMLINUX_SYMBOL_STR(usb_put_dev) },
	{ 0x7ef0b00e, __VMLINUX_SYMBOL_STR(nfc_register_device) },
	{ 0x5e584490, __VMLINUX_SYMBOL_STR(nfc_allocate_device) },
	{ 0x43a53735, __VMLINUX_SYMBOL_STR(__alloc_workqueue_key) },
	{ 0x593a99b, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0x148c8de9, __VMLINUX_SYMBOL_STR(usb_alloc_urb) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x7bd3b321, __VMLINUX_SYMBOL_STR(usb_get_dev) },
	{ 0xbb46cba5, __VMLINUX_SYMBOL_STR(nfc_alloc_recv_skb) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xe039aeb4, __VMLINUX_SYMBOL_STR(usb_unlink_urb) },
	{ 0x594ff15d, __VMLINUX_SYMBOL_STR(skb_trim) },
	{ 0x27d50b9, __VMLINUX_SYMBOL_STR(nfc_tm_data_received) },
	{ 0x18028683, __VMLINUX_SYMBOL_STR(nfc_tm_deactivated) },
	{ 0xe851bb05, __VMLINUX_SYMBOL_STR(queue_delayed_work_on) },
	{ 0x3bd1b1f6, __VMLINUX_SYMBOL_STR(msecs_to_jiffies) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xad83de93, __VMLINUX_SYMBOL_STR(nfc_tm_activated) },
	{ 0xff178f6, __VMLINUX_SYMBOL_STR(__aeabi_idivmod) },
	{ 0x7f72278e, __VMLINUX_SYMBOL_STR(nfc_dep_link_is_up) },
	{ 0x2d056ff2, __VMLINUX_SYMBOL_STR(nfc_set_remote_general_bytes) },
	{ 0xf407c8d6, __VMLINUX_SYMBOL_STR(nfc_targets_found) },
	{ 0xd4669fad, __VMLINUX_SYMBOL_STR(complete) },
	{ 0x1fab5905, __VMLINUX_SYMBOL_STR(wait_for_completion) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0x50d6202a, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x1cff016, __VMLINUX_SYMBOL_STR(skb_dequeue) },
	{ 0x7783bae2, __VMLINUX_SYMBOL_STR(skb_queue_tail) },
	{ 0xe40dc473, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0xc3e596f0, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x4059792f, __VMLINUX_SYMBOL_STR(print_hex_dump) },
	{ 0xa97c342f, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0x70b60936, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0x5515ca7f, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x4b9ab611, __VMLINUX_SYMBOL_STR(usb_free_urb) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xc996d097, __VMLINUX_SYMBOL_STR(del_timer) },
	{ 0xa4efed60, __VMLINUX_SYMBOL_STR(skb_queue_purge) },
	{ 0x8c03d20c, __VMLINUX_SYMBOL_STR(destroy_workqueue) },
	{ 0x74ce05b8, __VMLINUX_SYMBOL_STR(flush_delayed_work) },
	{ 0x68913526, __VMLINUX_SYMBOL_STR(usb_kill_urb) },
	{ 0x63d684c9, __VMLINUX_SYMBOL_STR(put_device) },
	{ 0x3894c7bc, __VMLINUX_SYMBOL_STR(nfc_unregister_device) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=nfc";

MODULE_ALIAS("usb:v04CCp2533d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v04E6p5591d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v054Cp02E1d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v072Fp2200d*dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "97094D1AB179355B55227C0");
