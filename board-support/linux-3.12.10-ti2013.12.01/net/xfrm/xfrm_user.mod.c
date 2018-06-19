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
	{ 0xc22487b3, __VMLINUX_SYMBOL_STR(xfrm_unregister_km) },
	{ 0xdc8cb9d7, __VMLINUX_SYMBOL_STR(unregister_pernet_subsys) },
	{ 0xb2f7e289, __VMLINUX_SYMBOL_STR(xfrm_register_km) },
	{ 0xd7cb77a9, __VMLINUX_SYMBOL_STR(register_pernet_subsys) },
	{ 0x244a8387, __VMLINUX_SYMBOL_STR(xfrm_state_delete) },
	{ 0x15add6a2, __VMLINUX_SYMBOL_STR(xfrm_state_lookup_byaddr) },
	{ 0xbc223114, __VMLINUX_SYMBOL_STR(xfrm_find_acq) },
	{ 0x1976fb6b, __VMLINUX_SYMBOL_STR(xfrm_alloc_spi) },
	{ 0x2f1cfc57, __VMLINUX_SYMBOL_STR(xfrm_find_acq_byseq) },
	{ 0x328a05f1, __VMLINUX_SYMBOL_STR(strncpy) },
	{ 0xbb5d343d, __VMLINUX_SYMBOL_STR(xfrm_get_acqseq) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x722c9c8a, __VMLINUX_SYMBOL_STR(xfrm_garbage_collect) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x17021341, __VMLINUX_SYMBOL_STR(xfrm_sad_getinfo) },
	{ 0x54c5e35d, __VMLINUX_SYMBOL_STR(xfrm_spd_getinfo) },
	{ 0xfc8b84a4, __VMLINUX_SYMBOL_STR(init_net) },
	{ 0x455c3bc1, __VMLINUX_SYMBOL_STR(netlink_broadcast) },
	{ 0x4f391d0e, __VMLINUX_SYMBOL_STR(nla_parse) },
	{ 0x11815a9b, __VMLINUX_SYMBOL_STR(__netlink_dump_start) },
	{ 0xd2936c14, __VMLINUX_SYMBOL_STR(ns_capable) },
	{ 0x7c30b8c7, __VMLINUX_SYMBOL_STR(xfrm_calg_get_byname) },
	{ 0x778770, __VMLINUX_SYMBOL_STR(xfrm_ealg_get_byname) },
	{ 0x41964d66, __VMLINUX_SYMBOL_STR(xfrm_init_replay) },
	{ 0x4e85ee5e, __VMLINUX_SYMBOL_STR(xfrm_audit_state_add) },
	{ 0x3faafa1a, __VMLINUX_SYMBOL_STR(xfrm_state_update) },
	{ 0xcb3d8064, __VMLINUX_SYMBOL_STR(xfrm_state_add) },
	{ 0x256bbf08, __VMLINUX_SYMBOL_STR(__xfrm_init_state) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xe122af95, __VMLINUX_SYMBOL_STR(xfrm_aalg_get_byname) },
	{ 0xb9e5852, __VMLINUX_SYMBOL_STR(xfrm_aead_get_byname) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
	{ 0xe2fae716, __VMLINUX_SYMBOL_STR(kmemdup) },
	{ 0x35a5f66, __VMLINUX_SYMBOL_STR(xfrm_state_walk) },
	{ 0x51dce73b, __VMLINUX_SYMBOL_STR(xfrm_state_walk_init) },
	{ 0x388f9128, __VMLINUX_SYMBOL_STR(xfrm_state_walk_done) },
	{ 0x88cfbcb0, __VMLINUX_SYMBOL_STR(xfrm_audit_policy_add) },
	{ 0x246cd22a, __VMLINUX_SYMBOL_STR(xfrm_policy_insert) },
	{ 0xff086e5b, __VMLINUX_SYMBOL_STR(xfrm_policy_walk) },
	{ 0xe5ed5467, __VMLINUX_SYMBOL_STR(xfrm_policy_walk_init) },
	{ 0x5614b010, __VMLINUX_SYMBOL_STR(xfrm_policy_walk_done) },
	{ 0xa9351993, __VMLINUX_SYMBOL_STR(nla_reserve) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xd12f8a8d, __VMLINUX_SYMBOL_STR(km_query) },
	{ 0x1c26a519, __VMLINUX_SYMBOL_STR(xfrm_state_alloc) },
	{ 0x9042a02d, __VMLINUX_SYMBOL_STR(xfrm_policy_alloc) },
	{ 0xd7541e49, __VMLINUX_SYMBOL_STR(xfrm_audit_state_delete) },
	{ 0xc6a488e6, __VMLINUX_SYMBOL_STR(__xfrm_state_delete) },
	{ 0x85a05a2f, __VMLINUX_SYMBOL_STR(km_state_expired) },
	{ 0xc1b0da08, __VMLINUX_SYMBOL_STR(xfrm_policy_destroy) },
	{ 0xdaff86f0, __VMLINUX_SYMBOL_STR(km_policy_expired) },
	{ 0x1e047854, __VMLINUX_SYMBOL_STR(warn_slowpath_fmt) },
	{ 0x67a4361a, __VMLINUX_SYMBOL_STR(xfrm_audit_policy_delete) },
	{ 0x5d791185, __VMLINUX_SYMBOL_STR(xfrm_policy_delete) },
	{ 0x2f601a4d, __VMLINUX_SYMBOL_STR(xfrm_policy_bysel_ctx) },
	{ 0x31125c40, __VMLINUX_SYMBOL_STR(xfrm_policy_byid) },
	{ 0xe1f06ae0, __VMLINUX_SYMBOL_STR(xfrm_state_flush) },
	{ 0x233598f0, __VMLINUX_SYMBOL_STR(km_policy_notify) },
	{ 0xba5493ef, __VMLINUX_SYMBOL_STR(xfrm_policy_flush) },
	{ 0x7e58f543, __VMLINUX_SYMBOL_STR(security_task_getsecid) },
	{ 0x1bcc27a3, __VMLINUX_SYMBOL_STR(km_state_notify) },
	{ 0xdd3916ac, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_bh) },
	{ 0xe4cb61ae, __VMLINUX_SYMBOL_STR(netlink_unicast) },
	{ 0xa1d55e90, __VMLINUX_SYMBOL_STR(_raw_spin_lock_bh) },
	{ 0x95c68e4a, __VMLINUX_SYMBOL_STR(__xfrm_state_destroy) },
	{ 0xc3e596f0, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0x643f723d, __VMLINUX_SYMBOL_STR(xfrm_state_lookup) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x594ff15d, __VMLINUX_SYMBOL_STR(skb_trim) },
	{ 0x8dd61422, __VMLINUX_SYMBOL_STR(__nlmsg_put) },
	{ 0x9a46dd01, __VMLINUX_SYMBOL_STR(xfrm_migrate) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x63096cbc, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0xb52bca23, __VMLINUX_SYMBOL_STR(xfrm_cfg_mutex) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x24f77905, __VMLINUX_SYMBOL_STR(netlink_rcv_skb) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x2494f2e0, __VMLINUX_SYMBOL_STR(__netlink_kernel_create) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x171ffa4f, __VMLINUX_SYMBOL_STR(netlink_kernel_release) },
	{ 0x609f1c7e, __VMLINUX_SYMBOL_STR(synchronize_net) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=xfrm_algo";

