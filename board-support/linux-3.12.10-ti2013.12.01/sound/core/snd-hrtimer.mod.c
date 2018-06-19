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
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xccbfe1a2, __VMLINUX_SYMBOL_STR(hrtimer_forward) },
	{ 0x7840b42c, __VMLINUX_SYMBOL_STR(hrtimer_cancel) },
	{ 0x35fde73c, __VMLINUX_SYMBOL_STR(snd_timer_global_new) },
	{ 0xb5cb8145, __VMLINUX_SYMBOL_STR(hrtimer_get_res) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x94e1823c, __VMLINUX_SYMBOL_STR(hrtimer_start) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xf7e0a2e5, __VMLINUX_SYMBOL_STR(snd_timer_interrupt) },
	{ 0xfc3bd35, __VMLINUX_SYMBOL_STR(hrtimer_init) },
	{ 0x97fd76d4, __VMLINUX_SYMBOL_STR(snd_timer_global_register) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x737d851a, __VMLINUX_SYMBOL_STR(snd_timer_global_free) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

