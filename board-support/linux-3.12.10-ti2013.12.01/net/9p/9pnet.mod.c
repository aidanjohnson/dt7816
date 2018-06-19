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
	{ 0x92b57248, __VMLINUX_SYMBOL_STR(flush_work) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x8ec06bd1, __VMLINUX_SYMBOL_STR(perf_tp_event) },
	{ 0xfbc74f64, __VMLINUX_SYMBOL_STR(__copy_from_user) },
	{ 0x67c2fa54, __VMLINUX_SYMBOL_STR(__copy_to_user) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0xc8b57c27, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0x1b6314fd, __VMLINUX_SYMBOL_STR(in_aton) },
	{ 0x4c86184b, __VMLINUX_SYMBOL_STR(remove_wait_queue) },
	{ 0xacf4d843, __VMLINUX_SYMBOL_STR(match_strdup) },
	{ 0xe883861, __VMLINUX_SYMBOL_STR(sock_release) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0x2a3aa678, __VMLINUX_SYMBOL_STR(_test_and_clear_bit) },
	{ 0x4205ad24, __VMLINUX_SYMBOL_STR(cancel_work_sync) },
	{ 0x44e9a829, __VMLINUX_SYMBOL_STR(match_token) },
	{ 0x3f2a0f29, __VMLINUX_SYMBOL_STR(init_user_ns) },
	{ 0x9621849f, __VMLINUX_SYMBOL_STR(ring_buffer_event_data) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x85df9b6c, __VMLINUX_SYMBOL_STR(strsep) },
	{ 0x3393d733, __VMLINUX_SYMBOL_STR(filter_current_check_discard) },
	{ 0xc499ae1e, __VMLINUX_SYMBOL_STR(kstrdup) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x28124e6f, __VMLINUX_SYMBOL_STR(make_kgid) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x3d315771, __VMLINUX_SYMBOL_STR(kernel_read) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x1bd3c1ea, __VMLINUX_SYMBOL_STR(trace_event_buffer_lock_reserve) },
	{ 0xfcfa912, __VMLINUX_SYMBOL_STR(trace_define_field) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xdaf23bd8, __VMLINUX_SYMBOL_STR(from_kuid) },
	{ 0x5d891a64, __VMLINUX_SYMBOL_STR(idr_destroy) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x20c55ae0, __VMLINUX_SYMBOL_STR(sscanf) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0x4096bf3b, __VMLINUX_SYMBOL_STR(from_kgid) },
	{ 0x84b183ae, __VMLINUX_SYMBOL_STR(strncmp) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x84ffea8b, __VMLINUX_SYMBOL_STR(idr_preload) },
	{ 0xf74dae0f, __VMLINUX_SYMBOL_STR(idr_alloc) },
	{ 0x4e3567f7, __VMLINUX_SYMBOL_STR(match_int) },
	{ 0x7a082438, __VMLINUX_SYMBOL_STR(fput) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0xdf401846, __VMLINUX_SYMBOL_STR(idr_remove) },
	{ 0x250521eb, __VMLINUX_SYMBOL_STR(ftrace_event_reg) },
	{ 0xbca31af2, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0xf1806da9, __VMLINUX_SYMBOL_STR(idr_find_slowpath) },
	{ 0xdaf2fd26, __VMLINUX_SYMBOL_STR(make_kuid) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0xfb6af58d, __VMLINUX_SYMBOL_STR(recalc_sigpending) },
	{ 0x6b2dc060, __VMLINUX_SYMBOL_STR(dump_stack) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0xe2dfda3e, __VMLINUX_SYMBOL_STR(sock_alloc_file) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0xc7bcbc8d, __VMLINUX_SYMBOL_STR(add_wait_queue) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x222ce52f, __VMLINUX_SYMBOL_STR(trace_event_raw_init) },
	{ 0x499cb58c, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0xd788742d, __VMLINUX_SYMBOL_STR(perf_trace_buf_prepare) },
	{ 0x69fadbe6, __VMLINUX_SYMBOL_STR(kernel_bind) },
	{ 0x5952aaf, __VMLINUX_SYMBOL_STR(fget) },
	{ 0x34fef0bf, __VMLINUX_SYMBOL_STR(put_page) },
	{ 0x1cfb04fa, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x47b6a10f, __VMLINUX_SYMBOL_STR(ftrace_print_symbols_seq) },
	{ 0xf6e04730, __VMLINUX_SYMBOL_STR(event_storage) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0x1e3a88fb, __VMLINUX_SYMBOL_STR(trace_seq_printf) },
	{ 0x99bb8806, __VMLINUX_SYMBOL_STR(memmove) },
	{ 0xa77a369d, __VMLINUX_SYMBOL_STR(idr_init) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x43b8e8d8, __VMLINUX_SYMBOL_STR(ftrace_raw_output_prep) },
	{ 0xa6020fd9, __VMLINUX_SYMBOL_STR(event_storage_mutex) },
	{ 0x498d293a, __VMLINUX_SYMBOL_STR(trace_buffer_unlock_commit) },
	{ 0xf5afcd9d, __VMLINUX_SYMBOL_STR(try_module_get) },
	{ 0x393f0f7a, __VMLINUX_SYMBOL_STR(__sock_create) },
	{ 0x103aa319, __VMLINUX_SYMBOL_STR(get_user_pages_fast) },
	{ 0xd2f175c2, __VMLINUX_SYMBOL_STR(vfs_write) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

