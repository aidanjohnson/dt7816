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
	{ 0x1f8f5fc1, __VMLINUX_SYMBOL_STR(no_llseek) },
	{ 0xb223f9fb, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0xa3e8bb7a, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0xd62c833f, __VMLINUX_SYMBOL_STR(schedule_timeout) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xd9d7910e, __VMLINUX_SYMBOL_STR(usb_register_dev) },
	{ 0x148c8de9, __VMLINUX_SYMBOL_STR(usb_alloc_urb) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xe0b78cc1, __VMLINUX_SYMBOL_STR(usb_string) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xaabfa73f, __VMLINUX_SYMBOL_STR(usb_deregister_dev) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x4b9ab611, __VMLINUX_SYMBOL_STR(usb_free_urb) },
	{ 0x68913526, __VMLINUX_SYMBOL_STR(usb_kill_urb) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x861ccbb8, __VMLINUX_SYMBOL_STR(usb_find_interface) },
	{ 0x2cbe5bf9, __VMLINUX_SYMBOL_STR(nonseekable_open) },
	{ 0x67c2fa54, __VMLINUX_SYMBOL_STR(__copy_to_user) },
	{ 0x3507a132, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irq) },
	{ 0xac8f37b2, __VMLINUX_SYMBOL_STR(outer_cache) },
	{ 0xc8b57c27, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x1049b573, __VMLINUX_SYMBOL_STR(usb_control_msg) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xfbc74f64, __VMLINUX_SYMBOL_STR(__copy_from_user) },
	{ 0x1cfb04fa, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0x499cb58c, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x78f6258c, __VMLINUX_SYMBOL_STR(mutex_lock_interruptible) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xa97c342f, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0xbf670952, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("usb:v0F11p1000d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0F11p1001d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0F11p1010d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0F11p1011d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0F11p1020d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0F11p1021d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0F11p1031d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0F11p1032d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0F11p1033d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0F11p1035d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0F11p1038d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0F11p1080d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0F11p1081d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0F11p1090d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0F11p10A0d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0F11p10B0d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0F11p1100d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0F11p1101d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0F11p1200d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0F11p1210d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0F11p2000d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0F11p2010d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0F11p2020d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0F11p2030d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0F11p2040d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0F11p2050d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0F11p2051d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0F11p2060d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0F11p2070d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0F11p2080d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0F11p2090d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0F11p20A0d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v08F7p0002d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v08F7p0003d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v08F7p0004d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v08F7p0006d*dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "B30799C3B2A20FFABFF1469");
