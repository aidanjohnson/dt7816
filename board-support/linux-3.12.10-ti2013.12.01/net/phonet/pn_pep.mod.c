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
	{ 0xfd128d57, __VMLINUX_SYMBOL_STR(skb_queue_head) },
	{ 0xcf369001, __VMLINUX_SYMBOL_STR(release_sock) },
	{ 0x10137555, __VMLINUX_SYMBOL_STR(sock_init_data) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xc8b57c27, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0x7f11bf9b, __VMLINUX_SYMBOL_STR(pn_sock_unhash) },
	{ 0xa842ca0d, __VMLINUX_SYMBOL_STR(sk_stream_wait_connect) },
	{ 0x2a3aa678, __VMLINUX_SYMBOL_STR(_test_and_clear_bit) },
	{ 0x94ee05c8, __VMLINUX_SYMBOL_STR(netif_carrier_off) },
	{ 0x32516f50, __VMLINUX_SYMBOL_STR(sock_queue_rcv_skb) },
	{ 0x353e3fa5, __VMLINUX_SYMBOL_STR(__get_user_4) },
	{ 0x2ffedab0, __VMLINUX_SYMBOL_STR(skb_recv_datagram) },
	{ 0xdfc7be31, __VMLINUX_SYMBOL_STR(pn_sock_hash) },
	{ 0xdd486f2, __VMLINUX_SYMBOL_STR(phonet_proto_register) },
	{ 0xaa2654ba, __VMLINUX_SYMBOL_STR(sock_rfree) },
	{ 0xbca4357, __VMLINUX_SYMBOL_STR(sk_common_release) },
	{ 0x63a326ef, __VMLINUX_SYMBOL_STR(__netdev_alloc_skb) },
	{ 0xfcd5641, __VMLINUX_SYMBOL_STR(netif_rx) },
	{ 0xde49ad6a, __VMLINUX_SYMBOL_STR(pn_sock_get_port) },
	{ 0x71bc64b4, __VMLINUX_SYMBOL_STR(__pskb_pull_tail) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xa4efed60, __VMLINUX_SYMBOL_STR(skb_queue_purge) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xfec657f2, __VMLINUX_SYMBOL_STR(sk_alloc) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x285cbdae, __VMLINUX_SYMBOL_STR(lock_sock_nested) },
	{ 0xe94f1e83, __VMLINUX_SYMBOL_STR(free_netdev) },
	{ 0xd87c2198, __VMLINUX_SYMBOL_STR(register_netdev) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x5515ca7f, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0xaa0675de, __VMLINUX_SYMBOL_STR(sk_free) },
	{ 0xa20ce1b8, __VMLINUX_SYMBOL_STR(net_msg_warn) },
	{ 0x7783bae2, __VMLINUX_SYMBOL_STR(skb_queue_tail) },
	{ 0xc6cbbc89, __VMLINUX_SYMBOL_STR(capable) },
	{ 0xbc10dd97, __VMLINUX_SYMBOL_STR(__put_user_4) },
	{ 0xc3e596f0, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0xd62c833f, __VMLINUX_SYMBOL_STR(schedule_timeout) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0xfb4628f9, __VMLINUX_SYMBOL_STR(alloc_netdev_mqs) },
	{ 0xe736e7e7, __VMLINUX_SYMBOL_STR(sock_alloc_send_skb) },
	{ 0x765210b2, __VMLINUX_SYMBOL_STR(phonet_proto_unregister) },
	{ 0x750ee067, __VMLINUX_SYMBOL_STR(skb_copy_datagram_iovec) },
	{ 0x2098973, __VMLINUX_SYMBOL_STR(sk_receive_skb) },
	{ 0xf6ebc03b, __VMLINUX_SYMBOL_STR(net_ratelimit) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x499cb58c, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0x9fb3dd30, __VMLINUX_SYMBOL_STR(memcpy_fromiovec) },
	{ 0xabb7b22d, __VMLINUX_SYMBOL_STR(pn_skb_send) },
	{ 0x1cfb04fa, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x1cff016, __VMLINUX_SYMBOL_STR(skb_dequeue) },
	{ 0xf680cb71, __VMLINUX_SYMBOL_STR(unregister_netdev) },
	{ 0x2f27d5ae, __VMLINUX_SYMBOL_STR(phonet_stream_ops) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0x36026fb7, __VMLINUX_SYMBOL_STR(__netif_schedule) },
	{ 0x50d6202a, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0x70b60936, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0x9c273b30, __VMLINUX_SYMBOL_STR(sock_wfree) },
	{ 0xff924d9c, __VMLINUX_SYMBOL_STR(skb_copy_bits) },
	{ 0x17b10c5, __VMLINUX_SYMBOL_STR(skb_free_datagram) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=phonet";

