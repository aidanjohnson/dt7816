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
	{ 0xaa9087c0, __VMLINUX_SYMBOL_STR(param_ops_string) },
	{ 0x35c39aa9, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0x7781b4da, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x27bbf221, __VMLINUX_SYMBOL_STR(disable_irq_nosync) },
	{ 0xfcec0987, __VMLINUX_SYMBOL_STR(enable_irq) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0xb2468ee6, __VMLINUX_SYMBOL_STR(__pm_runtime_resume) },
	{ 0xc34ad504, __VMLINUX_SYMBOL_STR(__pm_runtime_idle) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0xf7868a8a, __VMLINUX_SYMBOL_STR(__uio_register_device) },
	{ 0x1bf9f43d, __VMLINUX_SYMBOL_STR(pm_runtime_enable) },
	{ 0xbf670952, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0xfa6be079, __VMLINUX_SYMBOL_STR(platform_get_irq) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x321c9d5e, __VMLINUX_SYMBOL_STR(__pm_runtime_disable) },
	{ 0x96d7ee3e, __VMLINUX_SYMBOL_STR(uio_unregister_device) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=uio";

MODULE_ALIAS("of:N*T*C*");
