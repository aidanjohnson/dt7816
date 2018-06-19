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
	{ 0xff1de796, __VMLINUX_SYMBOL_STR(usb_stor_post_reset) },
	{ 0x1bc3edc2, __VMLINUX_SYMBOL_STR(usb_stor_sense_invalidCDB) },
	{ 0xc24a9fdc, __VMLINUX_SYMBOL_STR(usb_stor_disconnect) },
	{ 0xd82bcd3d, __VMLINUX_SYMBOL_STR(scsi_eh_restore_cmnd) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xb223f9fb, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0x20ddf489, __VMLINUX_SYMBOL_STR(usb_stor_probe2) },
	{ 0x8c3176ae, __VMLINUX_SYMBOL_STR(usb_stor_transparent_scsi_command) },
	{ 0x50e282e0, __VMLINUX_SYMBOL_STR(usb_stor_pre_reset) },
	{ 0x716f36e8, __VMLINUX_SYMBOL_STR(usb_stor_reset_resume) },
	{ 0x94323571, __VMLINUX_SYMBOL_STR(usb_stor_suspend) },
	{ 0x7e20c089, __VMLINUX_SYMBOL_STR(usb_stor_probe1) },
	{ 0x6028a354, __VMLINUX_SYMBOL_STR(scsi_eh_prep_cmnd) },
	{ 0xfdcc943e, __VMLINUX_SYMBOL_STR(usb_stor_resume) },
	{ 0xa3e8bb7a, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("usb:v04B4p6830d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v04B4p6831d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v14CDp6116d02[0-1]*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v14CDp6116d0[0-1]*dc*dsc*dp*ic*isc*ip*in*");
