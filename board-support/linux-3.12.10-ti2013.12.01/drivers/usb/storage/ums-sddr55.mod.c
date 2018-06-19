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
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x2f2cce9e, __VMLINUX_SYMBOL_STR(usb_stor_set_xfer_buf) },
	{ 0x8acc7982, __VMLINUX_SYMBOL_STR(usb_stor_bulk_transfer_buf) },
	{ 0x18191966, __VMLINUX_SYMBOL_STR(usb_stor_access_xfer_buf) },
	{ 0xff1de796, __VMLINUX_SYMBOL_STR(usb_stor_post_reset) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0xc24a9fdc, __VMLINUX_SYMBOL_STR(usb_stor_disconnect) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xb223f9fb, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x20ddf489, __VMLINUX_SYMBOL_STR(usb_stor_probe2) },
	{ 0x7f0719b2, __VMLINUX_SYMBOL_STR(fill_inquiry_response) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0x50e282e0, __VMLINUX_SYMBOL_STR(usb_stor_pre_reset) },
	{ 0x716f36e8, __VMLINUX_SYMBOL_STR(usb_stor_reset_resume) },
	{ 0x94323571, __VMLINUX_SYMBOL_STR(usb_stor_suspend) },
	{ 0x7e20c089, __VMLINUX_SYMBOL_STR(usb_stor_probe1) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xfdcc943e, __VMLINUX_SYMBOL_STR(usb_stor_resume) },
	{ 0xa3e8bb7a, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("usb:v07C4pA103d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v07C4pA109d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0C0BpA109d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v55AApA103d*dc*dsc*dp*ic*isc*ip*in*");
