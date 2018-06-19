#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.arch = MODULE_ARCH_INIT,
};

MODULE_INFO(intree, "Y");

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xb5c97a0d, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xd4da7cba, __VMLINUX_SYMBOL_STR(vb2_put_vma) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xe52e3763, __VMLINUX_SYMBOL_STR(mem_map) },
	{ 0x3f358d29, __VMLINUX_SYMBOL_STR(page_address) },
	{ 0x655b8063, __VMLINUX_SYMBOL_STR(arm_dma_ops) },
	{ 0xc57df12a, __VMLINUX_SYMBOL_STR(dma_buf_detach) },
	{ 0xfb752ce8, __VMLINUX_SYMBOL_STR(set_page_dirty_lock) },
	{ 0xd5152710, __VMLINUX_SYMBOL_STR(sg_next) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x51e77c97, __VMLINUX_SYMBOL_STR(pfn_valid) },
	{ 0x6ccf7bd7, __VMLINUX_SYMBOL_STR(__pv_phys_offset) },
	{ 0xf6836ba3, __VMLINUX_SYMBOL_STR(dma_common_get_sgtable) },
	{ 0xbfb8d6f, __VMLINUX_SYMBOL_STR(follow_pfn) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x336e4314, __VMLINUX_SYMBOL_STR(vb2_get_vma) },
	{ 0x216c4974, __VMLINUX_SYMBOL_STR(dma_buf_unmap_attachment) },
	{ 0xcdd158d, __VMLINUX_SYMBOL_STR(sg_alloc_table) },
	{ 0x79ae86f6, __VMLINUX_SYMBOL_STR(find_vma) },
	{ 0x20c10d1e, __VMLINUX_SYMBOL_STR(dma_buf_map_attachment) },
	{ 0x63d684c9, __VMLINUX_SYMBOL_STR(put_device) },
	{ 0xa5083cf1, __VMLINUX_SYMBOL_STR(get_user_pages) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x45c1c1e2, __VMLINUX_SYMBOL_STR(dma_buf_attach) },
	{ 0x2c413068, __VMLINUX_SYMBOL_STR(get_device) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xa32fc9c3, __VMLINUX_SYMBOL_STR(vb2_common_vm_ops) },
	{ 0x34fef0bf, __VMLINUX_SYMBOL_STR(put_page) },
	{ 0x322af836, __VMLINUX_SYMBOL_STR(sg_alloc_table_from_pages) },
	{ 0xcbb77fcf, __VMLINUX_SYMBOL_STR(dma_buf_export_named) },
	{ 0xf57488de, __VMLINUX_SYMBOL_STR(dma_common_mmap) },
	{ 0x9cd60539, __VMLINUX_SYMBOL_STR(sg_free_table) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=videobuf2-memops";

