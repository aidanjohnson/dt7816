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
	{ 0xfcec0987, __VMLINUX_SYMBOL_STR(enable_irq) },
	{ 0x3ce4ca6f, __VMLINUX_SYMBOL_STR(disable_irq) },
	{ 0xb79a5aed, __VMLINUX_SYMBOL_STR(input_event) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x55e25a41, __VMLINUX_SYMBOL_STR(input_free_device) },
	{ 0xaa58a0ae, __VMLINUX_SYMBOL_STR(input_register_device) },
	{ 0xc34ad504, __VMLINUX_SYMBOL_STR(__pm_runtime_idle) },
	{ 0xd6b8e852, __VMLINUX_SYMBOL_STR(request_threaded_irq) },
	{ 0xfc6327d3, __VMLINUX_SYMBOL_STR(matrix_keypad_build_keymap) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0xfc88fbae, __VMLINUX_SYMBOL_STR(input_set_capability) },
	{ 0x26a6901f, __VMLINUX_SYMBOL_STR(input_allocate_device) },
	{ 0xb2468ee6, __VMLINUX_SYMBOL_STR(__pm_runtime_resume) },
	{ 0x1bf9f43d, __VMLINUX_SYMBOL_STR(pm_runtime_enable) },
	{ 0xfb961d14, __VMLINUX_SYMBOL_STR(__arm_ioremap) },
	{ 0xadf42bd5, __VMLINUX_SYMBOL_STR(__request_region) },
	{ 0x260cf8f8, __VMLINUX_SYMBOL_STR(of_get_property) },
	{ 0x18ec14d3, __VMLINUX_SYMBOL_STR(matrix_keypad_parse_of_params) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xfa6be079, __VMLINUX_SYMBOL_STR(platform_get_irq) },
	{ 0x788fe103, __VMLINUX_SYMBOL_STR(iomem_resource) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9bce482f, __VMLINUX_SYMBOL_STR(__release_region) },
	{ 0xbed18b93, __VMLINUX_SYMBOL_STR(platform_get_resource) },
	{ 0xc2165d85, __VMLINUX_SYMBOL_STR(__arm_iounmap) },
	{ 0x657c72c4, __VMLINUX_SYMBOL_STR(input_unregister_device) },
	{ 0x7ee11bc1, __VMLINUX_SYMBOL_STR(device_init_wakeup) },
	{ 0x321c9d5e, __VMLINUX_SYMBOL_STR(__pm_runtime_disable) },
	{ 0xf20dabd8, __VMLINUX_SYMBOL_STR(free_irq) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xce2840e7, __VMLINUX_SYMBOL_STR(irq_set_irq_wake) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("of:N*T*Cti,omap4-keypad*");
