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
	{ 0x32d5baca, __VMLINUX_SYMBOL_STR(kobject_put) },
	{ 0x92b57248, __VMLINUX_SYMBOL_STR(flush_work) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0xb64de2d, __VMLINUX_SYMBOL_STR(kmem_cache_destroy) },
	{ 0x402b8281, __VMLINUX_SYMBOL_STR(__request_module) },
	{ 0x1050dba9, __VMLINUX_SYMBOL_STR(part_round_stats) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x779db581, __VMLINUX_SYMBOL_STR(blk_queue_bio) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0xb82454b2, __VMLINUX_SYMBOL_STR(blk_delay_queue) },
	{ 0x2e2935bb, __VMLINUX_SYMBOL_STR(alloc_disk) },
	{ 0xfbc74f64, __VMLINUX_SYMBOL_STR(__copy_from_user) },
	{ 0x7425e3b4, __VMLINUX_SYMBOL_STR(blk_cleanup_queue) },
	{ 0x22e1ae6f, __VMLINUX_SYMBOL_STR(up_read) },
	{ 0x1aa51a6d, __VMLINUX_SYMBOL_STR(bio_alloc_bioset) },
	{ 0x2ae51800, __VMLINUX_SYMBOL_STR(blk_queue_prep_rq) },
	{ 0x86f6b99d, __VMLINUX_SYMBOL_STR(synchronize_rcu_expedited) },
	{ 0xe52e3763, __VMLINUX_SYMBOL_STR(mem_map) },
	{ 0x8bb9df5e, __VMLINUX_SYMBOL_STR(blk_integrity_is_initialized) },
	{ 0x349cba85, __VMLINUX_SYMBOL_STR(strchr) },
	{ 0x67c2fa54, __VMLINUX_SYMBOL_STR(__copy_to_user) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0x60a13e90, __VMLINUX_SYMBOL_STR(rcu_barrier) },
	{ 0x43a53735, __VMLINUX_SYMBOL_STR(__alloc_workqueue_key) },
	{ 0x83295d73, __VMLINUX_SYMBOL_STR(bdev_stack_limits) },
	{ 0xc8b57c27, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0xcc37f55c, __VMLINUX_SYMBOL_STR(blk_limits_io_opt) },
	{ 0x4c86184b, __VMLINUX_SYMBOL_STR(remove_wait_queue) },
	{ 0x68ab787c, __VMLINUX_SYMBOL_STR(bd_link_disk_holder) },
	{ 0xa5449d2d, __VMLINUX_SYMBOL_STR(__tracepoint_block_rq_remap) },
	{ 0x742def44, __VMLINUX_SYMBOL_STR(__tracepoint_block_bio_remap) },
	{ 0x19db6c4b, __VMLINUX_SYMBOL_STR(kobject_uevent) },
	{ 0xba8374b, __VMLINUX_SYMBOL_STR(__srcu_read_unlock) },
	{ 0x76cf47f6, __VMLINUX_SYMBOL_STR(__aeabi_llsl) },
	{ 0xd3f57a2, __VMLINUX_SYMBOL_STR(_find_next_bit_le) },
	{ 0x8fdc79c2, __VMLINUX_SYMBOL_STR(__tracepoint_block_bio_complete) },
	{ 0xa58fea9d, __VMLINUX_SYMBOL_STR(mempool_destroy) },
	{ 0x50c89f23, __VMLINUX_SYMBOL_STR(__alloc_percpu) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0xbbc975e8, __VMLINUX_SYMBOL_STR(blk_queue_flush) },
	{ 0xf161ba0e, __VMLINUX_SYMBOL_STR(blk_start_queue) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xfc55d6db, __VMLINUX_SYMBOL_STR(__alloc_pages_nodemask) },
	{ 0xc499ae1e, __VMLINUX_SYMBOL_STR(kstrdup) },
	{ 0x754dac78, __VMLINUX_SYMBOL_STR(blk_limits_io_min) },
	{ 0x6ccf7bd7, __VMLINUX_SYMBOL_STR(__pv_phys_offset) },
	{ 0x2cbe5bf9, __VMLINUX_SYMBOL_STR(nonseekable_open) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0xc9ec4e21, __VMLINUX_SYMBOL_STR(free_percpu) },
	{ 0xbe54a8f9, __VMLINUX_SYMBOL_STR(lookup_bdev) },
	{ 0x455293f6, __VMLINUX_SYMBOL_STR(down_read) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0xde9360ba, __VMLINUX_SYMBOL_STR(totalram_pages) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0x5883bfc7, __VMLINUX_SYMBOL_STR(blk_insert_cloned_request) },
	{ 0xffd5a395, __VMLINUX_SYMBOL_STR(default_wake_function) },
	{ 0xfe7c4287, __VMLINUX_SYMBOL_STR(nr_cpu_ids) },
	{ 0x183fa88b, __VMLINUX_SYMBOL_STR(mempool_alloc_slab) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x73572db2, __VMLINUX_SYMBOL_STR(misc_register) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x6cbef71e, __VMLINUX_SYMBOL_STR(__blkdev_driver_ioctl) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xa0cb1cbd, __VMLINUX_SYMBOL_STR(bio_init) },
	{ 0x651358a0, __VMLINUX_SYMBOL_STR(bd_unlink_disk_holder) },
	{ 0x3674e151, __VMLINUX_SYMBOL_STR(blk_alloc_queue) },
	{ 0x5d891a64, __VMLINUX_SYMBOL_STR(idr_destroy) },
	{ 0x11089ac7, __VMLINUX_SYMBOL_STR(_ctype) },
	{ 0x15f571ec, __VMLINUX_SYMBOL_STR(blk_set_stacking_limits) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x37befc70, __VMLINUX_SYMBOL_STR(jiffies_to_msecs) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x20c55ae0, __VMLINUX_SYMBOL_STR(sscanf) },
	{ 0x169f3b59, __VMLINUX_SYMBOL_STR(blk_lld_busy) },
	{ 0x122a3634, __VMLINUX_SYMBOL_STR(cleanup_srcu_struct) },
	{ 0xe0513bd5, __VMLINUX_SYMBOL_STR(del_gendisk) },
	{ 0x4adb45c2, __VMLINUX_SYMBOL_STR(bio_add_page) },
	{ 0x4fcdd96d, __VMLINUX_SYMBOL_STR(kobject_init_and_add) },
	{ 0x95e6e500, __VMLINUX_SYMBOL_STR(blk_stack_limits) },
	{ 0xf13eba7b, __VMLINUX_SYMBOL_STR(blk_peek_request) },
	{ 0xaafdc258, __VMLINUX_SYMBOL_STR(strcasecmp) },
	{ 0x2455c156, __VMLINUX_SYMBOL_STR(__clear_user) },
	{ 0x328a05f1, __VMLINUX_SYMBOL_STR(strncpy) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0x88b454fd, __VMLINUX_SYMBOL_STR(kmem_cache_free) },
	{ 0x93a6e0b2, __VMLINUX_SYMBOL_STR(io_schedule) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x630bfcc7, __VMLINUX_SYMBOL_STR(bio_get_nr_vecs) },
	{ 0x8c03d20c, __VMLINUX_SYMBOL_STR(destroy_workqueue) },
	{ 0x84ffea8b, __VMLINUX_SYMBOL_STR(idr_preload) },
	{ 0x5c992c13, __VMLINUX_SYMBOL_STR(elv_register_queue) },
	{ 0x442f223b, __VMLINUX_SYMBOL_STR(blk_integrity_compare) },
	{ 0x71a50dbc, __VMLINUX_SYMBOL_STR(register_blkdev) },
	{ 0xe57e68bb, __VMLINUX_SYMBOL_STR(noop_llseek) },
	{ 0x246cd407, __VMLINUX_SYMBOL_STR(thaw_bdev) },
	{ 0x67128609, __VMLINUX_SYMBOL_STR(__srcu_read_lock) },
	{ 0xc312906b, __VMLINUX_SYMBOL_STR(generic_make_request) },
	{ 0x52c8cafd, __VMLINUX_SYMBOL_STR(blkdev_get_by_dev) },
	{ 0xf74dae0f, __VMLINUX_SYMBOL_STR(idr_alloc) },
	{ 0x8a99a016, __VMLINUX_SYMBOL_STR(mempool_free_slab) },
	{ 0x5a3d81f, __VMLINUX_SYMBOL_STR(blk_update_request) },
	{ 0x83211609, __VMLINUX_SYMBOL_STR(up_write) },
	{ 0xa958ed4, __VMLINUX_SYMBOL_STR(down_write) },
	{ 0x2a504ad2, __VMLINUX_SYMBOL_STR(init_srcu_struct) },
	{ 0x42160169, __VMLINUX_SYMBOL_STR(flush_workqueue) },
	{ 0x306a1617, __VMLINUX_SYMBOL_STR(contig_page_data) },
	{ 0x86c8f053, __VMLINUX_SYMBOL_STR(bio_endio) },
	{ 0xdfe6eaae, __VMLINUX_SYMBOL_STR(bio_put) },
	{ 0xd0bdbdb0, __VMLINUX_SYMBOL_STR(kobject_uevent_env) },
	{ 0x59e5070d, __VMLINUX_SYMBOL_STR(__do_div64) },
	{ 0x61651be, __VMLINUX_SYMBOL_STR(strcat) },
	{ 0xdf401846, __VMLINUX_SYMBOL_STR(idr_remove) },
	{ 0xb5a459dc, __VMLINUX_SYMBOL_STR(unregister_blkdev) },
	{ 0x4f6d9740, __VMLINUX_SYMBOL_STR(bio_sector_offset) },
	{ 0xbca31af2, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0x2208b72d, __VMLINUX_SYMBOL_STR(blk_queue_bounce_limit) },
	{ 0x238014c3, __VMLINUX_SYMBOL_STR(submit_bio) },
	{ 0xc6cbbc89, __VMLINUX_SYMBOL_STR(capable) },
	{ 0x13b715e2, __VMLINUX_SYMBOL_STR(blk_finish_plug) },
	{ 0x40a9b349, __VMLINUX_SYMBOL_STR(vzalloc) },
	{ 0xb0e93b81, __VMLINUX_SYMBOL_STR(kmem_cache_alloc) },
	{ 0x85cd3250, __VMLINUX_SYMBOL_STR(__free_pages) },
	{ 0xf1806da9, __VMLINUX_SYMBOL_STR(idr_find_slowpath) },
	{ 0x942b1b9e, __VMLINUX_SYMBOL_STR(blkdev_put) },
	{ 0x3026722, __VMLINUX_SYMBOL_STR(mempool_alloc) },
	{ 0xae359112, __VMLINUX_SYMBOL_STR(bio_integrity_clone) },
	{ 0x9bfa5ab7, __VMLINUX_SYMBOL_STR(__bio_clone) },
	{ 0xcf2b381c, __VMLINUX_SYMBOL_STR(bdevname) },
	{ 0x1efe6ec3, __VMLINUX_SYMBOL_STR(blk_queue_make_request) },
	{ 0xe761bb28, __VMLINUX_SYMBOL_STR(__blk_put_request) },
	{ 0x5574ab5b, __VMLINUX_SYMBOL_STR(blk_queue_softirq_done) },
	{ 0x7c62d042, __VMLINUX_SYMBOL_STR(cpu_possible_mask) },
	{ 0xf7207248, __VMLINUX_SYMBOL_STR(scsi_verify_blk_ioctl) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0x5b8d061d, __VMLINUX_SYMBOL_STR(bio_integrity_trim) },
	{ 0x72350130, __VMLINUX_SYMBOL_STR(___ratelimit) },
	{ 0xcbba804, __VMLINUX_SYMBOL_STR(put_disk) },
	{ 0x2b4e956e, __VMLINUX_SYMBOL_STR(mempool_create) },
	{ 0x8a7d1c31, __VMLINUX_SYMBOL_STR(high_memory) },
	{ 0xb988d6fd, __VMLINUX_SYMBOL_STR(bioset_create) },
	{ 0x3507a132, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irq) },
	{ 0x4238fd3f, __VMLINUX_SYMBOL_STR(bioset_integrity_create) },
	{ 0xca7dcff3, __VMLINUX_SYMBOL_STR(empty_zero_page) },
	{ 0x26021bc4, __VMLINUX_SYMBOL_STR(wake_up_process) },
	{ 0xd378c8f, __VMLINUX_SYMBOL_STR(blk_integrity_unregister) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x2232a8a5, __VMLINUX_SYMBOL_STR(mempool_free) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x1176e07f, __VMLINUX_SYMBOL_STR(__per_cpu_offset) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x88e43e81, __VMLINUX_SYMBOL_STR(kmem_cache_create) },
	{ 0x43c9806, __VMLINUX_SYMBOL_STR(synchronize_srcu) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x9b369454, __VMLINUX_SYMBOL_STR(blk_stop_queue) },
	{ 0xa85d8e2d, __VMLINUX_SYMBOL_STR(blk_rq_unprep_clone) },
	{ 0xbbf60324, __VMLINUX_SYMBOL_STR(blk_run_queue_async) },
	{ 0xc7bcbc8d, __VMLINUX_SYMBOL_STR(add_wait_queue) },
	{ 0x236f0b6, __VMLINUX_SYMBOL_STR(freeze_bdev) },
	{ 0x28d6861d, __VMLINUX_SYMBOL_STR(__vmalloc) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xa46f2f1b, __VMLINUX_SYMBOL_STR(kstrtouint) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xa75312bc, __VMLINUX_SYMBOL_STR(call_rcu_sched) },
	{ 0xb0ffda2f, __VMLINUX_SYMBOL_STR(blk_limits_max_hw_sectors) },
	{ 0xfafec243, __VMLINUX_SYMBOL_STR(blk_init_allocated_queue) },
	{ 0x499cb58c, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0x721b1851, __VMLINUX_SYMBOL_STR(skip_spaces) },
	{ 0x86f870d5, __VMLINUX_SYMBOL_STR(add_disk) },
	{ 0x805f074f, __VMLINUX_SYMBOL_STR(blk_end_request_all) },
	{ 0x2e7d17e, __VMLINUX_SYMBOL_STR(blk_rq_prep_clone) },
	{ 0xd67a2350, __VMLINUX_SYMBOL_STR(blk_requeue_request) },
	{ 0x2256fafa, __VMLINUX_SYMBOL_STR(div64_u64_rem) },
	{ 0x2eebed47, __VMLINUX_SYMBOL_STR(blk_complete_request) },
	{ 0x9613509a, __VMLINUX_SYMBOL_STR(idr_replace) },
	{ 0xf9e73082, __VMLINUX_SYMBOL_STR(scnprintf) },
	{ 0x74c134b9, __VMLINUX_SYMBOL_STR(__sw_hweight32) },
	{ 0x1db7dc40, __VMLINUX_SYMBOL_STR(pgprot_kernel) },
	{ 0x1cfb04fa, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x6335fa2, __VMLINUX_SYMBOL_STR(blk_queue_lld_busy) },
	{ 0x9e0c711d, __VMLINUX_SYMBOL_STR(vzalloc_node) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x8a4fa83b, __VMLINUX_SYMBOL_STR(__aeabi_llsr) },
	{ 0x1e1ff3f2, __VMLINUX_SYMBOL_STR(vmalloc_to_page) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x99367682, __VMLINUX_SYMBOL_STR(zero_fill_bio) },
	{ 0x8d2e268b, __VMLINUX_SYMBOL_STR(param_ops_ulong) },
	{ 0x47c8baf4, __VMLINUX_SYMBOL_STR(param_ops_uint) },
	{ 0x7ca68c37, __VMLINUX_SYMBOL_STR(bioset_free) },
	{ 0x74c3afb5, __VMLINUX_SYMBOL_STR(bdget_disk) },
	{ 0x65d67a20, __VMLINUX_SYMBOL_STR(blk_start_plug) },
	{ 0x49ac0df0, __VMLINUX_SYMBOL_STR(misc_deregister) },
	{ 0x8a4d2902, __VMLINUX_SYMBOL_STR(bdput) },
	{ 0x9ffa6b31, __VMLINUX_SYMBOL_STR(blk_start_request) },
	{ 0xf5afcd9d, __VMLINUX_SYMBOL_STR(try_module_get) },
	{ 0xfac1b0c4, __VMLINUX_SYMBOL_STR(blk_integrity_register) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
	{ 0xd0452d6c, __VMLINUX_SYMBOL_STR(set_disk_ro) },
	{ 0xa7f92105, __VMLINUX_SYMBOL_STR(add_uevent_var) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

