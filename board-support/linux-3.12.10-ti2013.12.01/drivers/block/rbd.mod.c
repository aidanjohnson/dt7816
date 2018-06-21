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
	{ 0x96c3c292, __VMLINUX_SYMBOL_STR(bus_unregister) },
	{ 0xbc32724b, __VMLINUX_SYMBOL_STR(bus_register) },
	{ 0x88e43e81, __VMLINUX_SYMBOL_STR(kmem_cache_create) },
	{ 0x466b85b8, __VMLINUX_SYMBOL_STR(libceph_compatible) },
	{ 0xaccdabb8, __VMLINUX_SYMBOL_STR(device_register) },
	{ 0x8ecb1aa8, __VMLINUX_SYMBOL_STR(dev_set_name) },
	{ 0x86f870d5, __VMLINUX_SYMBOL_STR(add_disk) },
	{ 0xb2b27c17, __VMLINUX_SYMBOL_STR(blk_queue_merge_bvec) },
	{ 0xd167485e, __VMLINUX_SYMBOL_STR(blk_queue_io_opt) },
	{ 0xf489df62, __VMLINUX_SYMBOL_STR(blk_queue_io_min) },
	{ 0x6ed54cba, __VMLINUX_SYMBOL_STR(blk_queue_max_segment_size) },
	{ 0x8b286462, __VMLINUX_SYMBOL_STR(blk_queue_max_hw_sectors) },
	{ 0xefe79bef, __VMLINUX_SYMBOL_STR(blk_queue_physical_block_size) },
	{ 0xeac70ec4, __VMLINUX_SYMBOL_STR(blk_init_queue) },
	{ 0x2e2935bb, __VMLINUX_SYMBOL_STR(alloc_disk) },
	{ 0x71a50dbc, __VMLINUX_SYMBOL_STR(register_blkdev) },
	{ 0x1475bf0d, __VMLINUX_SYMBOL_STR(ceph_pg_poolid_by_name) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xecffec44, __VMLINUX_SYMBOL_STR(ceph_open_session) },
	{ 0x1f57a4f0, __VMLINUX_SYMBOL_STR(ceph_create_client) },
	{ 0x4205ffd7, __VMLINUX_SYMBOL_STR(ceph_destroy_options) },
	{ 0x622af644, __VMLINUX_SYMBOL_STR(ceph_compare_options) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xc55de604, __VMLINUX_SYMBOL_STR(ceph_parse_options) },
	{ 0xe2fae716, __VMLINUX_SYMBOL_STR(kmemdup) },
	{ 0x6c1ce5ce, __VMLINUX_SYMBOL_STR(strcspn) },
	{ 0xc7ec6c27, __VMLINUX_SYMBOL_STR(strspn) },
	{ 0xf5afcd9d, __VMLINUX_SYMBOL_STR(try_module_get) },
	{ 0xe82c9c32, __VMLINUX_SYMBOL_STR(ceph_pg_pool_name_by_id) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0xc499ae1e, __VMLINUX_SYMBOL_STR(kstrdup) },
	{ 0x7e80aa1b, __VMLINUX_SYMBOL_STR(blk_fetch_request) },
	{ 0x5a6564a, __VMLINUX_SYMBOL_STR(__blk_end_request_all) },
	{ 0xb9054356, __VMLINUX_SYMBOL_STR(osd_req_op_raw_data_in_pages) },
	{ 0x72ea036a, __VMLINUX_SYMBOL_STR(osd_req_op_init) },
	{ 0x371b3778, __VMLINUX_SYMBOL_STR(fs_bio_set) },
	{ 0x1aa51a6d, __VMLINUX_SYMBOL_STR(bio_alloc_bioset) },
	{ 0xa204bd35, __VMLINUX_SYMBOL_STR(bio_clone_bioset) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x8a4fa83b, __VMLINUX_SYMBOL_STR(__aeabi_llsr) },
	{ 0xbca31af2, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0x8552b5b9, __VMLINUX_SYMBOL_STR(device_unregister) },
	{ 0x5a92d00a, __VMLINUX_SYMBOL_STR(ceph_osdc_flush_notifies) },
	{ 0x996bdb64, __VMLINUX_SYMBOL_STR(_kstrtoul) },
	{ 0x1fb93159, __VMLINUX_SYMBOL_STR(ceph_osdc_cancel_event) },
	{ 0x494b813d, __VMLINUX_SYMBOL_STR(ceph_osdc_unregister_linger_request) },
	{ 0x4a3ec846, __VMLINUX_SYMBOL_STR(ceph_osdc_set_request_linger) },
	{ 0xf1ce0d04, __VMLINUX_SYMBOL_STR(ceph_osdc_create_event) },
	{ 0x83cfc229, __VMLINUX_SYMBOL_STR(osd_req_op_watch_init) },
	{ 0x2872096, __VMLINUX_SYMBOL_STR(revalidate_disk) },
	{ 0x83211609, __VMLINUX_SYMBOL_STR(up_write) },
	{ 0xa958ed4, __VMLINUX_SYMBOL_STR(down_write) },
	{ 0xd9ce8f0c, __VMLINUX_SYMBOL_STR(strnlen) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0x6606a424, __VMLINUX_SYMBOL_STR(osd_req_op_extent_osd_data_pages) },
	{ 0x1fbdb19, __VMLINUX_SYMBOL_STR(osd_req_op_extent_osd_data_bio) },
	{ 0xa5677aa5, __VMLINUX_SYMBOL_STR(osd_req_op_extent_init) },
	{ 0xae1429b9, __VMLINUX_SYMBOL_STR(osd_req_op_cls_request_data_pages) },
	{ 0x7eecc551, __VMLINUX_SYMBOL_STR(blk_end_request) },
	{ 0xae3515ba, __VMLINUX_SYMBOL_STR(ceph_create_snap_context) },
	{ 0x76cf47f6, __VMLINUX_SYMBOL_STR(__aeabi_llsl) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x8e4468d3, __VMLINUX_SYMBOL_STR(ceph_copy_from_page_vector) },
	{ 0xfd5683b9, __VMLINUX_SYMBOL_STR(wait_for_completion_interruptible) },
	{ 0xc40e2841, __VMLINUX_SYMBOL_STR(osd_req_op_cls_response_data_pages) },
	{ 0x85c35474, __VMLINUX_SYMBOL_STR(osd_req_op_cls_request_data_pagelist) },
	{ 0x6ed41be2, __VMLINUX_SYMBOL_STR(ceph_pagelist_append) },
	{ 0xa24d3d88, __VMLINUX_SYMBOL_STR(osd_req_op_cls_init) },
	{ 0x91da95fe, __VMLINUX_SYMBOL_STR(ceph_alloc_page_vector) },
	{ 0xda407237, __VMLINUX_SYMBOL_STR(ceph_osdc_alloc_request) },
	{ 0x63d684c9, __VMLINUX_SYMBOL_STR(put_device) },
	{ 0x44e9a829, __VMLINUX_SYMBOL_STR(match_token) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0x34184afe, __VMLINUX_SYMBOL_STR(current_kernel_time) },
	{ 0x3ab0f55, __VMLINUX_SYMBOL_STR(ceph_osdc_build_request) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xb64de2d, __VMLINUX_SYMBOL_STR(kmem_cache_destroy) },
	{ 0xb5a459dc, __VMLINUX_SYMBOL_STR(unregister_blkdev) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0xcbba804, __VMLINUX_SYMBOL_STR(put_disk) },
	{ 0x7425e3b4, __VMLINUX_SYMBOL_STR(blk_cleanup_queue) },
	{ 0xe0513bd5, __VMLINUX_SYMBOL_STR(del_gendisk) },
	{ 0x5adff968, __VMLINUX_SYMBOL_STR(ceph_client_id) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
	{ 0x57d1ea7f, __VMLINUX_SYMBOL_STR(set_device_ro) },
	{ 0x2c413068, __VMLINUX_SYMBOL_STR(get_device) },
	{ 0x3507a132, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irq) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x7d4e2276, __VMLINUX_SYMBOL_STR(__init_rwsem) },
	{ 0x3f688151, __VMLINUX_SYMBOL_STR(ceph_put_snap_context) },
	{ 0x2a547a33, __VMLINUX_SYMBOL_STR(ceph_destroy_client) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0x22e1ae6f, __VMLINUX_SYMBOL_STR(up_read) },
	{ 0x6b2e3bcd, __VMLINUX_SYMBOL_STR(ceph_get_snap_context) },
	{ 0x455293f6, __VMLINUX_SYMBOL_STR(down_read) },
	{ 0xab694444, __VMLINUX_SYMBOL_STR(bsearch) },
	{ 0x3c0ae3fe, __VMLINUX_SYMBOL_STR(ceph_osdc_start_request) },
	{ 0x81f3afb, __VMLINUX_SYMBOL_STR(complete_all) },
	{ 0xed93f29e, __VMLINUX_SYMBOL_STR(__kunmap_atomic) },
	{ 0xa3932127, __VMLINUX_SYMBOL_STR(flush_dcache_page) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x34d04659, __VMLINUX_SYMBOL_STR(kmap_atomic) },
	{ 0x88b454fd, __VMLINUX_SYMBOL_STR(kmem_cache_free) },
	{ 0x8487d868, __VMLINUX_SYMBOL_STR(ceph_release_page_vector) },
	{ 0xdfe6eaae, __VMLINUX_SYMBOL_STR(bio_put) },
	{ 0x197effcb, __VMLINUX_SYMBOL_STR(ceph_osdc_release_request) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xb0e93b81, __VMLINUX_SYMBOL_STR(kmem_cache_alloc) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=libceph";
