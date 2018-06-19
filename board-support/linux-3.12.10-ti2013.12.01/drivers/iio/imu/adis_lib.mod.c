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
	{ 0x5b9b2249, __VMLINUX_SYMBOL_STR(iio_triggered_buffer_cleanup) },
	{ 0x3c454965, __VMLINUX_SYMBOL_STR(iio_trigger_unregister) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xdf76bbeb, __VMLINUX_SYMBOL_STR(iio_pollfunc_store_time) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x14a0818, __VMLINUX_SYMBOL_STR(iio_trigger_notify_done) },
	{ 0xfba080e4, __VMLINUX_SYMBOL_STR(iio_trigger_alloc) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xd6b8e852, __VMLINUX_SYMBOL_STR(request_threaded_irq) },
	{ 0xc00cee86, __VMLINUX_SYMBOL_STR(spi_sync) },
	{ 0xf97a88ca, __VMLINUX_SYMBOL_STR(iio_trigger_register) },
	{ 0x594424c7, __VMLINUX_SYMBOL_STR(iio_trigger_free) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x2d6bcdcb, __VMLINUX_SYMBOL_STR(iio_trigger_generic_data_rdy_poll) },
	{ 0xcd55807b, __VMLINUX_SYMBOL_STR(iio_push_to_buffers) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x440813f2, __VMLINUX_SYMBOL_STR(iio_triggered_buffer_setup) },
	{ 0xf20dabd8, __VMLINUX_SYMBOL_STR(free_irq) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=industrialio-triggered-buffer,industrialio";

