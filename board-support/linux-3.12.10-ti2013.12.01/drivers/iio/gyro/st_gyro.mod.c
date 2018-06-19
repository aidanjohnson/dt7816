#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.arch = MODULE_ARCH_INIT,
};

MODULE_INFO(intree, "Y");

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xb5c97a0d, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x5b9b2249, __VMLINUX_SYMBOL_STR(iio_triggered_buffer_cleanup) },
	{ 0x2aec1705, __VMLINUX_SYMBOL_STR(st_sensors_set_dataready_irq) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xdf76bbeb, __VMLINUX_SYMBOL_STR(iio_pollfunc_store_time) },
	{ 0xcddbabf, __VMLINUX_SYMBOL_STR(st_sensors_set_enable) },
	{ 0xec312177, __VMLINUX_SYMBOL_STR(st_sensors_sysfs_set_sampling_frequency) },
	{ 0x74d7047, __VMLINUX_SYMBOL_STR(st_sensors_trigger_handler) },
	{ 0x3c944738, __VMLINUX_SYMBOL_STR(st_sensors_deallocate_trigger) },
	{ 0xea4e9232, __VMLINUX_SYMBOL_STR(st_sensors_sysfs_sampling_frequency_avail) },
	{ 0xd8a93efc, __VMLINUX_SYMBOL_STR(iio_device_register) },
	{ 0xdf435b6f, __VMLINUX_SYMBOL_STR(st_sensors_allocate_trigger) },
	{ 0x17bcfee8, __VMLINUX_SYMBOL_STR(iio_device_unregister) },
	{ 0x2d28d223, __VMLINUX_SYMBOL_STR(st_sensors_set_fullscale_by_gain) },
	{ 0x1dbf76f1, __VMLINUX_SYMBOL_STR(st_sensors_check_device_support) },
	{ 0x8aa1d8ed, __VMLINUX_SYMBOL_STR(iio_triggered_buffer_postenable) },
	{ 0xec68915d, __VMLINUX_SYMBOL_STR(st_sensors_init_sensor) },
	{ 0x44412b98, __VMLINUX_SYMBOL_STR(iio_triggered_buffer_predisable) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x8097418, __VMLINUX_SYMBOL_STR(st_sensors_sysfs_get_sampling_frequency) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x24a53369, __VMLINUX_SYMBOL_STR(st_sensors_sysfs_scale_avail) },
	{ 0xd4062f80, __VMLINUX_SYMBOL_STR(st_sensors_set_axis_enable) },
	{ 0x379cba9f, __VMLINUX_SYMBOL_STR(st_sensors_read_info_raw) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x440813f2, __VMLINUX_SYMBOL_STR(iio_triggered_buffer_setup) },
	{ 0xb4ffe258, __VMLINUX_SYMBOL_STR(iio_sw_buffer_preenable) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=industrialio-triggered-buffer,st_sensors,industrialio";

