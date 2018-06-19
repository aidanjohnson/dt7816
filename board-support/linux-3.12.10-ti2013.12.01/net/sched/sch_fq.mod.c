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
	{ 0xa1dec0a, __VMLINUX_SYMBOL_STR(unregister_qdisc) },
	{ 0xb64de2d, __VMLINUX_SYMBOL_STR(kmem_cache_destroy) },
	{ 0xbb691297, __VMLINUX_SYMBOL_STR(register_qdisc) },
	{ 0x88e43e81, __VMLINUX_SYMBOL_STR(kmem_cache_create) },
	{ 0x80654086, __VMLINUX_SYMBOL_STR(qdisc_watchdog_init) },
	{ 0x3bd1b1f6, __VMLINUX_SYMBOL_STR(msecs_to_jiffies) },
	{ 0xdd3916ac, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_bh) },
	{ 0xb54c2b8b, __VMLINUX_SYMBOL_STR(qdisc_tree_decrease_qlen) },
	{ 0xb54533f7, __VMLINUX_SYMBOL_STR(usecs_to_jiffies) },
	{ 0x72350130, __VMLINUX_SYMBOL_STR(___ratelimit) },
	{ 0xa1d55e90, __VMLINUX_SYMBOL_STR(_raw_spin_lock_bh) },
	{ 0x6b2dc060, __VMLINUX_SYMBOL_STR(dump_stack) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x85670f1d, __VMLINUX_SYMBOL_STR(rtnl_is_locked) },
	{ 0x4f391d0e, __VMLINUX_SYMBOL_STR(nla_parse) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xb0e93b81, __VMLINUX_SYMBOL_STR(kmem_cache_alloc) },
	{ 0xc668ae36, __VMLINUX_SYMBOL_STR(__skb_get_rxhash) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x59e5070d, __VMLINUX_SYMBOL_STR(__do_div64) },
	{ 0xa5526619, __VMLINUX_SYMBOL_STR(rb_insert_color) },
	{ 0xb65f22fd, __VMLINUX_SYMBOL_STR(qdisc_watchdog_schedule_ns) },
	{ 0x6f39b0a, __VMLINUX_SYMBOL_STR(qdisc_watchdog_cancel) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xece784c2, __VMLINUX_SYMBOL_STR(rb_first) },
	{ 0x88b454fd, __VMLINUX_SYMBOL_STR(kmem_cache_free) },
	{ 0x4d9b652b, __VMLINUX_SYMBOL_STR(rb_erase) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x7f24de73, __VMLINUX_SYMBOL_STR(jiffies_to_usecs) },
	{ 0x63096cbc, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0xb02951fc, __VMLINUX_SYMBOL_STR(gnet_stats_copy_app) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xc87c1f84, __VMLINUX_SYMBOL_STR(ktime_get) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

