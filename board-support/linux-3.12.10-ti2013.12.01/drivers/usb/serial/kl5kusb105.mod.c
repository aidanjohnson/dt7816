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
	{ 0x1fd2a189, __VMLINUX_SYMBOL_STR(usb_serial_generic_unthrottle) },
	{ 0x6948bd9b, __VMLINUX_SYMBOL_STR(usb_serial_generic_throttle) },
	{ 0x284f60ef, __VMLINUX_SYMBOL_STR(usb_serial_deregister_drivers) },
	{ 0x8c9818d7, __VMLINUX_SYMBOL_STR(usb_serial_register_drivers) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0xd8dd97eb, __VMLINUX_SYMBOL_STR(usb_serial_generic_open) },
	{ 0x503169db, __VMLINUX_SYMBOL_STR(usb_serial_generic_close) },
	{ 0xd6c2e616, __VMLINUX_SYMBOL_STR(tty_encode_baud_rate) },
	{ 0x409873e3, __VMLINUX_SYMBOL_STR(tty_termios_baud_rate) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x1049b573, __VMLINUX_SYMBOL_STR(usb_control_msg) },
	{ 0xe86fb824, __VMLINUX_SYMBOL_STR(tty_flip_buffer_push) },
	{ 0x7d54d410, __VMLINUX_SYMBOL_STR(tty_insert_flip_string_fixed_flag) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x13d0adf7, __VMLINUX_SYMBOL_STR(__kfifo_out) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=usbserial";

MODULE_ALIAS("usb:v0830p0080d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v05E9p00C0d*dc*dsc*dp*ic*isc*ip*in*");
