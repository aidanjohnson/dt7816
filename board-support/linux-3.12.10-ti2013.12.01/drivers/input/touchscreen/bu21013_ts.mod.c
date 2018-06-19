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
	{ 0xc8b57c27, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0x74c134b9, __VMLINUX_SYMBOL_STR(__sw_hweight32) },
	{ 0xd62c833f, __VMLINUX_SYMBOL_STR(schedule_timeout) },
	{ 0x1cfb04fa, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x499cb58c, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x3bd1b1f6, __VMLINUX_SYMBOL_STR(msecs_to_jiffies) },
	{ 0x6c8d5ae8, __VMLINUX_SYMBOL_STR(__gpio_get_value) },
	{ 0xb79a5aed, __VMLINUX_SYMBOL_STR(input_event) },
	{ 0x6f1f3829, __VMLINUX_SYMBOL_STR(i2c_smbus_read_i2c_block_data) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x55e25a41, __VMLINUX_SYMBOL_STR(input_free_device) },
	{ 0xaa58a0ae, __VMLINUX_SYMBOL_STR(input_register_device) },
	{ 0xd6b8e852, __VMLINUX_SYMBOL_STR(request_threaded_irq) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0xcdc2d251, __VMLINUX_SYMBOL_STR(input_set_abs_params) },
	{ 0x403f9529, __VMLINUX_SYMBOL_STR(gpio_request_one) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xeaec5994, __VMLINUX_SYMBOL_STR(regulator_get) },
	{ 0x11f447ce, __VMLINUX_SYMBOL_STR(__gpio_to_irq) },
	{ 0x26a6901f, __VMLINUX_SYMBOL_STR(input_allocate_device) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x3757c9b, __VMLINUX_SYMBOL_STR(of_get_named_gpio_flags) },
	{ 0xdac11bae, __VMLINUX_SYMBOL_STR(of_property_read_u32_array) },
	{ 0x43632d7d, __VMLINUX_SYMBOL_STR(of_find_property) },
	{ 0x3d268c44, __VMLINUX_SYMBOL_STR(devm_kzalloc) },
	{ 0x7ee11bc1, __VMLINUX_SYMBOL_STR(device_init_wakeup) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xd85ac634, __VMLINUX_SYMBOL_STR(regulator_put) },
	{ 0x657c72c4, __VMLINUX_SYMBOL_STR(input_unregister_device) },
	{ 0xfe990052, __VMLINUX_SYMBOL_STR(gpio_free) },
	{ 0x432fd7f6, __VMLINUX_SYMBOL_STR(__gpio_set_value) },
	{ 0xbf670952, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0xa8f59416, __VMLINUX_SYMBOL_STR(gpio_direction_output) },
	{ 0xf20dabd8, __VMLINUX_SYMBOL_STR(free_irq) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x1258d9d9, __VMLINUX_SYMBOL_STR(regulator_disable) },
	{ 0x3ce4ca6f, __VMLINUX_SYMBOL_STR(disable_irq) },
	{ 0xfcec0987, __VMLINUX_SYMBOL_STR(enable_irq) },
	{ 0xce2840e7, __VMLINUX_SYMBOL_STR(irq_set_irq_wake) },
	{ 0xca16dbe7, __VMLINUX_SYMBOL_STR(regulator_enable) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x69d0f0ae, __VMLINUX_SYMBOL_STR(i2c_smbus_write_byte_data) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("i2c:bu21013_tp");
