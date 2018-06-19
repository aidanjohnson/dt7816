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
	{ 0x284f60ef, __VMLINUX_SYMBOL_STR(usb_serial_deregister_drivers) },
	{ 0x8c9818d7, __VMLINUX_SYMBOL_STR(usb_serial_register_drivers) },
	{ 0xd8dd97eb, __VMLINUX_SYMBOL_STR(usb_serial_generic_open) },
	{ 0x34bc973b, __VMLINUX_SYMBOL_STR(usb_clear_halt) },
	{ 0x409873e3, __VMLINUX_SYMBOL_STR(tty_termios_baud_rate) },
	{ 0xf2997713, __VMLINUX_SYMBOL_STR(tty_termios_hw_change) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x1049b573, __VMLINUX_SYMBOL_STR(usb_control_msg) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x67b27ec1, __VMLINUX_SYMBOL_STR(tty_std_termios) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=usbserial";

MODULE_ALIAS("usb:v0471p081Ed*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v04FCp0204d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v04FCp0231d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v04FCp0235d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v04FCp0201d*dc*dsc*dp*ic*isc*ip*in*");
