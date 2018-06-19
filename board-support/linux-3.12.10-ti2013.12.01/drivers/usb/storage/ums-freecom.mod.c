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
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x8acc7982, __VMLINUX_SYMBOL_STR(usb_stor_bulk_transfer_buf) },
	{ 0xff1de796, __VMLINUX_SYMBOL_STR(usb_stor_post_reset) },
	{ 0x3300bbd9, __VMLINUX_SYMBOL_STR(usb_stor_control_msg) },
	{ 0xc24a9fdc, __VMLINUX_SYMBOL_STR(usb_stor_disconnect) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xb223f9fb, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x20ddf489, __VMLINUX_SYMBOL_STR(usb_stor_probe2) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0x50e282e0, __VMLINUX_SYMBOL_STR(usb_stor_pre_reset) },
	{ 0x716f36e8, __VMLINUX_SYMBOL_STR(usb_stor_reset_resume) },
	{ 0x94323571, __VMLINUX_SYMBOL_STR(usb_stor_suspend) },
	{ 0x7e20c089, __VMLINUX_SYMBOL_STR(usb_stor_probe1) },
	{ 0xfdcc943e, __VMLINUX_SYMBOL_STR(usb_stor_resume) },
	{ 0xa3e8bb7a, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x4c36daac, __VMLINUX_SYMBOL_STR(usb_stor_bulk_srb) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("usb:v07ABpFC01d*dc*dsc*dp*ic*isc*ip*in*");
