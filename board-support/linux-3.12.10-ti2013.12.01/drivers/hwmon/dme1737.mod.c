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
	{ 0xafad493b, __VMLINUX_SYMBOL_STR(param_ops_ushort) },
	{ 0x33ba5cd4, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0xbadfd0e, __VMLINUX_SYMBOL_STR(platform_device_unregister) },
	{ 0xa731ccf6, __VMLINUX_SYMBOL_STR(i2c_del_driver) },
	{ 0x35c39aa9, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0xb3f38dbc, __VMLINUX_SYMBOL_STR(platform_device_put) },
	{ 0x4fb7d5a2, __VMLINUX_SYMBOL_STR(platform_device_add) },
	{ 0xac4a3fbd, __VMLINUX_SYMBOL_STR(platform_device_add_resources) },
	{ 0xd727a63c, __VMLINUX_SYMBOL_STR(platform_device_alloc) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x7781b4da, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0xe25a742c, __VMLINUX_SYMBOL_STR(i2c_register_driver) },
	{ 0x59d8223a, __VMLINUX_SYMBOL_STR(ioport_resource) },
	{ 0x6a164249, __VMLINUX_SYMBOL_STR(__devm_request_region) },
	{ 0xbed18b93, __VMLINUX_SYMBOL_STR(platform_get_resource) },
	{ 0xe38ec180, __VMLINUX_SYMBOL_STR(hwmon_device_register) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x3d268c44, __VMLINUX_SYMBOL_STR(devm_kzalloc) },
	{ 0x685d7756, __VMLINUX_SYMBOL_STR(sysfs_create_file) },
	{ 0xce917ae3, __VMLINUX_SYMBOL_STR(sysfs_create_group) },
	{ 0x8c40b2a9, __VMLINUX_SYMBOL_STR(sysfs_chmod_file) },
	{ 0xef1c781c, __VMLINUX_SYMBOL_STR(vid_which_vrm) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x903c239, __VMLINUX_SYMBOL_STR(vid_from_reg) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0x69d0f0ae, __VMLINUX_SYMBOL_STR(i2c_smbus_write_byte_data) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xbf670952, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0x11a13e31, __VMLINUX_SYMBOL_STR(_kstrtol) },
	{ 0xa7c6d1a5, __VMLINUX_SYMBOL_STR(hwmon_device_unregister) },
	{ 0xeb6bf215, __VMLINUX_SYMBOL_STR(sysfs_remove_file) },
	{ 0xb0cab2d5, __VMLINUX_SYMBOL_STR(sysfs_remove_group) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0xdd384ca3, __VMLINUX_SYMBOL_STR(i2c_smbus_read_byte_data) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xac8f37b2, __VMLINUX_SYMBOL_STR(outer_cache) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=hwmon-vid";

MODULE_ALIAS("i2c:dme1737");
MODULE_ALIAS("i2c:sch5027");
