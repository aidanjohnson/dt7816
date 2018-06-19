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
	{ 0x20b2bb2d, __VMLINUX_SYMBOL_STR(param_array_ops) },
	{ 0x33ba5cd4, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0x5d41c87c, __VMLINUX_SYMBOL_STR(param_ops_charp) },
	{ 0x47c8baf4, __VMLINUX_SYMBOL_STR(param_ops_uint) },
	{ 0xb223f9fb, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0xa3e8bb7a, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0x26021bc4, __VMLINUX_SYMBOL_STR(wake_up_process) },
	{ 0xa63812b, __VMLINUX_SYMBOL_STR(usbatm_usb_probe) },
	{ 0x2607e1cb, __VMLINUX_SYMBOL_STR(request_firmware_nowait) },
	{ 0xe72ae005, __VMLINUX_SYMBOL_STR(usb_reset_device) },
	{ 0x11b78479, __VMLINUX_SYMBOL_STR(usb_bulk_msg) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xbd59f360, __VMLINUX_SYMBOL_STR(kthread_create_on_node) },
	{ 0x148c8de9, __VMLINUX_SYMBOL_STR(usb_alloc_urb) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xce917ae3, __VMLINUX_SYMBOL_STR(sysfs_create_group) },
	{ 0x3704802d, __VMLINUX_SYMBOL_STR(usb_set_interface) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xf188018f, __VMLINUX_SYMBOL_STR(usb_driver_claim_interface) },
	{ 0xc2d63bc1, __VMLINUX_SYMBOL_STR(usb_ifnum_to_if) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x84b183ae, __VMLINUX_SYMBOL_STR(strncmp) },
	{ 0xbf670952, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0xd11c0dc1, __VMLINUX_SYMBOL_STR(__kernel_param_unlock) },
	{ 0xdd0a2ba2, __VMLINUX_SYMBOL_STR(strlcat) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
	{ 0xaf91d89f, __VMLINUX_SYMBOL_STR(__kernel_param_lock) },
	{ 0xb7b61546, __VMLINUX_SYMBOL_STR(crc32_be) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x155a3d9f, __VMLINUX_SYMBOL_STR(request_firmware) },
	{ 0x7ab88a45, __VMLINUX_SYMBOL_STR(system_freezing_cnt) },
	{ 0x4482cdb, __VMLINUX_SYMBOL_STR(__refrigerator) },
	{ 0x41da4b21, __VMLINUX_SYMBOL_STR(freezing_slow_path) },
	{ 0xe6269bbd, __VMLINUX_SYMBOL_STR(atm_dev_signal_change) },
	{ 0x9e61bb05, __VMLINUX_SYMBOL_STR(set_freezable) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0xd62c833f, __VMLINUX_SYMBOL_STR(schedule_timeout) },
	{ 0xb3f7646e, __VMLINUX_SYMBOL_STR(kthread_should_stop) },
	{ 0x3bd1b1f6, __VMLINUX_SYMBOL_STR(msecs_to_jiffies) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xa97c342f, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0xc8b57c27, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0x1cfb04fa, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0x499cb58c, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x8b5187c3, __VMLINUX_SYMBOL_STR(release_firmware) },
	{ 0x92b57248, __VMLINUX_SYMBOL_STR(flush_work) },
	{ 0x4b9ab611, __VMLINUX_SYMBOL_STR(usb_free_urb) },
	{ 0x68913526, __VMLINUX_SYMBOL_STR(usb_kill_urb) },
	{ 0x90a20675, __VMLINUX_SYMBOL_STR(kthread_stop) },
	{ 0xb0cab2d5, __VMLINUX_SYMBOL_STR(sysfs_remove_group) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x1049b573, __VMLINUX_SYMBOL_STR(usb_control_msg) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xe2fae716, __VMLINUX_SYMBOL_STR(kmemdup) },
	{ 0x11f7ed4c, __VMLINUX_SYMBOL_STR(hex_to_bin) },
	{ 0xe0b78cc1, __VMLINUX_SYMBOL_STR(usb_string) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x1cba36f3, __VMLINUX_SYMBOL_STR(usbatm_usb_disconnect) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=usbatm,atm";

MODULE_ALIAS("usb:v1110p9001d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1110p9000d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1110p9010d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1110p900Fd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1110p9022d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1110p9021d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1110p9024d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1110p9023d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1110p9032d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1110p9031d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1110p9042d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1110p9041d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1039p2111d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1039p2110d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1039p2101d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1039p2100d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1039p2131d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1039p2130d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1039p2121d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1039p2120d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v05CCp3351d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v05CCp3350d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v05CCp3352d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v05CCp3353d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v05CCp3362d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v05CCp3363d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BAFp00F2d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BAFp00F1d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BAFp00FAd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BAFp00F9d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BAFp00F6d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BAFp00F5d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BAFp00F8d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0BAFp00F7d*dc*dsc*dp*ic*isc*ip*in*");
