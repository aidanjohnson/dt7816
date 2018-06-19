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
	{ 0xecf4ba7, __VMLINUX_SYMBOL_STR(iio_buffer_register) },
	{ 0x8f4c9415, __VMLINUX_SYMBOL_STR(iio_kfifo_allocate) },
	{ 0x8aa1d8ed, __VMLINUX_SYMBOL_STR(iio_triggered_buffer_postenable) },
	{ 0x50fc2a9c, __VMLINUX_SYMBOL_STR(iio_buffer_unregister) },
	{ 0x44412b98, __VMLINUX_SYMBOL_STR(iio_triggered_buffer_predisable) },
	{ 0xab0bbbee, __VMLINUX_SYMBOL_STR(iio_kfifo_free) },
	{ 0x1a5fe10c, __VMLINUX_SYMBOL_STR(iio_alloc_pollfunc) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x1227333a, __VMLINUX_SYMBOL_STR(iio_dealloc_pollfunc) },
	{ 0xb4ffe258, __VMLINUX_SYMBOL_STR(iio_sw_buffer_preenable) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=industrialio,kfifo_buf";

