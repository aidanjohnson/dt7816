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
	{ 0x78bc26d7, __VMLINUX_SYMBOL_STR(netdev_info) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xc9bf8bed, __VMLINUX_SYMBOL_STR(mii_ethtool_gset) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x1f44f4d2, __VMLINUX_SYMBOL_STR(phy_disconnect) },
	{ 0xe8abd28b, __VMLINUX_SYMBOL_STR(usbnet_resume) },
	{ 0xed6b9bcf, __VMLINUX_SYMBOL_STR(phy_stop) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x1ea0d766, __VMLINUX_SYMBOL_STR(usbnet_probe) },
	{ 0x599751b9, __VMLINUX_SYMBOL_STR(usbnet_set_settings) },
	{ 0x79aa04a2, __VMLINUX_SYMBOL_STR(get_random_bytes) },
	{ 0x104b440, __VMLINUX_SYMBOL_STR(usbnet_link_change) },
	{ 0xcebe8978, __VMLINUX_SYMBOL_STR(usbnet_disconnect) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0x3604ccb8, __VMLINUX_SYMBOL_STR(generic_mii_ioctl) },
	{ 0x3f2b396f, __VMLINUX_SYMBOL_STR(phy_ethtool_gset) },
	{ 0xbff95b28, __VMLINUX_SYMBOL_STR(usbnet_stop) },
	{ 0x61c9df52, __VMLINUX_SYMBOL_STR(usbnet_update_max_qlen) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xb4ee82dd, __VMLINUX_SYMBOL_STR(mdiobus_unregister) },
	{ 0x63a326ef, __VMLINUX_SYMBOL_STR(__netdev_alloc_skb) },
	{ 0x326dd5c2, __VMLINUX_SYMBOL_STR(phy_start_aneg) },
	{ 0xeba24b67, __VMLINUX_SYMBOL_STR(phy_print_status) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xed24697c, __VMLINUX_SYMBOL_STR(usbnet_nway_reset) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x103266b7, __VMLINUX_SYMBOL_STR(phy_start) },
	{ 0xf55620dc, __VMLINUX_SYMBOL_STR(mii_nway_restart) },
	{ 0xb223f9fb, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0xaabaaa8f, __VMLINUX_SYMBOL_STR(mdiobus_free) },
	{ 0x1264f54c, __VMLINUX_SYMBOL_STR(usbnet_get_endpoints) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0xc34fb7e8, __VMLINUX_SYMBOL_STR(usbnet_get_drvinfo) },
	{ 0x5515ca7f, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xa34f1ef5, __VMLINUX_SYMBOL_STR(crc32_le) },
	{ 0xd25bbb0, __VMLINUX_SYMBOL_STR(usbnet_start_xmit) },
	{ 0x3f97822e, __VMLINUX_SYMBOL_STR(usbnet_suspend) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0x935da5ae, __VMLINUX_SYMBOL_STR(usbnet_get_link) },
	{ 0xe2ea17e8, __VMLINUX_SYMBOL_STR(dev_kfree_skb_any) },
	{ 0xd96f4113, __VMLINUX_SYMBOL_STR(usbnet_get_settings) },
	{ 0xe0816cce, __VMLINUX_SYMBOL_STR(skb_copy_expand) },
	{ 0xd0e4b174, __VMLINUX_SYMBOL_STR(usbnet_read_cmd) },
	{ 0xb1ab37e8, __VMLINUX_SYMBOL_STR(mdiobus_register) },
	{ 0x1879316f, __VMLINUX_SYMBOL_STR(usbnet_tx_timeout) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x2e412c66, __VMLINUX_SYMBOL_STR(genphy_resume) },
	{ 0x14dd10cc, __VMLINUX_SYMBOL_STR(usbnet_skb_return) },
	{ 0x42ee5024, __VMLINUX_SYMBOL_STR(usbnet_open) },
	{ 0xf13c1341, __VMLINUX_SYMBOL_STR(mii_check_media) },
	{ 0x893b615a, __VMLINUX_SYMBOL_STR(usbnet_get_msglevel) },
	{ 0xbc35e3cc, __VMLINUX_SYMBOL_STR(netdev_err) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xfaf98462, __VMLINUX_SYMBOL_STR(bitrev32) },
	{ 0x253d43c1, __VMLINUX_SYMBOL_STR(usbnet_unlink_rx_urbs) },
	{ 0xd63271fb, __VMLINUX_SYMBOL_STR(eth_validate_addr) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x39fee11, __VMLINUX_SYMBOL_STR(usbnet_write_cmd_async) },
	{ 0x1e1a511c, __VMLINUX_SYMBOL_STR(usbnet_change_mtu) },
	{ 0x6486efff, __VMLINUX_SYMBOL_STR(phy_connect) },
	{ 0xa3e8bb7a, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xea4b5bd2, __VMLINUX_SYMBOL_STR(phy_mii_ioctl) },
	{ 0x4abc8791, __VMLINUX_SYMBOL_STR(phy_ethtool_sset) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x4a7c1a63, __VMLINUX_SYMBOL_STR(mii_link_ok) },
	{ 0x99bb8806, __VMLINUX_SYMBOL_STR(memmove) },
	{ 0x70b60936, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0x5471c290, __VMLINUX_SYMBOL_STR(eth_mac_addr) },
	{ 0x5146ad18, __VMLINUX_SYMBOL_STR(usbnet_write_cmd) },
	{ 0x5e4e83de, __VMLINUX_SYMBOL_STR(usbnet_set_msglevel) },
	{ 0x38c242ac, __VMLINUX_SYMBOL_STR(mdiobus_alloc_size) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=usbnet";

MODULE_ALIAS("usb:v077Bp2226d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0846p1040d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2001p1A00d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0B95p1720d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v07B8p420Ad*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v08DDp90FFd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0557p2009d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0411p003Dd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0411p006Ed*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v6189p182Dd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0DF6p0056d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v07AAp0017d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1189p0893d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1631p6200d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v04F1p3008d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v17EFp7203d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0B95p772Bd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0B95p7720d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0B95p1780d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0789p0160d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v13B1p0018d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1557p7720d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v07D1p3C05d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2001p3C05d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2001p1A02d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1737p0039d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v04BBp0930d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v050Dp5055d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v05ACp1402d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0B95p772Ad*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v14EApAB11d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0DB0pA877d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0B95p7E2Bd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0B95p172Ad*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v066Bp20F9d*dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "EE904045B70F9BD8F86F7CA");
