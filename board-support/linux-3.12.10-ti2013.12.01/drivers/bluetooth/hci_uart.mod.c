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
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0xfd128d57, __VMLINUX_SYMBOL_STR(skb_queue_head) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x84767764, __VMLINUX_SYMBOL_STR(hci_recv_stream_fragment) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xc996d097, __VMLINUX_SYMBOL_STR(del_timer) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0xaf8d5f9, __VMLINUX_SYMBOL_STR(hci_register_dev) },
	{ 0xca150a51, __VMLINUX_SYMBOL_STR(tty_unthrottle) },
	{ 0x2a3aa678, __VMLINUX_SYMBOL_STR(_test_and_clear_bit) },
	{ 0x4205ad24, __VMLINUX_SYMBOL_STR(cancel_work_sync) },
	{ 0x33ba5cd4, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0x593a99b, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0x43d05fa0, __VMLINUX_SYMBOL_STR(hci_recv_frame) },
	{ 0xebcbcaea, __VMLINUX_SYMBOL_STR(hci_unregister_dev) },
	{ 0xa120d33c, __VMLINUX_SYMBOL_STR(tty_unregister_ldisc) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x594ff15d, __VMLINUX_SYMBOL_STR(skb_trim) },
	{ 0xb61a0c3b, __VMLINUX_SYMBOL_STR(bt_err) },
	{ 0x7c640527, __VMLINUX_SYMBOL_STR(bt_info) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xa4efed60, __VMLINUX_SYMBOL_STR(skb_queue_purge) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0xd1b63571, __VMLINUX_SYMBOL_STR(tty_ldisc_flush) },
	{ 0x6d0e42fc, __VMLINUX_SYMBOL_STR(n_tty_ioctl_helper) },
	{ 0xec49f3c8, __VMLINUX_SYMBOL_STR(hci_alloc_dev) },
	{ 0x5515ca7f, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0x8834396c, __VMLINUX_SYMBOL_STR(mod_timer) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0xe40dc473, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0x7783bae2, __VMLINUX_SYMBOL_STR(skb_queue_tail) },
	{ 0xc3e596f0, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0xa49bbc9c, __VMLINUX_SYMBOL_STR(tty_driver_flush_buffer) },
	{ 0x3bd1b1f6, __VMLINUX_SYMBOL_STR(msecs_to_jiffies) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x215ebd78, __VMLINUX_SYMBOL_STR(bitrev16) },
	{ 0x1cff016, __VMLINUX_SYMBOL_STR(skb_dequeue) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0x21f30159, __VMLINUX_SYMBOL_STR(hci_free_dev) },
	{ 0xadd8c681, __VMLINUX_SYMBOL_STR(tty_register_ldisc) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x70b60936, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x112e6f60, __VMLINUX_SYMBOL_STR(tty_set_termios) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=bluetooth";


MODULE_INFO(srcversion, "2BDC8A19A265817808B3C49");
