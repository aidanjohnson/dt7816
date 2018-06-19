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
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0xa3afaa39, __VMLINUX_SYMBOL_STR(v4l2_ctrl_cluster) },
	{ 0x74562d0, __VMLINUX_SYMBOL_STR(gspca_suspend) },
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x43a53735, __VMLINUX_SYMBOL_STR(__alloc_workqueue_key) },
	{ 0x42598f0c, __VMLINUX_SYMBOL_STR(gspca_dev_probe) },
	{ 0xda26fb6e, __VMLINUX_SYMBOL_STR(gspca_resume) },
	{ 0x447fa5c0, __VMLINUX_SYMBOL_STR(v4l2_ctrl_g_ctrl) },
	{ 0xdac751f0, __VMLINUX_SYMBOL_STR(v4l2_ctrl_new_std) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x750c45c9, __VMLINUX_SYMBOL_STR(gspca_disconnect) },
	{ 0xb79a5aed, __VMLINUX_SYMBOL_STR(input_event) },
	{ 0xafdf6647, __VMLINUX_SYMBOL_STR(v4l2_ctrl_new_std_menu) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x6e96893d, __VMLINUX_SYMBOL_STR(v4l2_ctrl_s_ctrl) },
	{ 0xb223f9fb, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x1049b573, __VMLINUX_SYMBOL_STR(usb_control_msg) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x8c03d20c, __VMLINUX_SYMBOL_STR(destroy_workqueue) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0x9df055b, __VMLINUX_SYMBOL_STR(v4l2_ctrl_auto_cluster) },
	{ 0x9670af2c, __VMLINUX_SYMBOL_STR(gspca_debug) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x107fa771, __VMLINUX_SYMBOL_STR(gspca_frame_add) },
	{ 0xb3f1ab10, __VMLINUX_SYMBOL_STR(v4l2_ctrl_handler_init_class) },
	{ 0xa3e8bb7a, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=gspca_main";

MODULE_ALIAS("usb:v03F0p1B07d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v041Ep041Ed*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v041Ep4017d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v041Ep401Cd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v041Ep401Ed*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v041Ep401Fd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v041Ep4022d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v041Ep4029d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v041Ep4034d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v041Ep4035d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v041Ep4036d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v041Ep403Ad*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v041Ep4051d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v041Ep4053d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0458p7007d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0458p700Cd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0458p700Fd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0461p0A00d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v046Dp089Dd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v046Dp08A0d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v046Dp08A1d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v046Dp08A2d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v046Dp08A3d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v046Dp08A6d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v046Dp08A7d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v046Dp08A9d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v046Dp08AAd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v046Dp08ACd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v046Dp08ADd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v046Dp08AEd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v046Dp08AFd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v046Dp08B9d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v046Dp08D7d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v046Dp08D8d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v046Dp08D9d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v046Dp08DAd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v046Dp08DDd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0471p0325d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0471p0326d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0471p032Dd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0471p032Ed*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v055FpC005d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v055FpD003d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v055FpD004d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0698p2003d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0AC8p0301d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0AC8p0302d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0AC8p301Bd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0AC8p303Bd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0AC8p305Bd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0AC8p307Bd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10FDp0128d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10FDp804Dd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10FDp8050d*dc*dsc*dp*ic*isc*ip*in*");
