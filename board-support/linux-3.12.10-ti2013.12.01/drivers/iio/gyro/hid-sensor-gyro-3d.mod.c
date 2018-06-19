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
	{ 0xdf76bbeb, __VMLINUX_SYMBOL_STR(iio_pollfunc_store_time) },
	{ 0xdb387113, __VMLINUX_SYMBOL_STR(sensor_hub_register_callback) },
	{ 0xd8a93efc, __VMLINUX_SYMBOL_STR(iio_device_register) },
	{ 0x746f0bb9, __VMLINUX_SYMBOL_STR(hid_sensor_setup_trigger) },
	{ 0x440813f2, __VMLINUX_SYMBOL_STR(iio_triggered_buffer_setup) },
	{ 0xcee2a5c9, __VMLINUX_SYMBOL_STR(sensor_hub_input_get_attribute_info) },
	{ 0xe2fae716, __VMLINUX_SYMBOL_STR(kmemdup) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xdff2aeb7, __VMLINUX_SYMBOL_STR(hid_sensor_parse_common_attributes) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0xb12e51ef, __VMLINUX_SYMBOL_STR(devm_iio_device_alloc) },
	{ 0x43eeb330, __VMLINUX_SYMBOL_STR(hid_sensor_write_raw_hyst_value) },
	{ 0xd55c6369, __VMLINUX_SYMBOL_STR(hid_sensor_write_samp_freq_value) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xcd55807b, __VMLINUX_SYMBOL_STR(iio_push_to_buffers) },
	{ 0xd7c63a2f, __VMLINUX_SYMBOL_STR(hid_sensor_read_raw_hyst_value) },
	{ 0xc3622ac6, __VMLINUX_SYMBOL_STR(hid_sensor_read_samp_freq_value) },
	{ 0x96b29dc2, __VMLINUX_SYMBOL_STR(sensor_hub_input_attr_get_raw_value) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x5b9b2249, __VMLINUX_SYMBOL_STR(iio_triggered_buffer_cleanup) },
	{ 0x84f78755, __VMLINUX_SYMBOL_STR(hid_sensor_remove_trigger) },
	{ 0x17bcfee8, __VMLINUX_SYMBOL_STR(iio_device_unregister) },
	{ 0xde2ad086, __VMLINUX_SYMBOL_STR(sensor_hub_remove_callback) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=industrialio,hid-sensor-hub,hid-sensor-trigger,industrialio-triggered-buffer,hid-sensor-iio-common";

MODULE_ALIAS("platform:HID-SENSOR-200076");
