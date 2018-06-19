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
	{ 0xa9083704, __VMLINUX_SYMBOL_STR(dm_unregister_target) },
	{ 0x743cd8a8, __VMLINUX_SYMBOL_STR(dm_register_target) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xc5977995, __VMLINUX_SYMBOL_STR(md_run) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xb1425b32, __VMLINUX_SYMBOL_STR(dm_table_add_target_callbacks) },
	{ 0x306a1617, __VMLINUX_SYMBOL_STR(contig_page_data) },
	{ 0x34fef0bf, __VMLINUX_SYMBOL_STR(put_page) },
	{ 0x38a0b521, __VMLINUX_SYMBOL_STR(md_error) },
	{ 0xfc55d6db, __VMLINUX_SYMBOL_STR(__alloc_pages_nodemask) },
	{ 0xe7424251, __VMLINUX_SYMBOL_STR(dm_get_device) },
	{ 0x6d0f1f89, __VMLINUX_SYMBOL_STR(dm_table_get_mode) },
	{ 0x59e5070d, __VMLINUX_SYMBOL_STR(__do_div64) },
	{ 0xf4019fae, __VMLINUX_SYMBOL_STR(dm_set_target_max_io_len) },
	{ 0x79fe037b, __VMLINUX_SYMBOL_STR(raid5_set_cache_size) },
	{ 0xd5331292, __VMLINUX_SYMBOL_STR(md_rdev_init) },
	{ 0x1cea6b87, __VMLINUX_SYMBOL_STR(mddev_init) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x996bdb64, __VMLINUX_SYMBOL_STR(_kstrtoul) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0x74c134b9, __VMLINUX_SYMBOL_STR(__sw_hweight32) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0xf9e73082, __VMLINUX_SYMBOL_STR(scnprintf) },
	{ 0x1e98d590, __VMLINUX_SYMBOL_STR(md_raid5_congested) },
	{ 0xbbb9db62, __VMLINUX_SYMBOL_STR(md_raid10_congested) },
	{ 0x746b5628, __VMLINUX_SYMBOL_STR(md_raid1_congested) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x76cf47f6, __VMLINUX_SYMBOL_STR(__aeabi_llsl) },
	{ 0xad84bef8, __VMLINUX_SYMBOL_STR(dm_table_event) },
	{ 0xce92ba3f, __VMLINUX_SYMBOL_STR(md_stop) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x23cf9046, __VMLINUX_SYMBOL_STR(md_rdev_clear) },
	{ 0x45771896, __VMLINUX_SYMBOL_STR(dm_put_device) },
	{ 0x8732a5c1, __VMLINUX_SYMBOL_STR(md_stop_writes) },
	{ 0x414432c9, __VMLINUX_SYMBOL_STR(mddev_suspend) },
	{ 0xdade8ce9, __VMLINUX_SYMBOL_STR(mddev_resume) },
	{ 0x3f358d29, __VMLINUX_SYMBOL_STR(page_address) },
	{ 0x3d272bd7, __VMLINUX_SYMBOL_STR(sync_page_io) },
	{ 0xa144a3d6, __VMLINUX_SYMBOL_STR(bitmap_load) },
	{ 0xce651bb6, __VMLINUX_SYMBOL_STR(md_wakeup_thread) },
	{ 0xef7e9d5b, __VMLINUX_SYMBOL_STR(md_reap_sync_thread) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xaafdc258, __VMLINUX_SYMBOL_STR(strcasecmp) },
	{ 0xcc37f55c, __VMLINUX_SYMBOL_STR(blk_limits_io_opt) },
	{ 0x754dac78, __VMLINUX_SYMBOL_STR(blk_limits_io_min) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=dm-mod,md-mod,raid456,raid10,raid1";

