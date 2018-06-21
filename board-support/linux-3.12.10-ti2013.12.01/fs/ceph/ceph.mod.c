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
	{ 0xafb8a407, __VMLINUX_SYMBOL_STR(ceph_msgr_flush) },
	{ 0x4b08e2ae, __VMLINUX_SYMBOL_STR(ceph_con_close) },
	{ 0xb64de2d, __VMLINUX_SYMBOL_STR(kmem_cache_destroy) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xc1303126, __VMLINUX_SYMBOL_STR(set_anon_super) },
	{ 0xff178f6, __VMLINUX_SYMBOL_STR(__aeabi_idivmod) },
	{ 0xfbc74f64, __VMLINUX_SYMBOL_STR(__copy_from_user) },
	{ 0x22e1ae6f, __VMLINUX_SYMBOL_STR(up_read) },
	{ 0x4205ffd7, __VMLINUX_SYMBOL_STR(ceph_destroy_options) },
	{ 0x84439fcd, __VMLINUX_SYMBOL_STR(generic_file_llseek) },
	{ 0xfcc0e334, __VMLINUX_SYMBOL_STR(__mark_inode_dirty) },
	{ 0x962374c4, __VMLINUX_SYMBOL_STR(d_invalidate) },
	{ 0x9b2ffb2d, __VMLINUX_SYMBOL_STR(__set_page_dirty_nobuffers) },
	{ 0x8f302771, __VMLINUX_SYMBOL_STR(filemap_fault) },
	{ 0x349cba85, __VMLINUX_SYMBOL_STR(strchr) },
	{ 0xf88dd612, __VMLINUX_SYMBOL_STR(single_open) },
	{ 0x9eaf5515, __VMLINUX_SYMBOL_STR(generic_write_checks) },
	{ 0x6f649850, __VMLINUX_SYMBOL_STR(ceph_con_init) },
	{ 0x91eb9b4, __VMLINUX_SYMBOL_STR(round_jiffies) },
	{ 0x67c2fa54, __VMLINUX_SYMBOL_STR(__copy_to_user) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0x60a13e90, __VMLINUX_SYMBOL_STR(rcu_barrier) },
	{ 0x75922855, __VMLINUX_SYMBOL_STR(d_set_d_op) },
	{ 0x654be527, __VMLINUX_SYMBOL_STR(filemap_write_and_wait_range) },
	{ 0x43a53735, __VMLINUX_SYMBOL_STR(__alloc_workqueue_key) },
	{ 0xd59d3854, __VMLINUX_SYMBOL_STR(iget5_locked) },
	{ 0xd713c35a, __VMLINUX_SYMBOL_STR(kill_anon_super) },
	{ 0x9f534f4d, __VMLINUX_SYMBOL_STR(ceph_buffer_release) },
	{ 0x3abec91f, __VMLINUX_SYMBOL_STR(ceph_pr_addr) },
	{ 0xc8b57c27, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0x79aa04a2, __VMLINUX_SYMBOL_STR(get_random_bytes) },
	{ 0x34184afe, __VMLINUX_SYMBOL_STR(current_kernel_time) },
	{ 0x4cd9d440, __VMLINUX_SYMBOL_STR(single_release) },
	{ 0x57baf885, __VMLINUX_SYMBOL_STR(ceph_str_hash) },
	{ 0xd2ce469a, __VMLINUX_SYMBOL_STR(seq_puts) },
	{ 0x488882e7, __VMLINUX_SYMBOL_STR(downgrade_write) },
	{ 0x6bb4f607, __VMLINUX_SYMBOL_STR(truncate_inode_pages_range) },
	{ 0xe68b90f6, __VMLINUX_SYMBOL_STR(test_set_page_writeback) },
	{ 0x7fd7a7b1, __VMLINUX_SYMBOL_STR(__lock_page) },
	{ 0xc55de604, __VMLINUX_SYMBOL_STR(ceph_parse_options) },
	{ 0x7e5c8920, __VMLINUX_SYMBOL_STR(filemap_write_and_wait) },
	{ 0xdbe69fb4, __VMLINUX_SYMBOL_STR(ceph_osdc_writepages) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0x324b4cd7, __VMLINUX_SYMBOL_STR(touch_atime) },
	{ 0xb9fc6bad, __VMLINUX_SYMBOL_STR(deactivate_locked_super) },
	{ 0x6b06fdce, __VMLINUX_SYMBOL_STR(delayed_work_timer_fn) },
	{ 0x8cb6a962, __VMLINUX_SYMBOL_STR(lockref_get) },
	{ 0x1c929f64, __VMLINUX_SYMBOL_STR(generic_file_aio_read) },
	{ 0x85a8397f, __VMLINUX_SYMBOL_STR(ceph_monc_validate_auth) },
	{ 0x7bf11e89, __VMLINUX_SYMBOL_STR(dput) },
	{ 0x1b4b27b6, __VMLINUX_SYMBOL_STR(ceph_monc_do_statfs) },
	{ 0x2247cba2, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0x5295aeaf, __VMLINUX_SYMBOL_STR(generic_file_remap_pages) },
	{ 0x91da95fe, __VMLINUX_SYMBOL_STR(ceph_alloc_page_vector) },
	{ 0xa58fea9d, __VMLINUX_SYMBOL_STR(mempool_destroy) },
	{ 0x44e9a829, __VMLINUX_SYMBOL_STR(match_token) },
	{ 0x55ea5930, __VMLINUX_SYMBOL_STR(d_materialise_unique) },
	{ 0xe2fae716, __VMLINUX_SYMBOL_STR(kmemdup) },
	{ 0x7ac68dbd, __VMLINUX_SYMBOL_STR(d_find_alias) },
	{ 0xcb466063, __VMLINUX_SYMBOL_STR(wait_for_completion_killable_timeout) },
	{ 0x3f2a0f29, __VMLINUX_SYMBOL_STR(init_user_ns) },
	{ 0x593a99b, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0xe7288fd8, __VMLINUX_SYMBOL_STR(add_to_page_cache_lru) },
	{ 0x24d7b4eb, __VMLINUX_SYMBOL_STR(cancel_delayed_work_sync) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x8a0f4230, __VMLINUX_SYMBOL_STR(rename_lock) },
	{ 0xf427ff35, __VMLINUX_SYMBOL_STR(__ceph_open_session) },
	{ 0x53010423, __VMLINUX_SYMBOL_STR(igrab) },
	{ 0xbdfc0bc0, __VMLINUX_SYMBOL_STR(debugfs_create_file) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x92c80041, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0xfc55d6db, __VMLINUX_SYMBOL_STR(__alloc_pages_nodemask) },
	{ 0xaebd2aa2, __VMLINUX_SYMBOL_STR(ceph_copy_user_to_page_vector) },
	{ 0x2a547a33, __VMLINUX_SYMBOL_STR(ceph_destroy_client) },
	{ 0xc499ae1e, __VMLINUX_SYMBOL_STR(kstrdup) },
	{ 0x56d79fc2, __VMLINUX_SYMBOL_STR(set_page_dirty) },
	{ 0xa677b94c, __VMLINUX_SYMBOL_STR(ceph_osdc_sync) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x6606a424, __VMLINUX_SYMBOL_STR(osd_req_op_extent_osd_data_pages) },
	{ 0xe2deaa38, __VMLINUX_SYMBOL_STR(mutex_trylock) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x455293f6, __VMLINUX_SYMBOL_STR(down_read) },
	{ 0x3158173e, __VMLINUX_SYMBOL_STR(ceph_pagelist_release) },
	{ 0xe8b53ecc, __VMLINUX_SYMBOL_STR(down_write_trylock) },
	{ 0x369f3371, __VMLINUX_SYMBOL_STR(end_page_writeback) },
	{ 0x55ae484c, __VMLINUX_SYMBOL_STR(simple_attr_read) },
	{ 0xde9360ba, __VMLINUX_SYMBOL_STR(totalram_pages) },
	{ 0x31ca8d3, __VMLINUX_SYMBOL_STR(flock_lock_file_wait) },
	{ 0x53b03933, __VMLINUX_SYMBOL_STR(d_delete) },
	{ 0x81f3afb, __VMLINUX_SYMBOL_STR(complete_all) },
	{ 0xece784c2, __VMLINUX_SYMBOL_STR(rb_first) },
	{ 0x28124e6f, __VMLINUX_SYMBOL_STR(make_kgid) },
	{ 0x3c32cd83, __VMLINUX_SYMBOL_STR(ceph_auth_create_authorizer) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x1fab5905, __VMLINUX_SYMBOL_STR(wait_for_completion) },
	{ 0x34d04659, __VMLINUX_SYMBOL_STR(kmap_atomic) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x6b2e3bcd, __VMLINUX_SYMBOL_STR(ceph_get_snap_context) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xdaf23bd8, __VMLINUX_SYMBOL_STR(from_kuid) },
	{ 0x390c743e, __VMLINUX_SYMBOL_STR(ceph_put_page_vector) },
	{ 0xd17e90f1, __VMLINUX_SYMBOL_STR(finish_no_open) },
	{ 0x3f5b67d5, __VMLINUX_SYMBOL_STR(wait_for_completion_killable) },
	{ 0x43c8d341, __VMLINUX_SYMBOL_STR(ceph_buffer_new) },
	{ 0xae5e121e, __VMLINUX_SYMBOL_STR(ceph_msg_dump) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xf0b61226, __VMLINUX_SYMBOL_STR(d_rehash) },
	{ 0x21187185, __VMLINUX_SYMBOL_STR(find_lock_page) },
	{ 0xc6f6192e, __VMLINUX_SYMBOL_STR(d_obtain_alias) },
	{ 0x622af644, __VMLINUX_SYMBOL_STR(ceph_compare_options) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0x821191c4, __VMLINUX_SYMBOL_STR(sget) },
	{ 0x3c0ae3fe, __VMLINUX_SYMBOL_STR(ceph_osdc_start_request) },
	{ 0x3df0ec7c, __VMLINUX_SYMBOL_STR(ceph_calc_ceph_pg) },
	{ 0xeb27d287, __VMLINUX_SYMBOL_STR(ceph_zero_page_vector_range) },
	{ 0x4d9b652b, __VMLINUX_SYMBOL_STR(rb_erase) },
	{ 0x328a05f1, __VMLINUX_SYMBOL_STR(strncpy) },
	{ 0x1a999c92, __VMLINUX_SYMBOL_STR(ceph_con_send) },
	{ 0x4096bf3b, __VMLINUX_SYMBOL_STR(from_kgid) },
	{ 0xc4d05e79, __VMLINUX_SYMBOL_STR(d_move) },
	{ 0x7d79cf69, __VMLINUX_SYMBOL_STR(bdi_init) },
	{ 0xabf2ad9e, __VMLINUX_SYMBOL_STR(ceph_osdc_readpages) },
	{ 0x84b183ae, __VMLINUX_SYMBOL_STR(strncmp) },
	{ 0xef86a3ea, __VMLINUX_SYMBOL_STR(debugfs_remove) },
	{ 0x6437f1, __VMLINUX_SYMBOL_STR(ceph_monc_got_mdsmap) },
	{ 0x88b454fd, __VMLINUX_SYMBOL_STR(kmem_cache_free) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x67e60b31, __VMLINUX_SYMBOL_STR(set_nlink) },
	{ 0x7f8c0c35, __VMLINUX_SYMBOL_STR(file_remove_suid) },
	{ 0xf11afc0b, __VMLINUX_SYMBOL_STR(file_update_time) },
	{ 0xed93f29e, __VMLINUX_SYMBOL_STR(__kunmap_atomic) },
	{ 0x8c03d20c, __VMLINUX_SYMBOL_STR(destroy_workqueue) },
	{ 0x43efd647, __VMLINUX_SYMBOL_STR(ceph_calc_file_object_mapping) },
	{ 0xa735db59, __VMLINUX_SYMBOL_STR(prandom_u32) },
	{ 0xff941689, __VMLINUX_SYMBOL_STR(clear_bdi_congested) },
	{ 0x8e1cb29f, __VMLINUX_SYMBOL_STR(simple_attr_release) },
	{ 0x4e3567f7, __VMLINUX_SYMBOL_STR(match_int) },
	{ 0x11d8dcdf, __VMLINUX_SYMBOL_STR(wait_on_page_bit) },
	{ 0x7c1d8ae6, __VMLINUX_SYMBOL_STR(unlock_page) },
	{ 0x310917fe, __VMLINUX_SYMBOL_STR(sort) },
	{ 0x83211609, __VMLINUX_SYMBOL_STR(up_write) },
	{ 0xa958ed4, __VMLINUX_SYMBOL_STR(down_write) },
	{ 0x306a1617, __VMLINUX_SYMBOL_STR(contig_page_data) },
	{ 0x51ef33b8, __VMLINUX_SYMBOL_STR(kstrndup) },
	{ 0x1f97cf7b, __VMLINUX_SYMBOL_STR(ilookup5) },
	{ 0x59e5070d, __VMLINUX_SYMBOL_STR(__do_div64) },
	{ 0x7ad8634b, __VMLINUX_SYMBOL_STR(ceph_osdc_new_request) },
	{ 0xdec1eb4f, __VMLINUX_SYMBOL_STR(inode_init_once) },
	{ 0x35618998, __VMLINUX_SYMBOL_STR(ceph_osdc_wait_request) },
	{ 0xe82c9c32, __VMLINUX_SYMBOL_STR(ceph_pg_pool_name_by_id) },
	{ 0x4059792f, __VMLINUX_SYMBOL_STR(print_hex_dump) },
	{ 0xb0e93b81, __VMLINUX_SYMBOL_STR(kmem_cache_alloc) },
	{ 0x85cd3250, __VMLINUX_SYMBOL_STR(__free_pages) },
	{ 0x3026722, __VMLINUX_SYMBOL_STR(mempool_alloc) },
	{ 0x30efa762, __VMLINUX_SYMBOL_STR(ceph_get_direct_page_vector) },
	{ 0x8ad95e6a, __VMLINUX_SYMBOL_STR(ceph_auth_update_authorizer) },
	{ 0x180d1e52, __VMLINUX_SYMBOL_STR(kmap) },
	{ 0x65d30af1, __VMLINUX_SYMBOL_STR(d_alloc) },
	{ 0xdaf2fd26, __VMLINUX_SYMBOL_STR(make_kuid) },
	{ 0xa5ee4a61, __VMLINUX_SYMBOL_STR(ceph_auth_verify_authorizer_reply) },
	{ 0x2931e5ed, __VMLINUX_SYMBOL_STR(pagevec_lookup_tag) },
	{ 0x6ed41be2, __VMLINUX_SYMBOL_STR(ceph_pagelist_append) },
	{ 0xe851bb05, __VMLINUX_SYMBOL_STR(queue_delayed_work_on) },
	{ 0x709fc94e, __VMLINUX_SYMBOL_STR(ceph_check_fsid) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0xd62c833f, __VMLINUX_SYMBOL_STR(schedule_timeout) },
	{ 0x8487d868, __VMLINUX_SYMBOL_STR(ceph_release_page_vector) },
	{ 0x2b4e956e, __VMLINUX_SYMBOL_STR(mempool_create) },
	{ 0x44e905ef, __VMLINUX_SYMBOL_STR(do_sync_read) },
	{ 0xea71e805, __VMLINUX_SYMBOL_STR(unlock_new_inode) },
	{ 0x1ace3f1d, __VMLINUX_SYMBOL_STR(d_drop) },
	{ 0x6a037cf1, __VMLINUX_SYMBOL_STR(mempool_kfree) },
	{ 0xb678366f, __VMLINUX_SYMBOL_STR(int_sqrt) },
	{ 0x982404cc, __VMLINUX_SYMBOL_STR(generic_file_buffered_write) },
	{ 0x66d28b63, __VMLINUX_SYMBOL_STR(d_prune_aliases) },
	{ 0xb54676fa, __VMLINUX_SYMBOL_STR(ceph_msg_type_name) },
	{ 0x6f20960a, __VMLINUX_SYMBOL_STR(full_name_hash) },
	{ 0xa1d47d61, __VMLINUX_SYMBOL_STR(vfs_setpos) },
	{ 0xc8dbe553, __VMLINUX_SYMBOL_STR(ceph_msg_data_add_pagelist) },
	{ 0x55df4f71, __VMLINUX_SYMBOL_STR(clear_page_dirty_for_io) },
	{ 0x282870a, __VMLINUX_SYMBOL_STR(inode_change_ok) },
	{ 0x91aec064, __VMLINUX_SYMBOL_STR(down_read_trylock) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x2232a8a5, __VMLINUX_SYMBOL_STR(mempool_free) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0xa5526619, __VMLINUX_SYMBOL_STR(rb_insert_color) },
	{ 0x418ef697, __VMLINUX_SYMBOL_STR(ceph_auth_invalidate_authorizer) },
	{ 0x88e43e81, __VMLINUX_SYMBOL_STR(kmem_cache_create) },
	{ 0x1a92170e, __VMLINUX_SYMBOL_STR(register_filesystem) },
	{ 0x7d27876f, __VMLINUX_SYMBOL_STR(ceph_msg_new) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0xa9b5f948, __VMLINUX_SYMBOL_STR(d_lookup) },
	{ 0x5533868b, __VMLINUX_SYMBOL_STR(__pagevec_release) },
	{ 0xa05c03df, __VMLINUX_SYMBOL_STR(mempool_kmalloc) },
	{ 0x94b932f1, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0xe8efbcc5, __VMLINUX_SYMBOL_STR(default_backing_dev_info) },
	{ 0x646f02dd, __VMLINUX_SYMBOL_STR(iput) },
	{ 0x44bba238, __VMLINUX_SYMBOL_STR(finish_open) },
	{ 0x591f5053, __VMLINUX_SYMBOL_STR(posix_lock_file) },
	{ 0x1eb9516e, __VMLINUX_SYMBOL_STR(round_jiffies_relative) },
	{ 0x34c8f9, __VMLINUX_SYMBOL_STR(invalidate_inode_pages2_range) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x33152ef9, __VMLINUX_SYMBOL_STR(truncate_pagecache_range) },
	{ 0xd907d2fe, __VMLINUX_SYMBOL_STR(generic_permission) },
	{ 0xfc457764, __VMLINUX_SYMBOL_STR(do_sync_write) },
	{ 0x566efd27, __VMLINUX_SYMBOL_STR(ceph_copy_page_vector_to_user) },
	{ 0x20fd4671, __VMLINUX_SYMBOL_STR(ihold) },
	{ 0x1612e048, __VMLINUX_SYMBOL_STR(generic_file_splice_write) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xa75312bc, __VMLINUX_SYMBOL_STR(call_rcu_sched) },
	{ 0xf098a424, __VMLINUX_SYMBOL_STR(osd_req_op_extent_update) },
	{ 0x499cb58c, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0xb5a3101e, __VMLINUX_SYMBOL_STR(generic_error_remove_page) },
	{ 0x5379cea3, __VMLINUX_SYMBOL_STR(ceph_caps_for_mode) },
	{ 0x77692acb, __VMLINUX_SYMBOL_STR(ceph_msg_last_put) },
	{ 0x3f688151, __VMLINUX_SYMBOL_STR(ceph_put_snap_context) },
	{ 0xd2c107bb, __VMLINUX_SYMBOL_STR(ceph_flags_to_mode) },
	{ 0x3432d30, __VMLINUX_SYMBOL_STR(invalidate_mapping_pages) },
	{ 0x59c74d1d, __VMLINUX_SYMBOL_STR(generic_readlink) },
	{ 0x34fef0bf, __VMLINUX_SYMBOL_STR(put_page) },
	{ 0x9289a5b5, __VMLINUX_SYMBOL_STR(d_make_root) },
	{ 0x821ed24c, __VMLINUX_SYMBOL_STR(ceph_auth_destroy_authorizer) },
	{ 0x1cfb04fa, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x6d7153c3, __VMLINUX_SYMBOL_STR(bdi_destroy) },
	{ 0xca9360b5, __VMLINUX_SYMBOL_STR(rb_next) },
	{ 0x8290ccde, __VMLINUX_SYMBOL_STR(debugfs_create_symlink) },
	{ 0x7dc3609c, __VMLINUX_SYMBOL_STR(unregister_filesystem) },
	{ 0x5aea48fd, __VMLINUX_SYMBOL_STR(init_special_inode) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xf5c05914, __VMLINUX_SYMBOL_STR(generic_segment_checks) },
	{ 0xdeb21859, __VMLINUX_SYMBOL_STR(bdi_register) },
	{ 0xf551cab1, __VMLINUX_SYMBOL_STR(ceph_con_open) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0xb4b32206, __VMLINUX_SYMBOL_STR(generic_file_splice_read) },
	{ 0xa4d9dfcf, __VMLINUX_SYMBOL_STR(bdi_unregister) },
	{ 0x197effcb, __VMLINUX_SYMBOL_STR(ceph_osdc_release_request) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x6c5d5ac1, __VMLINUX_SYMBOL_STR(ceph_calc_pg_primary) },
	{ 0xe711c063, __VMLINUX_SYMBOL_STR(osd_req_op_extent_osd_data) },
	{ 0x7cf9099, __VMLINUX_SYMBOL_STR(wait_for_completion_timeout) },
	{ 0x68eb8a44, __VMLINUX_SYMBOL_STR(grab_cache_page_write_begin) },
	{ 0x1f57a4f0, __VMLINUX_SYMBOL_STR(ceph_create_client) },
	{ 0xae3515ba, __VMLINUX_SYMBOL_STR(ceph_create_snap_context) },
	{ 0xe8d30d19, __VMLINUX_SYMBOL_STR(simple_attr_open) },
	{ 0x146b7fa, __VMLINUX_SYMBOL_STR(d_instantiate) },
	{ 0x7d4e2276, __VMLINUX_SYMBOL_STR(__init_rwsem) },
	{ 0xa5dadb7c, __VMLINUX_SYMBOL_STR(ceph_msg_data_add_pages) },
	{ 0xa3932127, __VMLINUX_SYMBOL_STR(flush_dcache_page) },
	{ 0x43464a34, __VMLINUX_SYMBOL_STR(simple_attr_write) },
	{ 0x3ab0f55, __VMLINUX_SYMBOL_STR(ceph_osdc_build_request) },
	{ 0x12424aa, __VMLINUX_SYMBOL_STR(vfs_fsync_range) },
	{ 0xa92b44e0, __VMLINUX_SYMBOL_STR(generic_fillattr) },
	{ 0xb613a8a0, __VMLINUX_SYMBOL_STR(set_bdi_congested) },
	{ 0x3f494b3c, __VMLINUX_SYMBOL_STR(filemap_fdatawrite) },
	{ 0x8f914c89, __VMLINUX_SYMBOL_STR(truncate_inode_pages) },
	{ 0x5da359b4, __VMLINUX_SYMBOL_STR(ceph_con_keepalive) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=libceph";
