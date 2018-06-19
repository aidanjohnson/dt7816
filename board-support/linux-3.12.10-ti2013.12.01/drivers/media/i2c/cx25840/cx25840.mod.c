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
	{ 0x1e9f1a37, __VMLINUX_SYMBOL_STR(i2c_master_send) },
	{ 0xff178f6, __VMLINUX_SYMBOL_STR(__aeabi_idivmod) },
	{ 0x13d0adf7, __VMLINUX_SYMBOL_STR(__kfifo_out) },
	{ 0xa3afaa39, __VMLINUX_SYMBOL_STR(v4l2_ctrl_cluster) },
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xc068440e, __VMLINUX_SYMBOL_STR(__kfifo_alloc) },
	{ 0x43a53735, __VMLINUX_SYMBOL_STR(__alloc_workqueue_key) },
	{ 0xa731ccf6, __VMLINUX_SYMBOL_STR(i2c_del_driver) },
	{ 0x71ab7ace, __VMLINUX_SYMBOL_STR(v4l2_subdev_querymenu) },
	{ 0x3d268c44, __VMLINUX_SYMBOL_STR(devm_kzalloc) },
	{ 0xc8b57c27, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0x8169d80e, __VMLINUX_SYMBOL_STR(i2c_transfer) },
	{ 0x14c47d67, __VMLINUX_SYMBOL_STR(v4l2_ctrl_handler_free) },
	{ 0xdac751f0, __VMLINUX_SYMBOL_STR(v4l2_ctrl_new_std) },
	{ 0x7717d7c4, __VMLINUX_SYMBOL_STR(v4l2_subdev_g_ctrl) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x3200659d, __VMLINUX_SYMBOL_STR(v4l2_subdev_g_ext_ctrls) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x5d41c87c, __VMLINUX_SYMBOL_STR(param_ops_charp) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x8c03d20c, __VMLINUX_SYMBOL_STR(destroy_workqueue) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0x838a9964, __VMLINUX_SYMBOL_STR(v4l2_device_unregister_subdev) },
	{ 0xe25a742c, __VMLINUX_SYMBOL_STR(i2c_register_driver) },
	{ 0xd466e51c, __VMLINUX_SYMBOL_STR(v4l2_subdev_s_ctrl) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0x70806c73, __VMLINUX_SYMBOL_STR(v4l2_ctrl_handler_setup) },
	{ 0xb6ce7eb5, __VMLINUX_SYMBOL_STR(v4l2_ctrl_handler_log_status) },
	{ 0x5b95951d, __VMLINUX_SYMBOL_STR(v4l2_subdev_try_ext_ctrls) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0xdb760f52, __VMLINUX_SYMBOL_STR(__kfifo_free) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x499cb58c, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0xb3f1ab10, __VMLINUX_SYMBOL_STR(v4l2_ctrl_handler_init_class) },
	{ 0x155a3d9f, __VMLINUX_SYMBOL_STR(request_firmware) },
	{ 0x1cfb04fa, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xf23fcb99, __VMLINUX_SYMBOL_STR(__kfifo_in) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x68b81a89, __VMLINUX_SYMBOL_STR(v4l2_subdev_s_ext_ctrls) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x8b5187c3, __VMLINUX_SYMBOL_STR(release_firmware) },
	{ 0x9c59680f, __VMLINUX_SYMBOL_STR(v4l2_subdev_queryctrl) },
	{ 0x76973130, __VMLINUX_SYMBOL_STR(v4l2_i2c_subdev_init) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("i2c:cx25840");
