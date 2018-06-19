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
	{ 0xb819f01f, __VMLINUX_SYMBOL_STR(v4l2_event_unsubscribe) },
	{ 0xbe048a49, __VMLINUX_SYMBOL_STR(v4l2_ctrl_subscribe_event) },
	{ 0x9a8b408e, __VMLINUX_SYMBOL_STR(v4l2_ctrl_log_status) },
	{ 0x9be04d52, __VMLINUX_SYMBOL_STR(video_ioctl2) },
	{ 0xb223f9fb, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0xa3e8bb7a, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0x123959a1, __VMLINUX_SYMBOL_STR(v4l2_type_names) },
	{ 0xbdb83dff, __VMLINUX_SYMBOL_STR(videobuf_queue_vmalloc_init) },
	{ 0xa40bfc02, __VMLINUX_SYMBOL_STR(v4l2_fh_add) },
	{ 0xad5c298a, __VMLINUX_SYMBOL_STR(v4l2_fh_init) },
	{ 0xcf18e3, __VMLINUX_SYMBOL_STR(__video_register_device) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0x950d5b27, __VMLINUX_SYMBOL_STR(v4l2_ctrl_new_custom) },
	{ 0xdac751f0, __VMLINUX_SYMBOL_STR(v4l2_ctrl_new_std) },
	{ 0xb3f1ab10, __VMLINUX_SYMBOL_STR(v4l2_ctrl_handler_init_class) },
	{ 0xe426c33e, __VMLINUX_SYMBOL_STR(v4l2_device_register) },
	{ 0xd6ee688f, __VMLINUX_SYMBOL_STR(vmalloc) },
	{ 0x86a4889a, __VMLINUX_SYMBOL_STR(kmalloc_order_trace) },
	{ 0xe72ae005, __VMLINUX_SYMBOL_STR(usb_reset_device) },
	{ 0x155a3d9f, __VMLINUX_SYMBOL_STR(request_firmware) },
	{ 0x148c8de9, __VMLINUX_SYMBOL_STR(usb_alloc_urb) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0x593a99b, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0x7bd3b321, __VMLINUX_SYMBOL_STR(usb_get_dev) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x8834396c, __VMLINUX_SYMBOL_STR(mod_timer) },
	{ 0x14c47d67, __VMLINUX_SYMBOL_STR(v4l2_ctrl_handler_free) },
	{ 0x8a39eb7, __VMLINUX_SYMBOL_STR(video_unregister_device) },
	{ 0xa3492aff, __VMLINUX_SYMBOL_STR(v4l2_device_disconnect) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x6f444176, __VMLINUX_SYMBOL_STR(v4l2_device_unregister) },
	{ 0xbb9e326a, __VMLINUX_SYMBOL_STR(usb_put_dev) },
	{ 0x8b5187c3, __VMLINUX_SYMBOL_STR(release_firmware) },
	{ 0xc996d097, __VMLINUX_SYMBOL_STR(del_timer) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x6da625c4, __VMLINUX_SYMBOL_STR(videobuf_iolock) },
	{ 0x1049b573, __VMLINUX_SYMBOL_STR(usb_control_msg) },
	{ 0xf24052a8, __VMLINUX_SYMBOL_STR(v4l2_fh_exit) },
	{ 0xd8842c8a, __VMLINUX_SYMBOL_STR(v4l2_fh_del) },
	{ 0x67acc003, __VMLINUX_SYMBOL_STR(videobuf_mmap_free) },
	{ 0x15cc910, __VMLINUX_SYMBOL_STR(video_devdata) },
	{ 0xd898e9dc, __VMLINUX_SYMBOL_STR(videobuf_streamoff) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0x4b9ab611, __VMLINUX_SYMBOL_STR(usb_free_urb) },
	{ 0x68913526, __VMLINUX_SYMBOL_STR(usb_kill_urb) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x17e9f0be, __VMLINUX_SYMBOL_STR(videobuf_streamon) },
	{ 0x8b58595a, __VMLINUX_SYMBOL_STR(videobuf_queue_is_busy) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0xc8b57c27, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xd62c833f, __VMLINUX_SYMBOL_STR(schedule_timeout) },
	{ 0x1cfb04fa, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x499cb58c, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x3bd1b1f6, __VMLINUX_SYMBOL_STR(msecs_to_jiffies) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x11b78479, __VMLINUX_SYMBOL_STR(usb_bulk_msg) },
	{ 0x664776f5, __VMLINUX_SYMBOL_STR(videobuf_vmalloc_free) },
	{ 0x6e96893d, __VMLINUX_SYMBOL_STR(v4l2_ctrl_s_ctrl) },
	{ 0xd89decaf, __VMLINUX_SYMBOL_STR(videobuf_poll_stream) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x904e29cb, __VMLINUX_SYMBOL_STR(v4l2_ctrl_poll) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x715c156a, __VMLINUX_SYMBOL_STR(videobuf_mmap_mapper) },
	{ 0x78f6258c, __VMLINUX_SYMBOL_STR(mutex_lock_interruptible) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x312bc183, __VMLINUX_SYMBOL_STR(videobuf_reqbufs) },
	{ 0x5b3fb26f, __VMLINUX_SYMBOL_STR(videobuf_querybuf) },
	{ 0xfc3d209d, __VMLINUX_SYMBOL_STR(videobuf_qbuf) },
	{ 0x61fbc681, __VMLINUX_SYMBOL_STR(videobuf_dqbuf) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x5c2bef44, __VMLINUX_SYMBOL_STR(videobuf_to_vmalloc) },
	{ 0x1c483a9, __VMLINUX_SYMBOL_STR(v4l2_get_timestamp) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0xa97c342f, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=videobuf-vmalloc,videobuf-core";

MODULE_ALIAS("usb:v1943p2255d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1943p2257d*dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "AFF3AAE46C7AC22CDCAD72D");
