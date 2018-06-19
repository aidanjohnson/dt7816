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
	{ 0xbb691297, __VMLINUX_SYMBOL_STR(register_qdisc) },
	{ 0x80654086, __VMLINUX_SYMBOL_STR(qdisc_watchdog_init) },
	{ 0x318cadb1, __VMLINUX_SYMBOL_STR(reciprocal_value) },
	{ 0xd6ee688f, __VMLINUX_SYMBOL_STR(vmalloc) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x4f391d0e, __VMLINUX_SYMBOL_STR(nla_parse) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x87d204aa, __VMLINUX_SYMBOL_STR(skb_copy) },
	{ 0xa5526619, __VMLINUX_SYMBOL_STR(rb_insert_color) },
	{ 0x59e5070d, __VMLINUX_SYMBOL_STR(__do_div64) },
	{ 0xdf2c2742, __VMLINUX_SYMBOL_STR(rb_last) },
	{ 0x9056d7a7, __VMLINUX_SYMBOL_STR(skb_checksum_help) },
	{ 0xb2038f57, __VMLINUX_SYMBOL_STR(skb_clone) },
	{ 0xad63ef19, __VMLINUX_SYMBOL_STR(skb_orphan_partial) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0xa735db59, __VMLINUX_SYMBOL_STR(prandom_u32) },
	{ 0xb65f22fd, __VMLINUX_SYMBOL_STR(qdisc_watchdog_schedule_ns) },
	{ 0xc4c803c1, __VMLINUX_SYMBOL_STR(__qdisc_calculate_pkt_len) },
	{ 0xc87c1f84, __VMLINUX_SYMBOL_STR(ktime_get) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0xece784c2, __VMLINUX_SYMBOL_STR(rb_first) },
	{ 0x4d9b652b, __VMLINUX_SYMBOL_STR(rb_erase) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x731f20f0, __VMLINUX_SYMBOL_STR(qdisc_destroy) },
	{ 0x6f39b0a, __VMLINUX_SYMBOL_STR(qdisc_watchdog_cancel) },
	{ 0x8a7d1c31, __VMLINUX_SYMBOL_STR(high_memory) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0x594ff15d, __VMLINUX_SYMBOL_STR(skb_trim) },
	{ 0x63096cbc, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0xdd3916ac, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_bh) },
	{ 0x9f5e91dd, __VMLINUX_SYMBOL_STR(qdisc_reset) },
	{ 0xb54c2b8b, __VMLINUX_SYMBOL_STR(qdisc_tree_decrease_qlen) },
	{ 0xa1d55e90, __VMLINUX_SYMBOL_STR(_raw_spin_lock_bh) },
	{ 0x6b2dc060, __VMLINUX_SYMBOL_STR(dump_stack) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x85670f1d, __VMLINUX_SYMBOL_STR(rtnl_is_locked) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

