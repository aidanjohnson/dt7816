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
	{ 0x402b8281, __VMLINUX_SYMBOL_STR(__request_module) },
	{ 0xc2290b94, __VMLINUX_SYMBOL_STR(device_remove_file) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x67c2fa54, __VMLINUX_SYMBOL_STR(__copy_to_user) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x7302371d, __VMLINUX_SYMBOL_STR(dvb_dmx_init) },
	{ 0xd51c05b5, __VMLINUX_SYMBOL_STR(dvb_unregister_adapter) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0xa99ac8f, __VMLINUX_SYMBOL_STR(v4l2_i2c_new_subdev) },
	{ 0x43a53735, __VMLINUX_SYMBOL_STR(__alloc_workqueue_key) },
	{ 0xc8b57c27, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0x2c73d048, __VMLINUX_SYMBOL_STR(tveeprom_hauppauge_analog) },
	{ 0xd2217c63, __VMLINUX_SYMBOL_STR(dvb_register_frontend) },
	{ 0x6f444176, __VMLINUX_SYMBOL_STR(v4l2_device_unregister) },
	{ 0x8169d80e, __VMLINUX_SYMBOL_STR(i2c_transfer) },
	{ 0x7ab88a45, __VMLINUX_SYMBOL_STR(system_freezing_cnt) },
	{ 0x2342f1ae, __VMLINUX_SYMBOL_STR(v4l2_prio_open) },
	{ 0x68913526, __VMLINUX_SYMBOL_STR(usb_kill_urb) },
	{ 0xe2fae716, __VMLINUX_SYMBOL_STR(kmemdup) },
	{ 0xe748d08d, __VMLINUX_SYMBOL_STR(dvb_unregister_frontend) },
	{ 0xcf18e3, __VMLINUX_SYMBOL_STR(__video_register_device) },
	{ 0x593a99b, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xcf76ce95, __VMLINUX_SYMBOL_STR(cx2341x_fill_defaults) },
	{ 0xe039aeb4, __VMLINUX_SYMBOL_STR(usb_unlink_urb) },
	{ 0xb0cab2d5, __VMLINUX_SYMBOL_STR(sysfs_remove_group) },
	{ 0x1ca0c084, __VMLINUX_SYMBOL_STR(cx2341x_log_status) },
	{ 0x2eea13d5, __VMLINUX_SYMBOL_STR(dvb_net_release) },
	{ 0xbd59f360, __VMLINUX_SYMBOL_STR(kthread_create_on_node) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0xc4a6a709, __VMLINUX_SYMBOL_STR(i2c_add_adapter) },
	{ 0xa432424c, __VMLINUX_SYMBOL_STR(dvb_frontend_detach) },
	{ 0xe426c33e, __VMLINUX_SYMBOL_STR(v4l2_device_register) },
	{ 0xc184ec1e, __VMLINUX_SYMBOL_STR(cx2341x_ctrl_get_menu) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x1fab5905, __VMLINUX_SYMBOL_STR(wait_for_completion) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xd5f2172f, __VMLINUX_SYMBOL_STR(del_timer_sync) },
	{ 0xa3492aff, __VMLINUX_SYMBOL_STR(v4l2_device_disconnect) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xda2478d0, __VMLINUX_SYMBOL_STR(param_ops_short) },
	{ 0xaccdabb8, __VMLINUX_SYMBOL_STR(device_register) },
	{ 0xfe296051, __VMLINUX_SYMBOL_STR(usb_lock_device_for_reset) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x2f25eee2, __VMLINUX_SYMBOL_STR(cx2341x_update) },
	{ 0x41da4b21, __VMLINUX_SYMBOL_STR(freezing_slow_path) },
	{ 0xb223f9fb, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0xf5b09563, __VMLINUX_SYMBOL_STR(dvb_dmxdev_release) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x90a20675, __VMLINUX_SYMBOL_STR(kthread_stop) },
	{ 0xce917ae3, __VMLINUX_SYMBOL_STR(sysfs_create_group) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0x8a39eb7, __VMLINUX_SYMBOL_STR(video_unregister_device) },
	{ 0xd29c47a6, __VMLINUX_SYMBOL_STR(dvb_dmx_swfilter) },
	{ 0x210d8549, __VMLINUX_SYMBOL_STR(class_unregister) },
	{ 0xaa6fac1b, __VMLINUX_SYMBOL_STR(dvb_net_init) },
	{ 0x3704802d, __VMLINUX_SYMBOL_STR(usb_set_interface) },
	{ 0xcda04a5b, __VMLINUX_SYMBOL_STR(v4l2_prio_close) },
	{ 0x328a05f1, __VMLINUX_SYMBOL_STR(strncpy) },
	{ 0x1049b573, __VMLINUX_SYMBOL_STR(usb_control_msg) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x8c03d20c, __VMLINUX_SYMBOL_STR(destroy_workqueue) },
	{ 0x448f60db, __VMLINUX_SYMBOL_STR(device_move) },
	{ 0xbe2c0274, __VMLINUX_SYMBOL_STR(add_timer) },
	{ 0x2f51d70c, __VMLINUX_SYMBOL_STR(__class_register) },
	{ 0xdbe7dd6c, __VMLINUX_SYMBOL_STR(dvb_dmx_release) },
	{ 0x42160169, __VMLINUX_SYMBOL_STR(flush_workqueue) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0x868784cb, __VMLINUX_SYMBOL_STR(__symbol_get) },
	{ 0xbc5671dc, __VMLINUX_SYMBOL_STR(v4l_printk_ioctl) },
	{ 0x16244fe5, __VMLINUX_SYMBOL_STR(v4l2_prio_check) },
	{ 0xfc27bfdd, __VMLINUX_SYMBOL_STR(device_create_file) },
	{ 0x999a475f, __VMLINUX_SYMBOL_STR(i2c_del_adapter) },
	{ 0xa97c342f, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0x63d684c9, __VMLINUX_SYMBOL_STR(put_device) },
	{ 0x15cc910, __VMLINUX_SYMBOL_STR(video_devdata) },
	{ 0xe72ae005, __VMLINUX_SYMBOL_STR(usb_reset_device) },
	{ 0x11b78479, __VMLINUX_SYMBOL_STR(usb_bulk_msg) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0x86a4889a, __VMLINUX_SYMBOL_STR(kmalloc_order_trace) },
	{ 0x34bc973b, __VMLINUX_SYMBOL_STR(usb_clear_halt) },
	{ 0x3db8be82, __VMLINUX_SYMBOL_STR(cx2341x_ctrl_query) },
	{ 0x4482cdb, __VMLINUX_SYMBOL_STR(__refrigerator) },
	{ 0x26021bc4, __VMLINUX_SYMBOL_STR(wake_up_process) },
	{ 0x72f4f140, __VMLINUX_SYMBOL_STR(dvb_register_adapter) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x2c413068, __VMLINUX_SYMBOL_STR(get_device) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0xb3f7646e, __VMLINUX_SYMBOL_STR(kthread_should_stop) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x499cb58c, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0x20b2bb2d, __VMLINUX_SYMBOL_STR(param_array_ops) },
	{ 0x9e61bb05, __VMLINUX_SYMBOL_STR(set_freezable) },
	{ 0x3bdd0f94, __VMLINUX_SYMBOL_STR(v4l2_prio_change) },
	{ 0xf9e73082, __VMLINUX_SYMBOL_STR(scnprintf) },
	{ 0xa3e8bb7a, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0x155a3d9f, __VMLINUX_SYMBOL_STR(request_firmware) },
	{ 0x1cfb04fa, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x8552b5b9, __VMLINUX_SYMBOL_STR(device_unregister) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x5b88faf6, __VMLINUX_SYMBOL_STR(cx2341x_ext_ctrls) },
	{ 0x8106095a, __VMLINUX_SYMBOL_STR(v4l2_prio_max) },
	{ 0xb742fd7, __VMLINUX_SYMBOL_STR(simple_strtol) },
	{ 0x6e9dd606, __VMLINUX_SYMBOL_STR(__symbol_put) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0xd4669fad, __VMLINUX_SYMBOL_STR(complete) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x8ecb1aa8, __VMLINUX_SYMBOL_STR(dev_set_name) },
	{ 0xec54ea64, __VMLINUX_SYMBOL_STR(i2c_new_device) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x4b9ab611, __VMLINUX_SYMBOL_STR(usb_free_urb) },
	{ 0x8b5187c3, __VMLINUX_SYMBOL_STR(release_firmware) },
	{ 0x9be04d52, __VMLINUX_SYMBOL_STR(video_ioctl2) },
	{ 0x148c8de9, __VMLINUX_SYMBOL_STR(usb_alloc_urb) },
	{ 0x79a4264a, __VMLINUX_SYMBOL_STR(dvb_dmxdev_init) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=tveeprom,cx2341x";

MODULE_ALIAS("usb:v2040p2900d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p2950d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p2400d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1164p0622d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1164p0602d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v11BAp1003d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v11BAp1001d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p7300d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p7500d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p7501d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0CCDp0039d*dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "421D4D440E1E18D974C2C04");
