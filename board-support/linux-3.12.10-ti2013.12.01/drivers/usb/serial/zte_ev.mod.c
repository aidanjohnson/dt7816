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
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x503169db, __VMLINUX_SYMBOL_STR(usb_serial_generic_close) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x1049b573, __VMLINUX_SYMBOL_STR(usb_control_msg) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=usbserial";

MODULE_ALIAS("usb:v19D2pFFFFd*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v19D2pFFFEd*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v19D2pFFFDd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v19D2pFFFCd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v19D2pFFFBd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v19D2pFFF6d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v19D2pFFF7d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v19D2pFFF8d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v19D2pFFF9d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v19D2pFFEEd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v19D2pFFEDd*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v19D2pFFEBd*dc*dsc*dp*icFFiscFFipFFin*");
MODULE_ALIAS("usb:v19D2pFFECd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v05C6p3197d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v05C6p6000d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v05C6p9008d*dc*dsc*dp*ic*isc*ip*in*");
