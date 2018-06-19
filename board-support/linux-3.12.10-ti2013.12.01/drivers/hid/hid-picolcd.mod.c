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
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0xc2290b94, __VMLINUX_SYMBOL_STR(device_remove_file) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xf6d4d012, __VMLINUX_SYMBOL_STR(rc_unregister_device) },
	{ 0x7129e5f8, __VMLINUX_SYMBOL_STR(hex_asc) },
	{ 0xfbc74f64, __VMLINUX_SYMBOL_STR(__copy_from_user) },
	{ 0x84439fcd, __VMLINUX_SYMBOL_STR(generic_file_llseek) },
	{ 0x29af4459, __VMLINUX_SYMBOL_STR(hid_open_report) },
	{ 0xd6ee688f, __VMLINUX_SYMBOL_STR(vmalloc) },
	{ 0xf88dd612, __VMLINUX_SYMBOL_STR(single_open) },
	{ 0x67c2fa54, __VMLINUX_SYMBOL_STR(__copy_to_user) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0xedd8a3bf, __VMLINUX_SYMBOL_STR(framebuffer_release) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x80d216b9, __VMLINUX_SYMBOL_STR(led_classdev_register) },
	{ 0x4cd9d440, __VMLINUX_SYMBOL_STR(single_release) },
	{ 0xed98d3e0, __VMLINUX_SYMBOL_STR(fb_sys_read) },
	{ 0x6a61296a, __VMLINUX_SYMBOL_STR(backlight_device_register) },
	{ 0x2247cba2, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0xbdfc0bc0, __VMLINUX_SYMBOL_STR(debugfs_create_file) },
	{ 0x633fe25b, __VMLINUX_SYMBOL_STR(sys_copyarea) },
	{ 0x92c80041, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0xa43e3b01, __VMLINUX_SYMBOL_STR(rc_allocate_device) },
	{ 0xa169522d, __VMLINUX_SYMBOL_STR(hid_debug_event) },
	{ 0x5495392, __VMLINUX_SYMBOL_STR(hid_debug) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0xb79a5aed, __VMLINUX_SYMBOL_STR(input_event) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x6637f527, __VMLINUX_SYMBOL_STR(rc_free_device) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x20c55ae0, __VMLINUX_SYMBOL_STR(sscanf) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0x932d4b63, __VMLINUX_SYMBOL_STR(register_framebuffer) },
	{ 0x84b183ae, __VMLINUX_SYMBOL_STR(strncmp) },
	{ 0xef86a3ea, __VMLINUX_SYMBOL_STR(debugfs_remove) },
	{ 0x55fb4413, __VMLINUX_SYMBOL_STR(rc_register_device) },
	{ 0xfc88fbae, __VMLINUX_SYMBOL_STR(input_set_capability) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x3d8cd9aa, __VMLINUX_SYMBOL_STR(hid_disconnect) },
	{ 0xb73c3b37, __VMLINUX_SYMBOL_STR(lcd_device_unregister) },
	{ 0xd9769313, __VMLINUX_SYMBOL_STR(hid_set_field) },
	{ 0xdae7127e, __VMLINUX_SYMBOL_STR(simple_open) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0xfc27bfdd, __VMLINUX_SYMBOL_STR(device_create_file) },
	{ 0xd5be9b0a, __VMLINUX_SYMBOL_STR(hid_alloc_report_buf) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0xbbf94b7c, __VMLINUX_SYMBOL_STR(sys_fillrect) },
	{ 0xe851bb05, __VMLINUX_SYMBOL_STR(queue_delayed_work_on) },
	{ 0xaa58a0ae, __VMLINUX_SYMBOL_STR(input_register_device) },
	{ 0x68b077dd, __VMLINUX_SYMBOL_STR(sys_imageblit) },
	{ 0x74ce05b8, __VMLINUX_SYMBOL_STR(flush_delayed_work) },
	{ 0x1698c419, __VMLINUX_SYMBOL_STR(fb_sys_write) },
	{ 0x55e25a41, __VMLINUX_SYMBOL_STR(input_free_device) },
	{ 0x6c6cdd4d, __VMLINUX_SYMBOL_STR(wait_for_completion_interruptible_timeout) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x1a85aa8a, __VMLINUX_SYMBOL_STR(framebuffer_alloc) },
	{ 0x990182bb, __VMLINUX_SYMBOL_STR(fb_deferred_io_cleanup) },
	{ 0x1b66436f, __VMLINUX_SYMBOL_STR(fb_deferred_io_init) },
	{ 0xc91156f9, __VMLINUX_SYMBOL_STR(led_classdev_unregister) },
	{ 0xb68b7fb0, __VMLINUX_SYMBOL_STR(lcd_device_register) },
	{ 0x94b932f1, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x657c72c4, __VMLINUX_SYMBOL_STR(input_unregister_device) },
	{ 0x58beadf4, __VMLINUX_SYMBOL_STR(__hid_register_driver) },
	{ 0xbf235b4c, __VMLINUX_SYMBOL_STR(ir_raw_event_store) },
	{ 0xbf670952, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xd4669fad, __VMLINUX_SYMBOL_STR(complete) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xb81dbb46, __VMLINUX_SYMBOL_STR(hid_unregister_driver) },
	{ 0x13adb290, __VMLINUX_SYMBOL_STR(backlight_device_unregister) },
	{ 0x67979914, __VMLINUX_SYMBOL_STR(ir_raw_event_handle) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
	{ 0x2fbba5c2, __VMLINUX_SYMBOL_STR(hid_output_report) },
	{ 0x26a6901f, __VMLINUX_SYMBOL_STR(input_allocate_device) },
	{ 0x70c3a44f, __VMLINUX_SYMBOL_STR(unregister_framebuffer) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("hid:b0003g*v000004D8p0000C002");
MODULE_ALIAS("hid:b0003g*v000004D8p0000F002");
