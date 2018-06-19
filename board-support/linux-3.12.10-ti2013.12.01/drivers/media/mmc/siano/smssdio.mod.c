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
	{ 0xd6f52eb1, __VMLINUX_SYMBOL_STR(sdio_unregister_driver) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x377db316, __VMLINUX_SYMBOL_STR(sdio_register_driver) },
	{ 0x56ed5566, __VMLINUX_SYMBOL_STR(sdio_memcpy_toio) },
	{ 0x37d91069, __VMLINUX_SYMBOL_STR(smsendian_handle_tx_message) },
	{ 0x59c7dbbc, __VMLINUX_SYMBOL_STR(smscore_onresponse) },
	{ 0x45284ae9, __VMLINUX_SYMBOL_STR(smsendian_handle_rx_message) },
	{ 0xe4de6b33, __VMLINUX_SYMBOL_STR(sdio_memcpy_fromio) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x62e6752e, __VMLINUX_SYMBOL_STR(smscore_getbuffer) },
	{ 0x4dff5858, __VMLINUX_SYMBOL_STR(sdio_readb) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xbdaa8393, __VMLINUX_SYMBOL_STR(smscore_start_device) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x9df247a9, __VMLINUX_SYMBOL_STR(sdio_claim_irq) },
	{ 0x69c15397, __VMLINUX_SYMBOL_STR(sdio_set_block_size) },
	{ 0x151e56a5, __VMLINUX_SYMBOL_STR(sdio_enable_func) },
	{ 0x96a10e54, __VMLINUX_SYMBOL_STR(smscore_set_board_id) },
	{ 0x807fec50, __VMLINUX_SYMBOL_STR(smscore_register_device) },
	{ 0x844539ae, __VMLINUX_SYMBOL_STR(sms_get_board) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x2407dc39, __VMLINUX_SYMBOL_STR(sdio_release_host) },
	{ 0x161a8033, __VMLINUX_SYMBOL_STR(sdio_disable_func) },
	{ 0x37e33744, __VMLINUX_SYMBOL_STR(sdio_release_irq) },
	{ 0x44a17998, __VMLINUX_SYMBOL_STR(sdio_claim_host) },
	{ 0x33ed1caf, __VMLINUX_SYMBOL_STR(smscore_unregister_device) },
	{ 0xdc3f3281, __VMLINUX_SYMBOL_STR(smscore_putbuffer) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=smsmdtv";

MODULE_ALIAS("sdio:c*v039Ad5347*");
MODULE_ALIAS("sdio:c*v039Ad1100*");
MODULE_ALIAS("sdio:c*v039Ad0201*");
MODULE_ALIAS("sdio:c*v039Ad0300*");
MODULE_ALIAS("sdio:c*v039Ad0301*");
MODULE_ALIAS("sdio:c*v039Ad0302*");
MODULE_ALIAS("sdio:c*v039Ad0500*");
MODULE_ALIAS("sdio:c*v039Ad0600*");
MODULE_ALIAS("sdio:c*v039Ad0700*");
MODULE_ALIAS("sdio:c*v039Ad0800*");
