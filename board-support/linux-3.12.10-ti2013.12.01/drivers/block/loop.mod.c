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
	{ 0x86d6a42b, __VMLINUX_SYMBOL_STR(d_path) },
	{ 0x371b3778, __VMLINUX_SYMBOL_STR(fs_bio_set) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x2e2935bb, __VMLINUX_SYMBOL_STR(alloc_disk) },
	{ 0xff178f6, __VMLINUX_SYMBOL_STR(__aeabi_idivmod) },
	{ 0xfbc74f64, __VMLINUX_SYMBOL_STR(__copy_from_user) },
	{ 0x7425e3b4, __VMLINUX_SYMBOL_STR(blk_cleanup_queue) },
	{ 0x1aa51a6d, __VMLINUX_SYMBOL_STR(bio_alloc_bioset) },
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x67c2fa54, __VMLINUX_SYMBOL_STR(__copy_to_user) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0x3a9b6fb9, __VMLINUX_SYMBOL_STR(blk_unregister_region) },
	{ 0x3f358d29, __VMLINUX_SYMBOL_STR(page_address) },
	{ 0xc8b57c27, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0x19db6c4b, __VMLINUX_SYMBOL_STR(kobject_uevent) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x1da5e798, __VMLINUX_SYMBOL_STR(vfs_fsync) },
	{ 0xbbc975e8, __VMLINUX_SYMBOL_STR(blk_queue_flush) },
	{ 0x4881d505, __VMLINUX_SYMBOL_STR(idr_for_each) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xfc55d6db, __VMLINUX_SYMBOL_STR(__alloc_pages_nodemask) },
	{ 0xb0cab2d5, __VMLINUX_SYMBOL_STR(sysfs_remove_group) },
	{ 0xbd59f360, __VMLINUX_SYMBOL_STR(kthread_create_on_node) },
	{ 0x2cbe5bf9, __VMLINUX_SYMBOL_STR(nonseekable_open) },
	{ 0xf98d7712, __VMLINUX_SYMBOL_STR(splice_direct_to_actor) },
	{ 0x3416022, __VMLINUX_SYMBOL_STR(invalidate_bdev) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0x1fab5905, __VMLINUX_SYMBOL_STR(wait_for_completion) },
	{ 0x34d04659, __VMLINUX_SYMBOL_STR(kmap_atomic) },
	{ 0x73572db2, __VMLINUX_SYMBOL_STR(misc_register) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x57d1ea7f, __VMLINUX_SYMBOL_STR(set_device_ro) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x3674e151, __VMLINUX_SYMBOL_STR(blk_alloc_queue) },
	{ 0x5d891a64, __VMLINUX_SYMBOL_STR(idr_destroy) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x90a20675, __VMLINUX_SYMBOL_STR(kthread_stop) },
	{ 0xce917ae3, __VMLINUX_SYMBOL_STR(sysfs_create_group) },
	{ 0xe0513bd5, __VMLINUX_SYMBOL_STR(del_gendisk) },
	{ 0xfe67cbd6, __VMLINUX_SYMBOL_STR(kunmap) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0x64977c2d, __VMLINUX_SYMBOL_STR(blk_register_region) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xed93f29e, __VMLINUX_SYMBOL_STR(__kunmap_atomic) },
	{ 0x71a50dbc, __VMLINUX_SYMBOL_STR(register_blkdev) },
	{ 0xe57e68bb, __VMLINUX_SYMBOL_STR(noop_llseek) },
	{ 0xd94a33c, __VMLINUX_SYMBOL_STR(__splice_from_pipe) },
	{ 0xf74dae0f, __VMLINUX_SYMBOL_STR(idr_alloc) },
	{ 0x7a082438, __VMLINUX_SYMBOL_STR(fput) },
	{ 0x5e95afd0, __VMLINUX_SYMBOL_STR(get_disk) },
	{ 0x306a1617, __VMLINUX_SYMBOL_STR(contig_page_data) },
	{ 0x86c8f053, __VMLINUX_SYMBOL_STR(bio_endio) },
	{ 0xdfe6eaae, __VMLINUX_SYMBOL_STR(bio_put) },
	{ 0xdf401846, __VMLINUX_SYMBOL_STR(idr_remove) },
	{ 0xb5a459dc, __VMLINUX_SYMBOL_STR(unregister_blkdev) },
	{ 0xbca31af2, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0xc6cbbc89, __VMLINUX_SYMBOL_STR(capable) },
	{ 0x85cd3250, __VMLINUX_SYMBOL_STR(__free_pages) },
	{ 0xf1806da9, __VMLINUX_SYMBOL_STR(idr_find_slowpath) },
	{ 0x5744fc3a, __VMLINUX_SYMBOL_STR(bd_set_size) },
	{ 0x180d1e52, __VMLINUX_SYMBOL_STR(kmap) },
	{ 0x1efe6ec3, __VMLINUX_SYMBOL_STR(blk_queue_make_request) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0xcbba804, __VMLINUX_SYMBOL_STR(put_disk) },
	{ 0x3507a132, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irq) },
	{ 0x517e0e19, __VMLINUX_SYMBOL_STR(bdgrab) },
	{ 0x26021bc4, __VMLINUX_SYMBOL_STR(wake_up_process) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x74971a96, __VMLINUX_SYMBOL_STR(__module_get) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0xb3f7646e, __VMLINUX_SYMBOL_STR(kthread_should_stop) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xfa4ee31, __VMLINUX_SYMBOL_STR(__sb_end_write) },
	{ 0x499cb58c, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0x86f870d5, __VMLINUX_SYMBOL_STR(add_disk) },
	{ 0x7734e841, __VMLINUX_SYMBOL_STR(set_user_nice) },
	{ 0x5952aaf, __VMLINUX_SYMBOL_STR(fget) },
	{ 0xd0eaecdc, __VMLINUX_SYMBOL_STR(__sb_start_write) },
	{ 0x1cfb04fa, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x6e27fb5b, __VMLINUX_SYMBOL_STR(ioctl_by_bdev) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xd4669fad, __VMLINUX_SYMBOL_STR(complete) },
	{ 0x99bb8806, __VMLINUX_SYMBOL_STR(memmove) },
	{ 0xa962640c, __VMLINUX_SYMBOL_STR(set_blocksize) },
	{ 0x99367682, __VMLINUX_SYMBOL_STR(zero_fill_bio) },
	{ 0xa17bdc05, __VMLINUX_SYMBOL_STR(vfs_getattr) },
	{ 0x49ac0df0, __VMLINUX_SYMBOL_STR(misc_deregister) },
	{ 0x8a4d2902, __VMLINUX_SYMBOL_STR(bdput) },
	{ 0xa3932127, __VMLINUX_SYMBOL_STR(flush_dcache_page) },
	{ 0xf5afcd9d, __VMLINUX_SYMBOL_STR(try_module_get) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

