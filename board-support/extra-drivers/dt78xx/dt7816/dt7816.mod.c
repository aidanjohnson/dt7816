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

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xb5c97a0d, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x32ad8add, __VMLINUX_SYMBOL_STR(dt78xx_fpga_write) },
	{ 0x971377ac, __VMLINUX_SYMBOL_STR(dt78xx_fpga_rmw) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0xed20995b, __VMLINUX_SYMBOL_STR(file_to_dt78xx) },
	{ 0xfbc74f64, __VMLINUX_SYMBOL_STR(__copy_from_user) },
	{ 0x67c2fa54, __VMLINUX_SYMBOL_STR(__copy_to_user) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x9e5fd1e8, __VMLINUX_SYMBOL_STR(dt78xx_potentiometer_cal2wiper) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0xbec25473, __VMLINUX_SYMBOL_STR(of_parse_phandle) },
	{ 0x3d268c44, __VMLINUX_SYMBOL_STR(devm_kzalloc) },
	{ 0xe02fdd1c, __VMLINUX_SYMBOL_STR(dt78xx_aio) },
	{ 0x20000329, __VMLINUX_SYMBOL_STR(simple_strtoul) },
	{ 0xa93736b7, __VMLINUX_SYMBOL_STR(dt78xx_potentiometer_wiper_read) },
	{ 0xa8a8110c, __VMLINUX_SYMBOL_STR(kernel_neon_end) },
	{ 0x752a8f5f, __VMLINUX_SYMBOL_STR(dt78xx_potentiometer_cal_write) },
	{ 0xc1841ad0, __VMLINUX_SYMBOL_STR(dt78xx_potentiometer_init) },
	{ 0x64992b72, __VMLINUX_SYMBOL_STR(dt78xx_edma_start) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x7781b4da, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0x4ed3a8f, __VMLINUX_SYMBOL_STR(dt78xx_edma_stop) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x73572db2, __VMLINUX_SYMBOL_STR(misc_register) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x97e7d22e, __VMLINUX_SYMBOL_STR(dt78xx_fopen) },
	{ 0xdbe5356b, __VMLINUX_SYMBOL_STR(dt78xx_fclose) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x29ff0720, __VMLINUX_SYMBOL_STR(dt78xx_fasync) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xa7f7de43, __VMLINUX_SYMBOL_STR(dt78xx_free) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x1e6d26a8, __VMLINUX_SYMBOL_STR(strstr) },
	{ 0x11137789, __VMLINUX_SYMBOL_STR(sysfs_merge_group) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0x876ec3cf, __VMLINUX_SYMBOL_STR(devm_kfree) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0xedd3426d, __VMLINUX_SYMBOL_STR(dev_driver_string) },
	{ 0x260cf8f8, __VMLINUX_SYMBOL_STR(of_get_property) },
	{ 0xf9e73082, __VMLINUX_SYMBOL_STR(scnprintf) },
	{ 0x5ba512ea, __VMLINUX_SYMBOL_STR(dt78xx_potentiometer_wiper_write) },
	{ 0xb9acd3d9, __VMLINUX_SYMBOL_STR(__put_user_2) },
	{ 0x95dbe078, __VMLINUX_SYMBOL_STR(__get_user_2) },
	{ 0x8fd180e7, __VMLINUX_SYMBOL_STR(kernel_neon_begin) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x8a6dc521, __VMLINUX_SYMBOL_STR(dt78xx_fpga_read) },
	{ 0x35c39aa9, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0x2c290059, __VMLINUX_SYMBOL_STR(dt78xx_potentiometer_cal_read) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x6248c33e, __VMLINUX_SYMBOL_STR(dt78xx_init) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=dt78xx";

MODULE_ALIAS("of:N*T*Cdt7816*");

MODULE_INFO(srcversion, "1CEEC625FC099E89F91D4A7");
