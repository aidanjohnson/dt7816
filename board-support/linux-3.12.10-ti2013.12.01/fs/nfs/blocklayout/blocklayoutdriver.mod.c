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
	{ 0xf8821b74, __VMLINUX_SYMBOL_STR(pnfs_unregister_layoutdriver) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0x6f17b5b3, __VMLINUX_SYMBOL_STR(pnfs_generic_pg_init_write) },
	{ 0x371b3778, __VMLINUX_SYMBOL_STR(fs_bio_set) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xfbc74f64, __VMLINUX_SYMBOL_STR(__copy_from_user) },
	{ 0x1aa51a6d, __VMLINUX_SYMBOL_STR(bio_alloc_bioset) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xaaa14361, __VMLINUX_SYMBOL_STR(nfs_dreq_bytes_left) },
	{ 0x3f358d29, __VMLINUX_SYMBOL_STR(page_address) },
	{ 0x4c86184b, __VMLINUX_SYMBOL_STR(remove_wait_queue) },
	{ 0x677b9823, __VMLINUX_SYMBOL_STR(rpc_unlink) },
	{ 0xaed50637, __VMLINUX_SYMBOL_STR(pnfs_ld_write_done) },
	{ 0x30cada8f, __VMLINUX_SYMBOL_STR(radix_tree_next_hole) },
	{ 0xe68b90f6, __VMLINUX_SYMBOL_STR(test_set_page_writeback) },
	{ 0x7fd7a7b1, __VMLINUX_SYMBOL_STR(__lock_page) },
	{ 0xa1d55e90, __VMLINUX_SYMBOL_STR(_raw_spin_lock_bh) },
	{ 0x7bf11e89, __VMLINUX_SYMBOL_STR(dput) },
	{ 0x3ca31f35, __VMLINUX_SYMBOL_STR(nfs_net_id) },
	{ 0x23bfded, __VMLINUX_SYMBOL_STR(nfs4_proc_getdevicelist) },
	{ 0xf92f7cc2, __VMLINUX_SYMBOL_STR(nfs4_proc_getdeviceinfo) },
	{ 0xfe7bb07, __VMLINUX_SYMBOL_STR(rpc_mkpipe_data) },
	{ 0x9f16b706, __VMLINUX_SYMBOL_STR(rpc_mkpipe_dentry) },
	{ 0xfc55d6db, __VMLINUX_SYMBOL_STR(__alloc_pages_nodemask) },
	{ 0x58158965, __VMLINUX_SYMBOL_STR(xdr_reserve_space) },
	{ 0xcb491215, __VMLINUX_SYMBOL_STR(pnfs_generic_pg_test) },
	{ 0x369f3371, __VMLINUX_SYMBOL_STR(end_page_writeback) },
	{ 0xc17c036b, __VMLINUX_SYMBOL_STR(rpc_get_sb_net) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xffd5a395, __VMLINUX_SYMBOL_STR(default_wake_function) },
	{ 0x34d04659, __VMLINUX_SYMBOL_STR(kmap_atomic) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x292fcd4b, __VMLINUX_SYMBOL_STR(xdr_init_decode_pages) },
	{ 0xe0a45875, __VMLINUX_SYMBOL_STR(rpc_queue_upcall) },
	{ 0xdc8cb9d7, __VMLINUX_SYMBOL_STR(unregister_pernet_subsys) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0x4adb45c2, __VMLINUX_SYMBOL_STR(bio_add_page) },
	{ 0x29c189e, __VMLINUX_SYMBOL_STR(find_or_create_page) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x782cca3, __VMLINUX_SYMBOL_STR(nfs_pageio_reset_write_mds) },
	{ 0xed93f29e, __VMLINUX_SYMBOL_STR(__kunmap_atomic) },
	{ 0x35d86f64, __VMLINUX_SYMBOL_STR(rpc_d_lookup_sb) },
	{ 0x52c8cafd, __VMLINUX_SYMBOL_STR(blkdev_get_by_dev) },
	{ 0x11d8dcdf, __VMLINUX_SYMBOL_STR(wait_on_page_bit) },
	{ 0x7c1d8ae6, __VMLINUX_SYMBOL_STR(unlock_page) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0x306a1617, __VMLINUX_SYMBOL_STR(contig_page_data) },
	{ 0xdfe6eaae, __VMLINUX_SYMBOL_STR(bio_put) },
	{ 0x59e5070d, __VMLINUX_SYMBOL_STR(__do_div64) },
	{ 0x97b738f0, __VMLINUX_SYMBOL_STR(bh_submit_read) },
	{ 0x170f3ed6, __VMLINUX_SYMBOL_STR(nfs41_maxgetdevinfo_overhead) },
	{ 0xbca31af2, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0x80becce4, __VMLINUX_SYMBOL_STR(rpc_pipe_generic_upcall) },
	{ 0x238014c3, __VMLINUX_SYMBOL_STR(submit_bio) },
	{ 0x387e1639, __VMLINUX_SYMBOL_STR(rpc_pipefs_notifier_register) },
	{ 0x85cd3250, __VMLINUX_SYMBOL_STR(__free_pages) },
	{ 0xaf26d70d, __VMLINUX_SYMBOL_STR(rpc_destroy_pipe_data) },
	{ 0x942b1b9e, __VMLINUX_SYMBOL_STR(blkdev_put) },
	{ 0xdb939b7b, __VMLINUX_SYMBOL_STR(free_buffer_head) },
	{ 0xdd3916ac, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_bh) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0xd7cb77a9, __VMLINUX_SYMBOL_STR(register_pernet_subsys) },
	{ 0x477d9d2e, __VMLINUX_SYMBOL_STR(rpc_put_sb_net) },
	{ 0xdc8139d, __VMLINUX_SYMBOL_STR(pnfs_generic_pg_readpages) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x65994f1, __VMLINUX_SYMBOL_STR(xdr_encode_opaque_fixed) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0xc7bcbc8d, __VMLINUX_SYMBOL_STR(add_wait_queue) },
	{ 0x2745629c, __VMLINUX_SYMBOL_STR(pnfs_generic_pg_writepages) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x147ff5f8, __VMLINUX_SYMBOL_STR(pnfs_generic_pg_init_read) },
	{ 0x34fef0bf, __VMLINUX_SYMBOL_STR(put_page) },
	{ 0xb51a3724, __VMLINUX_SYMBOL_STR(rpc_pipefs_notifier_unregister) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x34a1edf1, __VMLINUX_SYMBOL_STR(xdr_inline_decode) },
	{ 0xa37efdd3, __VMLINUX_SYMBOL_STR(find_get_page) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0x8a4fa83b, __VMLINUX_SYMBOL_STR(__aeabi_llsr) },
	{ 0x59475264, __VMLINUX_SYMBOL_STR(nfs_pageio_reset_read_mds) },
	{ 0x6a5a31d6, __VMLINUX_SYMBOL_STR(pnfs_set_lo_fail) },
	{ 0x2cb998fa, __VMLINUX_SYMBOL_STR(xdr_set_scratch_buffer) },
	{ 0xa3932127, __VMLINUX_SYMBOL_STR(flush_dcache_page) },
	{ 0x115fdec5, __VMLINUX_SYMBOL_STR(pnfs_ld_read_done) },
	{ 0x96e39853, __VMLINUX_SYMBOL_STR(alloc_page_buffers) },
	{ 0xf5afcd9d, __VMLINUX_SYMBOL_STR(try_module_get) },
	{ 0xfe7ad51a, __VMLINUX_SYMBOL_STR(pnfs_register_layoutdriver) },
	{ 0x5b6fb024, __VMLINUX_SYMBOL_STR(bh_uptodate_or_lock) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

