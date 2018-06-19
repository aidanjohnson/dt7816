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
	{ 0x67acc003, __VMLINUX_SYMBOL_STR(videobuf_mmap_free) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xb819f01f, __VMLINUX_SYMBOL_STR(v4l2_event_unsubscribe) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0xed19e7e6, __VMLINUX_SYMBOL_STR(video_device_release_empty) },
	{ 0xd6ee688f, __VMLINUX_SYMBOL_STR(vmalloc) },
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x7302371d, __VMLINUX_SYMBOL_STR(dvb_dmx_init) },
	{ 0xd51c05b5, __VMLINUX_SYMBOL_STR(dvb_unregister_adapter) },
	{ 0x715c156a, __VMLINUX_SYMBOL_STR(videobuf_mmap_mapper) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x8edb4a9f, __VMLINUX_SYMBOL_STR(snd_pcm_period_elapsed) },
	{ 0xea400b69, __VMLINUX_SYMBOL_STR(snd_card_create) },
	{ 0xd2217c63, __VMLINUX_SYMBOL_STR(dvb_register_frontend) },
	{ 0x6f444176, __VMLINUX_SYMBOL_STR(v4l2_device_unregister) },
	{ 0x14c47d67, __VMLINUX_SYMBOL_STR(v4l2_ctrl_handler_free) },
	{ 0x7b6646bb, __VMLINUX_SYMBOL_STR(_raw_read_lock) },
	{ 0xbdb83dff, __VMLINUX_SYMBOL_STR(videobuf_queue_vmalloc_init) },
	{ 0xdac751f0, __VMLINUX_SYMBOL_STR(v4l2_ctrl_new_std) },
	{ 0x68913526, __VMLINUX_SYMBOL_STR(usb_kill_urb) },
	{ 0xe2fae716, __VMLINUX_SYMBOL_STR(kmemdup) },
	{ 0x17e9f0be, __VMLINUX_SYMBOL_STR(videobuf_streamon) },
	{ 0xe748d08d, __VMLINUX_SYMBOL_STR(dvb_unregister_frontend) },
	{ 0xcf18e3, __VMLINUX_SYMBOL_STR(__video_register_device) },
	{ 0x6da625c4, __VMLINUX_SYMBOL_STR(videobuf_iolock) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x7ccbce9f, __VMLINUX_SYMBOL_STR(usb_autopm_get_interface) },
	{ 0x13ba89f8, __VMLINUX_SYMBOL_STR(usb_enable_autosuspend) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0x8790467f, __VMLINUX_SYMBOL_STR(snd_pcm_hw_constraint_integer) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x6e88e56f, __VMLINUX_SYMBOL_STR(snd_pcm_link_rwlock) },
	{ 0xe426c33e, __VMLINUX_SYMBOL_STR(v4l2_device_register) },
	{ 0xafdf6647, __VMLINUX_SYMBOL_STR(v4l2_ctrl_new_std_menu) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xda2478d0, __VMLINUX_SYMBOL_STR(param_ops_short) },
	{ 0xfe296051, __VMLINUX_SYMBOL_STR(usb_lock_device_for_reset) },
	{ 0x37befc70, __VMLINUX_SYMBOL_STR(jiffies_to_msecs) },
	{ 0xf5b09563, __VMLINUX_SYMBOL_STR(dvb_dmxdev_release) },
	{ 0xb223f9fb, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xfc3d209d, __VMLINUX_SYMBOL_STR(videobuf_qbuf) },
	{ 0x8a39eb7, __VMLINUX_SYMBOL_STR(video_unregister_device) },
	{ 0xd29c47a6, __VMLINUX_SYMBOL_STR(dvb_dmx_swfilter) },
	{ 0xf48b3acf, __VMLINUX_SYMBOL_STR(snd_pcm_set_ops) },
	{ 0x3704802d, __VMLINUX_SYMBOL_STR(usb_set_interface) },
	{ 0xbe048a49, __VMLINUX_SYMBOL_STR(v4l2_ctrl_subscribe_event) },
	{ 0x5b3fb26f, __VMLINUX_SYMBOL_STR(videobuf_querybuf) },
	{ 0x1049b573, __VMLINUX_SYMBOL_STR(usb_control_msg) },
	{ 0x9cc4f70a, __VMLINUX_SYMBOL_STR(register_pm_notifier) },
	{ 0x84b183ae, __VMLINUX_SYMBOL_STR(strncmp) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x89823484, __VMLINUX_SYMBOL_STR(v4l2_fh_release) },
	{ 0xfea7d91a, __VMLINUX_SYMBOL_STR(v4l2_fh_is_singular) },
	{ 0x91e783eb, __VMLINUX_SYMBOL_STR(videobuf_read_stream) },
	{ 0xdf219bfe, __VMLINUX_SYMBOL_STR(snd_pcm_lib_ioctl) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0x7ee11bc1, __VMLINUX_SYMBOL_STR(device_init_wakeup) },
	{ 0x9f038e56, __VMLINUX_SYMBOL_STR(usb_free_coherent) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0xc5496443, __VMLINUX_SYMBOL_STR(videobuf_stop) },
	{ 0xa97c342f, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0x7bd3b321, __VMLINUX_SYMBOL_STR(usb_get_dev) },
	{ 0x15cc910, __VMLINUX_SYMBOL_STR(video_devdata) },
	{ 0xe72ae005, __VMLINUX_SYMBOL_STR(usb_reset_device) },
	{ 0x11b78479, __VMLINUX_SYMBOL_STR(usb_bulk_msg) },
	{ 0xbb9e326a, __VMLINUX_SYMBOL_STR(usb_put_dev) },
	{ 0xd62c833f, __VMLINUX_SYMBOL_STR(schedule_timeout) },
	{ 0x664776f5, __VMLINUX_SYMBOL_STR(videobuf_vmalloc_free) },
	{ 0x72f4f140, __VMLINUX_SYMBOL_STR(dvb_register_adapter) },
	{ 0x5c2bef44, __VMLINUX_SYMBOL_STR(videobuf_to_vmalloc) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x5acf88bb, __VMLINUX_SYMBOL_STR(usb_get_intf) },
	{ 0x61fbc681, __VMLINUX_SYMBOL_STR(videobuf_dqbuf) },
	{ 0x9a681893, __VMLINUX_SYMBOL_STR(v4l2_fh_open) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x20b2bb2d, __VMLINUX_SYMBOL_STR(param_array_ops) },
	{ 0x312bc183, __VMLINUX_SYMBOL_STR(videobuf_reqbufs) },
	{ 0xb3f1ab10, __VMLINUX_SYMBOL_STR(v4l2_ctrl_handler_init_class) },
	{ 0x7681946c, __VMLINUX_SYMBOL_STR(unregister_pm_notifier) },
	{ 0xa3e8bb7a, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0x155a3d9f, __VMLINUX_SYMBOL_STR(request_firmware) },
	{ 0x33f9de6, __VMLINUX_SYMBOL_STR(snd_card_free) },
	{ 0x9f48b0b9, __VMLINUX_SYMBOL_STR(pm_runtime_set_autosuspend_delay) },
	{ 0xd98f6438, __VMLINUX_SYMBOL_STR(snd_card_register) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xfa228ab4, __VMLINUX_SYMBOL_STR(snd_pcm_new) },
	{ 0x82925eed, __VMLINUX_SYMBOL_STR(usb_alloc_coherent) },
	{ 0x1e1ff3f2, __VMLINUX_SYMBOL_STR(vmalloc_to_page) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x4b9ab611, __VMLINUX_SYMBOL_STR(usb_free_urb) },
	{ 0x1c483a9, __VMLINUX_SYMBOL_STR(v4l2_get_timestamp) },
	{ 0x8b5187c3, __VMLINUX_SYMBOL_STR(release_firmware) },
	{ 0x9be04d52, __VMLINUX_SYMBOL_STR(video_ioctl2) },
	{ 0xd89decaf, __VMLINUX_SYMBOL_STR(videobuf_poll_stream) },
	{ 0x904e29cb, __VMLINUX_SYMBOL_STR(v4l2_ctrl_poll) },
	{ 0x833c4c97, __VMLINUX_SYMBOL_STR(usb_autopm_put_interface) },
	{ 0x148c8de9, __VMLINUX_SYMBOL_STR(usb_alloc_urb) },
	{ 0x69a46d4d, __VMLINUX_SYMBOL_STR(usb_put_intf) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
	{ 0x79a4264a, __VMLINUX_SYMBOL_STR(dvb_dmxdev_init) },
	{ 0xd898e9dc, __VMLINUX_SYMBOL_STR(videobuf_streamoff) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=videobuf-core,videobuf-vmalloc";

MODULE_ALIAS("usb:v1B24p4001d*dc*dsc*dp*icFFisc01ip00in*");
MODULE_ALIAS("usb:v1B24p4001d*dc*dsc*dp*icFFisc01ip01in*");

MODULE_INFO(srcversion, "A094093AF6578E4D710A107");
