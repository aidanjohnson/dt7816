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
	{ 0x5e686973, __VMLINUX_SYMBOL_STR(sbc_get_device_type) },
	{ 0x64999605, __VMLINUX_SYMBOL_STR(transport_subsystem_release) },
	{ 0x9baa4ea4, __VMLINUX_SYMBOL_STR(transport_subsystem_register) },
	{ 0x59e5070d, __VMLINUX_SYMBOL_STR(__do_div64) },
	{ 0xe5a39e92, __VMLINUX_SYMBOL_STR(blkdev_get_by_path) },
	{ 0xb988d6fd, __VMLINUX_SYMBOL_STR(bioset_create) },
	{ 0x7ca68c37, __VMLINUX_SYMBOL_STR(bioset_free) },
	{ 0x942b1b9e, __VMLINUX_SYMBOL_STR(blkdev_put) },
	{ 0x85df9b6c, __VMLINUX_SYMBOL_STR(strsep) },
	{ 0x996bdb64, __VMLINUX_SYMBOL_STR(_kstrtoul) },
	{ 0xacf4d843, __VMLINUX_SYMBOL_STR(match_strdup) },
	{ 0x462a2e75, __VMLINUX_SYMBOL_STR(match_strlcpy) },
	{ 0x44e9a829, __VMLINUX_SYMBOL_STR(match_token) },
	{ 0xc499ae1e, __VMLINUX_SYMBOL_STR(kstrdup) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xcf2b381c, __VMLINUX_SYMBOL_STR(bdevname) },
	{ 0xd5152710, __VMLINUX_SYMBOL_STR(sg_next) },
	{ 0x4adb45c2, __VMLINUX_SYMBOL_STR(bio_add_page) },
	{ 0x13b715e2, __VMLINUX_SYMBOL_STR(blk_finish_plug) },
	{ 0x65d67a20, __VMLINUX_SYMBOL_STR(blk_start_plug) },
	{ 0x371b3778, __VMLINUX_SYMBOL_STR(fs_bio_set) },
	{ 0x238014c3, __VMLINUX_SYMBOL_STR(submit_bio) },
	{ 0x1aa51a6d, __VMLINUX_SYMBOL_STR(bio_alloc_bioset) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xdfe6eaae, __VMLINUX_SYMBOL_STR(bio_put) },
	{ 0xa7ddb88e, __VMLINUX_SYMBOL_STR(target_complete_cmd) },
	{ 0x786ce5a3, __VMLINUX_SYMBOL_STR(sbc_get_write_same_sectors) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x4fe5186e, __VMLINUX_SYMBOL_STR(blkdev_issue_discard) },
	{ 0x4f29a9c, __VMLINUX_SYMBOL_STR(sbc_execute_unmap) },
	{ 0x3dc852c8, __VMLINUX_SYMBOL_STR(sbc_parse_cdb) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=target_core_mod";

