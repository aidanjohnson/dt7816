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
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x4cd9d440, __VMLINUX_SYMBOL_STR(single_release) },
	{ 0x92c80041, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0x94b932f1, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0x9d0d6206, __VMLINUX_SYMBOL_STR(unregister_netdevice_notifier) },
	{ 0xdc8cb9d7, __VMLINUX_SYMBOL_STR(unregister_pernet_subsys) },
	{ 0xd2da1048, __VMLINUX_SYMBOL_STR(register_netdevice_notifier) },
	{ 0xd7cb77a9, __VMLINUX_SYMBOL_STR(register_pernet_subsys) },
	{ 0xb3f7646e, __VMLINUX_SYMBOL_STR(kthread_should_stop) },
	{ 0x1fcf4d4b, __VMLINUX_SYMBOL_STR(_raw_read_unlock_bh) },
	{ 0xe11f3cbc, __VMLINUX_SYMBOL_STR(_raw_read_lock_bh) },
	{ 0x7ab88a45, __VMLINUX_SYMBOL_STR(system_freezing_cnt) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0xc8b57c27, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0xdd3916ac, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_bh) },
	{ 0xa1d55e90, __VMLINUX_SYMBOL_STR(_raw_spin_lock_bh) },
	{ 0xe40dc473, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0xd796878f, __VMLINUX_SYMBOL_STR(pskb_expand_head) },
	{ 0x24af1414, __VMLINUX_SYMBOL_STR(udp4_hwcsum) },
	{ 0x2124474, __VMLINUX_SYMBOL_STR(ip_send_check) },
	{ 0xe113bbbc, __VMLINUX_SYMBOL_STR(csum_partial) },
	{ 0x44da5d0f, __VMLINUX_SYMBOL_STR(__csum_ipv6_magic) },
	{ 0xf6ebc03b, __VMLINUX_SYMBOL_STR(net_ratelimit) },
	{ 0x5515ca7f, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0x4482cdb, __VMLINUX_SYMBOL_STR(__refrigerator) },
	{ 0x41da4b21, __VMLINUX_SYMBOL_STR(freezing_slow_path) },
	{ 0xd62c833f, __VMLINUX_SYMBOL_STR(schedule_timeout) },
	{ 0x1cfb04fa, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x499cb58c, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0x9e61bb05, __VMLINUX_SYMBOL_STR(set_freezable) },
	{ 0xd4669fad, __VMLINUX_SYMBOL_STR(complete) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xf1deabf2, __VMLINUX_SYMBOL_STR(div64_u64) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0xa6822854, __VMLINUX_SYMBOL_STR(dev_get_by_name) },
	{ 0x9e0c711d, __VMLINUX_SYMBOL_STR(vzalloc_node) },
	{ 0x95c68e4a, __VMLINUX_SYMBOL_STR(__xfrm_state_destroy) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xfe7c4287, __VMLINUX_SYMBOL_STR(nr_cpu_ids) },
	{ 0x7272c3c8, __VMLINUX_SYMBOL_STR(cpu_online_mask) },
	{ 0xd3f57a2, __VMLINUX_SYMBOL_STR(_find_next_bit_le) },
	{ 0x1fab5905, __VMLINUX_SYMBOL_STR(wait_for_completion) },
	{ 0x26021bc4, __VMLINUX_SYMBOL_STR(wake_up_process) },
	{ 0x93e47ab5, __VMLINUX_SYMBOL_STR(kthread_bind) },
	{ 0xbd59f360, __VMLINUX_SYMBOL_STR(kthread_create_on_node) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x3e300a64, __VMLINUX_SYMBOL_STR(proc_mkdir) },
	{ 0xf9141363, __VMLINUX_SYMBOL_STR(proc_create_data) },
	{ 0xfba197b8, __VMLINUX_SYMBOL_STR(proc_remove) },
	{ 0x7840b42c, __VMLINUX_SYMBOL_STR(hrtimer_cancel) },
	{ 0x86ffbf0b, __VMLINUX_SYMBOL_STR(hrtimer_start_range_ns) },
	{ 0x9632d23d, __VMLINUX_SYMBOL_STR(hrtimer_init_sleeper) },
	{ 0xfc3bd35, __VMLINUX_SYMBOL_STR(hrtimer_init) },
	{ 0x306a1617, __VMLINUX_SYMBOL_STR(contig_page_data) },
	{ 0x4f68e5c9, __VMLINUX_SYMBOL_STR(do_gettimeofday) },
	{ 0xf2f138ef, __VMLINUX_SYMBOL_STR(__get_page_tail) },
	{ 0xfc55d6db, __VMLINUX_SYMBOL_STR(__alloc_pages_nodemask) },
	{ 0x70b60936, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0x63a326ef, __VMLINUX_SYMBOL_STR(__netdev_alloc_skb) },
	{ 0xc3e596f0, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0x8235888d, __VMLINUX_SYMBOL_STR(xfrm_stateonly_find) },
	{ 0xa735db59, __VMLINUX_SYMBOL_STR(prandom_u32) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0x84b183ae, __VMLINUX_SYMBOL_STR(strncmp) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0x25c677c4, __VMLINUX_SYMBOL_STR(mac_pton) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xe57878a1, __VMLINUX_SYMBOL_STR(in6_pton) },
	{ 0x1b6314fd, __VMLINUX_SYMBOL_STR(in_aton) },
	{ 0x328a05f1, __VMLINUX_SYMBOL_STR(strncpy) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
	{ 0x34fef0bf, __VMLINUX_SYMBOL_STR(put_page) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x11f7ed4c, __VMLINUX_SYMBOL_STR(hex_to_bin) },
	{ 0x4cdb3178, __VMLINUX_SYMBOL_STR(ns_to_timeval) },
	{ 0xc87c1f84, __VMLINUX_SYMBOL_STR(ktime_get) },
	{ 0x2247cba2, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x9c55cec, __VMLINUX_SYMBOL_STR(schedule_timeout_interruptible) },
	{ 0x3bd1b1f6, __VMLINUX_SYMBOL_STR(msecs_to_jiffies) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xfbc74f64, __VMLINUX_SYMBOL_STR(__copy_from_user) },
	{ 0xc6cbbc89, __VMLINUX_SYMBOL_STR(capable) },
	{ 0xcc5005fe, __VMLINUX_SYMBOL_STR(msleep_interruptible) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0xd2ce469a, __VMLINUX_SYMBOL_STR(seq_puts) },
	{ 0xf88dd612, __VMLINUX_SYMBOL_STR(single_open) },
	{ 0xbbcbd046, __VMLINUX_SYMBOL_STR(PDE_DATA) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x688c3c76, __VMLINUX_SYMBOL_STR(remove_proc_entry) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x90a20675, __VMLINUX_SYMBOL_STR(kthread_stop) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x28118cb6, __VMLINUX_SYMBOL_STR(__get_user_1) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "452EB7AC053A395F020345C");
