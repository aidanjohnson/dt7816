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
	{ 0x1cba36f3, __VMLINUX_SYMBOL_STR(usbatm_usb_disconnect) },
	{ 0xafad493b, __VMLINUX_SYMBOL_STR(param_ops_ushort) },
	{ 0x8779a34f, __VMLINUX_SYMBOL_STR(param_ops_byte) },
	{ 0xb223f9fb, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xa3e8bb7a, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0x3704802d, __VMLINUX_SYMBOL_STR(usb_set_interface) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xf188018f, __VMLINUX_SYMBOL_STR(usb_driver_claim_interface) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xfd3bb210, __VMLINUX_SYMBOL_STR(usb_altnum_to_altsetting) },
	{ 0x32ab70a8, __VMLINUX_SYMBOL_STR(usb_driver_release_interface) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x79aa04a2, __VMLINUX_SYMBOL_STR(get_random_bytes) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xa63812b, __VMLINUX_SYMBOL_STR(usbatm_usb_probe) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=usbatm";


MODULE_INFO(srcversion, "8A3F7E476E7840158E1522D");
