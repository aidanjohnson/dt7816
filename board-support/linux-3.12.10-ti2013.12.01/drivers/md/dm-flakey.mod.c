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
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x743cd8a8, __VMLINUX_SYMBOL_STR(dm_register_target) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0xaafdc258, __VMLINUX_SYMBOL_STR(strcasecmp) },
	{ 0xe04f7caa, __VMLINUX_SYMBOL_STR(dm_read_arg_group) },
	{ 0xe7424251, __VMLINUX_SYMBOL_STR(dm_get_device) },
	{ 0x6d0f1f89, __VMLINUX_SYMBOL_STR(dm_table_get_mode) },
	{ 0x46feb099, __VMLINUX_SYMBOL_STR(dm_read_arg) },
	{ 0x20c55ae0, __VMLINUX_SYMBOL_STR(sscanf) },
	{ 0x5eb24829, __VMLINUX_SYMBOL_STR(dm_shift_arg) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x45771896, __VMLINUX_SYMBOL_STR(dm_put_device) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x86c8f053, __VMLINUX_SYMBOL_STR(bio_endio) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x3f358d29, __VMLINUX_SYMBOL_STR(page_address) },
	{ 0xf9e73082, __VMLINUX_SYMBOL_STR(scnprintf) },
	{ 0x6cbef71e, __VMLINUX_SYMBOL_STR(__blkdev_driver_ioctl) },
	{ 0xf7207248, __VMLINUX_SYMBOL_STR(scsi_verify_blk_ioctl) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=dm-mod";

