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
	{ 0xf3017e21, __VMLINUX_SYMBOL_STR(dccp_statistics) },
	{ 0x82856b93, __VMLINUX_SYMBOL_STR(dccp_init_sock) },
	{ 0x5f14d21a, __VMLINUX_SYMBOL_STR(__kfree_skb) },
	{ 0x2838895c, __VMLINUX_SYMBOL_STR(dccp_v4_do_rcv) },
	{ 0xf6b72020, __VMLINUX_SYMBOL_STR(inet6_csk_update_pmtu) },
	{ 0xf658eff2, __VMLINUX_SYMBOL_STR(sk_filter) },
	{ 0xb5ddb023, __VMLINUX_SYMBOL_STR(dccp_set_state) },
	{ 0x8a90cdad, __VMLINUX_SYMBOL_STR(inet6_csk_bind_conflict) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x4b993e46, __VMLINUX_SYMBOL_STR(ipv6_getsockopt) },
	{ 0x1858caa3, __VMLINUX_SYMBOL_STR(inet_unhash) },
	{ 0x9f1ec650, __VMLINUX_SYMBOL_STR(inet_twsk_put) },
	{ 0x2a07688c, __VMLINUX_SYMBOL_STR(dccp_hashinfo) },
	{ 0xb46351a0, __VMLINUX_SYMBOL_STR(inet6_add_protocol) },
	{ 0x96645a56, __VMLINUX_SYMBOL_STR(inet6_lookup_listener) },
	{ 0xc1782359, __VMLINUX_SYMBOL_STR(dccp_sendmsg) },
	{ 0x23ee97e6, __VMLINUX_SYMBOL_STR(ipv6_opt_accepted) },
	{ 0x5237da88, __VMLINUX_SYMBOL_STR(sk_setup_caps) },
	{ 0x42b00eba, __VMLINUX_SYMBOL_STR(dccp_ctl_make_reset) },
	{ 0x6b5335a7, __VMLINUX_SYMBOL_STR(dccp_destroy_sock) },
	{ 0xb6efeeb4, __VMLINUX_SYMBOL_STR(dccp_make_response) },
	{ 0x9700966d, __VMLINUX_SYMBOL_STR(dst_release) },
	{ 0xb2038f57, __VMLINUX_SYMBOL_STR(skb_clone) },
	{ 0xbff0ab48, __VMLINUX_SYMBOL_STR(dccp_rcv_established) },
	{ 0x841a461, __VMLINUX_SYMBOL_STR(inet6_csk_search_req) },
	{ 0xb81cc3a6, __VMLINUX_SYMBOL_STR(dccp_v4_conn_request) },
	{ 0x3de55af6, __VMLINUX_SYMBOL_STR(inet_csk_prepare_forced_close) },
	{ 0x1d67862b, __VMLINUX_SYMBOL_STR(dccp_create_openreq_child) },
	{ 0x523f5753, __VMLINUX_SYMBOL_STR(ipv6_dup_options) },
	{ 0x1170f9b, __VMLINUX_SYMBOL_STR(dccp_check_req) },
	{ 0x5ca46e99, __VMLINUX_SYMBOL_STR(inet_sendmsg) },
	{ 0x1adaf33f, __VMLINUX_SYMBOL_STR(inet6_release) },
	{ 0xb0d888b, __VMLINUX_SYMBOL_STR(icmpv6_err_convert) },
	{ 0x7c08cb52, __VMLINUX_SYMBOL_STR(inet6_register_protosw) },
	{ 0xf9c97411, __VMLINUX_SYMBOL_STR(dccp_recvmsg) },
	{ 0xcc21964d, __VMLINUX_SYMBOL_STR(ip6_xmit) },
	{ 0x485c6f35, __VMLINUX_SYMBOL_STR(inet_sk_rebuild_header) },
	{ 0x6ad53559, __VMLINUX_SYMBOL_STR(inet6_getname) },
	{ 0xaa2654ba, __VMLINUX_SYMBOL_STR(sock_rfree) },
	{ 0x10d57764, __VMLINUX_SYMBOL_STR(inet6_csk_xmit) },
	{ 0x28f42224, __VMLINUX_SYMBOL_STR(__inet6_hash) },
	{ 0xbba2e2ab, __VMLINUX_SYMBOL_STR(dccp_ioctl) },
	{ 0xa3c52474, __VMLINUX_SYMBOL_STR(dccp_setsockopt) },
	{ 0xf79280bf, __VMLINUX_SYMBOL_STR(sock_common_recvmsg) },
	{ 0x55312da4, __VMLINUX_SYMBOL_STR(sock_no_sendpage) },
	{ 0x6b5e8d81, __VMLINUX_SYMBOL_STR(dccp_child_process) },
	{ 0x89a4982e, __VMLINUX_SYMBOL_STR(sock_no_mmap) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x97b69043, __VMLINUX_SYMBOL_STR(sock_no_socketpair) },
	{ 0xa0658c45, __VMLINUX_SYMBOL_STR(skb_checksum) },
	{ 0x959fb115, __VMLINUX_SYMBOL_STR(ip6_dst_lookup_flow) },
	{ 0xdc8cb9d7, __VMLINUX_SYMBOL_STR(unregister_pernet_subsys) },
	{ 0xb044ede7, __VMLINUX_SYMBOL_STR(__inet6_lookup_established) },
	{ 0xa2a34eb0, __VMLINUX_SYMBOL_STR(dccp_v4_request_recv_sock) },
	{ 0x678f91b6, __VMLINUX_SYMBOL_STR(dccp_parse_options) },
	{ 0x37a73873, __VMLINUX_SYMBOL_STR(dccp_getsockopt) },
	{ 0xa5871670, __VMLINUX_SYMBOL_STR(inet6_csk_reqsk_queue_hash_add) },
	{ 0x2deda4a1, __VMLINUX_SYMBOL_STR(security_sk_classify_flow) },
	{ 0x1a1c496c, __VMLINUX_SYMBOL_STR(inet6_ioctl) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x44f0b164, __VMLINUX_SYMBOL_STR(inet_csk_delete_keepalive_timer) },
	{ 0x4d4c731f, __VMLINUX_SYMBOL_STR(fl6_sock_lookup) },
	{ 0xd8525ea7, __VMLINUX_SYMBOL_STR(fl6_update_dst) },
	{ 0x88b454fd, __VMLINUX_SYMBOL_STR(kmem_cache_free) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x1ea06663, __VMLINUX_SYMBOL_STR(_raw_write_lock) },
	{ 0x77b3e039, __VMLINUX_SYMBOL_STR(dccp_reqsk_init) },
	{ 0x5ca18ad9, __VMLINUX_SYMBOL_STR(dccp_close) },
	{ 0xaa0675de, __VMLINUX_SYMBOL_STR(sk_free) },
	{ 0xd86c0353, __VMLINUX_SYMBOL_STR(inet_shutdown) },
	{ 0x9a123b7, __VMLINUX_SYMBOL_STR(dccp_orphan_count) },
	{ 0x2913ac9d, __VMLINUX_SYMBOL_STR(dccp_sync_mss) },
	{ 0xa20ce1b8, __VMLINUX_SYMBOL_STR(net_msg_warn) },
	{ 0x698da4a2, __VMLINUX_SYMBOL_STR(inet6_hash_connect) },
	{ 0xb0ba5fa7, __VMLINUX_SYMBOL_STR(inet_accept) },
	{ 0x2ebe4bd5, __VMLINUX_SYMBOL_STR(inet_csk_get_port) },
	{ 0x73eca7c9, __VMLINUX_SYMBOL_STR(dccp_death_row) },
	{ 0xc59b8904, __VMLINUX_SYMBOL_STR(inet_ctl_sock_create) },
	{ 0x5f31360e, __VMLINUX_SYMBOL_STR(dccp_poll) },
	{ 0x77a65690, __VMLINUX_SYMBOL_STR(inet_hash) },
	{ 0x3ff62317, __VMLINUX_SYMBOL_STR(local_bh_disable) },
	{ 0x90e9ff51, __VMLINUX_SYMBOL_STR(proto_register) },
	{ 0xe9739ae8, __VMLINUX_SYMBOL_STR(dccp_disconnect) },
	{ 0xb0e93b81, __VMLINUX_SYMBOL_STR(kmem_cache_alloc) },
	{ 0x46058283, __VMLINUX_SYMBOL_STR(__sk_dst_check) },
	{ 0xcdd38334, __VMLINUX_SYMBOL_STR(dccp_done) },
	{ 0xdf82a3b4, __VMLINUX_SYMBOL_STR(sk_release_kernel) },
	{ 0x9bdf77b9, __VMLINUX_SYMBOL_STR(dccp_v4_send_check) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0xcd08b124, __VMLINUX_SYMBOL_STR(proto_unregister) },
	{ 0x59710510, __VMLINUX_SYMBOL_STR(inet_stream_connect) },
	{ 0x317b7903, __VMLINUX_SYMBOL_STR(dccp_invalid_packet) },
	{ 0x799aca4, __VMLINUX_SYMBOL_STR(local_bh_enable) },
	{ 0xaa38dc66, __VMLINUX_SYMBOL_STR(inet6_del_protocol) },
	{ 0xd7cb77a9, __VMLINUX_SYMBOL_STR(register_pernet_subsys) },
	{ 0x7ad402ee, __VMLINUX_SYMBOL_STR(inet6_lookup) },
	{ 0x4cdd391d, __VMLINUX_SYMBOL_STR(dccp_feat_list_purge) },
	{ 0x8396ed95, __VMLINUX_SYMBOL_STR(dccp_syn_ack_timeout) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x2098973, __VMLINUX_SYMBOL_STR(sk_receive_skb) },
	{ 0xa9bd613e, __VMLINUX_SYMBOL_STR(ipv6_setsockopt) },
	{ 0xf6ebc03b, __VMLINUX_SYMBOL_STR(net_ratelimit) },
	{ 0x49da4f9b, __VMLINUX_SYMBOL_STR(sock_common_setsockopt) },
	{ 0xf8e9c35f, __VMLINUX_SYMBOL_STR(inet6_sk_rebuild_header) },
	{ 0x275de30d, __VMLINUX_SYMBOL_STR(__xfrm_policy_check) },
	{ 0x44da5d0f, __VMLINUX_SYMBOL_STR(__csum_ipv6_magic) },
	{ 0xae729e59, __VMLINUX_SYMBOL_STR(security_req_classify_flow) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xe1761617, __VMLINUX_SYMBOL_STR(security_inet_conn_request) },
	{ 0xa797a7af, __VMLINUX_SYMBOL_STR(inet_dccp_listen) },
	{ 0x7663a323, __VMLINUX_SYMBOL_STR(__inet_inherit_port) },
	{ 0xb46a09cd, __VMLINUX_SYMBOL_STR(sock_common_getsockopt) },
	{ 0xe200f872, __VMLINUX_SYMBOL_STR(secure_dccpv6_sequence_number) },
	{ 0xd435beb0, __VMLINUX_SYMBOL_STR(inet6_unregister_protosw) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x47cd208d, __VMLINUX_SYMBOL_STR(inet_csk_accept) },
	{ 0x20817409, __VMLINUX_SYMBOL_STR(inet6_bind) },
	{ 0x96d73cdb, __VMLINUX_SYMBOL_STR(dccp_reqsk_send_ack) },
	{ 0x1488da67, __VMLINUX_SYMBOL_STR(dccp_rcv_state_process) },
	{ 0x50d6202a, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0x69f2aa02, __VMLINUX_SYMBOL_STR(dccp_connect) },
	{ 0x7db4a8ce, __VMLINUX_SYMBOL_STR(dccp_shutdown) },
	{ 0x8dc1dfb8, __VMLINUX_SYMBOL_STR(ip_queue_xmit) },
	{ 0x8a2d3244, __VMLINUX_SYMBOL_STR(dccp_v4_connect) },
	{ 0xd542439, __VMLINUX_SYMBOL_STR(__ipv6_addr_type) },
	{ 0x2abc6b67, __VMLINUX_SYMBOL_STR(inet6_csk_addr2sockaddr) },
	{ 0x79e4c178, __VMLINUX_SYMBOL_STR(inet6_destroy_sock) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=dccp,dccp_ipv4";
