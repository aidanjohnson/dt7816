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
	{ 0x32d5baca, __VMLINUX_SYMBOL_STR(kobject_put) },
	{ 0xb84dc0b4, __VMLINUX_SYMBOL_STR(cdev_alloc) },
	{ 0x7e341a6e, __VMLINUX_SYMBOL_STR(cdev_del) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xfbc74f64, __VMLINUX_SYMBOL_STR(__copy_from_user) },
	{ 0xe52e3763, __VMLINUX_SYMBOL_STR(mem_map) },
	{ 0x67c2fa54, __VMLINUX_SYMBOL_STR(__copy_to_user) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x4c86184b, __VMLINUX_SYMBOL_STR(remove_wait_queue) },
	{ 0x19db6c4b, __VMLINUX_SYMBOL_STR(kobject_uevent) },
	{ 0x13de81b5, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0xe47249b6, __VMLINUX_SYMBOL_STR(kobject_set_name) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x7485e15e, __VMLINUX_SYMBOL_STR(unregister_chrdev_region) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x6ccf7bd7, __VMLINUX_SYMBOL_STR(__pv_phys_offset) },
	{ 0x216ce896, __VMLINUX_SYMBOL_STR(kobject_create_and_add) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xffd5a395, __VMLINUX_SYMBOL_STR(default_wake_function) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x210d8549, __VMLINUX_SYMBOL_STR(class_unregister) },
	{ 0x78d318c0, __VMLINUX_SYMBOL_STR(fasync_helper) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xe57e68bb, __VMLINUX_SYMBOL_STR(noop_llseek) },
	{ 0xddf26bab, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0xd6b8e852, __VMLINUX_SYMBOL_STR(request_threaded_irq) },
	{ 0xf74dae0f, __VMLINUX_SYMBOL_STR(idr_alloc) },
	{ 0xc45678b0, __VMLINUX_SYMBOL_STR(kobject_add) },
	{ 0x2f51d70c, __VMLINUX_SYMBOL_STR(__class_register) },
	{ 0xf2f138ef, __VMLINUX_SYMBOL_STR(__get_page_tail) },
	{ 0xdf401846, __VMLINUX_SYMBOL_STR(idr_remove) },
	{ 0x572e9cc8, __VMLINUX_SYMBOL_STR(cdev_add) },
	{ 0xbca31af2, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0xf1806da9, __VMLINUX_SYMBOL_STR(idr_find_slowpath) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0xc7bcbc8d, __VMLINUX_SYMBOL_STR(add_wait_queue) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x55d549ff, __VMLINUX_SYMBOL_STR(remap_pfn_range) },
	{ 0x343848e4, __VMLINUX_SYMBOL_STR(kobject_init) },
	{ 0x6569bb8d, __VMLINUX_SYMBOL_STR(kill_fasync) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x1e1ff3f2, __VMLINUX_SYMBOL_STR(vmalloc_to_page) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x29537c9e, __VMLINUX_SYMBOL_STR(alloc_chrdev_region) },
	{ 0xf5afcd9d, __VMLINUX_SYMBOL_STR(try_module_get) },
	{ 0xf20dabd8, __VMLINUX_SYMBOL_STR(free_irq) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

