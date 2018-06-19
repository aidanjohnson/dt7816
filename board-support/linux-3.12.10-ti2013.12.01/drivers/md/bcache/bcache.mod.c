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
	{ 0x61b7b126, __VMLINUX_SYMBOL_STR(simple_strtoull) },
	{ 0x32d5baca, __VMLINUX_SYMBOL_STR(kobject_put) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0xb64de2d, __VMLINUX_SYMBOL_STR(kmem_cache_destroy) },
	{ 0x2d6507b5, __VMLINUX_SYMBOL_STR(_find_next_zero_bit_le) },
	{ 0x371b3778, __VMLINUX_SYMBOL_STR(fs_bio_set) },
	{ 0x1050dba9, __VMLINUX_SYMBOL_STR(part_round_stats) },
	{ 0x262f20a8, __VMLINUX_SYMBOL_STR(local_clock) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x8ec06bd1, __VMLINUX_SYMBOL_STR(perf_tp_event) },
	{ 0x405c1144, __VMLINUX_SYMBOL_STR(get_seconds) },
	{ 0x2e2935bb, __VMLINUX_SYMBOL_STR(alloc_disk) },
	{ 0x22e1ae6f, __VMLINUX_SYMBOL_STR(up_read) },
	{ 0x7425e3b4, __VMLINUX_SYMBOL_STR(blk_cleanup_queue) },
	{ 0x41bea1e8, __VMLINUX_SYMBOL_STR(__bread) },
	{ 0x1aa51a6d, __VMLINUX_SYMBOL_STR(bio_alloc_bioset) },
	{ 0xa70dcea1, __VMLINUX_SYMBOL_STR(debugfs_create_dir) },
	{ 0xe52e3763, __VMLINUX_SYMBOL_STR(mem_map) },
	{ 0xd6ee688f, __VMLINUX_SYMBOL_STR(vmalloc) },
	{ 0x67c2fa54, __VMLINUX_SYMBOL_STR(__copy_to_user) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xc996d097, __VMLINUX_SYMBOL_STR(del_timer) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0xd0ee38b8, __VMLINUX_SYMBOL_STR(schedule_timeout_uninterruptible) },
	{ 0xc7ec6c27, __VMLINUX_SYMBOL_STR(strspn) },
	{ 0x3f358d29, __VMLINUX_SYMBOL_STR(page_address) },
	{ 0xc7a1840e, __VMLINUX_SYMBOL_STR(llist_add_batch) },
	{ 0x43a53735, __VMLINUX_SYMBOL_STR(__alloc_workqueue_key) },
	{ 0xc8b57c27, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0xd3dbfbc4, __VMLINUX_SYMBOL_STR(_find_first_zero_bit_le) },
	{ 0x79aa04a2, __VMLINUX_SYMBOL_STR(get_random_bytes) },
	{ 0xf1deabf2, __VMLINUX_SYMBOL_STR(div64_u64) },
	{ 0x488882e7, __VMLINUX_SYMBOL_STR(downgrade_write) },
	{ 0x68ab787c, __VMLINUX_SYMBOL_STR(bd_link_disk_holder) },
	{ 0x7ab88a45, __VMLINUX_SYMBOL_STR(system_freezing_cnt) },
	{ 0x20000329, __VMLINUX_SYMBOL_STR(simple_strtoul) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0x6b06fdce, __VMLINUX_SYMBOL_STR(delayed_work_timer_fn) },
	{ 0x76cf47f6, __VMLINUX_SYMBOL_STR(__aeabi_llsl) },
	{ 0xd3f57a2, __VMLINUX_SYMBOL_STR(_find_next_bit_le) },
	{ 0x4205ad24, __VMLINUX_SYMBOL_STR(cancel_work_sync) },
	{ 0xdb2fd587, __VMLINUX_SYMBOL_STR(sysfs_create_files) },
	{ 0xa58fea9d, __VMLINUX_SYMBOL_STR(mempool_destroy) },
	{ 0x5b19634d, __VMLINUX_SYMBOL_STR(div_s64_rem) },
	{ 0x593a99b, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0x9621849f, __VMLINUX_SYMBOL_STR(ring_buffer_event_data) },
	{ 0x24d7b4eb, __VMLINUX_SYMBOL_STR(cancel_delayed_work_sync) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xf7becfaa, __VMLINUX_SYMBOL_STR(bio_advance) },
	{ 0xddfcee1e, __VMLINUX_SYMBOL_STR(kobject_del) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0x7593d385, __VMLINUX_SYMBOL_STR(div64_s64) },
	{ 0xbdfc0bc0, __VMLINUX_SYMBOL_STR(debugfs_create_file) },
	{ 0x3393d733, __VMLINUX_SYMBOL_STR(filter_current_check_discard) },
	{ 0xbbc975e8, __VMLINUX_SYMBOL_STR(blk_queue_flush) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xe716df6f, __VMLINUX_SYMBOL_STR(debugfs_remove_recursive) },
	{ 0xbd59f360, __VMLINUX_SYMBOL_STR(kthread_create_on_node) },
	{ 0x6ccf7bd7, __VMLINUX_SYMBOL_STR(__pv_phys_offset) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0xbe54a8f9, __VMLINUX_SYMBOL_STR(lookup_bdev) },
	{ 0xe2deaa38, __VMLINUX_SYMBOL_STR(mutex_trylock) },
	{ 0x455293f6, __VMLINUX_SYMBOL_STR(down_read) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x216ce896, __VMLINUX_SYMBOL_STR(kobject_create_and_add) },
	{ 0xe8b53ecc, __VMLINUX_SYMBOL_STR(down_write_trylock) },
	{ 0x733c3b54, __VMLINUX_SYMBOL_STR(kasprintf) },
	{ 0xece784c2, __VMLINUX_SYMBOL_STR(rb_first) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0x183fa88b, __VMLINUX_SYMBOL_STR(mempool_alloc_slab) },
	{ 0x8cb5bf23, __VMLINUX_SYMBOL_STR(bio_reset) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xd5f2172f, __VMLINUX_SYMBOL_STR(del_timer_sync) },
	{ 0x1bd3c1ea, __VMLINUX_SYMBOL_STR(trace_event_buffer_lock_reserve) },
	{ 0xfcfa912, __VMLINUX_SYMBOL_STR(trace_define_field) },
	{ 0x6cbef71e, __VMLINUX_SYMBOL_STR(__blkdev_driver_ioctl) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xa0cb1cbd, __VMLINUX_SYMBOL_STR(bio_init) },
	{ 0x8f045d1c, __VMLINUX_SYMBOL_STR(cancel_delayed_work) },
	{ 0x651358a0, __VMLINUX_SYMBOL_STR(bd_unlink_disk_holder) },
	{ 0x3674e151, __VMLINUX_SYMBOL_STR(blk_alloc_queue) },
	{ 0x11089ac7, __VMLINUX_SYMBOL_STR(_ctype) },
	{ 0x41da4b21, __VMLINUX_SYMBOL_STR(freezing_slow_path) },
	{ 0x37befc70, __VMLINUX_SYMBOL_STR(jiffies_to_msecs) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x90a20675, __VMLINUX_SYMBOL_STR(kthread_stop) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0xe0513bd5, __VMLINUX_SYMBOL_STR(del_gendisk) },
	{ 0xfe67cbd6, __VMLINUX_SYMBOL_STR(kunmap) },
	{ 0x14d4a9c5, __VMLINUX_SYMBOL_STR(_change_bit) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0x4d9b652b, __VMLINUX_SYMBOL_STR(rb_erase) },
	{ 0xe5a39e92, __VMLINUX_SYMBOL_STR(blkdev_get_by_path) },
	{ 0xef86a3ea, __VMLINUX_SYMBOL_STR(debugfs_remove) },
	{ 0xbf8ba54a, __VMLINUX_SYMBOL_STR(vprintk) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x4b38d3df, __VMLINUX_SYMBOL_STR(blk_sync_queue) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x8c03d20c, __VMLINUX_SYMBOL_STR(destroy_workqueue) },
	{ 0xf473ffaf, __VMLINUX_SYMBOL_STR(down) },
	{ 0x71a50dbc, __VMLINUX_SYMBOL_STR(register_blkdev) },
	{ 0xbe2c0274, __VMLINUX_SYMBOL_STR(add_timer) },
	{ 0xc312906b, __VMLINUX_SYMBOL_STR(generic_make_request) },
	{ 0xb6f20d88, __VMLINUX_SYMBOL_STR(sysfs_remove_link) },
	{ 0x8a99a016, __VMLINUX_SYMBOL_STR(mempool_free_slab) },
	{ 0x310917fe, __VMLINUX_SYMBOL_STR(sort) },
	{ 0x83211609, __VMLINUX_SYMBOL_STR(up_write) },
	{ 0xc45678b0, __VMLINUX_SYMBOL_STR(kobject_add) },
	{ 0xa958ed4, __VMLINUX_SYMBOL_STR(down_write) },
	{ 0xf09de776, __VMLINUX_SYMBOL_STR(get_random_int) },
	{ 0xf2f138ef, __VMLINUX_SYMBOL_STR(__get_page_tail) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0x86c8f053, __VMLINUX_SYMBOL_STR(bio_endio) },
	{ 0xdfe6eaae, __VMLINUX_SYMBOL_STR(bio_put) },
	{ 0xd0bdbdb0, __VMLINUX_SYMBOL_STR(kobject_uevent_env) },
	{ 0x51ef33b8, __VMLINUX_SYMBOL_STR(kstrndup) },
	{ 0x59e5070d, __VMLINUX_SYMBOL_STR(__do_div64) },
	{ 0x61651be, __VMLINUX_SYMBOL_STR(strcat) },
	{ 0xac1a55be, __VMLINUX_SYMBOL_STR(unregister_reboot_notifier) },
	{ 0xb5a459dc, __VMLINUX_SYMBOL_STR(unregister_blkdev) },
	{ 0x250521eb, __VMLINUX_SYMBOL_STR(ftrace_event_reg) },
	{ 0x14227bac, __VMLINUX_SYMBOL_STR(sysfs_create_link) },
	{ 0xbca31af2, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0x238014c3, __VMLINUX_SYMBOL_STR(submit_bio) },
	{ 0x40a9b349, __VMLINUX_SYMBOL_STR(vzalloc) },
	{ 0x85cd3250, __VMLINUX_SYMBOL_STR(__free_pages) },
	{ 0x942b1b9e, __VMLINUX_SYMBOL_STR(blkdev_put) },
	{ 0xa0966e4b, __VMLINUX_SYMBOL_STR(unregister_shrinker) },
	{ 0x3026722, __VMLINUX_SYMBOL_STR(mempool_alloc) },
	{ 0xae359112, __VMLINUX_SYMBOL_STR(bio_integrity_clone) },
	{ 0x180d1e52, __VMLINUX_SYMBOL_STR(kmap) },
	{ 0x27afe945, __VMLINUX_SYMBOL_STR(fs_kobj) },
	{ 0xcf2b381c, __VMLINUX_SYMBOL_STR(bdevname) },
	{ 0x3517383e, __VMLINUX_SYMBOL_STR(register_reboot_notifier) },
	{ 0x1efe6ec3, __VMLINUX_SYMBOL_STR(blk_queue_make_request) },
	{ 0x93fca811, __VMLINUX_SYMBOL_STR(__get_free_pages) },
	{ 0xe851bb05, __VMLINUX_SYMBOL_STR(queue_delayed_work_on) },
	{ 0x3bd1b1f6, __VMLINUX_SYMBOL_STR(msecs_to_jiffies) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0xd62c833f, __VMLINUX_SYMBOL_STR(schedule_timeout) },
	{ 0x5b8d061d, __VMLINUX_SYMBOL_STR(bio_integrity_trim) },
	{ 0x86a4889a, __VMLINUX_SYMBOL_STR(kmalloc_order_trace) },
	{ 0xcbba804, __VMLINUX_SYMBOL_STR(put_disk) },
	{ 0x8a7d1c31, __VMLINUX_SYMBOL_STR(high_memory) },
	{ 0x2b4e956e, __VMLINUX_SYMBOL_STR(mempool_create) },
	{ 0xb988d6fd, __VMLINUX_SYMBOL_STR(bioset_create) },
	{ 0x6b2dc060, __VMLINUX_SYMBOL_STR(dump_stack) },
	{ 0x996bdb64, __VMLINUX_SYMBOL_STR(_kstrtoul) },
	{ 0x4482cdb, __VMLINUX_SYMBOL_STR(__refrigerator) },
	{ 0x6a037cf1, __VMLINUX_SYMBOL_STR(mempool_kfree) },
	{ 0xb678366f, __VMLINUX_SYMBOL_STR(int_sqrt) },
	{ 0x26021bc4, __VMLINUX_SYMBOL_STR(wake_up_process) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x2232a8a5, __VMLINUX_SYMBOL_STR(mempool_free) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0xa204bd35, __VMLINUX_SYMBOL_STR(bio_clone_bioset) },
	{ 0x1176e07f, __VMLINUX_SYMBOL_STR(__per_cpu_offset) },
	{ 0xa5526619, __VMLINUX_SYMBOL_STR(rb_insert_color) },
	{ 0x88e43e81, __VMLINUX_SYMBOL_STR(kmem_cache_create) },
	{ 0x74971a96, __VMLINUX_SYMBOL_STR(__module_get) },
	{ 0x4302d0eb, __VMLINUX_SYMBOL_STR(free_pages) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0xb3f7646e, __VMLINUX_SYMBOL_STR(kthread_should_stop) },
	{ 0xa05c03df, __VMLINUX_SYMBOL_STR(mempool_kmalloc) },
	{ 0x1e047854, __VMLINUX_SYMBOL_STR(warn_slowpath_fmt) },
	{ 0x855144ab, __VMLINUX_SYMBOL_STR(bio_alloc_pages) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x222ce52f, __VMLINUX_SYMBOL_STR(trace_event_raw_init) },
	{ 0x499cb58c, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0xc1b82d22, __VMLINUX_SYMBOL_STR(register_shrinker) },
	{ 0x86f870d5, __VMLINUX_SYMBOL_STR(add_disk) },
	{ 0x343848e4, __VMLINUX_SYMBOL_STR(kobject_init) },
	{ 0xd788742d, __VMLINUX_SYMBOL_STR(perf_trace_buf_prepare) },
	{ 0x4be7fb63, __VMLINUX_SYMBOL_STR(up) },
	{ 0x34fef0bf, __VMLINUX_SYMBOL_STR(put_page) },
	{ 0xf9e73082, __VMLINUX_SYMBOL_STR(scnprintf) },
	{ 0x74c134b9, __VMLINUX_SYMBOL_STR(__sw_hweight32) },
	{ 0x1cfb04fa, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x758a782e, __VMLINUX_SYMBOL_STR(blk_fill_rwbs) },
	{ 0xca9360b5, __VMLINUX_SYMBOL_STR(rb_next) },
	{ 0xf6e04730, __VMLINUX_SYMBOL_STR(event_storage) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xb742fd7, __VMLINUX_SYMBOL_STR(simple_strtol) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0x1e3a88fb, __VMLINUX_SYMBOL_STR(trace_seq_printf) },
	{ 0x99bb8806, __VMLINUX_SYMBOL_STR(memmove) },
	{ 0x8a4fa83b, __VMLINUX_SYMBOL_STR(__aeabi_llsr) },
	{ 0x1e1ff3f2, __VMLINUX_SYMBOL_STR(vmalloc_to_page) },
	{ 0xa962640c, __VMLINUX_SYMBOL_STR(set_blocksize) },
	{ 0x77bc13a0, __VMLINUX_SYMBOL_STR(strim) },
	{ 0xbae78a7b, __VMLINUX_SYMBOL_STR(bio_copy_data) },
	{ 0xd7e56a4e, __VMLINUX_SYMBOL_STR(simple_strtoll) },
	{ 0xdf2c2742, __VMLINUX_SYMBOL_STR(rb_last) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x7ca68c37, __VMLINUX_SYMBOL_STR(bioset_free) },
	{ 0x43b8e8d8, __VMLINUX_SYMBOL_STR(ftrace_raw_output_prep) },
	{ 0xa6020fd9, __VMLINUX_SYMBOL_STR(event_storage_mutex) },
	{ 0x7d4e2276, __VMLINUX_SYMBOL_STR(__init_rwsem) },
	{ 0x498d293a, __VMLINUX_SYMBOL_STR(trace_buffer_unlock_commit) },
	{ 0xf5afcd9d, __VMLINUX_SYMBOL_STR(try_module_get) },
	{ 0xb859f38b, __VMLINUX_SYMBOL_STR(krealloc) },
	{ 0xa7f92105, __VMLINUX_SYMBOL_STR(add_uevent_var) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

