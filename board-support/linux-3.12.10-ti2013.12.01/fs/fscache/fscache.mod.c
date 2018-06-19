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
	{ 0x32d5baca, __VMLINUX_SYMBOL_STR(kobject_put) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0xb64de2d, __VMLINUX_SYMBOL_STR(kmem_cache_destroy) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x22e1ae6f, __VMLINUX_SYMBOL_STR(up_read) },
	{ 0x3fab3ca9, __VMLINUX_SYMBOL_STR(register_sysctl_table) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xa0fbac79, __VMLINUX_SYMBOL_STR(wake_up_bit) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0x43a53735, __VMLINUX_SYMBOL_STR(__alloc_workqueue_key) },
	{ 0xc8b57c27, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0xe43274bc, __VMLINUX_SYMBOL_STR(proc_dointvec) },
	{ 0x19db6c4b, __VMLINUX_SYMBOL_STR(kobject_uevent) },
	{ 0xd3f57a2, __VMLINUX_SYMBOL_STR(_find_next_bit_le) },
	{ 0x2a3aa678, __VMLINUX_SYMBOL_STR(_test_and_clear_bit) },
	{ 0x688c3c76, __VMLINUX_SYMBOL_STR(remove_proc_entry) },
	{ 0xa26d9b4f, __VMLINUX_SYMBOL_STR(workqueue_congested) },
	{ 0xe29e1d0e, __VMLINUX_SYMBOL_STR(out_of_line_wait_on_atomic_t) },
	{ 0x737de5e9, __VMLINUX_SYMBOL_STR(radix_tree_tag_get) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x455293f6, __VMLINUX_SYMBOL_STR(down_read) },
	{ 0x216ce896, __VMLINUX_SYMBOL_STR(kobject_create_and_add) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xfe7c4287, __VMLINUX_SYMBOL_STR(nr_cpu_ids) },
	{ 0xd8ded085, __VMLINUX_SYMBOL_STR(radix_tree_maybe_preload) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x3e300a64, __VMLINUX_SYMBOL_STR(proc_mkdir) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x18bd76a4, __VMLINUX_SYMBOL_STR(_raw_spin_trylock) },
	{ 0xf31b3fd1, __VMLINUX_SYMBOL_STR(workqueue_set_max_active) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0x88b454fd, __VMLINUX_SYMBOL_STR(kmem_cache_free) },
	{ 0x8c03d20c, __VMLINUX_SYMBOL_STR(destroy_workqueue) },
	{ 0xb6822a33, __VMLINUX_SYMBOL_STR(radix_tree_gang_lookup_tag) },
	{ 0x83211609, __VMLINUX_SYMBOL_STR(up_write) },
	{ 0xa958ed4, __VMLINUX_SYMBOL_STR(down_write) },
	{ 0xf2f138ef, __VMLINUX_SYMBOL_STR(__get_page_tail) },
	{ 0x5d5b5a16, __VMLINUX_SYMBOL_STR(radix_tree_delete) },
	{ 0xa1f0ebea, __VMLINUX_SYMBOL_STR(bit_waitqueue) },
	{ 0x783b3563, __VMLINUX_SYMBOL_STR(wake_up_atomic_t) },
	{ 0x617a218d, __VMLINUX_SYMBOL_STR(__cond_resched_lock) },
	{ 0xb0e93b81, __VMLINUX_SYMBOL_STR(kmem_cache_alloc) },
	{ 0x54434d6, __VMLINUX_SYMBOL_STR(radix_tree_tag_set) },
	{ 0xe912da6b, __VMLINUX_SYMBOL_STR(unregister_sysctl_table) },
	{ 0x7c62d042, __VMLINUX_SYMBOL_STR(cpu_possible_mask) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0xd62c833f, __VMLINUX_SYMBOL_STR(schedule_timeout) },
	{ 0x6b2dc060, __VMLINUX_SYMBOL_STR(dump_stack) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x1176e07f, __VMLINUX_SYMBOL_STR(__per_cpu_offset) },
	{ 0x5642793a, __VMLINUX_SYMBOL_STR(radix_tree_tag_clear) },
	{ 0x88e43e81, __VMLINUX_SYMBOL_STR(kmem_cache_create) },
	{ 0x7afa89fc, __VMLINUX_SYMBOL_STR(vsnprintf) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x5533868b, __VMLINUX_SYMBOL_STR(__pagevec_release) },
	{ 0xa0ceef51, __VMLINUX_SYMBOL_STR(out_of_line_wait_on_bit) },
	{ 0xb9f18815, __VMLINUX_SYMBOL_STR(kernel_kobj) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x4ab66610, __VMLINUX_SYMBOL_STR(pagevec_lookup) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x499cb58c, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0xa414882d, __VMLINUX_SYMBOL_STR(add_wait_queue_exclusive) },
	{ 0x34fef0bf, __VMLINUX_SYMBOL_STR(put_page) },
	{ 0x74c134b9, __VMLINUX_SYMBOL_STR(__sw_hweight32) },
	{ 0x1cfb04fa, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x870bf928, __VMLINUX_SYMBOL_STR(radix_tree_lookup) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0xf202c5cb, __VMLINUX_SYMBOL_STR(radix_tree_insert) },
	{ 0x47c8baf4, __VMLINUX_SYMBOL_STR(param_ops_uint) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

