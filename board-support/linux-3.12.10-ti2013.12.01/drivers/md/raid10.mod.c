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
	{ 0xb2b27c17, __VMLINUX_SYMBOL_STR(blk_queue_merge_bvec) },
	{ 0xf634c93b, __VMLINUX_SYMBOL_STR(bio_split) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x3314eaaa, __VMLINUX_SYMBOL_STR(submit_bio_wait) },
	{ 0xff178f6, __VMLINUX_SYMBOL_STR(__aeabi_idivmod) },
	{ 0xd167485e, __VMLINUX_SYMBOL_STR(blk_queue_io_opt) },
	{ 0x1aa51a6d, __VMLINUX_SYMBOL_STR(bio_alloc_bioset) },
	{ 0xccd65b4c, __VMLINUX_SYMBOL_STR(mddev_congested) },
	{ 0xcc432404, __VMLINUX_SYMBOL_STR(rdev_set_badblocks) },
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xd2260e3, __VMLINUX_SYMBOL_STR(md_is_badblock) },
	{ 0x3f358d29, __VMLINUX_SYMBOL_STR(page_address) },
	{ 0xe2999247, __VMLINUX_SYMBOL_STR(bio_clone_mddev) },
	{ 0xc8b57c27, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0x6851073, __VMLINUX_SYMBOL_STR(bio_alloc_mddev) },
	{ 0xcc1d1698, __VMLINUX_SYMBOL_STR(md_check_recovery) },
	{ 0xf489df62, __VMLINUX_SYMBOL_STR(blk_queue_io_min) },
	{ 0x76cf47f6, __VMLINUX_SYMBOL_STR(__aeabi_llsl) },
	{ 0x4e58faa, __VMLINUX_SYMBOL_STR(md_write_end) },
	{ 0x2a3aa678, __VMLINUX_SYMBOL_STR(_test_and_clear_bit) },
	{ 0x2247cba2, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0xd80dc18c, __VMLINUX_SYMBOL_STR(bitmap_endwrite) },
	{ 0xa58fea9d, __VMLINUX_SYMBOL_STR(mempool_destroy) },
	{ 0x6db0cf18, __VMLINUX_SYMBOL_STR(bitmap_unplug) },
	{ 0xfbb595b0, __VMLINUX_SYMBOL_STR(md_new_event) },
	{ 0xc60a2544, __VMLINUX_SYMBOL_STR(unregister_md_personality) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x2872096, __VMLINUX_SYMBOL_STR(revalidate_disk) },
	{ 0xfc55d6db, __VMLINUX_SYMBOL_STR(__alloc_pages_nodemask) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x12413331, __VMLINUX_SYMBOL_STR(bitmap_resize) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0x8cb5bf23, __VMLINUX_SYMBOL_STR(bio_reset) },
	{ 0x7d18c965, __VMLINUX_SYMBOL_STR(bitmap_start_sync) },
	{ 0xd27b25dd, __VMLINUX_SYMBOL_STR(blk_check_plugged) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x669494f0, __VMLINUX_SYMBOL_STR(md_register_thread) },
	{ 0xb628c3e0, __VMLINUX_SYMBOL_STR(md_flush_request) },
	{ 0x6c269097, __VMLINUX_SYMBOL_STR(bio_pair_release) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0x9987136c, __VMLINUX_SYMBOL_STR(blk_queue_max_discard_sectors) },
	{ 0x4adb45c2, __VMLINUX_SYMBOL_STR(bio_add_page) },
	{ 0xba955739, __VMLINUX_SYMBOL_STR(md_do_sync) },
	{ 0x6a26dd7e, __VMLINUX_SYMBOL_STR(disk_stack_limits) },
	{ 0x97c69305, __VMLINUX_SYMBOL_STR(bitmap_close_sync) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0x13e9301b, __VMLINUX_SYMBOL_STR(md_trim_bio) },
	{ 0x4b38d3df, __VMLINUX_SYMBOL_STR(blk_sync_queue) },
	{ 0xc2cdbf1, __VMLINUX_SYMBOL_STR(synchronize_sched) },
	{ 0xc312906b, __VMLINUX_SYMBOL_STR(generic_make_request) },
	{ 0xd9031887, __VMLINUX_SYMBOL_STR(md_wait_for_blocked_rdev) },
	{ 0xf2f138ef, __VMLINUX_SYMBOL_STR(__get_page_tail) },
	{ 0x80e75919, __VMLINUX_SYMBOL_STR(md_integrity_add_rdev) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0x306a1617, __VMLINUX_SYMBOL_STR(contig_page_data) },
	{ 0x86c8f053, __VMLINUX_SYMBOL_STR(bio_endio) },
	{ 0xdfe6eaae, __VMLINUX_SYMBOL_STR(bio_put) },
	{ 0x59e5070d, __VMLINUX_SYMBOL_STR(__do_div64) },
	{ 0xe3df3c23, __VMLINUX_SYMBOL_STR(md_done_sync) },
	{ 0x14227bac, __VMLINUX_SYMBOL_STR(sysfs_create_link) },
	{ 0x13b715e2, __VMLINUX_SYMBOL_STR(blk_finish_plug) },
	{ 0x5aa4b52, __VMLINUX_SYMBOL_STR(bitmap_cond_end_sync) },
	{ 0x3026722, __VMLINUX_SYMBOL_STR(mempool_alloc) },
	{ 0x47270ba6, __VMLINUX_SYMBOL_STR(md_write_start) },
	{ 0xcf2b381c, __VMLINUX_SYMBOL_STR(bdevname) },
	{ 0x419eebbc, __VMLINUX_SYMBOL_STR(sysfs_notify_dirent) },
	{ 0x7c17620a, __VMLINUX_SYMBOL_STR(rdev_clear_badblocks) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0x72350130, __VMLINUX_SYMBOL_STR(___ratelimit) },
	{ 0xfabdda90, __VMLINUX_SYMBOL_STR(md_set_array_sectors) },
	{ 0x2b4e956e, __VMLINUX_SYMBOL_STR(mempool_create) },
	{ 0x3507a132, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irq) },
	{ 0xc30523d8, __VMLINUX_SYMBOL_STR(sysfs_notify) },
	{ 0xce651bb6, __VMLINUX_SYMBOL_STR(md_wakeup_thread) },
	{ 0xcc5005fe, __VMLINUX_SYMBOL_STR(msleep_interruptible) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x2232a8a5, __VMLINUX_SYMBOL_STR(mempool_free) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0xce46e140, __VMLINUX_SYMBOL_STR(ktime_get_ts) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0xb3f7646e, __VMLINUX_SYMBOL_STR(kthread_should_stop) },
	{ 0x3d272bd7, __VMLINUX_SYMBOL_STR(sync_page_io) },
	{ 0x5e08d335, __VMLINUX_SYMBOL_STR(md_unregister_thread) },
	{ 0xc2fa0fb3, __VMLINUX_SYMBOL_STR(md_finish_reshape) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xa3500ee6, __VMLINUX_SYMBOL_STR(bitmap_startwrite) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x499cb58c, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0x1b82fefa, __VMLINUX_SYMBOL_STR(md_unplug) },
	{ 0x38a0b521, __VMLINUX_SYMBOL_STR(md_error) },
	{ 0x34fef0bf, __VMLINUX_SYMBOL_STR(put_page) },
	{ 0x1cfb04fa, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0x8a4fa83b, __VMLINUX_SYMBOL_STR(__aeabi_llsr) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x65d67a20, __VMLINUX_SYMBOL_STR(blk_start_plug) },
	{ 0x931f87e7, __VMLINUX_SYMBOL_STR(blk_queue_max_write_same_sectors) },
	{ 0x206ec28f, __VMLINUX_SYMBOL_STR(md_integrity_register) },
	{ 0x5bb8e699, __VMLINUX_SYMBOL_STR(register_md_personality) },
	{ 0xe237f1b3, __VMLINUX_SYMBOL_STR(bitmap_end_sync) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=md-mod";

