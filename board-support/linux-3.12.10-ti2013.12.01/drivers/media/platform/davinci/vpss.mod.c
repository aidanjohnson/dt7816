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
	{ 0xadf42bd5, __VMLINUX_SYMBOL_STR(__request_region) },
	{ 0xc34ad504, __VMLINUX_SYMBOL_STR(__pm_runtime_idle) },
	{ 0x321c9d5e, __VMLINUX_SYMBOL_STR(__pm_runtime_disable) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x788fe103, __VMLINUX_SYMBOL_STR(iomem_resource) },
	{ 0x518c5f17, __VMLINUX_SYMBOL_STR(devm_ioremap_resource) },
	{ 0xb2468ee6, __VMLINUX_SYMBOL_STR(__pm_runtime_resume) },
	{ 0x7781b4da, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xbed18b93, __VMLINUX_SYMBOL_STR(platform_get_resource) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x1bf9f43d, __VMLINUX_SYMBOL_STR(pm_runtime_enable) },
	{ 0xc2165d85, __VMLINUX_SYMBOL_STR(__arm_iounmap) },
	{ 0x9bce482f, __VMLINUX_SYMBOL_STR(__release_region) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0xfb961d14, __VMLINUX_SYMBOL_STR(__arm_ioremap) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x35c39aa9, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0xac8f37b2, __VMLINUX_SYMBOL_STR(outer_cache) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

