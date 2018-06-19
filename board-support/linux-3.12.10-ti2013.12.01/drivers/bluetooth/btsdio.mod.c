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
	{ 0xd6f52eb1, __VMLINUX_SYMBOL_STR(sdio_unregister_driver) },
	{ 0x377db316, __VMLINUX_SYMBOL_STR(sdio_register_driver) },
	{ 0x7c640527, __VMLINUX_SYMBOL_STR(bt_info) },
	{ 0x1cff016, __VMLINUX_SYMBOL_STR(skb_dequeue) },
	{ 0xfd128d57, __VMLINUX_SYMBOL_STR(skb_queue_head) },
	{ 0xe40dc473, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0xca24564a, __VMLINUX_SYMBOL_STR(sdio_writesb) },
	{ 0x5515ca7f, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0x43d05fa0, __VMLINUX_SYMBOL_STR(hci_recv_frame) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x70b60936, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0xc3e596f0, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0x2d43fdf2, __VMLINUX_SYMBOL_STR(sdio_readsb) },
	{ 0x4dff5858, __VMLINUX_SYMBOL_STR(sdio_readb) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x9df247a9, __VMLINUX_SYMBOL_STR(sdio_claim_irq) },
	{ 0x151e56a5, __VMLINUX_SYMBOL_STR(sdio_enable_func) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0x2407dc39, __VMLINUX_SYMBOL_STR(sdio_release_host) },
	{ 0x161a8033, __VMLINUX_SYMBOL_STR(sdio_disable_func) },
	{ 0x37e33744, __VMLINUX_SYMBOL_STR(sdio_release_irq) },
	{ 0xa26ada4a, __VMLINUX_SYMBOL_STR(sdio_writeb) },
	{ 0x44a17998, __VMLINUX_SYMBOL_STR(sdio_claim_host) },
	{ 0x2a3aa678, __VMLINUX_SYMBOL_STR(_test_and_clear_bit) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xa4efed60, __VMLINUX_SYMBOL_STR(skb_queue_purge) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x7783bae2, __VMLINUX_SYMBOL_STR(skb_queue_tail) },
	{ 0xaf8d5f9, __VMLINUX_SYMBOL_STR(hci_register_dev) },
	{ 0xec49f3c8, __VMLINUX_SYMBOL_STR(hci_alloc_dev) },
	{ 0x3d268c44, __VMLINUX_SYMBOL_STR(devm_kzalloc) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x21f30159, __VMLINUX_SYMBOL_STR(hci_free_dev) },
	{ 0xebcbcaea, __VMLINUX_SYMBOL_STR(hci_unregister_dev) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=bluetooth";

MODULE_ALIAS("sdio:c02v*d*");
MODULE_ALIAS("sdio:c03v*d*");
MODULE_ALIAS("sdio:c09v*d*");

MODULE_INFO(srcversion, "2FEB1C958E34A571B80F7DC");
