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
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x2bae5008, __VMLINUX_SYMBOL_STR(can_rx_register) },
	{ 0xf88dd612, __VMLINUX_SYMBOL_STR(single_open) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xccbfe1a2, __VMLINUX_SYMBOL_STR(hrtimer_forward) },
	{ 0xaa0c066b, __VMLINUX_SYMBOL_STR(sock_no_setsockopt) },
	{ 0x4898fdd9, __VMLINUX_SYMBOL_STR(sock_no_getsockopt) },
	{ 0x4cd9d440, __VMLINUX_SYMBOL_STR(single_release) },
	{ 0x7840b42c, __VMLINUX_SYMBOL_STR(hrtimer_cancel) },
	{ 0x47939e0d, __VMLINUX_SYMBOL_STR(__tasklet_hi_schedule) },
	{ 0x80a0002f, __VMLINUX_SYMBOL_STR(can_proto_unregister) },
	{ 0x2247cba2, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0xd2da1048, __VMLINUX_SYMBOL_STR(register_netdevice_notifier) },
	{ 0x9cb47ce8, __VMLINUX_SYMBOL_STR(sock_no_getname) },
	{ 0xc87c1f84, __VMLINUX_SYMBOL_STR(ktime_get) },
	{ 0x688c3c76, __VMLINUX_SYMBOL_STR(remove_proc_entry) },
	{ 0x32516f50, __VMLINUX_SYMBOL_STR(sock_queue_rcv_skb) },
	{ 0x2ffedab0, __VMLINUX_SYMBOL_STR(skb_recv_datagram) },
	{ 0xf2e604ec, __VMLINUX_SYMBOL_STR(sock_i_ino) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x92c80041, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0x9d0d6206, __VMLINUX_SYMBOL_STR(unregister_netdevice_notifier) },
	{ 0x55312da4, __VMLINUX_SYMBOL_STR(sock_no_sendpage) },
	{ 0x89a4982e, __VMLINUX_SYMBOL_STR(sock_no_mmap) },
	{ 0xbbcbd046, __VMLINUX_SYMBOL_STR(PDE_DATA) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x97b69043, __VMLINUX_SYMBOL_STR(sock_no_socketpair) },
	{ 0x3e300a64, __VMLINUX_SYMBOL_STR(proc_mkdir) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x71efa0c, __VMLINUX_SYMBOL_STR(sock_no_bind) },
	{ 0x285cbdae, __VMLINUX_SYMBOL_STR(lock_sock_nested) },
	{ 0xfaef0ed, __VMLINUX_SYMBOL_STR(__tasklet_schedule) },
	{ 0xf29942b3, __VMLINUX_SYMBOL_STR(seq_putc) },
	{ 0xff80103c, __VMLINUX_SYMBOL_STR(sock_no_listen) },
	{ 0x8d062cba, __VMLINUX_SYMBOL_STR(sock_no_accept) },
	{ 0xe937e5af, __VMLINUX_SYMBOL_STR(dev_get_by_index_rcu) },
	{ 0xaa0675de, __VMLINUX_SYMBOL_STR(sk_free) },
	{ 0x17a66c39, __VMLINUX_SYMBOL_STR(dev_get_by_index) },
	{ 0x9545af6d, __VMLINUX_SYMBOL_STR(tasklet_init) },
	{ 0xfc8b84a4, __VMLINUX_SYMBOL_STR(init_net) },
	{ 0xb4b148eb, __VMLINUX_SYMBOL_STR(sock_no_shutdown) },
	{ 0x82072614, __VMLINUX_SYMBOL_STR(tasklet_kill) },
	{ 0xf4119bf6, __VMLINUX_SYMBOL_STR(can_ioctl) },
	{ 0x7da66c8d, __VMLINUX_SYMBOL_STR(can_send) },
	{ 0x9dabe8f6, __VMLINUX_SYMBOL_STR(__sock_recv_ts_and_drops) },
	{ 0x9ceb163c, __VMLINUX_SYMBOL_STR(memcpy_toiovec) },
	{ 0xc3e596f0, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0x756b1899, __VMLINUX_SYMBOL_STR(datagram_poll) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x94e1823c, __VMLINUX_SYMBOL_STR(hrtimer_start) },
	{ 0x98458689, __VMLINUX_SYMBOL_STR(can_proto_register) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x8bd0a3fd, __VMLINUX_SYMBOL_STR(_raw_write_unlock_bh) },
	{ 0xf9141363, __VMLINUX_SYMBOL_STR(proc_create_data) },
	{ 0x94b932f1, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x9fb3dd30, __VMLINUX_SYMBOL_STR(memcpy_fromiovec) },
	{ 0xfc3bd35, __VMLINUX_SYMBOL_STR(hrtimer_init) },
	{ 0x85061b76, __VMLINUX_SYMBOL_STR(_raw_write_lock_bh) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xe5a3cf98, __VMLINUX_SYMBOL_STR(can_rx_unregister) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0x70b60936, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
	{ 0x17b10c5, __VMLINUX_SYMBOL_STR(skb_free_datagram) },
	{ 0x4cdb3178, __VMLINUX_SYMBOL_STR(ns_to_timeval) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=can";

