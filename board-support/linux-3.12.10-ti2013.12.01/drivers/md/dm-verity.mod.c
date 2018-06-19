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
	{ 0x47c8baf4, __VMLINUX_SYMBOL_STR(param_ops_uint) },
	{ 0xa9083704, __VMLINUX_SYMBOL_STR(dm_unregister_target) },
	{ 0x743cd8a8, __VMLINUX_SYMBOL_STR(dm_register_target) },
	{ 0x3909d3a8, __VMLINUX_SYMBOL_STR(dm_bufio_prefetch) },
	{ 0x7272c3c8, __VMLINUX_SYMBOL_STR(cpu_online_mask) },
	{ 0x6a037cf1, __VMLINUX_SYMBOL_STR(mempool_kfree) },
	{ 0xa05c03df, __VMLINUX_SYMBOL_STR(mempool_kmalloc) },
	{ 0x43a53735, __VMLINUX_SYMBOL_STR(__alloc_workqueue_key) },
	{ 0x74c134b9, __VMLINUX_SYMBOL_STR(__sw_hweight32) },
	{ 0x2b4e956e, __VMLINUX_SYMBOL_STR(mempool_create) },
	{ 0x62a23587, __VMLINUX_SYMBOL_STR(dm_bufio_get_device_size) },
	{ 0x80e1a60c, __VMLINUX_SYMBOL_STR(dm_bufio_client_create) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0xaa4a7797, __VMLINUX_SYMBOL_STR(hex2bin) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xbb2c2d13, __VMLINUX_SYMBOL_STR(crypto_alloc_shash) },
	{ 0xc499ae1e, __VMLINUX_SYMBOL_STR(kstrdup) },
	{ 0xe7424251, __VMLINUX_SYMBOL_STR(dm_get_device) },
	{ 0x20c55ae0, __VMLINUX_SYMBOL_STR(sscanf) },
	{ 0x6d0f1f89, __VMLINUX_SYMBOL_STR(dm_table_get_mode) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x76cf47f6, __VMLINUX_SYMBOL_STR(__aeabi_llsl) },
	{ 0x45771896, __VMLINUX_SYMBOL_STR(dm_put_device) },
	{ 0x2b18d6e2, __VMLINUX_SYMBOL_STR(crypto_destroy_tfm) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xeca7949e, __VMLINUX_SYMBOL_STR(dm_bufio_client_destroy) },
	{ 0xa58fea9d, __VMLINUX_SYMBOL_STR(mempool_destroy) },
	{ 0x8c03d20c, __VMLINUX_SYMBOL_STR(destroy_workqueue) },
	{ 0xed93f29e, __VMLINUX_SYMBOL_STR(__kunmap_atomic) },
	{ 0x34d04659, __VMLINUX_SYMBOL_STR(kmap_atomic) },
	{ 0xe6024e59, __VMLINUX_SYMBOL_STR(dm_bufio_release) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0x88a554a7, __VMLINUX_SYMBOL_STR(crypto_shash_final) },
	{ 0x58b63545, __VMLINUX_SYMBOL_STR(crypto_shash_update) },
	{ 0x594952bd, __VMLINUX_SYMBOL_STR(dm_bufio_read) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x74dcd98c, __VMLINUX_SYMBOL_STR(dm_bufio_get_aux_data) },
	{ 0x86c8f053, __VMLINUX_SYMBOL_STR(bio_endio) },
	{ 0x2232a8a5, __VMLINUX_SYMBOL_STR(mempool_free) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x19f5809b, __VMLINUX_SYMBOL_STR(dm_ratelimit_state) },
	{ 0xc312906b, __VMLINUX_SYMBOL_STR(generic_make_request) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x3026722, __VMLINUX_SYMBOL_STR(mempool_alloc) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x72350130, __VMLINUX_SYMBOL_STR(___ratelimit) },
	{ 0x8a4fa83b, __VMLINUX_SYMBOL_STR(__aeabi_llsr) },
	{ 0xf9e73082, __VMLINUX_SYMBOL_STR(scnprintf) },
	{ 0x6cbef71e, __VMLINUX_SYMBOL_STR(__blkdev_driver_ioctl) },
	{ 0xf7207248, __VMLINUX_SYMBOL_STR(scsi_verify_blk_ioctl) },
	{ 0x754dac78, __VMLINUX_SYMBOL_STR(blk_limits_io_min) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=dm-mod,dm-bufio";

