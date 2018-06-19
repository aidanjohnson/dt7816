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
	{ 0xb79a5aed, __VMLINUX_SYMBOL_STR(input_event) },
	{ 0x6c8d5ae8, __VMLINUX_SYMBOL_STR(__gpio_get_value) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xd28c80f4, __VMLINUX_SYMBOL_STR(input_register_polled_device) },
	{ 0xfc88fbae, __VMLINUX_SYMBOL_STR(input_set_capability) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0xad9c3b30, __VMLINUX_SYMBOL_STR(input_allocate_polled_device) },
	{ 0x65d6d0f0, __VMLINUX_SYMBOL_STR(gpio_direction_input) },
	{ 0x47229b5c, __VMLINUX_SYMBOL_STR(gpio_request) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xfe990052, __VMLINUX_SYMBOL_STR(gpio_free) },
	{ 0xc2e2733e, __VMLINUX_SYMBOL_STR(input_free_polled_device) },
	{ 0x7cbf151c, __VMLINUX_SYMBOL_STR(input_unregister_polled_device) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

