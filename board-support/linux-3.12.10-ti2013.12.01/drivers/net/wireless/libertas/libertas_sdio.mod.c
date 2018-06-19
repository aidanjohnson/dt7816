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
	{ 0xa26ada4a, __VMLINUX_SYMBOL_STR(sdio_writeb) },
	{ 0x4dff5858, __VMLINUX_SYMBOL_STR(sdio_readb) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0xc34ad504, __VMLINUX_SYMBOL_STR(__pm_runtime_idle) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x43a53735, __VMLINUX_SYMBOL_STR(__alloc_workqueue_key) },
	{ 0xacf58e0f, __VMLINUX_SYMBOL_STR(lbs_resume) },
	{ 0xc8b57c27, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0xca24564a, __VMLINUX_SYMBOL_STR(sdio_writesb) },
	{ 0x151e56a5, __VMLINUX_SYMBOL_STR(sdio_enable_func) },
	{ 0x9df247a9, __VMLINUX_SYMBOL_STR(sdio_claim_irq) },
	{ 0x4205ad24, __VMLINUX_SYMBOL_STR(cancel_work_sync) },
	{ 0xd4505c45, __VMLINUX_SYMBOL_STR(lbs_stop_card) },
	{ 0xb2468ee6, __VMLINUX_SYMBOL_STR(__pm_runtime_resume) },
	{ 0x40ad99d2, __VMLINUX_SYMBOL_STR(netdev_alert) },
	{ 0x80c2becc, __VMLINUX_SYMBOL_STR(__lbs_cmd) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x7e4f55f1, __VMLINUX_SYMBOL_STR(sdio_get_host_pm_caps) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x63a326ef, __VMLINUX_SYMBOL_STR(__netdev_alloc_skb) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0x855f562, __VMLINUX_SYMBOL_STR(lbs_start_card) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x20c55ae0, __VMLINUX_SYMBOL_STR(sscanf) },
	{ 0x8fe81c7, __VMLINUX_SYMBOL_STR(lbs_queue_event) },
	{ 0x8c03d20c, __VMLINUX_SYMBOL_STR(destroy_workqueue) },
	{ 0x8e98a6fc, __VMLINUX_SYMBOL_STR(lbs_get_firmware_async) },
	{ 0xf90d94b2, __VMLINUX_SYMBOL_STR(lbs_cmd_copyback) },
	{ 0xfd8a4fee, __VMLINUX_SYMBOL_STR(lbs_suspend) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0x42160169, __VMLINUX_SYMBOL_STR(flush_workqueue) },
	{ 0x2d43fdf2, __VMLINUX_SYMBOL_STR(sdio_readsb) },
	{ 0xd6f52eb1, __VMLINUX_SYMBOL_STR(sdio_unregister_driver) },
	{ 0x6423ad29, __VMLINUX_SYMBOL_STR(lbs_remove_card) },
	{ 0xee5c4205, __VMLINUX_SYMBOL_STR(sdio_f0_writeb) },
	{ 0x7dd82ea8, __VMLINUX_SYMBOL_STR(sdio_set_host_pm_flags) },
	{ 0x9b9980f2, __VMLINUX_SYMBOL_STR(lbs_process_rxed_packet) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x37e33744, __VMLINUX_SYMBOL_STR(sdio_release_irq) },
	{ 0x6fce93d4, __VMLINUX_SYMBOL_STR(lbs_host_to_card_done) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0x86a4889a, __VMLINUX_SYMBOL_STR(kmalloc_order_trace) },
	{ 0x1e8ffb87, __VMLINUX_SYMBOL_STR(sdio_align_size) },
	{ 0x4bd7cf8, __VMLINUX_SYMBOL_STR(lbs_add_card) },
	{ 0xb2cf734c, __VMLINUX_SYMBOL_STR(sdio_f0_readb) },
	{ 0x1fcb72d8, __VMLINUX_SYMBOL_STR(mmc_add_host) },
	{ 0xbc35e3cc, __VMLINUX_SYMBOL_STR(netdev_err) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0xf6607288, __VMLINUX_SYMBOL_STR(mmc_remove_host) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x499cb58c, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0x1cfb04fa, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x377db316, __VMLINUX_SYMBOL_STR(sdio_register_driver) },
	{ 0x44a17998, __VMLINUX_SYMBOL_STR(sdio_claim_host) },
	{ 0x70b60936, __VMLINUX_SYMBOL_STR(skb_put) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x69c15397, __VMLINUX_SYMBOL_STR(sdio_set_block_size) },
	{ 0x8b5187c3, __VMLINUX_SYMBOL_STR(release_firmware) },
	{ 0x161a8033, __VMLINUX_SYMBOL_STR(sdio_disable_func) },
	{ 0x2407dc39, __VMLINUX_SYMBOL_STR(sdio_release_host) },
	{ 0x4649a5ff, __VMLINUX_SYMBOL_STR(lbs_notify_command_response) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=libertas";

MODULE_ALIAS("sdio:c*v02DFd9103*");
MODULE_ALIAS("sdio:c*v02DFd9104*");
