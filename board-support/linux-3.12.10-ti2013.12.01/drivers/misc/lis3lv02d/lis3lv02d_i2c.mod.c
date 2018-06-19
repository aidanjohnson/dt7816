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
	{ 0xa731ccf6, __VMLINUX_SYMBOL_STR(i2c_del_driver) },
	{ 0xe25a742c, __VMLINUX_SYMBOL_STR(i2c_register_driver) },
	{ 0xada38534, __VMLINUX_SYMBOL_STR(regulator_bulk_disable) },
	{ 0x5d19772, __VMLINUX_SYMBOL_STR(lis3lv02d_init_device) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0xc01b1a5d, __VMLINUX_SYMBOL_STR(regulator_bulk_get) },
	{ 0x72dafab, __VMLINUX_SYMBOL_STR(lis3lv02d_init_dt) },
	{ 0x34bc3f3f, __VMLINUX_SYMBOL_STR(of_match_device) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x12a38747, __VMLINUX_SYMBOL_STR(usleep_range) },
	{ 0x4920a692, __VMLINUX_SYMBOL_STR(regulator_bulk_enable) },
	{ 0x36b500e3, __VMLINUX_SYMBOL_STR(lis3_dev) },
	{ 0x24fc46b6, __VMLINUX_SYMBOL_STR(regulator_bulk_free) },
	{ 0x1df1dca2, __VMLINUX_SYMBOL_STR(lis3lv02d_remove_fs) },
	{ 0xe800b66c, __VMLINUX_SYMBOL_STR(lis3lv02d_joystick_disable) },
	{ 0xcb67c79a, __VMLINUX_SYMBOL_STR(lis3lv02d_poweroff) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xb436fff2, __VMLINUX_SYMBOL_STR(lis3lv02d_poweron) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x6f1f3829, __VMLINUX_SYMBOL_STR(i2c_smbus_read_i2c_block_data) },
	{ 0xdd384ca3, __VMLINUX_SYMBOL_STR(i2c_smbus_read_byte_data) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x69d0f0ae, __VMLINUX_SYMBOL_STR(i2c_smbus_write_byte_data) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=lis3lv02d";

MODULE_ALIAS("i2c:lis3lv02d");
MODULE_ALIAS("i2c:lis331dlh");
MODULE_ALIAS("of:N*T*Cst,lis3lv02d*");
