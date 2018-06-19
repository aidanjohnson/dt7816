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
	{ 0x3c454965, __VMLINUX_SYMBOL_STR(iio_trigger_unregister) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0xfba080e4, __VMLINUX_SYMBOL_STR(iio_trigger_alloc) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xf97a88ca, __VMLINUX_SYMBOL_STR(iio_trigger_register) },
	{ 0xc9de10e5, __VMLINUX_SYMBOL_STR(sensor_hub_set_feature) },
	{ 0x594424c7, __VMLINUX_SYMBOL_STR(iio_trigger_free) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=industrialio,hid-sensor-hub";

