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
	{ 0x41677880, __VMLINUX_SYMBOL_STR(atm_dev_deregister) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xce917ae3, __VMLINUX_SYMBOL_STR(sysfs_create_group) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x7e7516a6, __VMLINUX_SYMBOL_STR(atm_dev_register) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0xe2ea17e8, __VMLINUX_SYMBOL_STR(dev_kfree_skb_any) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xe6269bbd, __VMLINUX_SYMBOL_STR(atm_dev_signal_change) },
	{ 0x20c55ae0, __VMLINUX_SYMBOL_STR(sscanf) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=atm";

