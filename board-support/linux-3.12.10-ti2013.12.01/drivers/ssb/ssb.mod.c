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
	{ 0xa26ada4a, __VMLINUX_SYMBOL_STR(sdio_writeb) },
	{ 0x4dff5858, __VMLINUX_SYMBOL_STR(sdio_readb) },
	{ 0xbc32724b, __VMLINUX_SYMBOL_STR(bus_register) },
	{ 0xc2290b94, __VMLINUX_SYMBOL_STR(device_remove_file) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0xaa13d05, __VMLINUX_SYMBOL_STR(__raw_readsw) },
	{ 0x6d1fb2cd, __VMLINUX_SYMBOL_STR(driver_register) },
	{ 0x999c3148, __VMLINUX_SYMBOL_STR(__raw_readsb) },
	{ 0xbdf2580d, __VMLINUX_SYMBOL_STR(__raw_readsl) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0xca24564a, __VMLINUX_SYMBOL_STR(sdio_writesb) },
	{ 0xfb6a700, __VMLINUX_SYMBOL_STR(pci_disable_device) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0x53a2cfe9, __VMLINUX_SYMBOL_STR(pci_release_regions) },
	{ 0xe6c3ebb0, __VMLINUX_SYMBOL_STR(__raw_writesw) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x94cab319, __VMLINUX_SYMBOL_STR(pci_bus_write_config_word) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x527e74c1, __VMLINUX_SYMBOL_STR(pci_set_master) },
	{ 0xc6d1587a, __VMLINUX_SYMBOL_STR(sdio_writel) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x21534191, __VMLINUX_SYMBOL_STR(pci_restore_state) },
	{ 0xaccdabb8, __VMLINUX_SYMBOL_STR(device_register) },
	{ 0x11089ac7, __VMLINUX_SYMBOL_STR(_ctype) },
	{ 0x9bd4f641, __VMLINUX_SYMBOL_STR(pci_iounmap) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x78f6258c, __VMLINUX_SYMBOL_STR(mutex_lock_interruptible) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x1f05bf4a, __VMLINUX_SYMBOL_STR(driver_unregister) },
	{ 0xf929b86c, __VMLINUX_SYMBOL_STR(sdio_readl) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x521934aa, __VMLINUX_SYMBOL_STR(pci_bus_write_config_dword) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0x96c3c292, __VMLINUX_SYMBOL_STR(bus_unregister) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0x2d43fdf2, __VMLINUX_SYMBOL_STR(sdio_readsb) },
	{ 0xfc27bfdd, __VMLINUX_SYMBOL_STR(device_create_file) },
	{ 0x8233b9b6, __VMLINUX_SYMBOL_STR(pci_bus_read_config_word) },
	{ 0x14cd8ec1, __VMLINUX_SYMBOL_STR(pci_bus_read_config_dword) },
	{ 0x63d684c9, __VMLINUX_SYMBOL_STR(put_device) },
	{ 0xc2165d85, __VMLINUX_SYMBOL_STR(__arm_iounmap) },
	{ 0x996bdb64, __VMLINUX_SYMBOL_STR(_kstrtoul) },
	{ 0xcd3f5e8a, __VMLINUX_SYMBOL_STR(pci_unregister_driver) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x2c413068, __VMLINUX_SYMBOL_STR(get_device) },
	{ 0x75fee7fd, __VMLINUX_SYMBOL_STR(__raw_writesb) },
	{ 0x6017850b, __VMLINUX_SYMBOL_STR(pci_set_power_state) },
	{ 0xbdbcbb8d, __VMLINUX_SYMBOL_STR(sdio_writew) },
	{ 0x51908eb8, __VMLINUX_SYMBOL_STR(__raw_writesl) },
	{ 0x1e047854, __VMLINUX_SYMBOL_STR(warn_slowpath_fmt) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x16613cac, __VMLINUX_SYMBOL_STR(pci_request_regions) },
	{ 0x2a6ee38b, __VMLINUX_SYMBOL_STR(__pci_register_driver) },
	{ 0x8552b5b9, __VMLINUX_SYMBOL_STR(device_unregister) },
	{ 0xfb961d14, __VMLINUX_SYMBOL_STR(__arm_ioremap) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x8cb34129, __VMLINUX_SYMBOL_STR(pci_choose_state) },
	{ 0x87d74938, __VMLINUX_SYMBOL_STR(sdio_readw) },
	{ 0x7ce54769, __VMLINUX_SYMBOL_STR(pci_iomap) },
	{ 0x44a17998, __VMLINUX_SYMBOL_STR(sdio_claim_host) },
	{ 0x8ecb1aa8, __VMLINUX_SYMBOL_STR(dev_set_name) },
	{ 0x95069dd9, __VMLINUX_SYMBOL_STR(pci_enable_device) },
	{ 0xac8f37b2, __VMLINUX_SYMBOL_STR(outer_cache) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x2407dc39, __VMLINUX_SYMBOL_STR(sdio_release_host) },
	{ 0x83e3367e, __VMLINUX_SYMBOL_STR(pci_save_state) },
	{ 0xa7f92105, __VMLINUX_SYMBOL_STR(add_uevent_var) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("pci:v000014E4d00004301sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d00004306sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d00004307sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d00004311sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d00004312sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d00004315sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d00004318sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014A4d00004318sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d00004319sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d00004320sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d00004321sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d00004322sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d0000A8D6sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d00004324sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d00004325sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d00004328sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d00004329sv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d0000432Bsv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d0000432Csv*sd*bc*sc*i*");
MODULE_ALIAS("pci:v000014E4d00004350sv*sd*bc*sc*i*");
