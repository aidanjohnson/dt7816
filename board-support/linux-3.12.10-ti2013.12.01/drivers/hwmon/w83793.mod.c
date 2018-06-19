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
	{ 0x20b2bb2d, __VMLINUX_SYMBOL_STR(param_array_ops) },
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x33ba5cd4, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0xda2478d0, __VMLINUX_SYMBOL_STR(param_ops_short) },
	{ 0x1f8f5fc1, __VMLINUX_SYMBOL_STR(no_llseek) },
	{ 0xa731ccf6, __VMLINUX_SYMBOL_STR(i2c_del_driver) },
	{ 0xe25a742c, __VMLINUX_SYMBOL_STR(i2c_register_driver) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x73572db2, __VMLINUX_SYMBOL_STR(misc_register) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x3517383e, __VMLINUX_SYMBOL_STR(register_reboot_notifier) },
	{ 0xe38ec180, __VMLINUX_SYMBOL_STR(hwmon_device_register) },
	{ 0xef1c781c, __VMLINUX_SYMBOL_STR(vid_which_vrm) },
	{ 0xfc27bfdd, __VMLINUX_SYMBOL_STR(device_create_file) },
	{ 0xfe076cd2, __VMLINUX_SYMBOL_STR(i2c_new_dummy) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xbc10dd97, __VMLINUX_SYMBOL_STR(__put_user_4) },
	{ 0x353e3fa5, __VMLINUX_SYMBOL_STR(__get_user_4) },
	{ 0x67c2fa54, __VMLINUX_SYMBOL_STR(__copy_to_user) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x2cbe5bf9, __VMLINUX_SYMBOL_STR(nonseekable_open) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0xe2deaa38, __VMLINUX_SYMBOL_STR(mutex_trylock) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0xeda50f97, __VMLINUX_SYMBOL_STR(dev_crit) },
	{ 0x19619cb5, __VMLINUX_SYMBOL_STR(i2c_unregister_device) },
	{ 0xc2290b94, __VMLINUX_SYMBOL_STR(device_remove_file) },
	{ 0xa7c6d1a5, __VMLINUX_SYMBOL_STR(hwmon_device_unregister) },
	{ 0xac1a55be, __VMLINUX_SYMBOL_STR(unregister_reboot_notifier) },
	{ 0xbf670952, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0x49ac0df0, __VMLINUX_SYMBOL_STR(misc_deregister) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x28118cb6, __VMLINUX_SYMBOL_STR(__get_user_1) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x11a13e31, __VMLINUX_SYMBOL_STR(_kstrtol) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x903c239, __VMLINUX_SYMBOL_STR(vid_from_reg) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xdd384ca3, __VMLINUX_SYMBOL_STR(i2c_smbus_read_byte_data) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x69d0f0ae, __VMLINUX_SYMBOL_STR(i2c_smbus_write_byte_data) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x996bdb64, __VMLINUX_SYMBOL_STR(_kstrtoul) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=hwmon-vid";

MODULE_ALIAS("i2c:w83793");
