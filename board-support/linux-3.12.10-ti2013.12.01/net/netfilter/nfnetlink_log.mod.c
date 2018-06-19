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
	{ 0xa9c6a267, __VMLINUX_SYMBOL_STR(nf_log_unregister) },
	{ 0xc996d097, __VMLINUX_SYMBOL_STR(del_timer) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0x27f15ec9, __VMLINUX_SYMBOL_STR(from_kuid_munged) },
	{ 0xfa599bb2, __VMLINUX_SYMBOL_STR(netlink_register_notifier) },
	{ 0xa302317, __VMLINUX_SYMBOL_STR(nf_log_bind_pf) },
	{ 0x79aa04a2, __VMLINUX_SYMBOL_STR(get_random_bytes) },
	{ 0xa1d55e90, __VMLINUX_SYMBOL_STR(_raw_spin_lock_bh) },
	{ 0x2247cba2, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0x688c3c76, __VMLINUX_SYMBOL_STR(remove_proc_entry) },
	{ 0xdf54a8f7, __VMLINUX_SYMBOL_STR(netlink_unregister_notifier) },
	{ 0x593a99b, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0x53b86f03, __VMLINUX_SYMBOL_STR(__put_net) },
	{ 0x92c80041, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x16a2a1ba, __VMLINUX_SYMBOL_STR(from_kgid_munged) },
	{ 0x8de38364, __VMLINUX_SYMBOL_STR(nfnetlink_subsys_unregister) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xdc8cb9d7, __VMLINUX_SYMBOL_STR(unregister_pernet_subsys) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x63096cbc, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0x1ef93c7c, __VMLINUX_SYMBOL_STR(nfnetlink_unicast) },
	{ 0x1118ff8b, __VMLINUX_SYMBOL_STR(seq_release_net) },
	{ 0xbe2c0274, __VMLINUX_SYMBOL_STR(add_timer) },
	{ 0xfc8b84a4, __VMLINUX_SYMBOL_STR(init_net) },
	{ 0xbca31af2, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0x3ff62317, __VMLINUX_SYMBOL_STR(local_bh_disable) },
	{ 0xbb2b494e, __VMLINUX_SYMBOL_STR(nf_log_unbind_pf) },
	{ 0xdd3916ac, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_bh) },
	{ 0x799aca4, __VMLINUX_SYMBOL_STR(local_bh_enable) },
	{ 0x8239527a, __VMLINUX_SYMBOL_STR(nfnetlink_alloc_skb) },
	{ 0xd7cb77a9, __VMLINUX_SYMBOL_STR(register_pernet_subsys) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x59e2743e, __VMLINUX_SYMBOL_STR(call_rcu_bh) },
	{ 0xf6ebc03b, __VMLINUX_SYMBOL_STR(net_ratelimit) },
	{ 0xf9141363, __VMLINUX_SYMBOL_STR(proc_create_data) },
	{ 0x94b932f1, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0xe11f3cbc, __VMLINUX_SYMBOL_STR(_raw_read_lock_bh) },
	{ 0x1ea5d950, __VMLINUX_SYMBOL_STR(nfnetlink_subsys_register) },
	{ 0x1fcf4d4b, __VMLINUX_SYMBOL_STR(_raw_read_unlock_bh) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xbd084931, __VMLINUX_SYMBOL_STR(seq_open_net) },
	{ 0x346fd450, __VMLINUX_SYMBOL_STR(nf_log_register) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x70b60936, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0x8dd61422, __VMLINUX_SYMBOL_STR(__nlmsg_put) },
	{ 0xff924d9c, __VMLINUX_SYMBOL_STR(skb_copy_bits) },
	{ 0xf5afcd9d, __VMLINUX_SYMBOL_STR(try_module_get) },
	{ 0x4cdb3178, __VMLINUX_SYMBOL_STR(ns_to_timeval) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=nfnetlink";

