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
	{ 0xe4d1591e, __VMLINUX_SYMBOL_STR(fsg_config_from_params) },
	{ 0x1ccb58f7, __VMLINUX_SYMBOL_STR(fsg_common_set_num_buffers) },
	{ 0x6acb4179, __VMLINUX_SYMBOL_STR(fsg_common_set_inquiry_string) },
	{ 0xc0e95803, __VMLINUX_SYMBOL_STR(usb_add_config) },
	{ 0x141fce2a, __VMLINUX_SYMBOL_STR(fsg_common_remove_luns) },
	{ 0xa5230df, __VMLINUX_SYMBOL_STR(fsg_common_set_nluns) },
	{ 0x33ba5cd4, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x96f8eb92, __VMLINUX_SYMBOL_STR(gether_set_host_addr) },
	{ 0x9a0221c7, __VMLINUX_SYMBOL_STR(fsg_common_free_buffers) },
	{ 0x5d41c87c, __VMLINUX_SYMBOL_STR(param_ops_charp) },
	{ 0xcfcaf3b6, __VMLINUX_SYMBOL_STR(fsg_common_set_cdev) },
	{ 0xc3de41c, __VMLINUX_SYMBOL_STR(usb_put_function_instance) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xe7e11537, __VMLINUX_SYMBOL_STR(gether_set_gadget) },
	{ 0xf4b71fe8, __VMLINUX_SYMBOL_STR(gether_set_qmult) },
	{ 0xcf1aa0cf, __VMLINUX_SYMBOL_STR(usb_composite_overwrite_options) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x54aecd30, __VMLINUX_SYMBOL_STR(gether_register_netdev) },
	{ 0x1dba1f67, __VMLINUX_SYMBOL_STR(usb_composite_probe) },
	{ 0x103019c, __VMLINUX_SYMBOL_STR(usb_add_function) },
	{ 0x7617b124, __VMLINUX_SYMBOL_STR(rndis_borrow_net) },
	{ 0xd3ae3b65, __VMLINUX_SYMBOL_STR(fsg_common_create_luns) },
	{ 0xc3825d44, __VMLINUX_SYMBOL_STR(usb_put_function) },
	{ 0x4ff2ad3e, __VMLINUX_SYMBOL_STR(gether_set_dev_addr) },
	{ 0xd28defee, __VMLINUX_SYMBOL_STR(usb_composite_unregister) },
	{ 0xe3405d47, __VMLINUX_SYMBOL_STR(usb_get_function) },
	{ 0x9dc025a5, __VMLINUX_SYMBOL_STR(fsg_common_free_luns) },
	{ 0x3aa4302b, __VMLINUX_SYMBOL_STR(usb_string_ids_tab) },
	{ 0x20b2bb2d, __VMLINUX_SYMBOL_STR(param_array_ops) },
	{ 0x51707c29, __VMLINUX_SYMBOL_STR(fsg_common_run_thread) },
	{ 0x22df473a, __VMLINUX_SYMBOL_STR(usb_get_function_instance) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x7e26d4a5, __VMLINUX_SYMBOL_STR(fsg_common_set_sysfs) },
	{ 0xafad493b, __VMLINUX_SYMBOL_STR(param_ops_ushort) },
	{ 0x47c8baf4, __VMLINUX_SYMBOL_STR(param_ops_uint) },
	{ 0xacb7343e, __VMLINUX_SYMBOL_STR(usb_remove_function) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=usb_f_mass_storage,libcomposite,u_ether,usb_f_rndis";

