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
	{ 0xb64de2d, __VMLINUX_SYMBOL_STR(kmem_cache_destroy) },
	{ 0x402b8281, __VMLINUX_SYMBOL_STR(__request_module) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x22e1ae6f, __VMLINUX_SYMBOL_STR(up_read) },
	{ 0xd6ee688f, __VMLINUX_SYMBOL_STR(vmalloc) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xa0fbac79, __VMLINUX_SYMBOL_STR(wake_up_bit) },
	{ 0xe7424251, __VMLINUX_SYMBOL_STR(dm_get_device) },
	{ 0x668cadbb, __VMLINUX_SYMBOL_STR(dm_io) },
	{ 0x43a53735, __VMLINUX_SYMBOL_STR(__alloc_workqueue_key) },
	{ 0xc8b57c27, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0x6d0f1f89, __VMLINUX_SYMBOL_STR(dm_table_get_mode) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0x76cf47f6, __VMLINUX_SYMBOL_STR(__aeabi_llsl) },
	{ 0x154c6338, __VMLINUX_SYMBOL_STR(dm_kcopyd_client_destroy) },
	{ 0xa58fea9d, __VMLINUX_SYMBOL_STR(mempool_destroy) },
	{ 0xc79bcd36, __VMLINUX_SYMBOL_STR(dm_vcalloc) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0x743cd8a8, __VMLINUX_SYMBOL_STR(dm_register_target) },
	{ 0xa6b602a4, __VMLINUX_SYMBOL_STR(dm_kcopyd_copy) },
	{ 0xc499ae1e, __VMLINUX_SYMBOL_STR(kstrdup) },
	{ 0x455293f6, __VMLINUX_SYMBOL_STR(down_read) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x9e4faeef, __VMLINUX_SYMBOL_STR(dm_io_client_destroy) },
	{ 0x183fa88b, __VMLINUX_SYMBOL_STR(mempool_alloc_slab) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xad84bef8, __VMLINUX_SYMBOL_STR(dm_table_event) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xf4019fae, __VMLINUX_SYMBOL_STR(dm_set_target_max_io_len) },
	{ 0x11089ac7, __VMLINUX_SYMBOL_STR(_ctype) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xa9083704, __VMLINUX_SYMBOL_STR(dm_unregister_target) },
	{ 0x88b454fd, __VMLINUX_SYMBOL_STR(kmem_cache_free) },
	{ 0x8c03d20c, __VMLINUX_SYMBOL_STR(destroy_workqueue) },
	{ 0xe9e0387f, __VMLINUX_SYMBOL_STR(dm_suspended) },
	{ 0xc312906b, __VMLINUX_SYMBOL_STR(generic_make_request) },
	{ 0x8a99a016, __VMLINUX_SYMBOL_STR(mempool_free_slab) },
	{ 0x83211609, __VMLINUX_SYMBOL_STR(up_write) },
	{ 0xa958ed4, __VMLINUX_SYMBOL_STR(down_write) },
	{ 0x42160169, __VMLINUX_SYMBOL_STR(flush_workqueue) },
	{ 0x86c8f053, __VMLINUX_SYMBOL_STR(bio_endio) },
	{ 0x59e5070d, __VMLINUX_SYMBOL_STR(__do_div64) },
	{ 0xbca31af2, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0x9f984513, __VMLINUX_SYMBOL_STR(strrchr) },
	{ 0x40a9b349, __VMLINUX_SYMBOL_STR(vzalloc) },
	{ 0xb0e93b81, __VMLINUX_SYMBOL_STR(kmem_cache_alloc) },
	{ 0x3026722, __VMLINUX_SYMBOL_STR(mempool_alloc) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0xd688716b, __VMLINUX_SYMBOL_STR(dm_kcopyd_client_create) },
	{ 0x2b4e956e, __VMLINUX_SYMBOL_STR(mempool_create) },
	{ 0x3507a132, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irq) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x2232a8a5, __VMLINUX_SYMBOL_STR(mempool_free) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x88e43e81, __VMLINUX_SYMBOL_STR(kmem_cache_create) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0xa0ceef51, __VMLINUX_SYMBOL_STR(out_of_line_wait_on_bit) },
	{ 0x601f665f, __VMLINUX_SYMBOL_STR(dm_io_client_create) },
	{ 0x7880c781, __VMLINUX_SYMBOL_STR(dm_kcopyd_prepare_callback) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xa46f2f1b, __VMLINUX_SYMBOL_STR(kstrtouint) },
	{ 0x499cb58c, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0xf9e73082, __VMLINUX_SYMBOL_STR(scnprintf) },
	{ 0x1cfb04fa, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x40a2d1dd, __VMLINUX_SYMBOL_STR(dm_table_get_size) },
	{ 0x45771896, __VMLINUX_SYMBOL_STR(dm_put_device) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0x8a4fa83b, __VMLINUX_SYMBOL_STR(__aeabi_llsr) },
	{ 0x4b5fd49e, __VMLINUX_SYMBOL_STR(dm_kcopyd_do_callback) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x47c8baf4, __VMLINUX_SYMBOL_STR(param_ops_uint) },
	{ 0x7d4e2276, __VMLINUX_SYMBOL_STR(__init_rwsem) },
	{ 0xf5afcd9d, __VMLINUX_SYMBOL_STR(try_module_get) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=dm-mod";

