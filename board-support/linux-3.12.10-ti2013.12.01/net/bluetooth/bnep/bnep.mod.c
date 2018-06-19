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
	{ 0x10137555, __VMLINUX_SYMBOL_STR(sock_init_data) },
	{ 0xfbc74f64, __VMLINUX_SYMBOL_STR(__copy_from_user) },
	{ 0x22e1ae6f, __VMLINUX_SYMBOL_STR(up_read) },
	{ 0x4bc2a92b, __VMLINUX_SYMBOL_STR(kernel_sendmsg) },
	{ 0x3267ede7, __VMLINUX_SYMBOL_STR(sockfd_lookup) },
	{ 0x67c2fa54, __VMLINUX_SYMBOL_STR(__copy_to_user) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xaa0c066b, __VMLINUX_SYMBOL_STR(sock_no_setsockopt) },
	{ 0x4898fdd9, __VMLINUX_SYMBOL_STR(sock_no_getsockopt) },
	{ 0x4c86184b, __VMLINUX_SYMBOL_STR(remove_wait_queue) },
	{ 0x4d763937, __VMLINUX_SYMBOL_STR(eth_change_mtu) },
	{ 0x2a3aa678, __VMLINUX_SYMBOL_STR(_test_and_clear_bit) },
	{ 0x9cb47ce8, __VMLINUX_SYMBOL_STR(sock_no_getname) },
	{ 0x33ba5cd4, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0xbdca2aea, __VMLINUX_SYMBOL_STR(bt_sock_register) },
	{ 0xbd59f360, __VMLINUX_SYMBOL_STR(kthread_create_on_node) },
	{ 0xc48bc00b, __VMLINUX_SYMBOL_STR(sock_no_poll) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x455293f6, __VMLINUX_SYMBOL_STR(down_read) },
	{ 0xb61a0c3b, __VMLINUX_SYMBOL_STR(bt_err) },
	{ 0x7c640527, __VMLINUX_SYMBOL_STR(bt_info) },
	{ 0x71bc64b4, __VMLINUX_SYMBOL_STR(__pskb_pull_tail) },
	{ 0x89a4982e, __VMLINUX_SYMBOL_STR(sock_no_mmap) },
	{ 0xffd5a395, __VMLINUX_SYMBOL_STR(default_wake_function) },
	{ 0x76bcd188, __VMLINUX_SYMBOL_STR(sock_no_recvmsg) },
	{ 0x9f90e5cb, __VMLINUX_SYMBOL_STR(bt_sock_unlink) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xde5dcfc2, __VMLINUX_SYMBOL_STR(hci_get_route) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x5bc60d2f, __VMLINUX_SYMBOL_STR(netif_rx_ni) },
	{ 0x97b69043, __VMLINUX_SYMBOL_STR(sock_no_socketpair) },
	{ 0xfec657f2, __VMLINUX_SYMBOL_STR(sk_alloc) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x71efa0c, __VMLINUX_SYMBOL_STR(sock_no_bind) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0xcc1fb551, __VMLINUX_SYMBOL_STR(baswap) },
	{ 0xe94f1e83, __VMLINUX_SYMBOL_STR(free_netdev) },
	{ 0xd87c2198, __VMLINUX_SYMBOL_STR(register_netdev) },
	{ 0xff80103c, __VMLINUX_SYMBOL_STR(sock_no_listen) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x8d062cba, __VMLINUX_SYMBOL_STR(sock_no_accept) },
	{ 0xaa0675de, __VMLINUX_SYMBOL_STR(sk_free) },
	{ 0x8fea24bd, __VMLINUX_SYMBOL_STR(bt_sock_unregister) },
	{ 0xe40dc473, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0x83211609, __VMLINUX_SYMBOL_STR(up_write) },
	{ 0xfc8b84a4, __VMLINUX_SYMBOL_STR(init_net) },
	{ 0xa958ed4, __VMLINUX_SYMBOL_STR(down_write) },
	{ 0x7a082438, __VMLINUX_SYMBOL_STR(fput) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0xb4b148eb, __VMLINUX_SYMBOL_STR(sock_no_shutdown) },
	{ 0x61651be, __VMLINUX_SYMBOL_STR(strcat) },
	{ 0x4986e229, __VMLINUX_SYMBOL_STR(bt_sock_link) },
	{ 0xbca31af2, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0x7783bae2, __VMLINUX_SYMBOL_STR(skb_queue_tail) },
	{ 0xc6cbbc89, __VMLINUX_SYMBOL_STR(capable) },
	{ 0x90e9ff51, __VMLINUX_SYMBOL_STR(proto_register) },
	{ 0xc3e596f0, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0x63d684c9, __VMLINUX_SYMBOL_STR(put_device) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0xcd08b124, __VMLINUX_SYMBOL_STR(proto_unregister) },
	{ 0xfb4628f9, __VMLINUX_SYMBOL_STR(alloc_netdev_mqs) },
	{ 0x746f15cf, __VMLINUX_SYMBOL_STR(eth_type_trans) },
	{ 0x11a118b9, __VMLINUX_SYMBOL_STR(__module_put_and_exit) },
	{ 0x26021bc4, __VMLINUX_SYMBOL_STR(wake_up_process) },
	{ 0xf1ef0fc0, __VMLINUX_SYMBOL_STR(ether_setup) },
	{ 0x74971a96, __VMLINUX_SYMBOL_STR(__module_get) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x42550473, __VMLINUX_SYMBOL_STR(sock_no_connect) },
	{ 0x8bd0a3fd, __VMLINUX_SYMBOL_STR(_raw_write_unlock_bh) },
	{ 0xd63271fb, __VMLINUX_SYMBOL_STR(eth_validate_addr) },
	{ 0xc7bcbc8d, __VMLINUX_SYMBOL_STR(add_wait_queue) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xb7b61546, __VMLINUX_SYMBOL_STR(crc32_be) },
	{ 0x49c86bad, __VMLINUX_SYMBOL_STR(sock_no_sendmsg) },
	{ 0x7734e841, __VMLINUX_SYMBOL_STR(set_user_nice) },
	{ 0x85061b76, __VMLINUX_SYMBOL_STR(_raw_write_lock_bh) },
	{ 0xd5b15371, __VMLINUX_SYMBOL_STR(bt_procfs_init) },
	{ 0x1cff016, __VMLINUX_SYMBOL_STR(skb_dequeue) },
	{ 0xf680cb71, __VMLINUX_SYMBOL_STR(unregister_netdev) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0x36026fb7, __VMLINUX_SYMBOL_STR(__netif_schedule) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0xd80a62a2, __VMLINUX_SYMBOL_STR(bt_procfs_cleanup) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=bluetooth";


MODULE_INFO(srcversion, "9A67591FF670B4767494C8C");
