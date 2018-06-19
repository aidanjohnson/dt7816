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
	{ 0xb819f01f, __VMLINUX_SYMBOL_STR(v4l2_event_unsubscribe) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xa3afaa39, __VMLINUX_SYMBOL_STR(v4l2_ctrl_cluster) },
	{ 0xed19e7e6, __VMLINUX_SYMBOL_STR(video_device_release_empty) },
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x67c2fa54, __VMLINUX_SYMBOL_STR(__copy_to_user) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x3f358d29, __VMLINUX_SYMBOL_STR(page_address) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0xc8b57c27, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0x6f444176, __VMLINUX_SYMBOL_STR(v4l2_device_unregister) },
	{ 0x14c47d67, __VMLINUX_SYMBOL_STR(v4l2_ctrl_handler_free) },
	{ 0xdac751f0, __VMLINUX_SYMBOL_STR(v4l2_ctrl_new_std) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0x68913526, __VMLINUX_SYMBOL_STR(usb_kill_urb) },
	{ 0xcf18e3, __VMLINUX_SYMBOL_STR(__video_register_device) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0xe426c33e, __VMLINUX_SYMBOL_STR(v4l2_device_register) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xafdf6647, __VMLINUX_SYMBOL_STR(v4l2_ctrl_new_std_menu) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xa3492aff, __VMLINUX_SYMBOL_STR(v4l2_device_disconnect) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xb223f9fb, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x78f6258c, __VMLINUX_SYMBOL_STR(mutex_lock_interruptible) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x8a39eb7, __VMLINUX_SYMBOL_STR(video_unregister_device) },
	{ 0x3704802d, __VMLINUX_SYMBOL_STR(usb_set_interface) },
	{ 0xbe048a49, __VMLINUX_SYMBOL_STR(v4l2_ctrl_subscribe_event) },
	{ 0xfacd2e14, __VMLINUX_SYMBOL_STR(pgprot_user) },
	{ 0x1049b573, __VMLINUX_SYMBOL_STR(usb_control_msg) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x89823484, __VMLINUX_SYMBOL_STR(v4l2_fh_release) },
	{ 0xfea7d91a, __VMLINUX_SYMBOL_STR(v4l2_fh_is_singular) },
	{ 0x950d5b27, __VMLINUX_SYMBOL_STR(v4l2_ctrl_new_custom) },
	{ 0x61651be, __VMLINUX_SYMBOL_STR(strcat) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0xa97c342f, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0x15cc910, __VMLINUX_SYMBOL_STR(video_devdata) },
	{ 0x3bd1b1f6, __VMLINUX_SYMBOL_STR(msecs_to_jiffies) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0xd62c833f, __VMLINUX_SYMBOL_STR(schedule_timeout) },
	{ 0x70806c73, __VMLINUX_SYMBOL_STR(v4l2_ctrl_handler_setup) },
	{ 0x32ab70a8, __VMLINUX_SYMBOL_STR(usb_driver_release_interface) },
	{ 0xa0b04675, __VMLINUX_SYMBOL_STR(vmalloc_32) },
	{ 0x1793bffb, __VMLINUX_SYMBOL_STR(v4l2_ctrl_grab) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9a681893, __VMLINUX_SYMBOL_STR(v4l2_fh_open) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x9c55cec, __VMLINUX_SYMBOL_STR(schedule_timeout_interruptible) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x55d549ff, __VMLINUX_SYMBOL_STR(remap_pfn_range) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x499cb58c, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0xb3f1ab10, __VMLINUX_SYMBOL_STR(v4l2_ctrl_handler_init_class) },
	{ 0xa3e8bb7a, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0x155a3d9f, __VMLINUX_SYMBOL_STR(request_firmware) },
	{ 0x1cfb04fa, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x1e1ff3f2, __VMLINUX_SYMBOL_STR(vmalloc_to_page) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0xcdac8a55, __VMLINUX_SYMBOL_STR(v4l2_device_put) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x4b9ab611, __VMLINUX_SYMBOL_STR(usb_free_urb) },
	{ 0x1c483a9, __VMLINUX_SYMBOL_STR(v4l2_get_timestamp) },
	{ 0x8b5187c3, __VMLINUX_SYMBOL_STR(release_firmware) },
	{ 0x9be04d52, __VMLINUX_SYMBOL_STR(video_ioctl2) },
	{ 0x904e29cb, __VMLINUX_SYMBOL_STR(v4l2_ctrl_poll) },
	{ 0x148c8de9, __VMLINUX_SYMBOL_STR(usb_alloc_urb) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("usb:v0553p0100d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0553p0140d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0553p0151d*dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "D5B5132D02BB9819B992D58");
