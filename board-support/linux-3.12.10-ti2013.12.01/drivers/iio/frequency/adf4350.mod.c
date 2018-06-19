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
	{ 0x1f05bf4a, __VMLINUX_SYMBOL_STR(driver_unregister) },
	{ 0xbdf61e00, __VMLINUX_SYMBOL_STR(spi_register_driver) },
	{ 0x13921363, __VMLINUX_SYMBOL_STR(clk_set_rate) },
	{ 0xb1a7e3f6, __VMLINUX_SYMBOL_STR(clk_round_rate) },
	{ 0x60ea2d6, __VMLINUX_SYMBOL_STR(kstrtoull) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xd8a93efc, __VMLINUX_SYMBOL_STR(iio_device_register) },
	{ 0x65d6d0f0, __VMLINUX_SYMBOL_STR(gpio_direction_input) },
	{ 0x8c987b84, __VMLINUX_SYMBOL_STR(devm_gpio_request) },
	{ 0x2a52919e, __VMLINUX_SYMBOL_STR(spi_get_device_id) },
	{ 0xca16dbe7, __VMLINUX_SYMBOL_STR(regulator_enable) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0xb1ad5f39, __VMLINUX_SYMBOL_STR(devm_regulator_get) },
	{ 0xb12e51ef, __VMLINUX_SYMBOL_STR(devm_iio_device_alloc) },
	{ 0x4ca4c9df, __VMLINUX_SYMBOL_STR(clk_enable) },
	{ 0x470fa426, __VMLINUX_SYMBOL_STR(clk_prepare) },
	{ 0xf433a513, __VMLINUX_SYMBOL_STR(devm_clk_get) },
	{ 0xbf670952, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0x43632d7d, __VMLINUX_SYMBOL_STR(of_find_property) },
	{ 0x3757c9b, __VMLINUX_SYMBOL_STR(of_get_named_gpio_flags) },
	{ 0xdac11bae, __VMLINUX_SYMBOL_STR(of_property_read_u32_array) },
	{ 0x328a05f1, __VMLINUX_SYMBOL_STR(strncpy) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x3d268c44, __VMLINUX_SYMBOL_STR(devm_kzalloc) },
	{ 0xea124bd1, __VMLINUX_SYMBOL_STR(gcd) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xd258217d, __VMLINUX_SYMBOL_STR(clk_get_rate) },
	{ 0x6c8d5ae8, __VMLINUX_SYMBOL_STR(__gpio_get_value) },
	{ 0x59e5070d, __VMLINUX_SYMBOL_STR(__do_div64) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x1258d9d9, __VMLINUX_SYMBOL_STR(regulator_disable) },
	{ 0x7c227088, __VMLINUX_SYMBOL_STR(clk_unprepare) },
	{ 0x4c2e1f24, __VMLINUX_SYMBOL_STR(clk_disable) },
	{ 0x17bcfee8, __VMLINUX_SYMBOL_STR(iio_device_unregister) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xc00cee86, __VMLINUX_SYMBOL_STR(spi_sync) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=industrialio";

