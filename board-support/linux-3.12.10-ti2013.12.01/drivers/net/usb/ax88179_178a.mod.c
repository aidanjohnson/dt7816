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
	{ 0xcebe8978, __VMLINUX_SYMBOL_STR(usbnet_disconnect) },
	{ 0x1ea0d766, __VMLINUX_SYMBOL_STR(usbnet_probe) },
	{ 0xa4c7fa32, __VMLINUX_SYMBOL_STR(ethtool_op_get_link) },
	{ 0xed24697c, __VMLINUX_SYMBOL_STR(usbnet_nway_reset) },
	{ 0x5e4e83de, __VMLINUX_SYMBOL_STR(usbnet_set_msglevel) },
	{ 0x893b615a, __VMLINUX_SYMBOL_STR(usbnet_get_msglevel) },
	{ 0x1879316f, __VMLINUX_SYMBOL_STR(usbnet_tx_timeout) },
	{ 0xd63271fb, __VMLINUX_SYMBOL_STR(eth_validate_addr) },
	{ 0xd25bbb0, __VMLINUX_SYMBOL_STR(usbnet_start_xmit) },
	{ 0xbff95b28, __VMLINUX_SYMBOL_STR(usbnet_stop) },
	{ 0x42ee5024, __VMLINUX_SYMBOL_STR(usbnet_open) },
	{ 0xb223f9fb, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0xa3e8bb7a, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0x39fee11, __VMLINUX_SYMBOL_STR(usbnet_write_cmd_async) },
	{ 0xfaf98462, __VMLINUX_SYMBOL_STR(bitrev32) },
	{ 0xa34f1ef5, __VMLINUX_SYMBOL_STR(crc32_le) },
	{ 0x61c9df52, __VMLINUX_SYMBOL_STR(usbnet_update_max_qlen) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x1264f54c, __VMLINUX_SYMBOL_STR(usbnet_get_endpoints) },
	{ 0xf55620dc, __VMLINUX_SYMBOL_STR(mii_nway_restart) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x4a8342f8, __VMLINUX_SYMBOL_STR(netif_carrier_on) },
	{ 0x78bc26d7, __VMLINUX_SYMBOL_STR(netdev_info) },
	{ 0x3f97822e, __VMLINUX_SYMBOL_STR(usbnet_suspend) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0xe8abd28b, __VMLINUX_SYMBOL_STR(usbnet_resume) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x104b440, __VMLINUX_SYMBOL_STR(usbnet_link_change) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x972c6109, __VMLINUX_SYMBOL_STR(usbnet_write_cmd_nopm) },
	{ 0x5146ad18, __VMLINUX_SYMBOL_STR(usbnet_write_cmd) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x24675689, __VMLINUX_SYMBOL_STR(usbnet_read_cmd_nopm) },
	{ 0xd0e4b174, __VMLINUX_SYMBOL_STR(usbnet_read_cmd) },
	{ 0x18b61eb6, __VMLINUX_SYMBOL_STR(netdev_warn) },
	{ 0x3604ccb8, __VMLINUX_SYMBOL_STR(generic_mii_ioctl) },
	{ 0xc9bf8bed, __VMLINUX_SYMBOL_STR(mii_ethtool_gset) },
	{ 0x34cf8908, __VMLINUX_SYMBOL_STR(mii_ethtool_sset) },
	{ 0x14dd10cc, __VMLINUX_SYMBOL_STR(usbnet_skb_return) },
	{ 0xb2038f57, __VMLINUX_SYMBOL_STR(skb_clone) },
	{ 0xe40dc473, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0x594ff15d, __VMLINUX_SYMBOL_STR(skb_trim) },
	{ 0x5515ca7f, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0xe2ea17e8, __VMLINUX_SYMBOL_STR(dev_kfree_skb_any) },
	{ 0xd796878f, __VMLINUX_SYMBOL_STR(pskb_expand_head) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=usbnet";

MODULE_ALIAS("usb:v0B95p1790d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0B95p178Ad*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0DF6p0072d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v04E8pA100d*dc*dsc*dp*ic*isc*ip*in*");
