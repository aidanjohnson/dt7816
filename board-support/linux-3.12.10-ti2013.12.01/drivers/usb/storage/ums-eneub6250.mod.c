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
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xc24a9fdc, __VMLINUX_SYMBOL_STR(usb_stor_disconnect) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xb223f9fb, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x20ddf489, __VMLINUX_SYMBOL_STR(usb_stor_probe2) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0x50e282e0, __VMLINUX_SYMBOL_STR(usb_stor_pre_reset) },
	{ 0x716f36e8, __VMLINUX_SYMBOL_STR(usb_stor_reset_resume) },
	{ 0x94323571, __VMLINUX_SYMBOL_STR(usb_stor_suspend) },
	{ 0x7e20c089, __VMLINUX_SYMBOL_STR(usb_stor_probe1) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xa3e8bb7a, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0x155a3d9f, __VMLINUX_SYMBOL_STR(request_firmware) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xc193aba7, __VMLINUX_SYMBOL_STR(usb_stor_bulk_transfer_sg) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x4c36daac, __VMLINUX_SYMBOL_STR(usb_stor_bulk_srb) },
	{ 0x8b5187c3, __VMLINUX_SYMBOL_STR(release_firmware) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("usb:v0CF2p6250d*dc*dsc*dp*ic*isc*ip*in*");
