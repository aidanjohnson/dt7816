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
	{ 0x35c39aa9, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0x7781b4da, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0xb6936ffe, __VMLINUX_SYMBOL_STR(_bcd2bin) },
	{ 0x80ca5026, __VMLINUX_SYMBOL_STR(_bin2bcd) },
	{ 0xff178f6, __VMLINUX_SYMBOL_STR(__aeabi_idivmod) },
	{ 0x51d12ba8, __VMLINUX_SYMBOL_STR(devm_rtc_device_register) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x3d268c44, __VMLINUX_SYMBOL_STR(devm_kzalloc) },
	{ 0x47229b5c, __VMLINUX_SYMBOL_STR(gpio_request) },
	{ 0xfe990052, __VMLINUX_SYMBOL_STR(gpio_free) },
	{ 0x6c8d5ae8, __VMLINUX_SYMBOL_STR(__gpio_get_value) },
	{ 0x65d6d0f0, __VMLINUX_SYMBOL_STR(gpio_direction_input) },
	{ 0x432fd7f6, __VMLINUX_SYMBOL_STR(__gpio_set_value) },
	{ 0xa8f59416, __VMLINUX_SYMBOL_STR(gpio_direction_output) },
	{ 0xfb961d14, __VMLINUX_SYMBOL_STR(__arm_ioremap) },
	{ 0xc2165d85, __VMLINUX_SYMBOL_STR(__arm_iounmap) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xac8f37b2, __VMLINUX_SYMBOL_STR(outer_cache) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";
