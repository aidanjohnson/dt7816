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
	{ 0x78bc26d7, __VMLINUX_SYMBOL_STR(netdev_info) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0xc34ad504, __VMLINUX_SYMBOL_STR(__pm_runtime_idle) },
	{ 0x71fbc0, __VMLINUX_SYMBOL_STR(register_candev) },
	{ 0x321c9d5e, __VMLINUX_SYMBOL_STR(__pm_runtime_disable) },
	{ 0x68ff13bb, __VMLINUX_SYMBOL_STR(alloc_can_err_skb) },
	{ 0x2bf3d68f, __VMLINUX_SYMBOL_STR(napi_complete) },
	{ 0x2a3aa678, __VMLINUX_SYMBOL_STR(_test_and_clear_bit) },
	{ 0xb2468ee6, __VMLINUX_SYMBOL_STR(__pm_runtime_resume) },
	{ 0x38f3cdba, __VMLINUX_SYMBOL_STR(alloc_candev) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x1c19c5e0, __VMLINUX_SYMBOL_STR(can_bus_off) },
	{ 0xcf31f774, __VMLINUX_SYMBOL_STR(close_candev) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xafcc3435, __VMLINUX_SYMBOL_STR(netif_receive_skb) },
	{ 0x798c534c, __VMLINUX_SYMBOL_STR(can_led_event) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xeb499f86, __VMLINUX_SYMBOL_STR(netif_napi_add) },
	{ 0xd6b8e852, __VMLINUX_SYMBOL_STR(request_threaded_irq) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0xb4446416, __VMLINUX_SYMBOL_STR(free_candev) },
	{ 0x90850bbd, __VMLINUX_SYMBOL_STR(unregister_candev) },
	{ 0xfeecc65d, __VMLINUX_SYMBOL_STR(alloc_can_skb) },
	{ 0x1bf9f43d, __VMLINUX_SYMBOL_STR(pm_runtime_enable) },
	{ 0x331bb128, __VMLINUX_SYMBOL_STR(__napi_schedule) },
	{ 0x3bd1b1f6, __VMLINUX_SYMBOL_STR(msecs_to_jiffies) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0xbc35e3cc, __VMLINUX_SYMBOL_STR(netdev_err) },
	{ 0x5664efb, __VMLINUX_SYMBOL_STR(open_candev) },
	{ 0x496a2677, __VMLINUX_SYMBOL_STR(devm_can_led_init) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xbcd24523, __VMLINUX_SYMBOL_STR(can_get_echo_skb) },
	{ 0x36026fb7, __VMLINUX_SYMBOL_STR(__netif_schedule) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0xf61f0839, __VMLINUX_SYMBOL_STR(can_put_echo_skb) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0xf20dabd8, __VMLINUX_SYMBOL_STR(free_irq) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=can-dev";

