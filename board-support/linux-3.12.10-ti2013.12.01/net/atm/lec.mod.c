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
	{ 0xbe73d5f1, __VMLINUX_SYMBOL_STR(seq_release_private) },
	{ 0x92c80041, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0x94b932f1, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0xf680cb71, __VMLINUX_SYMBOL_STR(unregister_netdev) },
	{ 0x5902f53f, __VMLINUX_SYMBOL_STR(deregister_atm_ioctl) },
	{ 0x688c3c76, __VMLINUX_SYMBOL_STR(remove_proc_entry) },
	{ 0x4443d399, __VMLINUX_SYMBOL_STR(atm_proc_root) },
	{ 0xd0e1dffc, __VMLINUX_SYMBOL_STR(register_atm_ioctl) },
	{ 0xf9141363, __VMLINUX_SYMBOL_STR(proc_create_data) },
	{ 0x70b60936, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0xe0816cce, __VMLINUX_SYMBOL_STR(skb_copy_expand) },
	{ 0x5515ca7f, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0x3474c0aa, __VMLINUX_SYMBOL_STR(skb_realloc_headroom) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x6b06fdce, __VMLINUX_SYMBOL_STR(delayed_work_timer_fn) },
	{ 0xbe2c0274, __VMLINUX_SYMBOL_STR(add_timer) },
	{ 0xfbc74f64, __VMLINUX_SYMBOL_STR(__copy_from_user) },
	{ 0x74971a96, __VMLINUX_SYMBOL_STR(__module_get) },
	{ 0xaf35eaf4, __VMLINUX_SYMBOL_STR(vcc_insert_socket) },
	{ 0xe94f1e83, __VMLINUX_SYMBOL_STR(free_netdev) },
	{ 0xd87c2198, __VMLINUX_SYMBOL_STR(register_netdev) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xcf636b9e, __VMLINUX_SYMBOL_STR(alloc_etherdev_mqs) },
	{ 0xc6cbbc89, __VMLINUX_SYMBOL_STR(capable) },
	{ 0x55e7a41a, __VMLINUX_SYMBOL_STR(br_fdb_test_addr_hook) },
	{ 0xf724ee1, __VMLINUX_SYMBOL_STR(dev_set_mtu) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x593a99b, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xf29942b3, __VMLINUX_SYMBOL_STR(seq_putc) },
	{ 0x2247cba2, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0xd2ce469a, __VMLINUX_SYMBOL_STR(seq_puts) },
	{ 0x61526098, __VMLINUX_SYMBOL_STR(seq_open_private) },
	{ 0xfcd5641, __VMLINUX_SYMBOL_STR(netif_rx) },
	{ 0x746f15cf, __VMLINUX_SYMBOL_STR(eth_type_trans) },
	{ 0xe40dc473, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0xe851bb05, __VMLINUX_SYMBOL_STR(queue_delayed_work_on) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xbca31af2, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0x1cff016, __VMLINUX_SYMBOL_STR(skb_dequeue) },
	{ 0x50d6202a, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0xd5f2172f, __VMLINUX_SYMBOL_STR(del_timer_sync) },
	{ 0x24d7b4eb, __VMLINUX_SYMBOL_STR(cancel_delayed_work_sync) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xe2fae716, __VMLINUX_SYMBOL_STR(kmemdup) },
	{ 0x8834396c, __VMLINUX_SYMBOL_STR(mod_timer) },
	{ 0x7783bae2, __VMLINUX_SYMBOL_STR(skb_queue_tail) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xc3e596f0, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xa4efed60, __VMLINUX_SYMBOL_STR(skb_queue_purge) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0xc996d097, __VMLINUX_SYMBOL_STR(del_timer) },
	{ 0xae5b6ab0, __VMLINUX_SYMBOL_STR(vcc_release_async) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x36026fb7, __VMLINUX_SYMBOL_STR(__netif_schedule) },
	{ 0x2a3aa678, __VMLINUX_SYMBOL_STR(_test_and_clear_bit) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=atm";

