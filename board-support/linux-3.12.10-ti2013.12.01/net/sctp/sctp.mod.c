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
	{ 0x9c9ec2a0, __VMLINUX_SYMBOL_STR(proc_dointvec_minmax) },
	{ 0xfd128d57, __VMLINUX_SYMBOL_STR(skb_queue_head) },
	{ 0xcf369001, __VMLINUX_SYMBOL_STR(release_sock) },
	{ 0xb64de2d, __VMLINUX_SYMBOL_STR(kmem_cache_destroy) },
	{ 0x2d6507b5, __VMLINUX_SYMBOL_STR(_find_next_zero_bit_le) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x10137555, __VMLINUX_SYMBOL_STR(sock_init_data) },
	{ 0x49045426, __VMLINUX_SYMBOL_STR(icmp_err_convert) },
	{ 0xff178f6, __VMLINUX_SYMBOL_STR(__aeabi_idivmod) },
	{ 0xfbc74f64, __VMLINUX_SYMBOL_STR(__copy_from_user) },
	{ 0xf658eff2, __VMLINUX_SYMBOL_STR(sk_filter) },
	{ 0xd74289f9, __VMLINUX_SYMBOL_STR(__percpu_counter_add) },
	{ 0xcfefe1e, __VMLINUX_SYMBOL_STR(percpu_counter_destroy) },
	{ 0xacb1a3c, __VMLINUX_SYMBOL_STR(__bitmap_shift_right) },
	{ 0x6b1abcee, __VMLINUX_SYMBOL_STR(ip_getsockopt) },
	{ 0x67c2fa54, __VMLINUX_SYMBOL_STR(__copy_to_user) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xc996d097, __VMLINUX_SYMBOL_STR(del_timer) },
	{ 0xdbcd416e, __VMLINUX_SYMBOL_STR(sysctl_ip_nonlocal_bind) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0x4b993e46, __VMLINUX_SYMBOL_STR(ipv6_getsockopt) },
	{ 0x60a13e90, __VMLINUX_SYMBOL_STR(rcu_barrier) },
	{ 0x369de012, __VMLINUX_SYMBOL_STR(ipv6_chk_addr) },
	{ 0x33077361, __VMLINUX_SYMBOL_STR(ip_setsockopt) },
	{ 0x27f15ec9, __VMLINUX_SYMBOL_STR(from_kuid_munged) },
	{ 0xb46351a0, __VMLINUX_SYMBOL_STR(inet6_add_protocol) },
	{ 0xf68285c0, __VMLINUX_SYMBOL_STR(register_inetaddr_notifier) },
	{ 0xc8b57c27, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0x9469482, __VMLINUX_SYMBOL_STR(kfree_call_rcu) },
	{ 0x2512642c, __VMLINUX_SYMBOL_STR(unregister_net_sysctl_table) },
	{ 0x1bb4358d, __VMLINUX_SYMBOL_STR(send_sig) },
	{ 0xc34efe27, __VMLINUX_SYMBOL_STR(snmp_fold_field) },
	{ 0xd3dbfbc4, __VMLINUX_SYMBOL_STR(_find_first_zero_bit_le) },
	{ 0x79aa04a2, __VMLINUX_SYMBOL_STR(get_random_bytes) },
	{ 0xe43274bc, __VMLINUX_SYMBOL_STR(proc_dointvec) },
	{ 0xe883861, __VMLINUX_SYMBOL_STR(sock_release) },
	{ 0x7b6646bb, __VMLINUX_SYMBOL_STR(_raw_read_lock) },
	{ 0x9700966d, __VMLINUX_SYMBOL_STR(dst_release) },
	{ 0xa1d55e90, __VMLINUX_SYMBOL_STR(_raw_spin_lock_bh) },
	{ 0xb2038f57, __VMLINUX_SYMBOL_STR(skb_clone) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0x87d204aa, __VMLINUX_SYMBOL_STR(skb_copy) },
	{ 0xd3f57a2, __VMLINUX_SYMBOL_STR(_find_next_bit_le) },
	{ 0x2247cba2, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0xc87c1f84, __VMLINUX_SYMBOL_STR(ktime_get) },
	{ 0x688c3c76, __VMLINUX_SYMBOL_STR(remove_proc_entry) },
	{ 0x60352082, __VMLINUX_SYMBOL_STR(register_inet6addr_notifier) },
	{ 0x353e3fa5, __VMLINUX_SYMBOL_STR(__get_user_4) },
	{ 0x28a82da4, __VMLINUX_SYMBOL_STR(snmp_mib_init) },
	{ 0xe2fae716, __VMLINUX_SYMBOL_STR(kmemdup) },
	{ 0xa843805a, __VMLINUX_SYMBOL_STR(get_unused_fd_flags) },
	{ 0x33ba5cd4, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0x593a99b, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0x5ca46e99, __VMLINUX_SYMBOL_STR(inet_sendmsg) },
	{ 0x2c988955, __VMLINUX_SYMBOL_STR(prepare_to_wait_exclusive) },
	{ 0x1adaf33f, __VMLINUX_SYMBOL_STR(inet6_release) },
	{ 0xb0d888b, __VMLINUX_SYMBOL_STR(icmpv6_err_convert) },
	{ 0x7c08cb52, __VMLINUX_SYMBOL_STR(inet6_register_protosw) },
	{ 0x1ecbb142, __VMLINUX_SYMBOL_STR(inet_del_protocol) },
	{ 0xcc21964d, __VMLINUX_SYMBOL_STR(ip6_xmit) },
	{ 0xa43b9539, __VMLINUX_SYMBOL_STR(memcpy_fromiovecend) },
	{ 0xf2e604ec, __VMLINUX_SYMBOL_STR(sock_i_ino) },
	{ 0x6ad53559, __VMLINUX_SYMBOL_STR(inet6_getname) },
	{ 0x27000b29, __VMLINUX_SYMBOL_STR(crc32c) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x92c80041, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0xbca4357, __VMLINUX_SYMBOL_STR(sk_common_release) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0xc9ec4e21, __VMLINUX_SYMBOL_STR(free_percpu) },
	{ 0x594ff15d, __VMLINUX_SYMBOL_STR(skb_trim) },
	{ 0x972b3e57, __VMLINUX_SYMBOL_STR(inet_dgram_connect) },
	{ 0xde9360ba, __VMLINUX_SYMBOL_STR(totalram_pages) },
	{ 0xf79280bf, __VMLINUX_SYMBOL_STR(sock_common_recvmsg) },
	{ 0x55312da4, __VMLINUX_SYMBOL_STR(sock_no_sendpage) },
	{ 0x71bc64b4, __VMLINUX_SYMBOL_STR(__pskb_pull_tail) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0x89a4982e, __VMLINUX_SYMBOL_STR(sock_no_mmap) },
	{ 0x2fe252cc, __VMLINUX_SYMBOL_STR(unregister_inet6addr_notifier) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x97b69043, __VMLINUX_SYMBOL_STR(sock_no_socketpair) },
	{ 0x959fb115, __VMLINUX_SYMBOL_STR(ip6_dst_lookup_flow) },
	{ 0xdc8cb9d7, __VMLINUX_SYMBOL_STR(unregister_pernet_subsys) },
	{ 0xfec657f2, __VMLINUX_SYMBOL_STR(sk_alloc) },
	{ 0x890dc2ed, __VMLINUX_SYMBOL_STR(idr_alloc_cyclic) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x1f27cba8, __VMLINUX_SYMBOL_STR(single_open_net) },
	{ 0x37befc70, __VMLINUX_SYMBOL_STR(jiffies_to_msecs) },
	{ 0x1a1c496c, __VMLINUX_SYMBOL_STR(inet6_ioctl) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x63ed4bd7, __VMLINUX_SYMBOL_STR(inet_addr_type) },
	{ 0x285cbdae, __VMLINUX_SYMBOL_STR(lock_sock_nested) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0xd2936c14, __VMLINUX_SYMBOL_STR(ns_capable) },
	{ 0x9fba304c, __VMLINUX_SYMBOL_STR(sock_prot_inuse_add) },
	{ 0x7dccc294, __VMLINUX_SYMBOL_STR(proc_doulongvec_minmax) },
	{ 0x84b183ae, __VMLINUX_SYMBOL_STR(strncmp) },
	{ 0xd8525ea7, __VMLINUX_SYMBOL_STR(fl6_update_dst) },
	{ 0xa6590e4e, __VMLINUX_SYMBOL_STR(__sk_mem_reclaim) },
	{ 0x88b454fd, __VMLINUX_SYMBOL_STR(kmem_cache_free) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x5515ca7f, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0x1ea06663, __VMLINUX_SYMBOL_STR(_raw_write_lock) },
	{ 0x3834b570, __VMLINUX_SYMBOL_STR(proc_mkdir_data) },
	{ 0x84ffea8b, __VMLINUX_SYMBOL_STR(idr_preload) },
	{ 0xe937e5af, __VMLINUX_SYMBOL_STR(dev_get_by_index_rcu) },
	{ 0x98344d91, __VMLINUX_SYMBOL_STR(sock_wake_async) },
	{ 0xaa0675de, __VMLINUX_SYMBOL_STR(sk_free) },
	{ 0xd86c0353, __VMLINUX_SYMBOL_STR(inet_shutdown) },
	{ 0xf4406e45, __VMLINUX_SYMBOL_STR(inet_add_protocol) },
	{ 0x1118ff8b, __VMLINUX_SYMBOL_STR(seq_release_net) },
	{ 0x8834396c, __VMLINUX_SYMBOL_STR(mod_timer) },
	{ 0xbe2c0274, __VMLINUX_SYMBOL_STR(add_timer) },
	{ 0xa735db59, __VMLINUX_SYMBOL_STR(prandom_u32) },
	{ 0x5240ee7, __VMLINUX_SYMBOL_STR(percpu_counter_batch) },
	{ 0x7e394c4e, __VMLINUX_SYMBOL_STR(sysctl_local_reserved_ports) },
	{ 0xe40dc473, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0xfc8b84a4, __VMLINUX_SYMBOL_STR(init_net) },
	{ 0xb0ba5fa7, __VMLINUX_SYMBOL_STR(inet_accept) },
	{ 0x7a082438, __VMLINUX_SYMBOL_STR(fput) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0xeed3635b, __VMLINUX_SYMBOL_STR(proc_dostring) },
	{ 0x8d5da549, __VMLINUX_SYMBOL_STR(inet_ioctl) },
	{ 0xc59b8904, __VMLINUX_SYMBOL_STR(inet_ctl_sock_create) },
	{ 0xdf401846, __VMLINUX_SYMBOL_STR(idr_remove) },
	{ 0x9dabe8f6, __VMLINUX_SYMBOL_STR(__sock_recv_ts_and_drops) },
	{ 0x3ff62317, __VMLINUX_SYMBOL_STR(local_bh_disable) },
	{ 0x2babe81f, __VMLINUX_SYMBOL_STR(__wake_up_sync_key) },
	{ 0xe0816cce, __VMLINUX_SYMBOL_STR(skb_copy_expand) },
	{ 0x90e9ff51, __VMLINUX_SYMBOL_STR(proto_register) },
	{ 0xb0e93b81, __VMLINUX_SYMBOL_STR(kmem_cache_alloc) },
	{ 0xf1806da9, __VMLINUX_SYMBOL_STR(idr_find_slowpath) },
	{ 0xf6d4ed20, __VMLINUX_SYMBOL_STR(inet_release) },
	{ 0xbc10dd97, __VMLINUX_SYMBOL_STR(__put_user_4) },
	{ 0xc3e596f0, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0xfe029963, __VMLINUX_SYMBOL_STR(unregister_inetaddr_notifier) },
	{ 0xdf82a3b4, __VMLINUX_SYMBOL_STR(sk_release_kernel) },
	{ 0x93fca811, __VMLINUX_SYMBOL_STR(__get_free_pages) },
	{ 0xdd3916ac, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_bh) },
	{ 0x3bd1b1f6, __VMLINUX_SYMBOL_STR(msecs_to_jiffies) },
	{ 0xd62c833f, __VMLINUX_SYMBOL_STR(schedule_timeout) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0xcd08b124, __VMLINUX_SYMBOL_STR(proto_unregister) },
	{ 0x642cc58c, __VMLINUX_SYMBOL_STR(inet_getname) },
	{ 0x799aca4, __VMLINUX_SYMBOL_STR(local_bh_enable) },
	{ 0xaa38dc66, __VMLINUX_SYMBOL_STR(inet6_del_protocol) },
	{ 0x2b18d6e2, __VMLINUX_SYMBOL_STR(crypto_destroy_tfm) },
	{ 0xe410672d, __VMLINUX_SYMBOL_STR(inet_sock_destruct) },
	{ 0x337cce46, __VMLINUX_SYMBOL_STR(put_cmsg) },
	{ 0xd7cb77a9, __VMLINUX_SYMBOL_STR(register_pernet_subsys) },
	{ 0x3f4547a7, __VMLINUX_SYMBOL_STR(put_unused_fd) },
	{ 0x9c3737fc, __VMLINUX_SYMBOL_STR(__percpu_counter_init) },
	{ 0x750ee067, __VMLINUX_SYMBOL_STR(skb_copy_datagram_iovec) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0xe2dfda3e, __VMLINUX_SYMBOL_STR(sock_alloc_file) },
	{ 0x2a18c74, __VMLINUX_SYMBOL_STR(nf_conntrack_destroy) },
	{ 0xa9bd613e, __VMLINUX_SYMBOL_STR(ipv6_setsockopt) },
	{ 0x20dbf607, __VMLINUX_SYMBOL_STR(__sk_mem_schedule) },
	{ 0x88e43e81, __VMLINUX_SYMBOL_STR(kmem_cache_create) },
	{ 0xddde3c32, __VMLINUX_SYMBOL_STR(ip_route_output_flow) },
	{ 0x4302d0eb, __VMLINUX_SYMBOL_STR(free_pages) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0xf6ebc03b, __VMLINUX_SYMBOL_STR(net_ratelimit) },
	{ 0x49da4f9b, __VMLINUX_SYMBOL_STR(sock_common_setsockopt) },
	{ 0xf9141363, __VMLINUX_SYMBOL_STR(proc_create_data) },
	{ 0x275de30d, __VMLINUX_SYMBOL_STR(__xfrm_policy_check) },
	{ 0x1e047854, __VMLINUX_SYMBOL_STR(warn_slowpath_fmt) },
	{ 0x94b932f1, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0xefdd2345, __VMLINUX_SYMBOL_STR(sg_init_one) },
	{ 0xe11f3cbc, __VMLINUX_SYMBOL_STR(_raw_read_lock_bh) },
	{ 0xa0ea6ee, __VMLINUX_SYMBOL_STR(in6_dev_finish_destroy) },
	{ 0x1fcf4d4b, __VMLINUX_SYMBOL_STR(_raw_read_unlock_bh) },
	{ 0x114433ca, __VMLINUX_SYMBOL_STR(inet_register_protosw) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xbd084931, __VMLINUX_SYMBOL_STR(seq_open_net) },
	{ 0xa75312bc, __VMLINUX_SYMBOL_STR(call_rcu_sched) },
	{ 0xf9708ca0, __VMLINUX_SYMBOL_STR(fd_install) },
	{ 0x499cb58c, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0x9fb3dd30, __VMLINUX_SYMBOL_STR(memcpy_fromiovec) },
	{ 0x46b2add2, __VMLINUX_SYMBOL_STR(sock_create) },
	{ 0xe718f603, __VMLINUX_SYMBOL_STR(inet_bind) },
	{ 0xb46a09cd, __VMLINUX_SYMBOL_STR(sock_common_getsockopt) },
	{ 0x7a4497db, __VMLINUX_SYMBOL_STR(kzfree) },
	{ 0x1cfb04fa, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0xd435beb0, __VMLINUX_SYMBOL_STR(inet6_unregister_protosw) },
	{ 0x4cbbd171, __VMLINUX_SYMBOL_STR(__bitmap_weight) },
	{ 0x1cff016, __VMLINUX_SYMBOL_STR(skb_dequeue) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xe2e8065e, __VMLINUX_SYMBOL_STR(memdup_user) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0x20817409, __VMLINUX_SYMBOL_STR(inet6_bind) },
	{ 0x50d6202a, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0xa77a369d, __VMLINUX_SYMBOL_STR(idr_init) },
	{ 0xb6ed309c, __VMLINUX_SYMBOL_STR(register_net_sysctl) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x70b60936, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0x8dc1dfb8, __VMLINUX_SYMBOL_STR(ip_queue_xmit) },
	{ 0xf67f7196, __VMLINUX_SYMBOL_STR(crypto_alloc_base) },
	{ 0x9c273b30, __VMLINUX_SYMBOL_STR(sock_wfree) },
	{ 0x2fe31438, __VMLINUX_SYMBOL_STR(inet_unregister_protosw) },
	{ 0x27fa66e1, __VMLINUX_SYMBOL_STR(nr_free_buffer_pages) },
	{ 0xd542439, __VMLINUX_SYMBOL_STR(__ipv6_addr_type) },
	{ 0x475100c2, __VMLINUX_SYMBOL_STR(inet_get_local_port_range) },
	{ 0xfc70e345, __VMLINUX_SYMBOL_STR(sock_i_uid) },
	{ 0x51c86539, __VMLINUX_SYMBOL_STR(single_release_net) },
	{ 0x4cdb3178, __VMLINUX_SYMBOL_STR(ns_to_timeval) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

