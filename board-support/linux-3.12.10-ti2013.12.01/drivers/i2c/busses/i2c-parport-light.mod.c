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
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x35c39aa9, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0x59d8223a, __VMLINUX_SYMBOL_STR(ioport_resource) },
	{ 0x7781b4da, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0x9bce482f, __VMLINUX_SYMBOL_STR(__release_region) },
	{ 0xbadfd0e, __VMLINUX_SYMBOL_STR(platform_device_unregister) },
	{ 0xb3f38dbc, __VMLINUX_SYMBOL_STR(platform_device_put) },
	{ 0x4fb7d5a2, __VMLINUX_SYMBOL_STR(platform_device_add) },
	{ 0xd727a63c, __VMLINUX_SYMBOL_STR(platform_device_alloc) },
	{ 0xadf42bd5, __VMLINUX_SYMBOL_STR(__request_region) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xbf670952, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0xd5cd59cc, __VMLINUX_SYMBOL_STR(i2c_setup_smbus_alert) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x48e7d219, __VMLINUX_SYMBOL_STR(i2c_bit_add_bus) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x999a475f, __VMLINUX_SYMBOL_STR(i2c_del_adapter) },
	{ 0x19619cb5, __VMLINUX_SYMBOL_STR(i2c_unregister_device) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xac8f37b2, __VMLINUX_SYMBOL_STR(outer_cache) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=i2c-smbus";

