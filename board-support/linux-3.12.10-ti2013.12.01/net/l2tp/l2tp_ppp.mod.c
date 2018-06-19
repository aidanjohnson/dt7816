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
	{ 0x5a021da6, __VMLINUX_SYMBOL_STR(l2tp_session_delete) },
	{ 0x89a4982e, __VMLINUX_SYMBOL_STR(sock_no_mmap) },
	{ 0xb4b148eb, __VMLINUX_SYMBOL_STR(sock_no_shutdown) },
	{ 0xff80103c, __VMLINUX_SYMBOL_STR(sock_no_listen) },
	{ 0x27148c08, __VMLINUX_SYMBOL_STR(pppox_ioctl) },
	{ 0x756b1899, __VMLINUX_SYMBOL_STR(datagram_poll) },
	{ 0x8d062cba, __VMLINUX_SYMBOL_STR(sock_no_accept) },
	{ 0x97b69043, __VMLINUX_SYMBOL_STR(sock_no_socketpair) },
	{ 0x71efa0c, __VMLINUX_SYMBOL_STR(sock_no_bind) },
	{ 0x1118ff8b, __VMLINUX_SYMBOL_STR(seq_release_net) },
	{ 0x92c80041, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0x94b932f1, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0x337f2432, __VMLINUX_SYMBOL_STR(l2tp_nl_unregister_ops) },
	{ 0x7fa72395, __VMLINUX_SYMBOL_STR(unregister_pernet_device) },
	{ 0xcd08b124, __VMLINUX_SYMBOL_STR(proto_unregister) },
	{ 0xe0ff7a18, __VMLINUX_SYMBOL_STR(unregister_pppox_proto) },
	{ 0x5689c003, __VMLINUX_SYMBOL_STR(l2tp_nl_register_ops) },
	{ 0xa98705ac, __VMLINUX_SYMBOL_STR(register_pppox_proto) },
	{ 0x90e9ff51, __VMLINUX_SYMBOL_STR(proto_register) },
	{ 0x74e0edeb, __VMLINUX_SYMBOL_STR(register_pernet_device) },
	{ 0xe40dc473, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0x71bc64b4, __VMLINUX_SYMBOL_STR(__pskb_pull_tail) },
	{ 0xd86c0353, __VMLINUX_SYMBOL_STR(inet_shutdown) },
	{ 0x3bd1b1f6, __VMLINUX_SYMBOL_STR(msecs_to_jiffies) },
	{ 0xdef4629d, __VMLINUX_SYMBOL_STR(udp_prot) },
	{ 0x7c8656e3, __VMLINUX_SYMBOL_STR(l2tp_session_find_nth) },
	{ 0x20971e6b, __VMLINUX_SYMBOL_STR(l2tp_session_free) },
	{ 0x37befc70, __VMLINUX_SYMBOL_STR(jiffies_to_msecs) },
	{ 0xd2ce469a, __VMLINUX_SYMBOL_STR(seq_puts) },
	{ 0x50fe832e, __VMLINUX_SYMBOL_STR(l2tp_udp_encap_recv) },
	{ 0xcc693ef5, __VMLINUX_SYMBOL_STR(l2tp_session_queue_purge) },
	{ 0x829b8501, __VMLINUX_SYMBOL_STR(__l2tp_session_unhash) },
	{ 0xa4efed60, __VMLINUX_SYMBOL_STR(skb_queue_purge) },
	{ 0x8bd0a3fd, __VMLINUX_SYMBOL_STR(_raw_write_unlock_bh) },
	{ 0x85061b76, __VMLINUX_SYMBOL_STR(_raw_write_lock_bh) },
	{ 0xe17f48b6, __VMLINUX_SYMBOL_STR(pppox_unbind_sock) },
	{ 0x867a18b, __VMLINUX_SYMBOL_STR(ppp_input) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x2a18c74, __VMLINUX_SYMBOL_STR(nf_conntrack_destroy) },
	{ 0xeb5af14d, __VMLINUX_SYMBOL_STR(__secpath_destroy) },
	{ 0xcf369001, __VMLINUX_SYMBOL_STR(release_sock) },
	{ 0x5d861571, __VMLINUX_SYMBOL_STR(ppp_register_net_channel) },
	{ 0x9700966d, __VMLINUX_SYMBOL_STR(dst_release) },
	{ 0x6fbedbe0, __VMLINUX_SYMBOL_STR(l2tp_tunnel_create) },
	{ 0x285cbdae, __VMLINUX_SYMBOL_STR(lock_sock_nested) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xd796878f, __VMLINUX_SYMBOL_STR(pskb_expand_head) },
	{ 0xc5ef064d, __VMLINUX_SYMBOL_STR(sock_wmalloc) },
	{ 0x799aca4, __VMLINUX_SYMBOL_STR(local_bh_enable) },
	{ 0x88c7f0fc, __VMLINUX_SYMBOL_STR(l2tp_xmit_skb) },
	{ 0x3ff62317, __VMLINUX_SYMBOL_STR(local_bh_disable) },
	{ 0x9fb3dd30, __VMLINUX_SYMBOL_STR(memcpy_fromiovec) },
	{ 0x70b60936, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x750ee067, __VMLINUX_SYMBOL_STR(skb_copy_datagram_iovec) },
	{ 0x2ffedab0, __VMLINUX_SYMBOL_STR(skb_recv_datagram) },
	{ 0x10137555, __VMLINUX_SYMBOL_STR(sock_init_data) },
	{ 0xfec657f2, __VMLINUX_SYMBOL_STR(sk_alloc) },
	{ 0x353e3fa5, __VMLINUX_SYMBOL_STR(__get_user_4) },
	{ 0xbc10dd97, __VMLINUX_SYMBOL_STR(__put_user_4) },
	{ 0x67c2fa54, __VMLINUX_SYMBOL_STR(__copy_to_user) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xfbc74f64, __VMLINUX_SYMBOL_STR(__copy_from_user) },
	{ 0xaa0675de, __VMLINUX_SYMBOL_STR(sk_free) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xabf89cad, __VMLINUX_SYMBOL_STR(l2tp_session_create) },
	{ 0xc02ac571, __VMLINUX_SYMBOL_STR(l2tp_session_find) },
	{ 0xe1f95329, __VMLINUX_SYMBOL_STR(l2tp_tunnel_find) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xf9141363, __VMLINUX_SYMBOL_STR(proc_create_data) },
	{ 0xb9552ea, __VMLINUX_SYMBOL_STR(l2tp_tunnel_find_nth) },
	{ 0x2247cba2, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0x4d7328ae, __VMLINUX_SYMBOL_STR(ppp_dev_name) },
	{ 0xbd084931, __VMLINUX_SYMBOL_STR(seq_open_net) },
	{ 0x688c3c76, __VMLINUX_SYMBOL_STR(remove_proc_entry) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=l2tp_core,pppox,l2tp_netlink,ppp_generic";


MODULE_INFO(srcversion, "02E8DEEAD4E2AA6132C1B50");
