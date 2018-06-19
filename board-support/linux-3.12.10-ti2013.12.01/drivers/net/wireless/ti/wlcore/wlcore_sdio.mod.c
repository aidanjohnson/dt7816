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
	{ 0xc34ad504, __VMLINUX_SYMBOL_STR(__pm_runtime_idle) },
	{ 0x36d7b11a, __VMLINUX_SYMBOL_STR(of_find_matching_node_and_match) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0xca24564a, __VMLINUX_SYMBOL_STR(sdio_writesb) },
	{ 0x151e56a5, __VMLINUX_SYMBOL_STR(sdio_enable_func) },
	{ 0xdac11bae, __VMLINUX_SYMBOL_STR(of_property_read_u32_array) },
	{ 0xe2fae716, __VMLINUX_SYMBOL_STR(kmemdup) },
	{ 0x403f9529, __VMLINUX_SYMBOL_STR(gpio_request_one) },
	{ 0x33ba5cd4, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0xb2468ee6, __VMLINUX_SYMBOL_STR(__pm_runtime_resume) },
	{ 0x93405ae0, __VMLINUX_SYMBOL_STR(wl12xx_get_platform_data) },
	{ 0x7e4f55f1, __VMLINUX_SYMBOL_STR(sdio_get_host_pm_caps) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x43632d7d, __VMLINUX_SYMBOL_STR(of_find_property) },
	{ 0xd727a63c, __VMLINUX_SYMBOL_STR(platform_device_alloc) },
	{ 0x4fb7d5a2, __VMLINUX_SYMBOL_STR(platform_device_add) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xbadfd0e, __VMLINUX_SYMBOL_STR(platform_device_unregister) },
	{ 0x2d43fdf2, __VMLINUX_SYMBOL_STR(sdio_readsb) },
	{ 0xd6f52eb1, __VMLINUX_SYMBOL_STR(sdio_unregister_driver) },
	{ 0xac4a3fbd, __VMLINUX_SYMBOL_STR(platform_device_add_resources) },
	{ 0xee5c4205, __VMLINUX_SYMBOL_STR(sdio_f0_writeb) },
	{ 0x7dd82ea8, __VMLINUX_SYMBOL_STR(sdio_set_host_pm_flags) },
	{ 0x4059792f, __VMLINUX_SYMBOL_STR(print_hex_dump) },
	{ 0x11f447ce, __VMLINUX_SYMBOL_STR(__gpio_to_irq) },
	{ 0xb2cf734c, __VMLINUX_SYMBOL_STR(sdio_f0_readb) },
	{ 0xac3c3cd9, __VMLINUX_SYMBOL_STR(platform_device_add_data) },
	{ 0x76458bb2, __VMLINUX_SYMBOL_STR(mmc_power_save_host) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x351fe609, __VMLINUX_SYMBOL_STR(mmc_power_restore_host) },
	{ 0x56ed5566, __VMLINUX_SYMBOL_STR(sdio_memcpy_toio) },
	{ 0xfe990052, __VMLINUX_SYMBOL_STR(gpio_free) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x377db316, __VMLINUX_SYMBOL_STR(sdio_register_driver) },
	{ 0xe4de6b33, __VMLINUX_SYMBOL_STR(sdio_memcpy_fromio) },
	{ 0x44a17998, __VMLINUX_SYMBOL_STR(sdio_claim_host) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x69c15397, __VMLINUX_SYMBOL_STR(sdio_set_block_size) },
	{ 0x161a8033, __VMLINUX_SYMBOL_STR(sdio_disable_func) },
	{ 0x2407dc39, __VMLINUX_SYMBOL_STR(sdio_release_host) },
	{ 0xb3f38dbc, __VMLINUX_SYMBOL_STR(platform_device_put) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("sdio:c*v0097d4076*");
MODULE_ALIAS("of:N*T*Cwlcore*");
