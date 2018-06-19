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
	{ 0xd4c463a9, __VMLINUX_SYMBOL_STR(iio_read_const_attr) },
	{ 0x2f088f2e, __VMLINUX_SYMBOL_STR(iio_enum_available_read) },
	{ 0x4862ff8a, __VMLINUX_SYMBOL_STR(iio_enum_write) },
	{ 0x441347fd, __VMLINUX_SYMBOL_STR(iio_enum_read) },
	{ 0xa731ccf6, __VMLINUX_SYMBOL_STR(i2c_del_driver) },
	{ 0xe25a742c, __VMLINUX_SYMBOL_STR(i2c_register_driver) },
	{ 0x2d6bcdcb, __VMLINUX_SYMBOL_STR(iio_trigger_generic_data_rdy_poll) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0xd8a93efc, __VMLINUX_SYMBOL_STR(iio_device_register) },
	{ 0x440813f2, __VMLINUX_SYMBOL_STR(iio_triggered_buffer_setup) },
	{ 0xf97a88ca, __VMLINUX_SYMBOL_STR(iio_trigger_register) },
	{ 0xa8e391d9, __VMLINUX_SYMBOL_STR(devm_request_threaded_irq) },
	{ 0xfba080e4, __VMLINUX_SYMBOL_STR(iio_trigger_alloc) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0xb12e51ef, __VMLINUX_SYMBOL_STR(devm_iio_device_alloc) },
	{ 0x594424c7, __VMLINUX_SYMBOL_STR(iio_trigger_free) },
	{ 0x3c454965, __VMLINUX_SYMBOL_STR(iio_trigger_unregister) },
	{ 0x5b9b2249, __VMLINUX_SYMBOL_STR(iio_triggered_buffer_cleanup) },
	{ 0x17bcfee8, __VMLINUX_SYMBOL_STR(iio_device_unregister) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x14a0818, __VMLINUX_SYMBOL_STR(iio_trigger_notify_done) },
	{ 0xcd55807b, __VMLINUX_SYMBOL_STR(iio_push_to_buffers) },
	{ 0xd3f57a2, __VMLINUX_SYMBOL_STR(_find_next_bit_le) },
	{ 0x6d662533, __VMLINUX_SYMBOL_STR(_find_first_bit_le) },
	{ 0x46608fa0, __VMLINUX_SYMBOL_STR(getnstimeofday) },
	{ 0x50a418b, __VMLINUX_SYMBOL_STR(i2c_smbus_read_word_data) },
	{ 0x3d268c44, __VMLINUX_SYMBOL_STR(devm_kzalloc) },
	{ 0x876ec3cf, __VMLINUX_SYMBOL_STR(devm_kfree) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x69d0f0ae, __VMLINUX_SYMBOL_STR(i2c_smbus_write_byte_data) },
	{ 0xdd384ca3, __VMLINUX_SYMBOL_STR(i2c_smbus_read_byte_data) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=industrialio,industrialio-triggered-buffer";

MODULE_ALIAS("i2c:bma180");
