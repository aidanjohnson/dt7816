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
	{ 0xcf3059bb, __VMLINUX_SYMBOL_STR(nf_ct_tcp_seqadj_set) },
	{ 0xdc8cb9d7, __VMLINUX_SYMBOL_STR(unregister_pernet_subsys) },
	{ 0x874a0895, __VMLINUX_SYMBOL_STR(nfq_ct_hook) },
	{ 0x8de38364, __VMLINUX_SYMBOL_STR(nfnetlink_subsys_unregister) },
	{ 0xd7cb77a9, __VMLINUX_SYMBOL_STR(register_pernet_subsys) },
	{ 0x1ea5d950, __VMLINUX_SYMBOL_STR(nfnetlink_subsys_register) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x69f54fcc, __VMLINUX_SYMBOL_STR(nf_ct_unlink_expect_report) },
	{ 0x648f39c1, __VMLINUX_SYMBOL_STR(nf_ct_expect_find_get) },
	{ 0x1293be20, __VMLINUX_SYMBOL_STR(__nf_ct_expect_find) },
	{ 0xea2172cc, __VMLINUX_SYMBOL_STR(nf_ct_delete) },
	{ 0xa85060aa, __VMLINUX_SYMBOL_STR(nf_conntrack_flush_report) },
	{ 0xc18ac88d, __VMLINUX_SYMBOL_STR(nf_ct_expect_hsize) },
	{ 0xedb25af7, __VMLINUX_SYMBOL_STR(nf_conntrack_free) },
	{ 0x428b3f2, __VMLINUX_SYMBOL_STR(nf_conntrack_hash_check_insert) },
	{ 0x2447533c, __VMLINUX_SYMBOL_STR(ktime_get_real) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x5fdb7019, __VMLINUX_SYMBOL_STR(__nf_ct_ext_add_length) },
	{ 0x1b8573e3, __VMLINUX_SYMBOL_STR(__nf_ct_try_assign_helper) },
	{ 0xd1abde20, __VMLINUX_SYMBOL_STR(nf_ct_helper_ext_add) },
	{ 0xa0399b1d, __VMLINUX_SYMBOL_STR(nf_conntrack_alloc) },
	{ 0xf038f35c, __VMLINUX_SYMBOL_STR(nfnetlink_parse_nat_setup_hook) },
	{ 0x5ce3b588, __VMLINUX_SYMBOL_STR(nfnl_lock) },
	{ 0xdb065657, __VMLINUX_SYMBOL_STR(nfnl_unlock) },
	{ 0x4117ce2c, __VMLINUX_SYMBOL_STR(nf_ct_expect_register_notifier) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xc15c4583, __VMLINUX_SYMBOL_STR(nf_conntrack_register_notifier) },
	{ 0xc6b1924a, __VMLINUX_SYMBOL_STR(nfnetlink_set_err) },
	{ 0x6e6f079a, __VMLINUX_SYMBOL_STR(nfnetlink_send) },
	{ 0x48ecc4c4, __VMLINUX_SYMBOL_STR(nfnetlink_has_listeners) },
	{ 0x4a83fcd, __VMLINUX_SYMBOL_STR(nf_conntrack_unregister_notifier) },
	{ 0xa7726d13, __VMLINUX_SYMBOL_STR(nf_ct_expect_unregister_notifier) },
	{ 0xc7be16d9, __VMLINUX_SYMBOL_STR(nf_ct_expect_related_report) },
	{ 0xcf65e931, __VMLINUX_SYMBOL_STR(nf_ct_helper_expectfn_find_by_name) },
	{ 0xe949bfe9, __VMLINUX_SYMBOL_STR(nf_ct_expect_alloc) },
	{ 0xf73eb86, __VMLINUX_SYMBOL_STR(nf_ct_helper_expectfn_find_by_symbol) },
	{ 0xac7f0706, __VMLINUX_SYMBOL_STR(nf_ct_expect_put) },
	{ 0x402b8281, __VMLINUX_SYMBOL_STR(__request_module) },
	{ 0x8e7b43ac, __VMLINUX_SYMBOL_STR(__nf_conntrack_helper_find) },
	{ 0x89ac4b93, __VMLINUX_SYMBOL_STR(nf_ct_remove_expectations) },
	{ 0xbe2c0274, __VMLINUX_SYMBOL_STR(add_timer) },
	{ 0xc996d097, __VMLINUX_SYMBOL_STR(del_timer) },
	{ 0xfbb99906, __VMLINUX_SYMBOL_STR(nf_connlabels_replace) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0xe4cb61ae, __VMLINUX_SYMBOL_STR(netlink_unicast) },
	{ 0xc3e596f0, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0xbc9a4f1, __VMLINUX_SYMBOL_STR(nf_conntrack_find_get) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x347013de, __VMLINUX_SYMBOL_STR(nla_validate) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x4f391d0e, __VMLINUX_SYMBOL_STR(nla_parse) },
	{ 0xb23f3373, __VMLINUX_SYMBOL_STR(nf_conntrack_lock) },
	{ 0xdd3916ac, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_bh) },
	{ 0xa1d55e90, __VMLINUX_SYMBOL_STR(_raw_spin_lock_bh) },
	{ 0x1176e07f, __VMLINUX_SYMBOL_STR(__per_cpu_offset) },
	{ 0x7c62d042, __VMLINUX_SYMBOL_STR(cpu_possible_mask) },
	{ 0xfe7c4287, __VMLINUX_SYMBOL_STR(nr_cpu_ids) },
	{ 0x594ff15d, __VMLINUX_SYMBOL_STR(skb_trim) },
	{ 0x8dd61422, __VMLINUX_SYMBOL_STR(__nlmsg_put) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x67d8d35, __VMLINUX_SYMBOL_STR(security_release_secctx) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0xefdd70ce, __VMLINUX_SYMBOL_STR(security_secid_to_secctx) },
	{ 0x4b932b82, __VMLINUX_SYMBOL_STR(nf_conntrack_l3proto_generic) },
	{ 0x8aa224fc, __VMLINUX_SYMBOL_STR(nf_ct_l3protos) },
	{ 0x6fd2e9c, __VMLINUX_SYMBOL_STR(__nf_ct_l4proto_find) },
	{ 0x63096cbc, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x2a18c74, __VMLINUX_SYMBOL_STR(nf_conntrack_destroy) },
	{ 0x11815a9b, __VMLINUX_SYMBOL_STR(__netlink_dump_start) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=nf_conntrack,nfnetlink";

