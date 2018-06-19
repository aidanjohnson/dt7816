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
	{ 0x71ab7ace, __VMLINUX_SYMBOL_STR(v4l2_subdev_querymenu) },
	{ 0x5b95951d, __VMLINUX_SYMBOL_STR(v4l2_subdev_try_ext_ctrls) },
	{ 0x68b81a89, __VMLINUX_SYMBOL_STR(v4l2_subdev_s_ext_ctrls) },
	{ 0x3200659d, __VMLINUX_SYMBOL_STR(v4l2_subdev_g_ext_ctrls) },
	{ 0xd466e51c, __VMLINUX_SYMBOL_STR(v4l2_subdev_s_ctrl) },
	{ 0x7717d7c4, __VMLINUX_SYMBOL_STR(v4l2_subdev_g_ctrl) },
	{ 0x9c59680f, __VMLINUX_SYMBOL_STR(v4l2_subdev_queryctrl) },
	{ 0xa731ccf6, __VMLINUX_SYMBOL_STR(i2c_del_driver) },
	{ 0xe25a742c, __VMLINUX_SYMBOL_STR(i2c_register_driver) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x8169d80e, __VMLINUX_SYMBOL_STR(i2c_transfer) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xdac751f0, __VMLINUX_SYMBOL_STR(v4l2_ctrl_new_std) },
	{ 0xb3f1ab10, __VMLINUX_SYMBOL_STR(v4l2_ctrl_handler_init_class) },
	{ 0x76973130, __VMLINUX_SYMBOL_STR(v4l2_i2c_subdev_init) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x14c47d67, __VMLINUX_SYMBOL_STR(v4l2_ctrl_handler_free) },
	{ 0x838a9964, __VMLINUX_SYMBOL_STR(v4l2_device_unregister_subdev) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x1e9f1a37, __VMLINUX_SYMBOL_STR(i2c_master_send) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("i2c:saa7706h");
