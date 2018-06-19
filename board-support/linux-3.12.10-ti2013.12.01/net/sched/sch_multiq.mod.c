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
	{ 0xc4c803c1, __VMLINUX_SYMBOL_STR(__qdisc_calculate_pkt_len) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x49694495, __VMLINUX_SYMBOL_STR(tc_classify) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xea6c9152, __VMLINUX_SYMBOL_STR(tcf_destroy_chain) },
	{ 0x5fad5f0b, __VMLINUX_SYMBOL_STR(pfifo_qdisc_ops) },
	{ 0xe0687ce6, __VMLINUX_SYMBOL_STR(qdisc_create_dflt) },
	{ 0x731f20f0, __VMLINUX_SYMBOL_STR(qdisc_destroy) },
	{ 0x594ff15d, __VMLINUX_SYMBOL_STR(skb_trim) },
	{ 0x63096cbc, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0x891ab9a9, __VMLINUX_SYMBOL_STR(noop_qdisc) },
	{ 0xdd3916ac, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_bh) },
	{ 0xb54c2b8b, __VMLINUX_SYMBOL_STR(qdisc_tree_decrease_qlen) },
	{ 0xa1d55e90, __VMLINUX_SYMBOL_STR(_raw_spin_lock_bh) },
	{ 0x6b2dc060, __VMLINUX_SYMBOL_STR(dump_stack) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x85670f1d, __VMLINUX_SYMBOL_STR(rtnl_is_locked) },
	{ 0x9f5e91dd, __VMLINUX_SYMBOL_STR(qdisc_reset) },
	{ 0x3512234b, __VMLINUX_SYMBOL_STR(gnet_stats_copy_queue) },
	{ 0x70c6d576, __VMLINUX_SYMBOL_STR(gnet_stats_copy_basic) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

