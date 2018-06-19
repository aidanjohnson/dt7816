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
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0xa731ccf6, __VMLINUX_SYMBOL_STR(i2c_del_driver) },
	{ 0xe25a742c, __VMLINUX_SYMBOL_STR(i2c_register_driver) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xd6b8e852, __VMLINUX_SYMBOL_STR(request_threaded_irq) },
	{ 0xa3afaa39, __VMLINUX_SYMBOL_STR(v4l2_ctrl_cluster) },
	{ 0xafdf6647, __VMLINUX_SYMBOL_STR(v4l2_ctrl_new_std_menu) },
	{ 0xdac751f0, __VMLINUX_SYMBOL_STR(v4l2_ctrl_new_std) },
	{ 0xb3f1ab10, __VMLINUX_SYMBOL_STR(v4l2_ctrl_handler_init_class) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0x76973130, __VMLINUX_SYMBOL_STR(v4l2_i2c_subdev_init) },
	{ 0xc01b1a5d, __VMLINUX_SYMBOL_STR(regulator_bulk_get) },
	{ 0xa8f59416, __VMLINUX_SYMBOL_STR(gpio_direction_output) },
	{ 0x47229b5c, __VMLINUX_SYMBOL_STR(gpio_request) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xd4669fad, __VMLINUX_SYMBOL_STR(complete) },
	{ 0x328a05f1, __VMLINUX_SYMBOL_STR(strncpy) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xfe990052, __VMLINUX_SYMBOL_STR(gpio_free) },
	{ 0x24fc46b6, __VMLINUX_SYMBOL_STR(regulator_bulk_free) },
	{ 0x14c47d67, __VMLINUX_SYMBOL_STR(v4l2_ctrl_handler_free) },
	{ 0x838a9964, __VMLINUX_SYMBOL_STR(v4l2_device_unregister_subdev) },
	{ 0xf20dabd8, __VMLINUX_SYMBOL_STR(free_irq) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0x4920a692, __VMLINUX_SYMBOL_STR(regulator_bulk_enable) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xada38534, __VMLINUX_SYMBOL_STR(regulator_bulk_disable) },
	{ 0x432fd7f6, __VMLINUX_SYMBOL_STR(__gpio_set_value) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xd01dae48, __VMLINUX_SYMBOL_STR(i2c_master_recv) },
	{ 0x7cf9099, __VMLINUX_SYMBOL_STR(wait_for_completion_timeout) },
	{ 0xb54533f7, __VMLINUX_SYMBOL_STR(usecs_to_jiffies) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x1e9f1a37, __VMLINUX_SYMBOL_STR(i2c_master_send) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("i2c:si4713");

MODULE_INFO(srcversion, "6C6173EE1D320E7FF236D40");
