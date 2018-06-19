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
	{ 0x33ba5cd4, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0x48d88451, __VMLINUX_SYMBOL_STR(usb_ep_autoconfig_reset) },
	{ 0x5d41c87c, __VMLINUX_SYMBOL_STR(param_ops_charp) },
	{ 0xc3de41c, __VMLINUX_SYMBOL_STR(usb_put_function_instance) },
	{ 0xcf1aa0cf, __VMLINUX_SYMBOL_STR(usb_composite_overwrite_options) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x1dba1f67, __VMLINUX_SYMBOL_STR(usb_composite_probe) },
	{ 0x103019c, __VMLINUX_SYMBOL_STR(usb_add_function) },
	{ 0xc3825d44, __VMLINUX_SYMBOL_STR(usb_put_function) },
	{ 0xd28defee, __VMLINUX_SYMBOL_STR(usb_composite_unregister) },
	{ 0xe3405d47, __VMLINUX_SYMBOL_STR(usb_get_function) },
	{ 0x3aa4302b, __VMLINUX_SYMBOL_STR(usb_string_ids_tab) },
	{ 0x9a254bad, __VMLINUX_SYMBOL_STR(usb_add_config_only) },
	{ 0x22df473a, __VMLINUX_SYMBOL_STR(usb_get_function_instance) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xafad493b, __VMLINUX_SYMBOL_STR(param_ops_ushort) },
	{ 0x47c8baf4, __VMLINUX_SYMBOL_STR(param_ops_uint) },
	{ 0xacb7343e, __VMLINUX_SYMBOL_STR(usb_remove_function) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=libcomposite";

