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
	{ 0x89a4982e, __VMLINUX_SYMBOL_STR(sock_no_mmap) },
	{ 0x76bcd188, __VMLINUX_SYMBOL_STR(sock_no_recvmsg) },
	{ 0x49c86bad, __VMLINUX_SYMBOL_STR(sock_no_sendmsg) },
	{ 0x4898fdd9, __VMLINUX_SYMBOL_STR(sock_no_getsockopt) },
	{ 0xaa0c066b, __VMLINUX_SYMBOL_STR(sock_no_setsockopt) },
	{ 0xb4b148eb, __VMLINUX_SYMBOL_STR(sock_no_shutdown) },
	{ 0xff80103c, __VMLINUX_SYMBOL_STR(sock_no_listen) },
	{ 0x27148c08, __VMLINUX_SYMBOL_STR(pppox_ioctl) },
	{ 0xc48bc00b, __VMLINUX_SYMBOL_STR(sock_no_poll) },
	{ 0x8d062cba, __VMLINUX_SYMBOL_STR(sock_no_accept) },
	{ 0x97b69043, __VMLINUX_SYMBOL_STR(sock_no_socketpair) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xe0ff7a18, __VMLINUX_SYMBOL_STR(unregister_pppox_proto) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0xbe294aa4, __VMLINUX_SYMBOL_STR(gre_del_protocol) },
	{ 0xcd08b124, __VMLINUX_SYMBOL_STR(proto_unregister) },
	{ 0xa98705ac, __VMLINUX_SYMBOL_STR(register_pppox_proto) },
	{ 0x90e9ff51, __VMLINUX_SYMBOL_STR(proto_register) },
	{ 0x9b63100b, __VMLINUX_SYMBOL_STR(gre_add_protocol) },
	{ 0x40a9b349, __VMLINUX_SYMBOL_STR(vzalloc) },
	{ 0x867a18b, __VMLINUX_SYMBOL_STR(ppp_input) },
	{ 0x32516f50, __VMLINUX_SYMBOL_STR(sock_queue_rcv_skb) },
	{ 0xa4efed60, __VMLINUX_SYMBOL_STR(skb_queue_purge) },
	{ 0xaa0675de, __VMLINUX_SYMBOL_STR(sk_free) },
	{ 0x8bd0a3fd, __VMLINUX_SYMBOL_STR(_raw_write_unlock_bh) },
	{ 0x85061b76, __VMLINUX_SYMBOL_STR(_raw_write_lock_bh) },
	{ 0xe17f48b6, __VMLINUX_SYMBOL_STR(pppox_unbind_sock) },
	{ 0xc2cdbf1, __VMLINUX_SYMBOL_STR(synchronize_sched) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0x2d6507b5, __VMLINUX_SYMBOL_STR(_find_next_zero_bit_le) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0xcf369001, __VMLINUX_SYMBOL_STR(release_sock) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x2a17fd47, __VMLINUX_SYMBOL_STR(ppp_register_channel) },
	{ 0x5237da88, __VMLINUX_SYMBOL_STR(sk_setup_caps) },
	{ 0x2deda4a1, __VMLINUX_SYMBOL_STR(security_sk_classify_flow) },
	{ 0x285cbdae, __VMLINUX_SYMBOL_STR(lock_sock_nested) },
	{ 0xd3f57a2, __VMLINUX_SYMBOL_STR(_find_next_bit_le) },
	{ 0xf6388c56, __VMLINUX_SYMBOL_STR(sysctl_ip_default_ttl) },
	{ 0x9c273b30, __VMLINUX_SYMBOL_STR(sock_wfree) },
	{ 0x83e60378, __VMLINUX_SYMBOL_STR(ip_local_out) },
	{ 0x2124474, __VMLINUX_SYMBOL_STR(ip_send_check) },
	{ 0x592cbcc0, __VMLINUX_SYMBOL_STR(__ip_select_ident) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5515ca7f, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0xe40dc473, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0x50d6202a, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0x3474c0aa, __VMLINUX_SYMBOL_STR(skb_realloc_headroom) },
	{ 0xddde3c32, __VMLINUX_SYMBOL_STR(ip_route_output_flow) },
	{ 0x10137555, __VMLINUX_SYMBOL_STR(sock_init_data) },
	{ 0xfec657f2, __VMLINUX_SYMBOL_STR(sk_alloc) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x2098973, __VMLINUX_SYMBOL_STR(sk_receive_skb) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x2a18c74, __VMLINUX_SYMBOL_STR(nf_conntrack_destroy) },
	{ 0x9700966d, __VMLINUX_SYMBOL_STR(dst_release) },
	{ 0x71bc64b4, __VMLINUX_SYMBOL_STR(__pskb_pull_tail) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x353e3fa5, __VMLINUX_SYMBOL_STR(__get_user_4) },
	{ 0xbc10dd97, __VMLINUX_SYMBOL_STR(__put_user_4) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=pppox,gre,ppp_generic";

