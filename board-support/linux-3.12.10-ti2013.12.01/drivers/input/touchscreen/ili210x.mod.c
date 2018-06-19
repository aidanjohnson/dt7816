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
	{ 0x3bd1b1f6, __VMLINUX_SYMBOL_STR(msecs_to_jiffies) },
	{ 0x266e0d, __VMLINUX_SYMBOL_STR(input_mt_report_pointer_emulation) },
	{ 0xcfc59fe6, __VMLINUX_SYMBOL_STR(input_mt_report_slot_state) },
	{ 0xb79a5aed, __VMLINUX_SYMBOL_STR(input_event) },
	{ 0x6b06fdce, __VMLINUX_SYMBOL_STR(delayed_work_timer_fn) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x55e25a41, __VMLINUX_SYMBOL_STR(input_free_device) },
	{ 0x7ee11bc1, __VMLINUX_SYMBOL_STR(device_init_wakeup) },
	{ 0xaa58a0ae, __VMLINUX_SYMBOL_STR(input_register_device) },
	{ 0xce917ae3, __VMLINUX_SYMBOL_STR(sysfs_create_group) },
	{ 0xd6b8e852, __VMLINUX_SYMBOL_STR(request_threaded_irq) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0xba1e33bf, __VMLINUX_SYMBOL_STR(input_mt_init_slots) },
	{ 0xcdc2d251, __VMLINUX_SYMBOL_STR(input_set_abs_params) },
	{ 0x593a99b, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0x26a6901f, __VMLINUX_SYMBOL_STR(input_allocate_device) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x8169d80e, __VMLINUX_SYMBOL_STR(i2c_transfer) },
	{ 0xce2840e7, __VMLINUX_SYMBOL_STR(irq_set_irq_wake) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0xe851bb05, __VMLINUX_SYMBOL_STR(queue_delayed_work_on) },
	{ 0x1e9f1a37, __VMLINUX_SYMBOL_STR(i2c_master_send) },
	{ 0x996bdb64, __VMLINUX_SYMBOL_STR(_kstrtoul) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x657c72c4, __VMLINUX_SYMBOL_STR(input_unregister_device) },
	{ 0x24d7b4eb, __VMLINUX_SYMBOL_STR(cancel_delayed_work_sync) },
	{ 0xf20dabd8, __VMLINUX_SYMBOL_STR(free_irq) },
	{ 0xb0cab2d5, __VMLINUX_SYMBOL_STR(sysfs_remove_group) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("i2c:ili210x");
