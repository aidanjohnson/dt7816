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
	{ 0xbd5a24ac, __VMLINUX_SYMBOL_STR(iio_bus_type) },
	{ 0x8552b5b9, __VMLINUX_SYMBOL_STR(device_unregister) },
	{ 0x5208f041, __VMLINUX_SYMBOL_STR(device_add) },
	{ 0x8ecb1aa8, __VMLINUX_SYMBOL_STR(dev_set_name) },
	{ 0x357d8144, __VMLINUX_SYMBOL_STR(device_initialize) },
	{ 0x40a54855, __VMLINUX_SYMBOL_STR(iio_trigger_poll) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x63d684c9, __VMLINUX_SYMBOL_STR(put_device) },
	{ 0x74971a96, __VMLINUX_SYMBOL_STR(__module_get) },
	{ 0xf97a88ca, __VMLINUX_SYMBOL_STR(iio_trigger_register) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0xfba080e4, __VMLINUX_SYMBOL_STR(iio_trigger_alloc) },
	{ 0xc690866c, __VMLINUX_SYMBOL_STR(irq_work_queue) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0xbca31af2, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x594424c7, __VMLINUX_SYMBOL_STR(iio_trigger_free) },
	{ 0x3c454965, __VMLINUX_SYMBOL_STR(iio_trigger_unregister) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x996bdb64, __VMLINUX_SYMBOL_STR(_kstrtoul) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=industrialio";

