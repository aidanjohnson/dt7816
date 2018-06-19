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
	{ 0xb64de2d, __VMLINUX_SYMBOL_STR(kmem_cache_destroy) },
	{ 0xee7a85cb, __VMLINUX_SYMBOL_STR(rds_trans_register) },
	{ 0x4bc2a92b, __VMLINUX_SYMBOL_STR(kernel_sendmsg) },
	{ 0x2d71500e, __VMLINUX_SYMBOL_STR(sock_create_lite) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xd7c3a815, __VMLINUX_SYMBOL_STR(rds_connect_complete) },
	{ 0x7272c3c8, __VMLINUX_SYMBOL_STR(cpu_online_mask) },
	{ 0xe883861, __VMLINUX_SYMBOL_STR(sock_release) },
	{ 0x7b6646bb, __VMLINUX_SYMBOL_STR(_raw_read_lock) },
	{ 0xb2038f57, __VMLINUX_SYMBOL_STR(skb_clone) },
	{ 0x50cbe7b3, __VMLINUX_SYMBOL_STR(rds_stats) },
	{ 0xd3f57a2, __VMLINUX_SYMBOL_STR(_find_next_bit_le) },
	{ 0x418bef25, __VMLINUX_SYMBOL_STR(rds_conn_create) },
	{ 0xb4f630d0, __VMLINUX_SYMBOL_STR(rds_recv_incoming) },
	{ 0x2c6c11a8, __VMLINUX_SYMBOL_STR(rds_inc_init) },
	{ 0x71bc64b4, __VMLINUX_SYMBOL_STR(__pskb_pull_tail) },
	{ 0xfe7c4287, __VMLINUX_SYMBOL_STR(nr_cpu_ids) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xa4efed60, __VMLINUX_SYMBOL_STR(skb_queue_purge) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x63ed4bd7, __VMLINUX_SYMBOL_STR(inet_addr_type) },
	{ 0x285cbdae, __VMLINUX_SYMBOL_STR(lock_sock_nested) },
	{ 0xdce3364f, __VMLINUX_SYMBOL_STR(rds_info_register_func) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0x88b454fd, __VMLINUX_SYMBOL_STR(kmem_cache_free) },
	{ 0x4b46dd7c, __VMLINUX_SYMBOL_STR(rds_inc_put) },
	{ 0x96fafe85, __VMLINUX_SYMBOL_STR(rds_stats_info_copy) },
	{ 0xc2dab779, __VMLINUX_SYMBOL_STR(rds_info_copy) },
	{ 0x4137cff, __VMLINUX_SYMBOL_STR(rds_send_drop_acked) },
	{ 0xfc8b84a4, __VMLINUX_SYMBOL_STR(init_net) },
	{ 0x42160169, __VMLINUX_SYMBOL_STR(flush_workqueue) },
	{ 0xf15f38eb, __VMLINUX_SYMBOL_STR(rds_conn_destroy) },
	{ 0x7783bae2, __VMLINUX_SYMBOL_STR(skb_queue_tail) },
	{ 0xb0e93b81, __VMLINUX_SYMBOL_STR(kmem_cache_alloc) },
	{ 0xe851bb05, __VMLINUX_SYMBOL_STR(queue_delayed_work_on) },
	{ 0xa467af, __VMLINUX_SYMBOL_STR(rds_wq) },
	{ 0x3507a132, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irq) },
	{ 0x750ee067, __VMLINUX_SYMBOL_STR(skb_copy_datagram_iovec) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x1176e07f, __VMLINUX_SYMBOL_STR(__per_cpu_offset) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x88e43e81, __VMLINUX_SYMBOL_STR(kmem_cache_create) },
	{ 0x8bd0a3fd, __VMLINUX_SYMBOL_STR(_raw_write_unlock_bh) },
	{ 0xb412a22, __VMLINUX_SYMBOL_STR(rds_info_deregister_func) },
	{ 0xd7cd63d6, __VMLINUX_SYMBOL_STR(___pskb_trim) },
	{ 0x77edcea7, __VMLINUX_SYMBOL_STR(rds_trans_unregister) },
	{ 0x46b2add2, __VMLINUX_SYMBOL_STR(sock_create) },
	{ 0x85061b76, __VMLINUX_SYMBOL_STR(_raw_write_lock_bh) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0xff924d9c, __VMLINUX_SYMBOL_STR(skb_copy_bits) },
	{ 0x730750a8, __VMLINUX_SYMBOL_STR(tcp_read_sock) },
	{ 0x438840ec, __VMLINUX_SYMBOL_STR(rds_conn_drop) },
	{ 0xc642cc2c, __VMLINUX_SYMBOL_STR(rds_cong_map_updated) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=rds";

