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
	{ 0xcf369001, __VMLINUX_SYMBOL_STR(release_sock) },
	{ 0x10137555, __VMLINUX_SYMBOL_STR(sock_init_data) },
	{ 0x5f14d21a, __VMLINUX_SYMBOL_STR(__kfree_skb) },
	{ 0x67c2fa54, __VMLINUX_SYMBOL_STR(__copy_to_user) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xc996d097, __VMLINUX_SYMBOL_STR(del_timer) },
	{ 0x27f15ec9, __VMLINUX_SYMBOL_STR(from_kuid_munged) },
	{ 0xea918ac3, __VMLINUX_SYMBOL_STR(dev_getbyhwaddr_rcu) },
	{ 0xdde0b0af, __VMLINUX_SYMBOL_STR(seq_open) },
	{ 0xc8b57c27, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0x2512642c, __VMLINUX_SYMBOL_STR(unregister_net_sysctl_table) },
	{ 0xd2ce469a, __VMLINUX_SYMBOL_STR(seq_puts) },
	{ 0xa1d55e90, __VMLINUX_SYMBOL_STR(_raw_spin_lock_bh) },
	{ 0xb2038f57, __VMLINUX_SYMBOL_STR(skb_clone) },
	{ 0x2247cba2, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0x688c3c76, __VMLINUX_SYMBOL_STR(remove_proc_entry) },
	{ 0x32516f50, __VMLINUX_SYMBOL_STR(sock_queue_rcv_skb) },
	{ 0x353e3fa5, __VMLINUX_SYMBOL_STR(__get_user_4) },
	{ 0x593a99b, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0xaa2654ba, __VMLINUX_SYMBOL_STR(sock_rfree) },
	{ 0x92c80041, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x55312da4, __VMLINUX_SYMBOL_STR(sock_no_sendpage) },
	{ 0x89a4982e, __VMLINUX_SYMBOL_STR(sock_no_mmap) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xb274114a, __VMLINUX_SYMBOL_STR(sk_wait_data) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xa4efed60, __VMLINUX_SYMBOL_STR(skb_queue_purge) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x97b69043, __VMLINUX_SYMBOL_STR(sock_no_socketpair) },
	{ 0xe0c93b4c, __VMLINUX_SYMBOL_STR(llc_set_station_handler) },
	{ 0x3e300a64, __VMLINUX_SYMBOL_STR(proc_mkdir) },
	{ 0xfec657f2, __VMLINUX_SYMBOL_STR(sk_alloc) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x285cbdae, __VMLINUX_SYMBOL_STR(lock_sock_nested) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0xd2936c14, __VMLINUX_SYMBOL_STR(ns_capable) },
	{ 0x52d7b2fd, __VMLINUX_SYMBOL_STR(llc_sap_list) },
	{ 0xb6851a3b, __VMLINUX_SYMBOL_STR(llc_mac_hdr_init) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x5515ca7f, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0xe937e5af, __VMLINUX_SYMBOL_STR(dev_get_by_index_rcu) },
	{ 0xaa0675de, __VMLINUX_SYMBOL_STR(sk_free) },
	{ 0x17a66c39, __VMLINUX_SYMBOL_STR(dev_get_by_index) },
	{ 0x8834396c, __VMLINUX_SYMBOL_STR(mod_timer) },
	{ 0x38b92846, __VMLINUX_SYMBOL_STR(llc_remove_pack) },
	{ 0xc599e294, __VMLINUX_SYMBOL_STR(llc_sap_find) },
	{ 0xfc8b84a4, __VMLINUX_SYMBOL_STR(init_net) },
	{ 0x51404dc5, __VMLINUX_SYMBOL_STR(llc_add_pack) },
	{ 0x7783bae2, __VMLINUX_SYMBOL_STR(skb_queue_tail) },
	{ 0x3ff62317, __VMLINUX_SYMBOL_STR(local_bh_disable) },
	{ 0x90e9ff51, __VMLINUX_SYMBOL_STR(proto_register) },
	{ 0xbc10dd97, __VMLINUX_SYMBOL_STR(__put_user_4) },
	{ 0xc3e596f0, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0xdd3916ac, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_bh) },
	{ 0x756b1899, __VMLINUX_SYMBOL_STR(datagram_poll) },
	{ 0x8f69f72e, __VMLINUX_SYMBOL_STR(sock_register) },
	{ 0xd62c833f, __VMLINUX_SYMBOL_STR(schedule_timeout) },
	{ 0x3b1d462a, __VMLINUX_SYMBOL_STR(dev_getfirstbyhwtype) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0xcd08b124, __VMLINUX_SYMBOL_STR(proto_unregister) },
	{ 0x799aca4, __VMLINUX_SYMBOL_STR(local_bh_enable) },
	{ 0xe736e7e7, __VMLINUX_SYMBOL_STR(sock_alloc_send_skb) },
	{ 0x337cce46, __VMLINUX_SYMBOL_STR(put_cmsg) },
	{ 0x750ee067, __VMLINUX_SYMBOL_STR(skb_copy_datagram_iovec) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x538a854c, __VMLINUX_SYMBOL_STR(llc_sap_open) },
	{ 0xf6ebc03b, __VMLINUX_SYMBOL_STR(net_ratelimit) },
	{ 0x8bd0a3fd, __VMLINUX_SYMBOL_STR(_raw_write_unlock_bh) },
	{ 0xf9141363, __VMLINUX_SYMBOL_STR(proc_create_data) },
	{ 0x94b932f1, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x499cb58c, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0x62737e1d, __VMLINUX_SYMBOL_STR(sock_unregister) },
	{ 0x9fb3dd30, __VMLINUX_SYMBOL_STR(memcpy_fromiovec) },
	{ 0x85061b76, __VMLINUX_SYMBOL_STR(_raw_write_lock_bh) },
	{ 0x1cfb04fa, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x1cff016, __VMLINUX_SYMBOL_STR(skb_dequeue) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xb9c81fa6, __VMLINUX_SYMBOL_STR(seq_release) },
	{ 0xbfcc2c6b, __VMLINUX_SYMBOL_STR(llc_sap_close) },
	{ 0xc11126ee, __VMLINUX_SYMBOL_STR(dev_queue_xmit) },
	{ 0xb6ed309c, __VMLINUX_SYMBOL_STR(register_net_sysctl) },
	{ 0x70b60936, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0x7a069348, __VMLINUX_SYMBOL_STR(llc_build_and_send_ui_pkt) },
	{ 0x9cf1b46, __VMLINUX_SYMBOL_STR(proc_dointvec_jiffies) },
	{ 0x9c273b30, __VMLINUX_SYMBOL_STR(sock_wfree) },
	{ 0xfc70e345, __VMLINUX_SYMBOL_STR(sock_i_uid) },
	{ 0xda10ec3, __VMLINUX_SYMBOL_STR(security_sock_graft) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=llc";

