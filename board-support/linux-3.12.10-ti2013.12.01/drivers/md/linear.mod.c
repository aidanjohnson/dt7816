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
	{ 0xccd65b4c, __VMLINUX_SYMBOL_STR(mddev_congested) },
	{ 0xc312906b, __VMLINUX_SYMBOL_STR(generic_make_request) },
	{ 0x86c8f053, __VMLINUX_SYMBOL_STR(bio_endio) },
	{ 0x6c269097, __VMLINUX_SYMBOL_STR(bio_pair_release) },
	{ 0xf634c93b, __VMLINUX_SYMBOL_STR(bio_split) },
	{ 0xcf2b381c, __VMLINUX_SYMBOL_STR(bdevname) },
	{ 0xb628c3e0, __VMLINUX_SYMBOL_STR(md_flush_request) },
	{ 0x206ec28f, __VMLINUX_SYMBOL_STR(md_integrity_register) },
	{ 0xb2b27c17, __VMLINUX_SYMBOL_STR(blk_queue_merge_bvec) },
	{ 0x8d8e2086, __VMLINUX_SYMBOL_STR(md_check_no_bitmap) },
	{ 0x4b38d3df, __VMLINUX_SYMBOL_STR(blk_sync_queue) },
	{ 0x60a13e90, __VMLINUX_SYMBOL_STR(rcu_barrier) },
	{ 0x2247cba2, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0x9469482, __VMLINUX_SYMBOL_STR(kfree_call_rcu) },
	{ 0x2872096, __VMLINUX_SYMBOL_STR(revalidate_disk) },
	{ 0xfabdda90, __VMLINUX_SYMBOL_STR(md_set_array_sectors) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x6a26dd7e, __VMLINUX_SYMBOL_STR(disk_stack_limits) },
	{ 0x59e5070d, __VMLINUX_SYMBOL_STR(__do_div64) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x1e047854, __VMLINUX_SYMBOL_STR(warn_slowpath_fmt) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=md-mod";

