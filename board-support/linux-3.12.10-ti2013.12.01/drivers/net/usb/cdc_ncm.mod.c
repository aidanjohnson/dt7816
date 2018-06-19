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
	{ 0xfd3bb210, __VMLINUX_SYMBOL_STR(usb_altnum_to_altsetting) },
	{ 0xe8abd28b, __VMLINUX_SYMBOL_STR(usbnet_resume) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x1ea0d766, __VMLINUX_SYMBOL_STR(usbnet_probe) },
	{ 0x599751b9, __VMLINUX_SYMBOL_STR(usbnet_set_settings) },
	{ 0x104b440, __VMLINUX_SYMBOL_STR(usbnet_link_change) },
	{ 0x7840b42c, __VMLINUX_SYMBOL_STR(hrtimer_cancel) },
	{ 0xcebe8978, __VMLINUX_SYMBOL_STR(usbnet_disconnect) },
	{ 0xa1d55e90, __VMLINUX_SYMBOL_STR(_raw_spin_lock_bh) },
	{ 0xb2038f57, __VMLINUX_SYMBOL_STR(skb_clone) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0x2a3aa678, __VMLINUX_SYMBOL_STR(_test_and_clear_bit) },
	{ 0x33ba5cd4, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xed24697c, __VMLINUX_SYMBOL_STR(usbnet_nway_reset) },
	{ 0xb223f9fb, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x3704802d, __VMLINUX_SYMBOL_STR(usb_set_interface) },
	{ 0xfaef0ed, __VMLINUX_SYMBOL_STR(__tasklet_schedule) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0xf188018f, __VMLINUX_SYMBOL_STR(usb_driver_claim_interface) },
	{ 0xd25bbb0, __VMLINUX_SYMBOL_STR(usbnet_start_xmit) },
	{ 0x3f97822e, __VMLINUX_SYMBOL_STR(usbnet_suspend) },
	{ 0x935da5ae, __VMLINUX_SYMBOL_STR(usbnet_get_link) },
	{ 0xe2ea17e8, __VMLINUX_SYMBOL_STR(dev_kfree_skb_any) },
	{ 0x82072614, __VMLINUX_SYMBOL_STR(tasklet_kill) },
	{ 0xd96f4113, __VMLINUX_SYMBOL_STR(usbnet_get_settings) },
	{ 0x3ff62317, __VMLINUX_SYMBOL_STR(local_bh_disable) },
	{ 0xd0e4b174, __VMLINUX_SYMBOL_STR(usbnet_read_cmd) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0xc3e596f0, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0xdd3916ac, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_bh) },
	{ 0x966d544c, __VMLINUX_SYMBOL_STR(usbnet_get_ethernet_addr) },
	{ 0x14dd10cc, __VMLINUX_SYMBOL_STR(usbnet_skb_return) },
	{ 0x94e1823c, __VMLINUX_SYMBOL_STR(hrtimer_start) },
	{ 0x32ab70a8, __VMLINUX_SYMBOL_STR(usb_driver_release_interface) },
	{ 0x799aca4, __VMLINUX_SYMBOL_STR(local_bh_enable) },
	{ 0x893b615a, __VMLINUX_SYMBOL_STR(usbnet_get_msglevel) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xfc3bd35, __VMLINUX_SYMBOL_STR(hrtimer_init) },
	{ 0xa3e8bb7a, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xc2d63bc1, __VMLINUX_SYMBOL_STR(usb_ifnum_to_if) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x36026fb7, __VMLINUX_SYMBOL_STR(__netif_schedule) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x70b60936, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0xa87b849e, __VMLINUX_SYMBOL_STR(usbnet_manage_power) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x5146ad18, __VMLINUX_SYMBOL_STR(usbnet_write_cmd) },
	{ 0x5e4e83de, __VMLINUX_SYMBOL_STR(usbnet_set_msglevel) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=usbnet";

MODULE_ALIAS("usb:v0BDBp*d*dc*dsc*dp*ic02isc0Dip00in*");
MODULE_ALIAS("usb:v413Cp*d*dc*dsc*dp*ic02isc0Dip00in*");
MODULE_ALIAS("usb:v0930p*d*dc*dsc*dp*ic02isc0Dip00in*");
MODULE_ALIAS("usb:v12D1p*d*dc*dsc*dp*ic02isc0Dip00in*");
MODULE_ALIAS("usb:v12D1p*d*dc*dsc*dp*icFFisc02ip16in*");
MODULE_ALIAS("usb:v12D1p*d*dc*dsc*dp*icFFisc02ip46in*");
MODULE_ALIAS("usb:v12D1p*d*dc*dsc*dp*icFFisc02ip76in*");
MODULE_ALIAS("usb:v1519p0443d*dc*dsc*dp*ic02isc0Dip00in*");
MODULE_ALIAS("usb:v*p*d*dc*dsc*dp*ic02isc0Dip00in*");
