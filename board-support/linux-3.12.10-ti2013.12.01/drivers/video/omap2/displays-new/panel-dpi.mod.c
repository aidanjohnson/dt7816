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
	{ 0xe077bbca, __VMLINUX_SYMBOL_STR(omapdss_default_get_resolution) },
	{ 0x35c39aa9, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0x7781b4da, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0xe14d9449, __VMLINUX_SYMBOL_STR(omapdss_register_display) },
	{ 0xe46cb53f, __VMLINUX_SYMBOL_STR(devm_gpio_request_one) },
	{ 0xe4440714, __VMLINUX_SYMBOL_STR(omap_dss_find_output) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x3d268c44, __VMLINUX_SYMBOL_STR(devm_kzalloc) },
	{ 0x2a4fabcf, __VMLINUX_SYMBOL_STR(videomode_to_omap_video_timings) },
	{ 0xdae715e0, __VMLINUX_SYMBOL_STR(videomode_from_timing) },
	{ 0x646ce2f0, __VMLINUX_SYMBOL_STR(of_get_display_timing) },
	{ 0x3757c9b, __VMLINUX_SYMBOL_STR(of_get_named_gpio_flags) },
	{ 0xdac11bae, __VMLINUX_SYMBOL_STR(of_property_read_u32_array) },
	{ 0x85b72223, __VMLINUX_SYMBOL_STR(omap_dss_find_output_by_node) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xbec25473, __VMLINUX_SYMBOL_STR(of_parse_phandle) },
	{ 0xc3325057, __VMLINUX_SYMBOL_STR(omap_dss_put_device) },
	{ 0x5aaede3b, __VMLINUX_SYMBOL_STR(omapdss_unregister_display) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x3441c3d6, __VMLINUX_SYMBOL_STR(gpio_set_value_cansleep) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=omapdss";

MODULE_ALIAS("of:N*T*Cpanel-dpi*");
