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
	{ 0x3c7a1215, __VMLINUX_SYMBOL_STR(i2400m_cmd_enter_powersave) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0xf83c6f7b, __VMLINUX_SYMBOL_STR(i2400m_dev_reset_handle) },
	{ 0xa70dcea1, __VMLINUX_SYMBOL_STR(debugfs_create_dir) },
	{ 0x349cba85, __VMLINUX_SYMBOL_STR(strchr) },
	{ 0x17636e62, __VMLINUX_SYMBOL_STR(debugfs_create_u8) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x84edca2d, __VMLINUX_SYMBOL_STR(usb_init_urb) },
	{ 0xc8b57c27, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0x68913526, __VMLINUX_SYMBOL_STR(usb_kill_urb) },
	{ 0x330d32c9, __VMLINUX_SYMBOL_STR(i2400m_tx_msg_get) },
	{ 0x3b6d8925, __VMLINUX_SYMBOL_STR(i2400m_rx) },
	{ 0x7ccbce9f, __VMLINUX_SYMBOL_STR(usb_autopm_get_interface) },
	{ 0x85df9b6c, __VMLINUX_SYMBOL_STR(strsep) },
	{ 0x13ba89f8, __VMLINUX_SYMBOL_STR(usb_enable_autosuspend) },
	{ 0xa913b6c0, __VMLINUX_SYMBOL_STR(usb_get_urb) },
	{ 0xe716df6f, __VMLINUX_SYMBOL_STR(debugfs_remove_recursive) },
	{ 0xc499ae1e, __VMLINUX_SYMBOL_STR(kstrdup) },
	{ 0xbd59f360, __VMLINUX_SYMBOL_STR(kthread_create_on_node) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0xaa9087c0, __VMLINUX_SYMBOL_STR(param_ops_string) },
	{ 0x63a326ef, __VMLINUX_SYMBOL_STR(__netdev_alloc_skb) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x1217a26c, __VMLINUX_SYMBOL_STR(i2400m_setup) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x67320893, __VMLINUX_SYMBOL_STR(i2400m_is_boot_barker) },
	{ 0x55a26adf, __VMLINUX_SYMBOL_STR(i2400m_post_reset) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0xb223f9fb, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xa4c7fa32, __VMLINUX_SYMBOL_STR(ethtool_op_get_link) },
	{ 0x20c55ae0, __VMLINUX_SYMBOL_STR(sscanf) },
	{ 0x90a20675, __VMLINUX_SYMBOL_STR(kthread_stop) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0x98ca720d, __VMLINUX_SYMBOL_STR(debugfs_create_size_t) },
	{ 0xe94f1e83, __VMLINUX_SYMBOL_STR(free_netdev) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x93fb6890, __VMLINUX_SYMBOL_STR(i2400m_netdev_setup) },
	{ 0x7ee11bc1, __VMLINUX_SYMBOL_STR(device_init_wakeup) },
	{ 0x2ef4acbb, __VMLINUX_SYMBOL_STR(i2400m_unknown_barker) },
	{ 0x1f60a7a7, __VMLINUX_SYMBOL_STR(i2400m_pre_reset) },
	{ 0xef155f47, __VMLINUX_SYMBOL_STR(usb_queue_reset_device) },
	{ 0x4059792f, __VMLINUX_SYMBOL_STR(print_hex_dump) },
	{ 0xe0816cce, __VMLINUX_SYMBOL_STR(skb_copy_expand) },
	{ 0xa97c342f, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0x7bd3b321, __VMLINUX_SYMBOL_STR(usb_get_dev) },
	{ 0xe72ae005, __VMLINUX_SYMBOL_STR(usb_reset_device) },
	{ 0x11b78479, __VMLINUX_SYMBOL_STR(usb_bulk_msg) },
	{ 0xbb9e326a, __VMLINUX_SYMBOL_STR(usb_put_dev) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x34bc973b, __VMLINUX_SYMBOL_STR(usb_clear_halt) },
	{ 0xfb4628f9, __VMLINUX_SYMBOL_STR(alloc_netdev_mqs) },
	{ 0x6c6cdd4d, __VMLINUX_SYMBOL_STR(wait_for_completion_interruptible_timeout) },
	{ 0xedd3426d, __VMLINUX_SYMBOL_STR(dev_driver_string) },
	{ 0x26021bc4, __VMLINUX_SYMBOL_STR(wake_up_process) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0xb00b793c, __VMLINUX_SYMBOL_STR(i2400m_bm_cmd_prepare) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x660a3e03, __VMLINUX_SYMBOL_STR(i2400m_release) },
	{ 0xb3f7646e, __VMLINUX_SYMBOL_STR(kthread_should_stop) },
	{ 0x5955286, __VMLINUX_SYMBOL_STR(i2400m_init) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x499cb58c, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0x6128b5fc, __VMLINUX_SYMBOL_STR(__printk_ratelimit) },
	{ 0xa3e8bb7a, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0x1cfb04fa, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x9f48b0b9, __VMLINUX_SYMBOL_STR(pm_runtime_set_autosuspend_delay) },
	{ 0xbf670952, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xd4669fad, __VMLINUX_SYMBOL_STR(complete) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x99bb8806, __VMLINUX_SYMBOL_STR(memmove) },
	{ 0x70b60936, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0xa7f748ee, __VMLINUX_SYMBOL_STR(i2400m_tx_msg_sent) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x4b9ab611, __VMLINUX_SYMBOL_STR(usb_free_urb) },
	{ 0x833c4c97, __VMLINUX_SYMBOL_STR(usb_autopm_put_interface) },
	{ 0x148c8de9, __VMLINUX_SYMBOL_STR(usb_alloc_urb) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=i2400m";

MODULE_ALIAS("usb:v8086p0186d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v8086p0188d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v8087p07D6d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v8087p07D7d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v8087p07D9d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v8086p0187d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v8086p0181d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v8086p1403d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v8086p1405d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v8086p0180d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v8086p0182d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v8086p1406d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v8086p1403d*dc*dsc*dp*ic*isc*ip*in*");
