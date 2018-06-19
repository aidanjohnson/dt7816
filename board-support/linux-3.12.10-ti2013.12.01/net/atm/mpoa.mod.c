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
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xfbc74f64, __VMLINUX_SYMBOL_STR(__copy_from_user) },
	{ 0xaf35eaf4, __VMLINUX_SYMBOL_STR(vcc_insert_socket) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xc996d097, __VMLINUX_SYMBOL_STR(del_timer) },
	{ 0xdde0b0af, __VMLINUX_SYMBOL_STR(seq_open) },
	{ 0x5902f53f, __VMLINUX_SYMBOL_STR(deregister_atm_ioctl) },
	{ 0xa6822854, __VMLINUX_SYMBOL_STR(dev_get_by_name) },
	{ 0xd0e1dffc, __VMLINUX_SYMBOL_STR(register_atm_ioctl) },
	{ 0x2247cba2, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0xd2da1048, __VMLINUX_SYMBOL_STR(register_netdevice_notifier) },
	{ 0x688c3c76, __VMLINUX_SYMBOL_STR(remove_proc_entry) },
	{ 0x4443d399, __VMLINUX_SYMBOL_STR(atm_proc_root) },
	{ 0xe2fae716, __VMLINUX_SYMBOL_STR(kmemdup) },
	{ 0x593a99b, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0x28118cb6, __VMLINUX_SYMBOL_STR(__get_user_1) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x3474c0aa, __VMLINUX_SYMBOL_STR(skb_realloc_headroom) },
	{ 0xae5b6ab0, __VMLINUX_SYMBOL_STR(vcc_release_async) },
	{ 0x92c80041, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x9d0d6206, __VMLINUX_SYMBOL_STR(unregister_netdevice_notifier) },
	{ 0xfcd5641, __VMLINUX_SYMBOL_STR(netif_rx) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x20c55ae0, __VMLINUX_SYMBOL_STR(sscanf) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0x84b183ae, __VMLINUX_SYMBOL_STR(strncmp) },
	{ 0x5515ca7f, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0xbe2c0274, __VMLINUX_SYMBOL_STR(add_timer) },
	{ 0xe40dc473, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0xfc8b84a4, __VMLINUX_SYMBOL_STR(init_net) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0xe2ea17e8, __VMLINUX_SYMBOL_STR(dev_kfree_skb_any) },
	{ 0xfd6293c2, __VMLINUX_SYMBOL_STR(boot_tvec_bases) },
	{ 0xbca31af2, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0x7783bae2, __VMLINUX_SYMBOL_STR(skb_queue_tail) },
	{ 0xc6cbbc89, __VMLINUX_SYMBOL_STR(capable) },
	{ 0x2e7be112, __VMLINUX_SYMBOL_STR(_raw_read_lock_irqsave) },
	{ 0xc3e596f0, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0x93fca811, __VMLINUX_SYMBOL_STR(__get_free_pages) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x746f15cf, __VMLINUX_SYMBOL_STR(eth_type_trans) },
	{ 0xd41fe818, __VMLINUX_SYMBOL_STR(_raw_read_unlock_irqrestore) },
	{ 0x2aa1ad41, __VMLINUX_SYMBOL_STR(_raw_write_lock_irq) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x74971a96, __VMLINUX_SYMBOL_STR(__module_get) },
	{ 0x4302d0eb, __VMLINUX_SYMBOL_STR(free_pages) },
	{ 0x8bd0a3fd, __VMLINUX_SYMBOL_STR(_raw_write_unlock_bh) },
	{ 0x4f68e5c9, __VMLINUX_SYMBOL_STR(do_gettimeofday) },
	{ 0xf9141363, __VMLINUX_SYMBOL_STR(proc_create_data) },
	{ 0x94b932f1, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0xe11f3cbc, __VMLINUX_SYMBOL_STR(_raw_read_lock_bh) },
	{ 0x1fcf4d4b, __VMLINUX_SYMBOL_STR(_raw_read_unlock_bh) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x85061b76, __VMLINUX_SYMBOL_STR(_raw_write_lock_bh) },
	{ 0x1cff016, __VMLINUX_SYMBOL_STR(skb_dequeue) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xb9c81fa6, __VMLINUX_SYMBOL_STR(seq_release) },
	{ 0x70b60936, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0x51749fc8, __VMLINUX_SYMBOL_STR(_raw_read_lock_irq) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=atm";

