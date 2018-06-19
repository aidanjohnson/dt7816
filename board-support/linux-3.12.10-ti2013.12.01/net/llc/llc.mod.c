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
	{ 0x609f1c7e, __VMLINUX_SYMBOL_STR(synchronize_net) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xa1d55e90, __VMLINUX_SYMBOL_STR(_raw_spin_lock_bh) },
	{ 0xb2038f57, __VMLINUX_SYMBOL_STR(skb_clone) },
	{ 0x71bc64b4, __VMLINUX_SYMBOL_STR(__pskb_pull_tail) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x5515ca7f, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0x5bed598, __VMLINUX_SYMBOL_STR(dev_remove_pack) },
	{ 0xc2cdbf1, __VMLINUX_SYMBOL_STR(synchronize_sched) },
	{ 0xe40dc473, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0xfc8b84a4, __VMLINUX_SYMBOL_STR(init_net) },
	{ 0x3ff62317, __VMLINUX_SYMBOL_STR(local_bh_disable) },
	{ 0xdd3916ac, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_bh) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x799aca4, __VMLINUX_SYMBOL_STR(local_bh_enable) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x1e047854, __VMLINUX_SYMBOL_STR(warn_slowpath_fmt) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xd7cd63d6, __VMLINUX_SYMBOL_STR(___pskb_trim) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xa25753f7, __VMLINUX_SYMBOL_STR(dev_add_pack) },
	{ 0x50d6202a, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0xc11126ee, __VMLINUX_SYMBOL_STR(dev_queue_xmit) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

