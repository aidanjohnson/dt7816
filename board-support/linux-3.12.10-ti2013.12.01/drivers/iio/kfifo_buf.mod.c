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
	{ 0xc068440e, __VMLINUX_SYMBOL_STR(__kfifo_alloc) },
	{ 0x5772770c, __VMLINUX_SYMBOL_STR(iio_buffer_read_length) },
	{ 0xdcd06e6f, __VMLINUX_SYMBOL_STR(iio_buffer_init) },
	{ 0x4578f528, __VMLINUX_SYMBOL_STR(__kfifo_to_user) },
	{ 0xa82c1c7, __VMLINUX_SYMBOL_STR(iio_buffer_write_length) },
	{ 0xd319eb4d, __VMLINUX_SYMBOL_STR(iio_buffer_store_enable) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xdb760f52, __VMLINUX_SYMBOL_STR(__kfifo_free) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xad31ae6c, __VMLINUX_SYMBOL_STR(iio_buffer_show_enable) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xf23fcb99, __VMLINUX_SYMBOL_STR(__kfifo_in) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=industrialio";

