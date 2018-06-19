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
	{ 0xc60a2544, __VMLINUX_SYMBOL_STR(unregister_md_personality) },
	{ 0x5bb8e699, __VMLINUX_SYMBOL_STR(register_md_personality) },
	{ 0x3026722, __VMLINUX_SYMBOL_STR(mempool_alloc) },
	{ 0xb628c3e0, __VMLINUX_SYMBOL_STR(md_flush_request) },
	{ 0xce651bb6, __VMLINUX_SYMBOL_STR(md_wakeup_thread) },
	{ 0x38a0b521, __VMLINUX_SYMBOL_STR(md_error) },
	{ 0xc312906b, __VMLINUX_SYMBOL_STR(generic_make_request) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xcc1d1698, __VMLINUX_SYMBOL_STR(md_check_recovery) },
	{ 0x2232a8a5, __VMLINUX_SYMBOL_STR(mempool_free) },
	{ 0x86c8f053, __VMLINUX_SYMBOL_STR(bio_endio) },
	{ 0xccd65b4c, __VMLINUX_SYMBOL_STR(mddev_congested) },
	{ 0x6a037cf1, __VMLINUX_SYMBOL_STR(mempool_kfree) },
	{ 0xa05c03df, __VMLINUX_SYMBOL_STR(mempool_kmalloc) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xfabdda90, __VMLINUX_SYMBOL_STR(md_set_array_sectors) },
	{ 0x669494f0, __VMLINUX_SYMBOL_STR(md_register_thread) },
	{ 0x2b4e956e, __VMLINUX_SYMBOL_STR(mempool_create) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x8d8e2086, __VMLINUX_SYMBOL_STR(md_check_no_bitmap) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xa58fea9d, __VMLINUX_SYMBOL_STR(mempool_destroy) },
	{ 0x4b38d3df, __VMLINUX_SYMBOL_STR(blk_sync_queue) },
	{ 0x5e08d335, __VMLINUX_SYMBOL_STR(md_unregister_thread) },
	{ 0x2247cba2, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x2a3aa678, __VMLINUX_SYMBOL_STR(_test_and_clear_bit) },
	{ 0x80e75919, __VMLINUX_SYMBOL_STR(md_integrity_add_rdev) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0x3507a132, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irq) },
	{ 0x1c5844da, __VMLINUX_SYMBOL_STR(blk_queue_segment_boundary) },
	{ 0x325110c1, __VMLINUX_SYMBOL_STR(blk_queue_max_segments) },
	{ 0x6a26dd7e, __VMLINUX_SYMBOL_STR(disk_stack_limits) },
	{ 0x206ec28f, __VMLINUX_SYMBOL_STR(md_integrity_register) },
	{ 0xc2cdbf1, __VMLINUX_SYMBOL_STR(synchronize_sched) },
	{ 0xcf2b381c, __VMLINUX_SYMBOL_STR(bdevname) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x1e047854, __VMLINUX_SYMBOL_STR(warn_slowpath_fmt) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=md-mod";

