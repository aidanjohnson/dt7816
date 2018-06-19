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
	{ 0x35c39aa9, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0x7781b4da, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0xdb387113, __VMLINUX_SYMBOL_STR(sensor_hub_register_callback) },
	{ 0x51d12ba8, __VMLINUX_SYMBOL_STR(devm_rtc_device_register) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xcee2a5c9, __VMLINUX_SYMBOL_STR(sensor_hub_input_get_attribute_info) },
	{ 0xdff2aeb7, __VMLINUX_SYMBOL_STR(hid_sensor_parse_common_attributes) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x3d268c44, __VMLINUX_SYMBOL_STR(devm_kzalloc) },
	{ 0xd4669fad, __VMLINUX_SYMBOL_STR(complete) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0xcb466063, __VMLINUX_SYMBOL_STR(wait_for_completion_killable_timeout) },
	{ 0x96b29dc2, __VMLINUX_SYMBOL_STR(sensor_hub_input_attr_get_raw_value) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xde2ad086, __VMLINUX_SYMBOL_STR(sensor_hub_remove_callback) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=hid-sensor-hub,hid-sensor-iio-common";

MODULE_ALIAS("platform:HID-SENSOR-2000a0");
