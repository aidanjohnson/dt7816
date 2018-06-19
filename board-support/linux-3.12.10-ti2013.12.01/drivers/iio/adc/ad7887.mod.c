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
	{ 0x44412b98, __VMLINUX_SYMBOL_STR(iio_triggered_buffer_predisable) },
	{ 0x8aa1d8ed, __VMLINUX_SYMBOL_STR(iio_triggered_buffer_postenable) },
	{ 0x1f05bf4a, __VMLINUX_SYMBOL_STR(driver_unregister) },
	{ 0xbdf61e00, __VMLINUX_SYMBOL_STR(spi_register_driver) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x698be398, __VMLINUX_SYMBOL_STR(regulator_get_voltage) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0xb4ffe258, __VMLINUX_SYMBOL_STR(iio_sw_buffer_preenable) },
	{ 0x14a0818, __VMLINUX_SYMBOL_STR(iio_trigger_notify_done) },
	{ 0xcd55807b, __VMLINUX_SYMBOL_STR(iio_push_to_buffers) },
	{ 0x46608fa0, __VMLINUX_SYMBOL_STR(getnstimeofday) },
	{ 0xdf76bbeb, __VMLINUX_SYMBOL_STR(iio_pollfunc_store_time) },
	{ 0xd8a93efc, __VMLINUX_SYMBOL_STR(iio_device_register) },
	{ 0x440813f2, __VMLINUX_SYMBOL_STR(iio_triggered_buffer_setup) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xca16dbe7, __VMLINUX_SYMBOL_STR(regulator_enable) },
	{ 0xb1ad5f39, __VMLINUX_SYMBOL_STR(devm_regulator_get) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x2a52919e, __VMLINUX_SYMBOL_STR(spi_get_device_id) },
	{ 0xb12e51ef, __VMLINUX_SYMBOL_STR(devm_iio_device_alloc) },
	{ 0xc00cee86, __VMLINUX_SYMBOL_STR(spi_sync) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x1258d9d9, __VMLINUX_SYMBOL_STR(regulator_disable) },
	{ 0x5b9b2249, __VMLINUX_SYMBOL_STR(iio_triggered_buffer_cleanup) },
	{ 0x17bcfee8, __VMLINUX_SYMBOL_STR(iio_device_unregister) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=industrialio,industrialio-triggered-buffer";

MODULE_ALIAS("spi:ad7887");
