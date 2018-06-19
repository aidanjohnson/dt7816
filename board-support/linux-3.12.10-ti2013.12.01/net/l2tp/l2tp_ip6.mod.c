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
	{ 0x1858caa3, __VMLINUX_SYMBOL_STR(inet_unhash) },
	{ 0x77a65690, __VMLINUX_SYMBOL_STR(inet_hash) },
	{ 0x4b993e46, __VMLINUX_SYMBOL_STR(ipv6_getsockopt) },
	{ 0xa9bd613e, __VMLINUX_SYMBOL_STR(ipv6_setsockopt) },
	{ 0xcee5f56a, __VMLINUX_SYMBOL_STR(udp_ioctl) },
	{ 0x55312da4, __VMLINUX_SYMBOL_STR(sock_no_sendpage) },
	{ 0x89a4982e, __VMLINUX_SYMBOL_STR(sock_no_mmap) },
	{ 0xf79280bf, __VMLINUX_SYMBOL_STR(sock_common_recvmsg) },
	{ 0x5ca46e99, __VMLINUX_SYMBOL_STR(inet_sendmsg) },
	{ 0xb46a09cd, __VMLINUX_SYMBOL_STR(sock_common_getsockopt) },
	{ 0x49da4f9b, __VMLINUX_SYMBOL_STR(sock_common_setsockopt) },
	{ 0xd86c0353, __VMLINUX_SYMBOL_STR(inet_shutdown) },
	{ 0xff80103c, __VMLINUX_SYMBOL_STR(sock_no_listen) },
	{ 0x1a1c496c, __VMLINUX_SYMBOL_STR(inet6_ioctl) },
	{ 0x756b1899, __VMLINUX_SYMBOL_STR(datagram_poll) },
	{ 0x8d062cba, __VMLINUX_SYMBOL_STR(sock_no_accept) },
	{ 0x97b69043, __VMLINUX_SYMBOL_STR(sock_no_socketpair) },
	{ 0x972b3e57, __VMLINUX_SYMBOL_STR(inet_dgram_connect) },
	{ 0x20817409, __VMLINUX_SYMBOL_STR(inet6_bind) },
	{ 0x1adaf33f, __VMLINUX_SYMBOL_STR(inet6_release) },
	{ 0xaa38dc66, __VMLINUX_SYMBOL_STR(inet6_del_protocol) },
	{ 0xd435beb0, __VMLINUX_SYMBOL_STR(inet6_unregister_protosw) },
	{ 0xcd08b124, __VMLINUX_SYMBOL_STR(proto_unregister) },
	{ 0x7c08cb52, __VMLINUX_SYMBOL_STR(inet6_register_protosw) },
	{ 0xb46351a0, __VMLINUX_SYMBOL_STR(inet6_add_protocol) },
	{ 0x90e9ff51, __VMLINUX_SYMBOL_STR(proto_register) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x369de012, __VMLINUX_SYMBOL_STR(ipv6_chk_addr) },
	{ 0xe937e5af, __VMLINUX_SYMBOL_STR(dev_get_by_index_rcu) },
	{ 0x2098973, __VMLINUX_SYMBOL_STR(sk_receive_skb) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x2a18c74, __VMLINUX_SYMBOL_STR(nf_conntrack_destroy) },
	{ 0x275de30d, __VMLINUX_SYMBOL_STR(__xfrm_policy_check) },
	{ 0x1fcf4d4b, __VMLINUX_SYMBOL_STR(_raw_read_unlock_bh) },
	{ 0xe11f3cbc, __VMLINUX_SYMBOL_STR(_raw_read_lock_bh) },
	{ 0xe1f95329, __VMLINUX_SYMBOL_STR(l2tp_tunnel_find) },
	{ 0xdde5f255, __VMLINUX_SYMBOL_STR(l2tp_recv_common) },
	{ 0x34908c14, __VMLINUX_SYMBOL_STR(print_hex_dump_bytes) },
	{ 0xc02ac571, __VMLINUX_SYMBOL_STR(l2tp_session_find) },
	{ 0x71bc64b4, __VMLINUX_SYMBOL_STR(__pskb_pull_tail) },
	{ 0xfc8b84a4, __VMLINUX_SYMBOL_STR(init_net) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x799aca4, __VMLINUX_SYMBOL_STR(local_bh_enable) },
	{ 0x3ff62317, __VMLINUX_SYMBOL_STR(local_bh_disable) },
	{ 0x32516f50, __VMLINUX_SYMBOL_STR(sock_queue_rcv_skb) },
	{ 0xbca4357, __VMLINUX_SYMBOL_STR(sk_common_release) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x10008442, __VMLINUX_SYMBOL_STR(ip6_datagram_connect) },
	{ 0x2c857a85, __VMLINUX_SYMBOL_STR(udp_disconnect) },
	{ 0x79e4c178, __VMLINUX_SYMBOL_STR(inet6_destroy_sock) },
	{ 0x3de318ca, __VMLINUX_SYMBOL_STR(l2tp_tunnel_closeall) },
	{ 0xaa0675de, __VMLINUX_SYMBOL_STR(sk_free) },
	{ 0x5a39fb9, __VMLINUX_SYMBOL_STR(ip_generic_getfrag) },
	{ 0x9700966d, __VMLINUX_SYMBOL_STR(dst_release) },
	{ 0xcf369001, __VMLINUX_SYMBOL_STR(release_sock) },
	{ 0x1e78994d, __VMLINUX_SYMBOL_STR(ip6_push_pending_frames) },
	{ 0xd819b2fa, __VMLINUX_SYMBOL_STR(ip6_flush_pending_frames) },
	{ 0x9d40d4b5, __VMLINUX_SYMBOL_STR(ip6_append_data) },
	{ 0x285cbdae, __VMLINUX_SYMBOL_STR(lock_sock_nested) },
	{ 0x2f512d52, __VMLINUX_SYMBOL_STR(ip6_dst_hoplimit) },
	{ 0x959fb115, __VMLINUX_SYMBOL_STR(ip6_dst_lookup_flow) },
	{ 0x2deda4a1, __VMLINUX_SYMBOL_STR(security_sk_classify_flow) },
	{ 0xd8525ea7, __VMLINUX_SYMBOL_STR(fl6_update_dst) },
	{ 0x58413099, __VMLINUX_SYMBOL_STR(ipv6_fixup_options) },
	{ 0x1f3779b4, __VMLINUX_SYMBOL_STR(fl6_merge_options) },
	{ 0x2749c427, __VMLINUX_SYMBOL_STR(ip6_datagram_send_ctl) },
	{ 0x4d4c731f, __VMLINUX_SYMBOL_STR(fl6_sock_lookup) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x17b10c5, __VMLINUX_SYMBOL_STR(skb_free_datagram) },
	{ 0x4e088532, __VMLINUX_SYMBOL_STR(ip6_datagram_recv_ctl) },
	{ 0xa20639b7, __VMLINUX_SYMBOL_STR(__sock_recv_wifi_status) },
	{ 0xfb763117, __VMLINUX_SYMBOL_STR(__sock_recv_timestamp) },
	{ 0x750ee067, __VMLINUX_SYMBOL_STR(skb_copy_datagram_iovec) },
	{ 0x2ffedab0, __VMLINUX_SYMBOL_STR(skb_recv_datagram) },
	{ 0x1be3315b, __VMLINUX_SYMBOL_STR(ipv6_recv_error) },
	{ 0x8bd0a3fd, __VMLINUX_SYMBOL_STR(_raw_write_unlock_bh) },
	{ 0x85061b76, __VMLINUX_SYMBOL_STR(_raw_write_lock_bh) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xd542439, __VMLINUX_SYMBOL_STR(__ipv6_addr_type) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=l2tp_core";


MODULE_INFO(srcversion, "3E932FFB347C0DF1D11F97D");
