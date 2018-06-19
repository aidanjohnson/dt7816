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
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0xc34ad504, __VMLINUX_SYMBOL_STR(__pm_runtime_idle) },
	{ 0x321c9d5e, __VMLINUX_SYMBOL_STR(__pm_runtime_disable) },
	{ 0x7cbf151c, __VMLINUX_SYMBOL_STR(input_unregister_polled_device) },
	{ 0x54e3cc3b, __VMLINUX_SYMBOL_STR(param_get_int) },
	{ 0x67c2fa54, __VMLINUX_SYMBOL_STR(__copy_to_user) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x6954dff2, __VMLINUX_SYMBOL_STR(pm_runtime_barrier) },
	{ 0x4c86184b, __VMLINUX_SYMBOL_STR(remove_wait_queue) },
	{ 0x1f8f5fc1, __VMLINUX_SYMBOL_STR(no_llseek) },
	{ 0xd28c80f4, __VMLINUX_SYMBOL_STR(input_register_polled_device) },
	{ 0xdac11bae, __VMLINUX_SYMBOL_STR(of_property_read_u32_array) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xb2468ee6, __VMLINUX_SYMBOL_STR(__pm_runtime_resume) },
	{ 0x74635e08, __VMLINUX_SYMBOL_STR(platform_device_register_full) },
	{ 0x853bf7c1, __VMLINUX_SYMBOL_STR(param_set_int) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xb0cab2d5, __VMLINUX_SYMBOL_STR(sysfs_remove_group) },
	{ 0xcdc2d251, __VMLINUX_SYMBOL_STR(input_set_abs_params) },
	{ 0xb79a5aed, __VMLINUX_SYMBOL_STR(input_event) },
	{ 0xffd5a395, __VMLINUX_SYMBOL_STR(default_wake_function) },
	{ 0x73572db2, __VMLINUX_SYMBOL_STR(misc_register) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xce917ae3, __VMLINUX_SYMBOL_STR(sysfs_create_group) },
	{ 0x78d318c0, __VMLINUX_SYMBOL_STR(fasync_helper) },
	{ 0xfc88fbae, __VMLINUX_SYMBOL_STR(input_set_capability) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xbadfd0e, __VMLINUX_SYMBOL_STR(platform_device_unregister) },
	{ 0xd6b8e852, __VMLINUX_SYMBOL_STR(request_threaded_irq) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0xc2e2733e, __VMLINUX_SYMBOL_STR(input_free_polled_device) },
	{ 0x1bf9f43d, __VMLINUX_SYMBOL_STR(pm_runtime_enable) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0xa76f5f55, __VMLINUX_SYMBOL_STR(pm_schedule_suspend) },
	{ 0x996bdb64, __VMLINUX_SYMBOL_STR(_kstrtoul) },
	{ 0xc53e5804, __VMLINUX_SYMBOL_STR(__pm_runtime_set_status) },
	{ 0xad9c3b30, __VMLINUX_SYMBOL_STR(input_allocate_polled_device) },
	{ 0x260cf8f8, __VMLINUX_SYMBOL_STR(of_get_property) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x1e047854, __VMLINUX_SYMBOL_STR(warn_slowpath_fmt) },
	{ 0xc7bcbc8d, __VMLINUX_SYMBOL_STR(add_wait_queue) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x20b2bb2d, __VMLINUX_SYMBOL_STR(param_array_ops) },
	{ 0x74c134b9, __VMLINUX_SYMBOL_STR(__sw_hweight32) },
	{ 0x6569bb8d, __VMLINUX_SYMBOL_STR(kill_fasync) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x49ac0df0, __VMLINUX_SYMBOL_STR(misc_deregister) },
	{ 0xf20dabd8, __VMLINUX_SYMBOL_STR(free_irq) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

