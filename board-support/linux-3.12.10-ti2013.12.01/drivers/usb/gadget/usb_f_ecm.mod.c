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
	{ 0x816e7c00, __VMLINUX_SYMBOL_STR(usb_gstrings_attach) },
	{ 0x8d224de9, __VMLINUX_SYMBOL_STR(usb_free_all_descriptors) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x12cfbf94, __VMLINUX_SYMBOL_STR(gether_get_qmult) },
	{ 0x42ce0e69, __VMLINUX_SYMBOL_STR(gether_setup_name_default) },
	{ 0xc29551e3, __VMLINUX_SYMBOL_STR(dev_printk) },
	{ 0x4af2e282, __VMLINUX_SYMBOL_STR(gether_get_host_addr_cdc) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x54ecda5c, __VMLINUX_SYMBOL_STR(gether_get_ifname) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x8878cfa6, __VMLINUX_SYMBOL_STR(gether_cleanup) },
	{ 0x83666d82, __VMLINUX_SYMBOL_STR(usb_function_unregister) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x96f8eb92, __VMLINUX_SYMBOL_STR(gether_set_host_addr) },
	{ 0x78d16ccf, __VMLINUX_SYMBOL_STR(gether_get_dev_addr) },
	{ 0xebac2198, __VMLINUX_SYMBOL_STR(gether_connect) },
	{ 0xc3de41c, __VMLINUX_SYMBOL_STR(usb_put_function_instance) },
	{ 0x5a5a94a6, __VMLINUX_SYMBOL_STR(kstrtou8) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x993db83b, __VMLINUX_SYMBOL_STR(usb_ep_autoconfig) },
	{ 0xe94f1e83, __VMLINUX_SYMBOL_STR(free_netdev) },
	{ 0xe7e11537, __VMLINUX_SYMBOL_STR(gether_set_gadget) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x5e214312, __VMLINUX_SYMBOL_STR(gether_get_host_addr) },
	{ 0xb335762d, __VMLINUX_SYMBOL_STR(config_group_init_type_name) },
	{ 0xf4b71fe8, __VMLINUX_SYMBOL_STR(gether_set_qmult) },
	{ 0x92fbb490, __VMLINUX_SYMBOL_STR(usb_function_register) },
	{ 0x54aecd30, __VMLINUX_SYMBOL_STR(gether_register_netdev) },
	{ 0x4ff2ad3e, __VMLINUX_SYMBOL_STR(gether_set_dev_addr) },
	{ 0x28ce7192, __VMLINUX_SYMBOL_STR(config_ep_by_speed) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xdf90cf2e, __VMLINUX_SYMBOL_STR(gether_disconnect) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x131d8fcf, __VMLINUX_SYMBOL_STR(usb_assign_descriptors) },
	{ 0x2e23ffa6, __VMLINUX_SYMBOL_STR(usb_interface_id) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=libcomposite,u_ether";

