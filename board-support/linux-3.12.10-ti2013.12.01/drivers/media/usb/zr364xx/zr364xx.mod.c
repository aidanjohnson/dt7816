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
	{ 0xed19e7e6, __VMLINUX_SYMBOL_STR(video_device_release_empty) },
	{ 0xb223f9fb, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0xa3e8bb7a, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0x8b58595a, __VMLINUX_SYMBOL_STR(videobuf_queue_is_busy) },
	{ 0xabbee291, __VMLINUX_SYMBOL_STR(videobuf_read_one) },
	{ 0x17e9f0be, __VMLINUX_SYMBOL_STR(videobuf_streamon) },
	{ 0x89823484, __VMLINUX_SYMBOL_STR(v4l2_fh_release) },
	{ 0x1049b573, __VMLINUX_SYMBOL_STR(usb_control_msg) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x6da625c4, __VMLINUX_SYMBOL_STR(videobuf_iolock) },
	{ 0x664776f5, __VMLINUX_SYMBOL_STR(videobuf_vmalloc_free) },
	{ 0x715c156a, __VMLINUX_SYMBOL_STR(videobuf_mmap_mapper) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0x67acc003, __VMLINUX_SYMBOL_STR(videobuf_mmap_free) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x70806c73, __VMLINUX_SYMBOL_STR(v4l2_ctrl_handler_setup) },
	{ 0x6f444176, __VMLINUX_SYMBOL_STR(v4l2_device_unregister) },
	{ 0x14c47d67, __VMLINUX_SYMBOL_STR(v4l2_ctrl_handler_free) },
	{ 0xcf18e3, __VMLINUX_SYMBOL_STR(__video_register_device) },
	{ 0xbdb83dff, __VMLINUX_SYMBOL_STR(videobuf_queue_vmalloc_init) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xd6ee688f, __VMLINUX_SYMBOL_STR(vmalloc) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0xdac751f0, __VMLINUX_SYMBOL_STR(v4l2_ctrl_new_std) },
	{ 0xb3f1ab10, __VMLINUX_SYMBOL_STR(v4l2_ctrl_handler_init_class) },
	{ 0xe426c33e, __VMLINUX_SYMBOL_STR(v4l2_device_register) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xd89decaf, __VMLINUX_SYMBOL_STR(videobuf_poll_stream) },
	{ 0x904e29cb, __VMLINUX_SYMBOL_STR(v4l2_ctrl_poll) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0x9a681893, __VMLINUX_SYMBOL_STR(v4l2_fh_open) },
	{ 0x78f6258c, __VMLINUX_SYMBOL_STR(mutex_lock_interruptible) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0x312bc183, __VMLINUX_SYMBOL_STR(videobuf_reqbufs) },
	{ 0x5b3fb26f, __VMLINUX_SYMBOL_STR(videobuf_querybuf) },
	{ 0xfc3d209d, __VMLINUX_SYMBOL_STR(videobuf_qbuf) },
	{ 0x61fbc681, __VMLINUX_SYMBOL_STR(videobuf_dqbuf) },
	{ 0xd898e9dc, __VMLINUX_SYMBOL_STR(videobuf_streamoff) },
	{ 0x15cc910, __VMLINUX_SYMBOL_STR(video_devdata) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
	{ 0xcdac8a55, __VMLINUX_SYMBOL_STR(v4l2_device_put) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xa3492aff, __VMLINUX_SYMBOL_STR(v4l2_device_disconnect) },
	{ 0x8a39eb7, __VMLINUX_SYMBOL_STR(video_unregister_device) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x4b9ab611, __VMLINUX_SYMBOL_STR(usb_free_urb) },
	{ 0x68913526, __VMLINUX_SYMBOL_STR(usb_kill_urb) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x5c2bef44, __VMLINUX_SYMBOL_STR(videobuf_to_vmalloc) },
	{ 0x1c483a9, __VMLINUX_SYMBOL_STR(v4l2_get_timestamp) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xa97c342f, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x148c8de9, __VMLINUX_SYMBOL_STR(usb_alloc_urb) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=videobuf-core,videobuf-vmalloc";

MODULE_ALIAS("usb:v08CAp0109d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v041Ep4024d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0D64p0108d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0546p3187d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0D64p3108d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0595p4343d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BB0p500Dd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0FEBp2004d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v055FpB500d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v08CAp2062d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v052Bp1A18d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v04C8p0729d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v04F2pA208d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0784p0040d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v06D6p0034d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0A17p0062d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v06D6p003Bd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0A17p004Ed*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v041Ep405Dd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v08CAp2102d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v06D6p003Dd*dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "BD0FC7D9724808686C3E6B4");
