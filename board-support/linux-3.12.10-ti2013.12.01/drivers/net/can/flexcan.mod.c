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
	{ 0x5664efb, __VMLINUX_SYMBOL_STR(open_candev) },
	{ 0xd6b8e852, __VMLINUX_SYMBOL_STR(request_threaded_irq) },
	{ 0x2bf3d68f, __VMLINUX_SYMBOL_STR(napi_complete) },
	{ 0xfeecc65d, __VMLINUX_SYMBOL_STR(alloc_can_skb) },
	{ 0xafcc3435, __VMLINUX_SYMBOL_STR(netif_receive_skb) },
	{ 0x1c19c5e0, __VMLINUX_SYMBOL_STR(can_bus_off) },
	{ 0x68ff13bb, __VMLINUX_SYMBOL_STR(alloc_can_err_skb) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x496a2677, __VMLINUX_SYMBOL_STR(devm_can_led_init) },
	{ 0x71fbc0, __VMLINUX_SYMBOL_STR(register_candev) },
	{ 0x4ca4c9df, __VMLINUX_SYMBOL_STR(clk_enable) },
	{ 0x470fa426, __VMLINUX_SYMBOL_STR(clk_prepare) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0xeb499f86, __VMLINUX_SYMBOL_STR(netif_napi_add) },
	{ 0xb1ad5f39, __VMLINUX_SYMBOL_STR(devm_regulator_get) },
	{ 0x38f3cdba, __VMLINUX_SYMBOL_STR(alloc_candev) },
	{ 0x34bc3f3f, __VMLINUX_SYMBOL_STR(of_match_device) },
	{ 0x518c5f17, __VMLINUX_SYMBOL_STR(devm_ioremap_resource) },
	{ 0xfa6be079, __VMLINUX_SYMBOL_STR(platform_get_irq) },
	{ 0xbed18b93, __VMLINUX_SYMBOL_STR(platform_get_resource) },
	{ 0xd258217d, __VMLINUX_SYMBOL_STR(clk_get_rate) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xf433a513, __VMLINUX_SYMBOL_STR(devm_clk_get) },
	{ 0xdac11bae, __VMLINUX_SYMBOL_STR(of_property_read_u32_array) },
	{ 0x36026fb7, __VMLINUX_SYMBOL_STR(__netif_schedule) },
	{ 0x2a3aa678, __VMLINUX_SYMBOL_STR(_test_and_clear_bit) },
	{ 0xbcd24523, __VMLINUX_SYMBOL_STR(can_get_echo_skb) },
	{ 0x331bb128, __VMLINUX_SYMBOL_STR(__napi_schedule) },
	{ 0xca16dbe7, __VMLINUX_SYMBOL_STR(regulator_enable) },
	{ 0x78bc26d7, __VMLINUX_SYMBOL_STR(netdev_info) },
	{ 0xbc35e3cc, __VMLINUX_SYMBOL_STR(netdev_err) },
	{ 0x798c534c, __VMLINUX_SYMBOL_STR(can_led_event) },
	{ 0xcf31f774, __VMLINUX_SYMBOL_STR(close_candev) },
	{ 0x7c227088, __VMLINUX_SYMBOL_STR(clk_unprepare) },
	{ 0x4c2e1f24, __VMLINUX_SYMBOL_STR(clk_disable) },
	{ 0xf20dabd8, __VMLINUX_SYMBOL_STR(free_irq) },
	{ 0x1258d9d9, __VMLINUX_SYMBOL_STR(regulator_disable) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0xf61f0839, __VMLINUX_SYMBOL_STR(can_put_echo_skb) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0xb4446416, __VMLINUX_SYMBOL_STR(free_candev) },
	{ 0x90850bbd, __VMLINUX_SYMBOL_STR(unregister_candev) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xfba0a21b, __VMLINUX_SYMBOL_STR(netif_device_detach) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0xac8f37b2, __VMLINUX_SYMBOL_STR(outer_cache) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x57feb1f2, __VMLINUX_SYMBOL_STR(netif_device_attach) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=can-dev";

MODULE_ALIAS("platform:flexcan");
MODULE_ALIAS("of:N*T*Cfsl,imx6q-flexcan*");
MODULE_ALIAS("of:N*T*Cfsl,imx28-flexcan*");
MODULE_ALIAS("of:N*T*Cfsl,p1010-flexcan*");
