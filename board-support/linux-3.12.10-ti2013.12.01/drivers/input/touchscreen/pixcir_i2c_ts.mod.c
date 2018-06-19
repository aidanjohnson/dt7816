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
	{ 0xaa58a0ae, __VMLINUX_SYMBOL_STR(input_register_device) },
	{ 0xa8e391d9, __VMLINUX_SYMBOL_STR(devm_request_threaded_irq) },
	{ 0xe46cb53f, __VMLINUX_SYMBOL_STR(devm_gpio_request_one) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0xba1e33bf, __VMLINUX_SYMBOL_STR(input_mt_init_slots) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0xcdc2d251, __VMLINUX_SYMBOL_STR(input_set_abs_params) },
	{ 0x7419bd2c, __VMLINUX_SYMBOL_STR(devm_input_allocate_device) },
	{ 0xdac11bae, __VMLINUX_SYMBOL_STR(of_property_read_u32_array) },
	{ 0x3757c9b, __VMLINUX_SYMBOL_STR(of_get_named_gpio_flags) },
	{ 0x3d268c44, __VMLINUX_SYMBOL_STR(devm_kzalloc) },
	{ 0x34bc3f3f, __VMLINUX_SYMBOL_STR(of_match_device) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xce2840e7, __VMLINUX_SYMBOL_STR(irq_set_irq_wake) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xfcec0987, __VMLINUX_SYMBOL_STR(enable_irq) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x3ce4ca6f, __VMLINUX_SYMBOL_STR(disable_irq) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x12a38747, __VMLINUX_SYMBOL_STR(usleep_range) },
	{ 0x6c8d5ae8, __VMLINUX_SYMBOL_STR(__gpio_get_value) },
	{ 0x44dc9602, __VMLINUX_SYMBOL_STR(input_mt_sync_frame) },
	{ 0xcfc59fe6, __VMLINUX_SYMBOL_STR(input_mt_report_slot_state) },
	{ 0xb79a5aed, __VMLINUX_SYMBOL_STR(input_event) },
	{ 0xb297e0bc, __VMLINUX_SYMBOL_STR(input_mt_get_slot_by_key) },
	{ 0xd01dae48, __VMLINUX_SYMBOL_STR(i2c_master_recv) },
	{ 0x1e9f1a37, __VMLINUX_SYMBOL_STR(i2c_master_send) },
	{ 0xac8f37b2, __VMLINUX_SYMBOL_STR(outer_cache) },
	{ 0x7ee11bc1, __VMLINUX_SYMBOL_STR(device_init_wakeup) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x69d0f0ae, __VMLINUX_SYMBOL_STR(i2c_smbus_write_byte_data) },
	{ 0xdd384ca3, __VMLINUX_SYMBOL_STR(i2c_smbus_read_byte_data) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("of:N*T*Cpixcir,pixcir_ts*");
MODULE_ALIAS("of:N*T*Cpixcir,pixcir_tangoc*");
MODULE_ALIAS("i2c:pixcir_ts");
MODULE_ALIAS("i2c:pixcir_tangoc");
