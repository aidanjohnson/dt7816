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
	{ 0xe05b1960, __VMLINUX_SYMBOL_STR(usb_serial_generic_get_icount) },
	{ 0x92c5db5b, __VMLINUX_SYMBOL_STR(usb_serial_generic_tiocmiwait) },
	{ 0x284f60ef, __VMLINUX_SYMBOL_STR(usb_serial_deregister_drivers) },
	{ 0x8c9818d7, __VMLINUX_SYMBOL_STR(usb_serial_register_drivers) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xa97c342f, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0xd8dd97eb, __VMLINUX_SYMBOL_STR(usb_serial_generic_open) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x68913526, __VMLINUX_SYMBOL_STR(usb_kill_urb) },
	{ 0x503169db, __VMLINUX_SYMBOL_STR(usb_serial_generic_close) },
	{ 0xfbc74f64, __VMLINUX_SYMBOL_STR(__copy_from_user) },
	{ 0x67c2fa54, __VMLINUX_SYMBOL_STR(__copy_to_user) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5641485b, __VMLINUX_SYMBOL_STR(tty_termios_encode_baud_rate) },
	{ 0xbf670952, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0x409873e3, __VMLINUX_SYMBOL_STR(tty_termios_baud_rate) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0x1049b573, __VMLINUX_SYMBOL_STR(usb_control_msg) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xe86fb824, __VMLINUX_SYMBOL_STR(tty_flip_buffer_push) },
	{ 0x7d54d410, __VMLINUX_SYMBOL_STR(tty_insert_flip_string_fixed_flag) },
	{ 0x500d4a78, __VMLINUX_SYMBOL_STR(tty_insert_flip_string_flags) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x67b27ec1, __VMLINUX_SYMBOL_STR(tty_std_termios) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=usbserial";

MODULE_ALIAS("usb:v6547p0232d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v18ECp3118d*dc*dsc*dp*ic*isc*ip*in*");
