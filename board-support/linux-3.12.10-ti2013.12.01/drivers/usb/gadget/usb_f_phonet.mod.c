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
	{ 0x8d224de9, __VMLINUX_SYMBOL_STR(usb_free_all_descriptors) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x3f358d29, __VMLINUX_SYMBOL_STR(page_address) },
	{ 0x4a8342f8, __VMLINUX_SYMBOL_STR(netif_carrier_on) },
	{ 0x2a3aa678, __VMLINUX_SYMBOL_STR(_test_and_clear_bit) },
	{ 0x94ee05c8, __VMLINUX_SYMBOL_STR(netif_carrier_off) },
	{ 0x54ecda5c, __VMLINUX_SYMBOL_STR(gether_get_ifname) },
	{ 0x83666d82, __VMLINUX_SYMBOL_STR(usb_function_unregister) },
	{ 0xfc55d6db, __VMLINUX_SYMBOL_STR(__alloc_pages_nodemask) },
	{ 0x63a326ef, __VMLINUX_SYMBOL_STR(__netdev_alloc_skb) },
	{ 0xfcd5641, __VMLINUX_SYMBOL_STR(netif_rx) },
	{ 0x29316ca9, __VMLINUX_SYMBOL_STR(phonet_header_ops) },
	{ 0xc3de41c, __VMLINUX_SYMBOL_STR(usb_put_function_instance) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x993db83b, __VMLINUX_SYMBOL_STR(usb_ep_autoconfig) },
	{ 0xe94f1e83, __VMLINUX_SYMBOL_STR(free_netdev) },
	{ 0xd87c2198, __VMLINUX_SYMBOL_STR(register_netdev) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xb335762d, __VMLINUX_SYMBOL_STR(config_group_init_type_name) },
	{ 0xe2ea17e8, __VMLINUX_SYMBOL_STR(dev_kfree_skb_any) },
	{ 0x92fbb490, __VMLINUX_SYMBOL_STR(usb_function_register) },
	{ 0x306a1617, __VMLINUX_SYMBOL_STR(contig_page_data) },
	{ 0x80dddc87, __VMLINUX_SYMBOL_STR(dev_kfree_skb_irq) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0xfb4628f9, __VMLINUX_SYMBOL_STR(alloc_netdev_mqs) },
	{ 0x28ce7192, __VMLINUX_SYMBOL_STR(config_ep_by_speed) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xa84a5285, __VMLINUX_SYMBOL_STR(skb_add_rx_frag) },
	{ 0x34fef0bf, __VMLINUX_SYMBOL_STR(put_page) },
	{ 0x131d8fcf, __VMLINUX_SYMBOL_STR(usb_assign_descriptors) },
	{ 0x2e23ffa6, __VMLINUX_SYMBOL_STR(usb_interface_id) },
	{ 0xf680cb71, __VMLINUX_SYMBOL_STR(unregister_netdev) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0x36026fb7, __VMLINUX_SYMBOL_STR(__netif_schedule) },
	{ 0x50d6202a, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0x70b60936, __VMLINUX_SYMBOL_STR(skb_put) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=libcomposite,u_ether,phonet";

