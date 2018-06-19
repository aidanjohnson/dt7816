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
	{ 0xb81dbb46, __VMLINUX_SYMBOL_STR(hid_unregister_driver) },
	{ 0x58beadf4, __VMLINUX_SYMBOL_STR(__hid_register_driver) },
	{ 0x4be7fb63, __VMLINUX_SYMBOL_STR(up) },
	{ 0xcad023f9, __VMLINUX_SYMBOL_STR(hid_validate_values) },
	{ 0xc068440e, __VMLINUX_SYMBOL_STR(__kfifo_alloc) },
	{ 0x3ebc7f9d, __VMLINUX_SYMBOL_STR(hid_parse_report) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x781f8a49, __VMLINUX_SYMBOL_STR(hid_add_device) },
	{ 0xdd0a2ba2, __VMLINUX_SYMBOL_STR(strlcat) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xa3fe17fe, __VMLINUX_SYMBOL_STR(hid_allocate_device) },
	{ 0x13d0adf7, __VMLINUX_SYMBOL_STR(__kfifo_out) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xb3e86727, __VMLINUX_SYMBOL_STR(hid_connect) },
	{ 0x29af4459, __VMLINUX_SYMBOL_STR(hid_open_report) },
	{ 0x2fbba5c2, __VMLINUX_SYMBOL_STR(hid_output_report) },
	{ 0xbf670952, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0xd5be9b0a, __VMLINUX_SYMBOL_STR(hid_alloc_report_buf) },
	{ 0xd9769313, __VMLINUX_SYMBOL_STR(hid_set_field) },
	{ 0x732521b5, __VMLINUX_SYMBOL_STR(hidinput_find_field) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0xdb760f52, __VMLINUX_SYMBOL_STR(__kfifo_free) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x3162d5be, __VMLINUX_SYMBOL_STR(hid_destroy_device) },
	{ 0x3d8cd9aa, __VMLINUX_SYMBOL_STR(hid_disconnect) },
	{ 0x4205ad24, __VMLINUX_SYMBOL_STR(cancel_work_sync) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0x5495392, __VMLINUX_SYMBOL_STR(hid_debug) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x3df55167, __VMLINUX_SYMBOL_STR(hid_input_report) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0xf23fcb99, __VMLINUX_SYMBOL_STR(__kfifo_in) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("hid:b0003g*v0000046Dp0000C52B");
MODULE_ALIAS("hid:b0003g*v0000046Dp0000C532");
