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
	{ 0x8db36500, __VMLINUX_SYMBOL_STR(vb2_ioctl_reqbufs) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xb819f01f, __VMLINUX_SYMBOL_STR(v4l2_event_unsubscribe) },
	{ 0xa3afaa39, __VMLINUX_SYMBOL_STR(v4l2_ctrl_cluster) },
	{ 0xed19e7e6, __VMLINUX_SYMBOL_STR(video_device_release_empty) },
	{ 0xfd3bb210, __VMLINUX_SYMBOL_STR(usb_altnum_to_altsetting) },
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x9a8b408e, __VMLINUX_SYMBOL_STR(v4l2_ctrl_log_status) },
	{ 0x6f444176, __VMLINUX_SYMBOL_STR(v4l2_device_unregister) },
	{ 0x14c47d67, __VMLINUX_SYMBOL_STR(v4l2_ctrl_handler_free) },
	{ 0xdac751f0, __VMLINUX_SYMBOL_STR(v4l2_ctrl_new_std) },
	{ 0xb174a548, __VMLINUX_SYMBOL_STR(vb2_fop_poll) },
	{ 0xcdf0d27d, __VMLINUX_SYMBOL_STR(vb2_ioctl_streamon) },
	{ 0x68913526, __VMLINUX_SYMBOL_STR(usb_kill_urb) },
	{ 0xa55d65e6, __VMLINUX_SYMBOL_STR(vb2_ops_wait_prepare) },
	{ 0xcf18e3, __VMLINUX_SYMBOL_STR(__video_register_device) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0xe426c33e, __VMLINUX_SYMBOL_STR(v4l2_device_register) },
	{ 0x3f7887a1, __VMLINUX_SYMBOL_STR(vb2_fop_read) },
	{ 0xb79a5aed, __VMLINUX_SYMBOL_STR(input_event) },
	{ 0xafdf6647, __VMLINUX_SYMBOL_STR(v4l2_ctrl_new_std_menu) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xdd0a2ba2, __VMLINUX_SYMBOL_STR(strlcat) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xa3492aff, __VMLINUX_SYMBOL_STR(v4l2_device_disconnect) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xff7a3526, __VMLINUX_SYMBOL_STR(vb2_vmalloc_memops) },
	{ 0xe0b78cc1, __VMLINUX_SYMBOL_STR(usb_string) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0xc6373326, __VMLINUX_SYMBOL_STR(vb2_fop_mmap) },
	{ 0x3a80e54a, __VMLINUX_SYMBOL_STR(vb2_ioctl_qbuf) },
	{ 0xb223f9fb, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x78f6258c, __VMLINUX_SYMBOL_STR(mutex_lock_interruptible) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x8a39eb7, __VMLINUX_SYMBOL_STR(video_unregister_device) },
	{ 0x3704802d, __VMLINUX_SYMBOL_STR(usb_set_interface) },
	{ 0xbe048a49, __VMLINUX_SYMBOL_STR(v4l2_ctrl_subscribe_event) },
	{ 0x6acff241, __VMLINUX_SYMBOL_STR(vb2_plane_vaddr) },
	{ 0x8e511414, __VMLINUX_SYMBOL_STR(vb2_buffer_done) },
	{ 0x1049b573, __VMLINUX_SYMBOL_STR(usb_control_msg) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x950d5b27, __VMLINUX_SYMBOL_STR(v4l2_ctrl_new_custom) },
	{ 0x9f038e56, __VMLINUX_SYMBOL_STR(usb_free_coherent) },
	{ 0x1b5dcb4b, __VMLINUX_SYMBOL_STR(vb2_ioctl_dqbuf) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0xa97c342f, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0x40a9b349, __VMLINUX_SYMBOL_STR(vzalloc) },
	{ 0x7444907b, __VMLINUX_SYMBOL_STR(vb2_fop_release) },
	{ 0x15cc910, __VMLINUX_SYMBOL_STR(video_devdata) },
	{ 0xaa58a0ae, __VMLINUX_SYMBOL_STR(input_register_device) },
	{ 0x86a4889a, __VMLINUX_SYMBOL_STR(kmalloc_order_trace) },
	{ 0x55e25a41, __VMLINUX_SYMBOL_STR(input_free_device) },
	{ 0x495426ee, __VMLINUX_SYMBOL_STR(v4l2_ctrl_get_name) },
	{ 0x9df055b, __VMLINUX_SYMBOL_STR(v4l2_ctrl_auto_cluster) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x9a681893, __VMLINUX_SYMBOL_STR(v4l2_fh_open) },
	{ 0xf2efe380, __VMLINUX_SYMBOL_STR(vb2_ioctl_querybuf) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x657c72c4, __VMLINUX_SYMBOL_STR(input_unregister_device) },
	{ 0x20b2bb2d, __VMLINUX_SYMBOL_STR(param_array_ops) },
	{ 0xb3f1ab10, __VMLINUX_SYMBOL_STR(v4l2_ctrl_handler_init_class) },
	{ 0xa3e8bb7a, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0xcde6c1a9, __VMLINUX_SYMBOL_STR(vb2_ops_wait_finish) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xc2d63bc1, __VMLINUX_SYMBOL_STR(usb_ifnum_to_if) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x82925eed, __VMLINUX_SYMBOL_STR(usb_alloc_coherent) },
	{ 0xc8166e2, __VMLINUX_SYMBOL_STR(vb2_ioctl_streamoff) },
	{ 0xcdac8a55, __VMLINUX_SYMBOL_STR(v4l2_device_put) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x4b9ab611, __VMLINUX_SYMBOL_STR(usb_free_urb) },
	{ 0x1c483a9, __VMLINUX_SYMBOL_STR(v4l2_get_timestamp) },
	{ 0x9be04d52, __VMLINUX_SYMBOL_STR(video_ioctl2) },
	{ 0x148c8de9, __VMLINUX_SYMBOL_STR(usb_alloc_urb) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
	{ 0x26a6901f, __VMLINUX_SYMBOL_STR(input_allocate_device) },
	{ 0x5f18405, __VMLINUX_SYMBOL_STR(vb2_queue_init) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=videobuf2-core,videobuf2-vmalloc";

MODULE_ALIAS("usb:v0471p0302d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0471p0303d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0471p0304d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0471p0307d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0471p0308d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0471p030Cd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0471p0310d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0471p0311d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0471p0312d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0471p0313d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0471p0329d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v069Ap0001d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v046Dp08B0d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v046Dp08B1d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v046Dp08B2d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v046Dp08B3d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v046Dp08B4d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v046Dp08B5d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v046Dp08B6d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v046Dp08B7d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v046Dp08B8d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v055Dp9000d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v055Dp9001d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v055Dp9002d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v041Ep400Cd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v041Ep4011d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v04CCp8116d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v06BEp8116d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0D81p1910d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0D81p1900d*dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "97982817863E478DA08CECC");
