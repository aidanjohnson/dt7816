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
	{ 0x71ab7ace, __VMLINUX_SYMBOL_STR(v4l2_subdev_querymenu) },
	{ 0x5b95951d, __VMLINUX_SYMBOL_STR(v4l2_subdev_try_ext_ctrls) },
	{ 0x68b81a89, __VMLINUX_SYMBOL_STR(v4l2_subdev_s_ext_ctrls) },
	{ 0x3200659d, __VMLINUX_SYMBOL_STR(v4l2_subdev_g_ext_ctrls) },
	{ 0xd466e51c, __VMLINUX_SYMBOL_STR(v4l2_subdev_s_ctrl) },
	{ 0x7717d7c4, __VMLINUX_SYMBOL_STR(v4l2_subdev_g_ctrl) },
	{ 0x9c59680f, __VMLINUX_SYMBOL_STR(v4l2_subdev_queryctrl) },
	{ 0xa731ccf6, __VMLINUX_SYMBOL_STR(i2c_del_driver) },
	{ 0xe25a742c, __VMLINUX_SYMBOL_STR(i2c_register_driver) },
	{ 0x70806c73, __VMLINUX_SYMBOL_STR(v4l2_ctrl_handler_setup) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x9df055b, __VMLINUX_SYMBOL_STR(v4l2_ctrl_auto_cluster) },
	{ 0xdac751f0, __VMLINUX_SYMBOL_STR(v4l2_ctrl_new_std) },
	{ 0xb3f1ab10, __VMLINUX_SYMBOL_STR(v4l2_ctrl_handler_init_class) },
	{ 0x76973130, __VMLINUX_SYMBOL_STR(v4l2_i2c_subdev_init) },
	{ 0x3d268c44, __VMLINUX_SYMBOL_STR(devm_kzalloc) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0x59e5070d, __VMLINUX_SYMBOL_STR(__do_div64) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0xb6ce7eb5, __VMLINUX_SYMBOL_STR(v4l2_ctrl_handler_log_status) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xdd384ca3, __VMLINUX_SYMBOL_STR(i2c_smbus_read_byte_data) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x69d0f0ae, __VMLINUX_SYMBOL_STR(i2c_smbus_write_byte_data) },
	{ 0x14c47d67, __VMLINUX_SYMBOL_STR(v4l2_ctrl_handler_free) },
	{ 0x838a9964, __VMLINUX_SYMBOL_STR(v4l2_device_unregister_subdev) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("i2c:saa7115_auto");
MODULE_ALIAS("i2c:saa7111");
MODULE_ALIAS("i2c:saa7113");
MODULE_ALIAS("i2c:saa7114");
MODULE_ALIAS("i2c:saa7115");
MODULE_ALIAS("i2c:saa7118");
MODULE_ALIAS("i2c:gm7113c");
