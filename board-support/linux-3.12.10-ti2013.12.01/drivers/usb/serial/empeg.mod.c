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
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x3cf3a63b, __VMLINUX_SYMBOL_STR(usb_reset_configuration) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xd6c2e616, __VMLINUX_SYMBOL_STR(tty_encode_baud_rate) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=usbserial";

MODULE_ALIAS("usb:v084Fp0001d*dc*dsc*dp*ic*isc*ip*in*");
