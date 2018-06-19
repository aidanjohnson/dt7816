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
	{ 0xb64de2d, __VMLINUX_SYMBOL_STR(kmem_cache_destroy) },
	{ 0x743cd8a8, __VMLINUX_SYMBOL_STR(dm_register_target) },
	{ 0x88e43e81, __VMLINUX_SYMBOL_STR(kmem_cache_create) },
	{ 0x64999478, __VMLINUX_SYMBOL_STR(congestion_wait) },
	{ 0x4adb45c2, __VMLINUX_SYMBOL_STR(bio_add_page) },
	{ 0x1aa51a6d, __VMLINUX_SYMBOL_STR(bio_alloc_bioset) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0x1fab5905, __VMLINUX_SYMBOL_STR(wait_for_completion) },
	{ 0xf88c3301, __VMLINUX_SYMBOL_STR(sg_init_table) },
	{ 0x3026722, __VMLINUX_SYMBOL_STR(mempool_alloc) },
	{ 0xefdd2345, __VMLINUX_SYMBOL_STR(sg_init_one) },
	{ 0xbb2c2d13, __VMLINUX_SYMBOL_STR(crypto_alloc_shash) },
	{ 0xed93f29e, __VMLINUX_SYMBOL_STR(__kunmap_atomic) },
	{ 0x8810ad5e, __VMLINUX_SYMBOL_STR(crypto_xor) },
	{ 0x34d04659, __VMLINUX_SYMBOL_STR(kmap_atomic) },
	{ 0xd4669fad, __VMLINUX_SYMBOL_STR(complete) },
	{ 0xdfe6eaae, __VMLINUX_SYMBOL_STR(bio_put) },
	{ 0xd985dc99, __VMLINUX_SYMBOL_STR(mempool_free_pages) },
	{ 0x53326531, __VMLINUX_SYMBOL_STR(mempool_alloc_pages) },
	{ 0x6a037cf1, __VMLINUX_SYMBOL_STR(mempool_kfree) },
	{ 0xa05c03df, __VMLINUX_SYMBOL_STR(mempool_kmalloc) },
	{ 0x8a99a016, __VMLINUX_SYMBOL_STR(mempool_free_slab) },
	{ 0x183fa88b, __VMLINUX_SYMBOL_STR(mempool_alloc_slab) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x43a53735, __VMLINUX_SYMBOL_STR(__alloc_workqueue_key) },
	{ 0x5eb24829, __VMLINUX_SYMBOL_STR(dm_shift_arg) },
	{ 0xe04f7caa, __VMLINUX_SYMBOL_STR(dm_read_arg_group) },
	{ 0xe7424251, __VMLINUX_SYMBOL_STR(dm_get_device) },
	{ 0x6d0f1f89, __VMLINUX_SYMBOL_STR(dm_table_get_mode) },
	{ 0xb988d6fd, __VMLINUX_SYMBOL_STR(bioset_create) },
	{ 0x2b4e956e, __VMLINUX_SYMBOL_STR(mempool_create) },
	{ 0x730e7296, __VMLINUX_SYMBOL_STR(crypto_alloc_ablkcipher) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x50c89f23, __VMLINUX_SYMBOL_STR(__alloc_percpu) },
	{ 0x20c55ae0, __VMLINUX_SYMBOL_STR(sscanf) },
	{ 0x85df9b6c, __VMLINUX_SYMBOL_STR(strsep) },
	{ 0xc499ae1e, __VMLINUX_SYMBOL_STR(kstrdup) },
	{ 0x349cba85, __VMLINUX_SYMBOL_STR(strchr) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xf67f7196, __VMLINUX_SYMBOL_STR(crypto_alloc_base) },
	{ 0x58b63545, __VMLINUX_SYMBOL_STR(crypto_shash_update) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x1176e07f, __VMLINUX_SYMBOL_STR(__per_cpu_offset) },
	{ 0xfe7c4287, __VMLINUX_SYMBOL_STR(nr_cpu_ids) },
	{ 0x7c62d042, __VMLINUX_SYMBOL_STR(cpu_possible_mask) },
	{ 0xc9ec4e21, __VMLINUX_SYMBOL_STR(free_percpu) },
	{ 0x45771896, __VMLINUX_SYMBOL_STR(dm_put_device) },
	{ 0xa58fea9d, __VMLINUX_SYMBOL_STR(mempool_destroy) },
	{ 0x7ca68c37, __VMLINUX_SYMBOL_STR(bioset_free) },
	{ 0xd3f57a2, __VMLINUX_SYMBOL_STR(_find_next_bit_le) },
	{ 0x8c03d20c, __VMLINUX_SYMBOL_STR(destroy_workqueue) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x7a4497db, __VMLINUX_SYMBOL_STR(kzfree) },
	{ 0x2b18d6e2, __VMLINUX_SYMBOL_STR(crypto_destroy_tfm) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x86c8f053, __VMLINUX_SYMBOL_STR(bio_endio) },
	{ 0x2232a8a5, __VMLINUX_SYMBOL_STR(mempool_free) },
	{ 0xc312906b, __VMLINUX_SYMBOL_STR(generic_make_request) },
	{ 0xa204bd35, __VMLINUX_SYMBOL_STR(bio_clone_bioset) },
	{ 0xf9e73082, __VMLINUX_SYMBOL_STR(scnprintf) },
	{ 0x76cf47f6, __VMLINUX_SYMBOL_STR(__aeabi_llsl) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xaafdc258, __VMLINUX_SYMBOL_STR(strcasecmp) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x5a5a94a6, __VMLINUX_SYMBOL_STR(kstrtou8) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=dm-mod";

