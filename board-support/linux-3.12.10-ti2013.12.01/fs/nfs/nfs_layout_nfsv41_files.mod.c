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
	{ 0xf8821b74, __VMLINUX_SYMBOL_STR(pnfs_unregister_layoutdriver) },
	{ 0x97a9b863, __VMLINUX_SYMBOL_STR(nfs4_schedule_session_recovery) },
	{ 0x51a7a5f, __VMLINUX_SYMBOL_STR(nfs4_set_ds_client) },
	{ 0x4807e661, __VMLINUX_SYMBOL_STR(nfs_request_add_commit_list) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xa0fbac79, __VMLINUX_SYMBOL_STR(wake_up_bit) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0x3f358d29, __VMLINUX_SYMBOL_STR(page_address) },
	{ 0x59467fb1, __VMLINUX_SYMBOL_STR(nfs_init_cinfo) },
	{ 0x97031f94, __VMLINUX_SYMBOL_STR(nfs_initiate_commit) },
	{ 0x2a3aa678, __VMLINUX_SYMBOL_STR(_test_and_clear_bit) },
	{ 0x8f58a708, __VMLINUX_SYMBOL_STR(nfs4_mark_deviceid_unavailable) },
	{ 0x91704d27, __VMLINUX_SYMBOL_STR(nfs_commitdata_alloc) },
	{ 0x7ba5bdfd, __VMLINUX_SYMBOL_STR(__tracepoint_nfs4_pnfs_commit_ds) },
	{ 0x57cc1978, __VMLINUX_SYMBOL_STR(nfs4_set_rw_stateid) },
	{ 0xf92f7cc2, __VMLINUX_SYMBOL_STR(nfs4_proc_getdeviceinfo) },
	{ 0xfc55d6db, __VMLINUX_SYMBOL_STR(__alloc_pages_nodemask) },
	{ 0xefcdad8e, __VMLINUX_SYMBOL_STR(nfs41_setup_sequence) },
	{ 0xcb491215, __VMLINUX_SYMBOL_STR(pnfs_generic_pg_test) },
	{ 0xb7e01627, __VMLINUX_SYMBOL_STR(nfs4_schedule_lease_recovery) },
	{ 0x29a55ef8, __VMLINUX_SYMBOL_STR(pnfs_update_layout) },
	{ 0x4e0a207f, __VMLINUX_SYMBOL_STR(rpc_exit) },
	{ 0xd4d7a32, __VMLINUX_SYMBOL_STR(_atomic_dec_and_lock) },
	{ 0x911d21b7, __VMLINUX_SYMBOL_STR(rpc_delay) },
	{ 0x292fcd4b, __VMLINUX_SYMBOL_STR(xdr_init_decode_pages) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x20c55ae0, __VMLINUX_SYMBOL_STR(sscanf) },
	{ 0x9aa1c6f1, __VMLINUX_SYMBOL_STR(_pnfs_return_layout) },
	{ 0x2e1ba6cf, __VMLINUX_SYMBOL_STR(nfs_request_remove_commit_list) },
	{ 0x2693521c, __VMLINUX_SYMBOL_STR(nfs4_find_get_deviceid) },
	{ 0x84b183ae, __VMLINUX_SYMBOL_STR(strncmp) },
	{ 0xfd699773, __VMLINUX_SYMBOL_STR(nfs4_find_or_create_ds_client) },
	{ 0xfa534d8, __VMLINUX_SYMBOL_STR(nfs_generic_pg_test) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x782cca3, __VMLINUX_SYMBOL_STR(nfs_pageio_reset_write_mds) },
	{ 0x6bcae52c, __VMLINUX_SYMBOL_STR(nfs_retry_commit) },
	{ 0x9a5e7038, __VMLINUX_SYMBOL_STR(nfs_initiate_write) },
	{ 0x97e4468, __VMLINUX_SYMBOL_STR(pnfs_destroy_layout) },
	{ 0x315f21bf, __VMLINUX_SYMBOL_STR(pnfs_put_lseg) },
	{ 0x306a1617, __VMLINUX_SYMBOL_STR(contig_page_data) },
	{ 0xa90270ea, __VMLINUX_SYMBOL_STR(nfs4_put_deviceid_node) },
	{ 0x59e5070d, __VMLINUX_SYMBOL_STR(__do_div64) },
	{ 0x7bd924af, __VMLINUX_SYMBOL_STR(nfs_put_client) },
	{ 0x8773a898, __VMLINUX_SYMBOL_STR(nfs4_insert_deviceid_node) },
	{ 0x1582a2da, __VMLINUX_SYMBOL_STR(pnfs_set_layoutcommit) },
	{ 0x170f3ed6, __VMLINUX_SYMBOL_STR(nfs41_maxgetdevinfo_overhead) },
	{ 0x617a218d, __VMLINUX_SYMBOL_STR(__cond_resched_lock) },
	{ 0xbe463073, __VMLINUX_SYMBOL_STR(nfs4_init_ds_session) },
	{ 0x9f984513, __VMLINUX_SYMBOL_STR(strrchr) },
	{ 0x85cd3250, __VMLINUX_SYMBOL_STR(__free_pages) },
	{ 0xdf9ae422, __VMLINUX_SYMBOL_STR(nfs_initiate_read) },
	{ 0xe49dd381, __VMLINUX_SYMBOL_STR(nfs4_schedule_stateid_recovery) },
	{ 0xf49d792d, __VMLINUX_SYMBOL_STR(nfs4_test_deviceid_unavailable) },
	{ 0x5300f07d, __VMLINUX_SYMBOL_STR(rpc_sleep_on) },
	{ 0xdc8139d, __VMLINUX_SYMBOL_STR(pnfs_generic_pg_readpages) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x9672e547, __VMLINUX_SYMBOL_STR(pnfs_read_done_resend_to_mds) },
	{ 0x89f22a3c, __VMLINUX_SYMBOL_STR(rpc_count_iostats) },
	{ 0x6f7c6df3, __VMLINUX_SYMBOL_STR(rpc_restart_call_prepare) },
	{ 0xa0ceef51, __VMLINUX_SYMBOL_STR(out_of_line_wait_on_bit) },
	{ 0x7251e3fe, __VMLINUX_SYMBOL_STR(rpc_wake_up_queued_task) },
	{ 0xfc9f42b1, __VMLINUX_SYMBOL_STR(rpc_pton) },
	{ 0x2745629c, __VMLINUX_SYMBOL_STR(pnfs_generic_pg_writepages) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xc4425a4c, __VMLINUX_SYMBOL_STR(__tracepoint_nfs4_pnfs_read) },
	{ 0xc77ede9b, __VMLINUX_SYMBOL_STR(pnfs_write_done_resend_to_mds) },
	{ 0x2750ed01, __VMLINUX_SYMBOL_STR(rpc_wake_up) },
	{ 0x860fe0f1, __VMLINUX_SYMBOL_STR(nfs_commitdata_release) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x84de4f8a, __VMLINUX_SYMBOL_STR(nfs_init_commit) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0x34a1edf1, __VMLINUX_SYMBOL_STR(xdr_inline_decode) },
	{ 0x40536a5a, __VMLINUX_SYMBOL_STR(__tracepoint_nfs4_pnfs_write) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0x89bc5a64, __VMLINUX_SYMBOL_STR(nfs_wait_bit_killable) },
	{ 0x59475264, __VMLINUX_SYMBOL_STR(nfs_pageio_reset_read_mds) },
	{ 0x18ffdc7a, __VMLINUX_SYMBOL_STR(nfs4_init_deviceid_node) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x47c8baf4, __VMLINUX_SYMBOL_STR(param_ops_uint) },
	{ 0x4c1d5992, __VMLINUX_SYMBOL_STR(nfs_remove_bad_delegation) },
	{ 0x2cb998fa, __VMLINUX_SYMBOL_STR(xdr_set_scratch_buffer) },
	{ 0xd542439, __VMLINUX_SYMBOL_STR(__ipv6_addr_type) },
	{ 0xfe7ad51a, __VMLINUX_SYMBOL_STR(pnfs_register_layoutdriver) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

