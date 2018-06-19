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
	{ 0xa08005d1, __VMLINUX_SYMBOL_STR(lp55xx_is_extclk_used) },
	{ 0x996bdb64, __VMLINUX_SYMBOL_STR(_kstrtoul) },
	{ 0x9c14f02f, __VMLINUX_SYMBOL_STR(lp55xx_register_sysfs) },
	{ 0x4311b126, __VMLINUX_SYMBOL_STR(lp55xx_register_leds) },
	{ 0xe049c68a, __VMLINUX_SYMBOL_STR(lp55xx_init_device) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x3d268c44, __VMLINUX_SYMBOL_STR(devm_kzalloc) },
	{ 0xcd004531, __VMLINUX_SYMBOL_STR(lp55xx_of_populate_pdata) },
	{ 0x20c55ae0, __VMLINUX_SYMBOL_STR(sscanf) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x9212963, __VMLINUX_SYMBOL_STR(lp55xx_read) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x222e7ce2, __VMLINUX_SYMBOL_STR(sysfs_streq) },
	{ 0x572cdd0d, __VMLINUX_SYMBOL_STR(lp55xx_update_bits) },
	{ 0xa240bd2e, __VMLINUX_SYMBOL_STR(lp55xx_deinit_device) },
	{ 0x51b014d2, __VMLINUX_SYMBOL_STR(lp55xx_unregister_leds) },
	{ 0xae59d94e, __VMLINUX_SYMBOL_STR(lp55xx_unregister_sysfs) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x12a38747, __VMLINUX_SYMBOL_STR(usleep_range) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x26d9352d, __VMLINUX_SYMBOL_STR(lp55xx_write) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=leds-lp55xx-common";

MODULE_ALIAS("of:N*T*Cti,lp5562*");
MODULE_ALIAS("i2c:lp5562");
