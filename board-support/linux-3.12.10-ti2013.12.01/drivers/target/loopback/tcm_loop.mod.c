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
	{ 0x5f5f1960, __VMLINUX_SYMBOL_STR(target_fabric_configfs_deregister) },
	{ 0x8c03d20c, __VMLINUX_SYMBOL_STR(destroy_workqueue) },
	{ 0xb64de2d, __VMLINUX_SYMBOL_STR(kmem_cache_destroy) },
	{ 0xaaa0d311, __VMLINUX_SYMBOL_STR(target_fabric_configfs_free) },
	{ 0xffa8efac, __VMLINUX_SYMBOL_STR(target_fabric_configfs_register) },
	{ 0x189c31a9, __VMLINUX_SYMBOL_STR(target_fabric_configfs_init) },
	{ 0x6d1fb2cd, __VMLINUX_SYMBOL_STR(driver_register) },
	{ 0xbc32724b, __VMLINUX_SYMBOL_STR(bus_register) },
	{ 0xb9debe, __VMLINUX_SYMBOL_STR(__root_device_register) },
	{ 0x88e43e81, __VMLINUX_SYMBOL_STR(kmem_cache_create) },
	{ 0x43a53735, __VMLINUX_SYMBOL_STR(__alloc_workqueue_key) },
	{ 0xaed0dc9f, __VMLINUX_SYMBOL_STR(scsi_device_put) },
	{ 0xb2987a33, __VMLINUX_SYMBOL_STR(scsi_remove_device) },
	{ 0x6544069, __VMLINUX_SYMBOL_STR(scsi_device_lookup) },
	{ 0xcae66210, __VMLINUX_SYMBOL_STR(core_tpg_deregister) },
	{ 0xb81bf74e, __VMLINUX_SYMBOL_STR(__transport_register_session) },
	{ 0x9c26624d, __VMLINUX_SYMBOL_STR(transport_free_session) },
	{ 0x46326340, __VMLINUX_SYMBOL_STR(core_tpg_check_initiator_node_acl) },
	{ 0x63de47cd, __VMLINUX_SYMBOL_STR(transport_init_session) },
	{ 0x84b183ae, __VMLINUX_SYMBOL_STR(strncmp) },
	{ 0x3d661388, __VMLINUX_SYMBOL_STR(transport_deregister_session) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0xfe21cf6, __VMLINUX_SYMBOL_STR(core_tpg_register) },
	{ 0x20000329, __VMLINUX_SYMBOL_STR(simple_strtoul) },
	{ 0xaccdabb8, __VMLINUX_SYMBOL_STR(device_register) },
	{ 0x8ecb1aa8, __VMLINUX_SYMBOL_STR(dev_set_name) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0x1e6d26a8, __VMLINUX_SYMBOL_STR(strstr) },
	{ 0x86a4889a, __VMLINUX_SYMBOL_STR(kmalloc_order_trace) },
	{ 0x8552b5b9, __VMLINUX_SYMBOL_STR(device_unregister) },
	{ 0x9fd7673d, __VMLINUX_SYMBOL_STR(sas_get_fabric_proto_ident) },
	{ 0x5bc24125, __VMLINUX_SYMBOL_STR(iscsi_get_fabric_proto_ident) },
	{ 0x614064ff, __VMLINUX_SYMBOL_STR(fc_get_fabric_proto_ident) },
	{ 0x1544a516, __VMLINUX_SYMBOL_STR(sas_get_pr_transport_id) },
	{ 0xe0ebfb81, __VMLINUX_SYMBOL_STR(iscsi_get_pr_transport_id) },
	{ 0xa1fbaec9, __VMLINUX_SYMBOL_STR(fc_get_pr_transport_id) },
	{ 0xf4c98d42, __VMLINUX_SYMBOL_STR(sas_get_pr_transport_id_len) },
	{ 0xbbda1abc, __VMLINUX_SYMBOL_STR(iscsi_get_pr_transport_id_len) },
	{ 0x3b5fd773, __VMLINUX_SYMBOL_STR(fc_get_pr_transport_id_len) },
	{ 0xc4d1f16f, __VMLINUX_SYMBOL_STR(sas_parse_pr_out_transport_id) },
	{ 0xece8e623, __VMLINUX_SYMBOL_STR(iscsi_parse_pr_out_transport_id) },
	{ 0x1beaa61f, __VMLINUX_SYMBOL_STR(fc_parse_pr_out_transport_id) },
	{ 0xb560fc25, __VMLINUX_SYMBOL_STR(target_execute_cmd) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x6f797f2, __VMLINUX_SYMBOL_STR(scsi_add_device) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xad69f86e, __VMLINUX_SYMBOL_STR(scsi_add_host_with_dma) },
	{ 0x3e34553, __VMLINUX_SYMBOL_STR(scsi_host_alloc) },
	{ 0x9c623e6f, __VMLINUX_SYMBOL_STR(target_submit_cmd_map_sgls) },
	{ 0xc29551e3, __VMLINUX_SYMBOL_STR(dev_printk) },
	{ 0xc8b57c27, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0x1cfb04fa, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0x499cb58c, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xb7184f60, __VMLINUX_SYMBOL_STR(transport_generic_handle_tmr) },
	{ 0xc4f3da22, __VMLINUX_SYMBOL_STR(transport_lookup_tmr_lun) },
	{ 0x8ed1fceb, __VMLINUX_SYMBOL_STR(core_tmr_alloc_req) },
	{ 0xb8e37010, __VMLINUX_SYMBOL_STR(transport_init_se_cmd) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xb0e93b81, __VMLINUX_SYMBOL_STR(kmem_cache_alloc) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x88b454fd, __VMLINUX_SYMBOL_STR(kmem_cache_free) },
	{ 0xbc1a8045, __VMLINUX_SYMBOL_STR(transport_generic_free_cmd) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0x63ad7ab8, __VMLINUX_SYMBOL_STR(scsi_adjust_queue_depth) },
	{ 0xd9e171b8, __VMLINUX_SYMBOL_STR(scsi_track_queue_full) },
	{ 0x2247cba2, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0x6a4865fd, __VMLINUX_SYMBOL_STR(scsi_host_put) },
	{ 0xbfbe31f9, __VMLINUX_SYMBOL_STR(scsi_remove_host) },
	{ 0x743e13fe, __VMLINUX_SYMBOL_STR(root_device_unregister) },
	{ 0x96c3c292, __VMLINUX_SYMBOL_STR(bus_unregister) },
	{ 0x1f05bf4a, __VMLINUX_SYMBOL_STR(driver_unregister) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=target_core_mod";

