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
	{ 0x7e341a6e, __VMLINUX_SYMBOL_STR(cdev_del) },
	{ 0x10137555, __VMLINUX_SYMBOL_STR(sock_init_data) },
	{ 0xc0802028, __VMLINUX_SYMBOL_STR(cdev_init) },
	{ 0x41efcd32, __VMLINUX_SYMBOL_STR(__skb_gso_segment) },
	{ 0xa8fe760b, __VMLINUX_SYMBOL_STR(macvlan_dellink) },
	{ 0x67c2fa54, __VMLINUX_SYMBOL_STR(__copy_to_user) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x65383ea3, __VMLINUX_SYMBOL_STR(skb_flow_dissect) },
	{ 0xc8b57c27, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0xc7a4fbed, __VMLINUX_SYMBOL_STR(rtnl_lock) },
	{ 0xbdb70c71, __VMLINUX_SYMBOL_STR(zerocopy_sg_from_iovec) },
	{ 0x1f8f5fc1, __VMLINUX_SYMBOL_STR(no_llseek) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0x7934dc49, __VMLINUX_SYMBOL_STR(macvlan_common_newlink) },
	{ 0x2a3aa678, __VMLINUX_SYMBOL_STR(_test_and_clear_bit) },
	{ 0xd2da1048, __VMLINUX_SYMBOL_STR(register_netdevice_notifier) },
	{ 0x13de81b5, __VMLINUX_SYMBOL_STR(device_destroy) },
	{ 0x353e3fa5, __VMLINUX_SYMBOL_STR(__get_user_4) },
	{ 0xd7357b0d, __VMLINUX_SYMBOL_STR(sock_alloc_send_pskb) },
	{ 0x7ce3e591, __VMLINUX_SYMBOL_STR(macvlan_link_register) },
	{ 0xf9c367e0, __VMLINUX_SYMBOL_STR(iov_pages) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x7485e15e, __VMLINUX_SYMBOL_STR(unregister_chrdev_region) },
	{ 0xa43b9539, __VMLINUX_SYMBOL_STR(memcpy_fromiovecend) },
	{ 0x711e5cc6, __VMLINUX_SYMBOL_STR(skb_partial_csum_set) },
	{ 0x9d0d6206, __VMLINUX_SYMBOL_STR(unregister_netdevice_notifier) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xa4efed60, __VMLINUX_SYMBOL_STR(skb_queue_purge) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xfec657f2, __VMLINUX_SYMBOL_STR(sk_alloc) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x210d8549, __VMLINUX_SYMBOL_STR(class_unregister) },
	{ 0x9e2000a7, __VMLINUX_SYMBOL_STR(memcpy_toiovecend) },
	{ 0x5515ca7f, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xa680257a, __VMLINUX_SYMBOL_STR(skb_copy_datagram_const_iovec) },
	{ 0xc668ae36, __VMLINUX_SYMBOL_STR(__skb_get_rxhash) },
	{ 0xaa0675de, __VMLINUX_SYMBOL_STR(sk_free) },
	{ 0xddf26bab, __VMLINUX_SYMBOL_STR(device_create) },
	{ 0xc2cdbf1, __VMLINUX_SYMBOL_STR(synchronize_sched) },
	{ 0xf74dae0f, __VMLINUX_SYMBOL_STR(idr_alloc) },
	{ 0xab4aa62b, __VMLINUX_SYMBOL_STR(rtnl_link_unregister) },
	{ 0x9e8ea120, __VMLINUX_SYMBOL_STR(macvlan_start_xmit) },
	{ 0xdf401846, __VMLINUX_SYMBOL_STR(idr_remove) },
	{ 0x572e9cc8, __VMLINUX_SYMBOL_STR(cdev_add) },
	{ 0x7783bae2, __VMLINUX_SYMBOL_STR(skb_queue_tail) },
	{ 0x3ff62317, __VMLINUX_SYMBOL_STR(local_bh_disable) },
	{ 0xf1806da9, __VMLINUX_SYMBOL_STR(idr_find_slowpath) },
	{ 0xbc10dd97, __VMLINUX_SYMBOL_STR(__put_user_4) },
	{ 0x5eee69c5, __VMLINUX_SYMBOL_STR(macvlan_common_setup) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x6b2dc060, __VMLINUX_SYMBOL_STR(dump_stack) },
	{ 0x799aca4, __VMLINUX_SYMBOL_STR(local_bh_enable) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x499cb58c, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0xb9acd3d9, __VMLINUX_SYMBOL_STR(__put_user_2) },
	{ 0x1cfb04fa, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x1cff016, __VMLINUX_SYMBOL_STR(skb_dequeue) },
	{ 0x95dbe078, __VMLINUX_SYMBOL_STR(__get_user_2) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0xbf2b601e, __VMLINUX_SYMBOL_STR(skb_copy_datagram_from_iovec) },
	{ 0xf3f92cf8, __VMLINUX_SYMBOL_STR(netdev_update_features) },
	{ 0x85670f1d, __VMLINUX_SYMBOL_STR(rtnl_is_locked) },
	{ 0x70b60936, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0x8666a173, __VMLINUX_SYMBOL_STR(__class_create) },
	{ 0x6e720ff2, __VMLINUX_SYMBOL_STR(rtnl_unlock) },
	{ 0x29537c9e, __VMLINUX_SYMBOL_STR(alloc_chrdev_region) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=macvlan";

