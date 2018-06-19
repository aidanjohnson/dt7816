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
	{ 0x33ba5cd4, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0x284f60ef, __VMLINUX_SYMBOL_STR(usb_serial_deregister_drivers) },
	{ 0x8c9818d7, __VMLINUX_SYMBOL_STR(usb_serial_register_drivers) },
	{ 0xe86fb824, __VMLINUX_SYMBOL_STR(tty_flip_buffer_push) },
	{ 0x7d54d410, __VMLINUX_SYMBOL_STR(tty_insert_flip_string_fixed_flag) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x13d0adf7, __VMLINUX_SYMBOL_STR(__kfifo_out) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=usbserial";

MODULE_ALIAS("usb:v049FpFFFFd*dc02dsc*dp*icFFisc02ip*in*");
MODULE_ALIAS("usb:v03F0p2101d*dc02dsc*dp*icFFisc02ip*in*");
MODULE_ALIAS("usb:v04DDp8001d*dc02dsc*dp*icFFisc02ip*in*");
MODULE_ALIAS("usb:v04DDp8002d*dc02dsc*dp*icFFisc02ip*in*");
MODULE_ALIAS("usb:v04DDp8003d*dc02dsc*dp*icFFisc02ip*in*");
MODULE_ALIAS("usb:v04DDp8004d*dc02dsc*dp*icFFisc02ip*in*");
MODULE_ALIAS("usb:v05F9pFFFFd*dc02dsc*dp*icFFisc02ip*in*");
