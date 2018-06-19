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
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x4d763937, __VMLINUX_SYMBOL_STR(eth_change_mtu) },
	{ 0xd63271fb, __VMLINUX_SYMBOL_STR(eth_validate_addr) },
	{ 0x1f05bf4a, __VMLINUX_SYMBOL_STR(driver_unregister) },
	{ 0xbdf61e00, __VMLINUX_SYMBOL_STR(spi_register_driver) },
	{ 0xd87c2198, __VMLINUX_SYMBOL_STR(register_netdev) },
	{ 0xd6b8e852, __VMLINUX_SYMBOL_STR(request_threaded_irq) },
	{ 0x79aa04a2, __VMLINUX_SYMBOL_STR(get_random_bytes) },
	{ 0x18b61eb6, __VMLINUX_SYMBOL_STR(netdev_warn) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0xcf636b9e, __VMLINUX_SYMBOL_STR(alloc_etherdev_mqs) },
	{ 0x36026fb7, __VMLINUX_SYMBOL_STR(__netif_schedule) },
	{ 0x2a3aa678, __VMLINUX_SYMBOL_STR(_test_and_clear_bit) },
	{ 0x1d86556, __VMLINUX_SYMBOL_STR(mii_check_link) },
	{ 0x5bc60d2f, __VMLINUX_SYMBOL_STR(netif_rx_ni) },
	{ 0x746f15cf, __VMLINUX_SYMBOL_STR(eth_type_trans) },
	{ 0x70b60936, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0x63a326ef, __VMLINUX_SYMBOL_STR(__netdev_alloc_skb) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x27cb133b, __VMLINUX_SYMBOL_STR(eeprom_93cx6_multiread) },
	{ 0x822222db, __VMLINUX_SYMBOL_STR(eeprom_93cx6_write) },
	{ 0x98bb5a22, __VMLINUX_SYMBOL_STR(eeprom_93cx6_read) },
	{ 0x63d2ff63, __VMLINUX_SYMBOL_STR(eeprom_93cx6_wren) },
	{ 0xfba0a21b, __VMLINUX_SYMBOL_STR(netif_device_detach) },
	{ 0x92b57248, __VMLINUX_SYMBOL_STR(flush_work) },
	{ 0x78bc26d7, __VMLINUX_SYMBOL_STR(netdev_info) },
	{ 0x57feb1f2, __VMLINUX_SYMBOL_STR(netif_device_attach) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x50d6202a, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0x1cff016, __VMLINUX_SYMBOL_STR(skb_dequeue) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0xbc35e3cc, __VMLINUX_SYMBOL_STR(netdev_err) },
	{ 0xc00cee86, __VMLINUX_SYMBOL_STR(spi_sync) },
	{ 0xc9bf8bed, __VMLINUX_SYMBOL_STR(mii_ethtool_gset) },
	{ 0x34cf8908, __VMLINUX_SYMBOL_STR(mii_ethtool_sset) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0xf55620dc, __VMLINUX_SYMBOL_STR(mii_nway_restart) },
	{ 0x4a7c1a63, __VMLINUX_SYMBOL_STR(mii_link_ok) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0x7783bae2, __VMLINUX_SYMBOL_STR(skb_queue_tail) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x70eae364, __VMLINUX_SYMBOL_STR(netdev_printk) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0xfaf98462, __VMLINUX_SYMBOL_STR(bitrev32) },
	{ 0xa34f1ef5, __VMLINUX_SYMBOL_STR(crc32_le) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x3604ccb8, __VMLINUX_SYMBOL_STR(generic_mii_ioctl) },
	{ 0xe94f1e83, __VMLINUX_SYMBOL_STR(free_netdev) },
	{ 0xf20dabd8, __VMLINUX_SYMBOL_STR(free_irq) },
	{ 0xf680cb71, __VMLINUX_SYMBOL_STR(unregister_netdev) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

