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
	{ 0x402b8281, __VMLINUX_SYMBOL_STR(__request_module) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xfbc74f64, __VMLINUX_SYMBOL_STR(__copy_from_user) },
	{ 0xeeabd10b, __VMLINUX_SYMBOL_STR(xt_unregister_table) },
	{ 0xd6ee688f, __VMLINUX_SYMBOL_STR(vmalloc) },
	{ 0x40728a63, __VMLINUX_SYMBOL_STR(xt_find_revision) },
	{ 0x67c2fa54, __VMLINUX_SYMBOL_STR(__copy_to_user) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0x4740c9e5, __VMLINUX_SYMBOL_STR(xt_check_target) },
	{ 0xd55169c1, __VMLINUX_SYMBOL_STR(xt_register_matches) },
	{ 0x463e0bfc, __VMLINUX_SYMBOL_STR(xt_proto_fini) },
	{ 0x8ca65c07, __VMLINUX_SYMBOL_STR(xt_table_unlock) },
	{ 0xd3f57a2, __VMLINUX_SYMBOL_STR(_find_next_bit_le) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0x54a73e19, __VMLINUX_SYMBOL_STR(xt_find_table_lock) },
	{ 0xd4182c5e, __VMLINUX_SYMBOL_STR(ipv6_find_hdr) },
	{ 0x6de492e5, __VMLINUX_SYMBOL_STR(xt_replace_table) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x92e7a4b1, __VMLINUX_SYMBOL_STR(nf_log_packet) },
	{ 0x83b0da58, __VMLINUX_SYMBOL_STR(xt_proto_init) },
	{ 0x5b2a2e8f, __VMLINUX_SYMBOL_STR(xt_register_table) },
	{ 0xfe7c4287, __VMLINUX_SYMBOL_STR(nr_cpu_ids) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xdc8cb9d7, __VMLINUX_SYMBOL_STR(unregister_pernet_subsys) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0xd2936c14, __VMLINUX_SYMBOL_STR(ns_capable) },
	{ 0xe5e0ca4a, __VMLINUX_SYMBOL_STR(xt_register_targets) },
	{ 0x328a05f1, __VMLINUX_SYMBOL_STR(strncpy) },
	{ 0x807d2b2c, __VMLINUX_SYMBOL_STR(xt_recseq) },
	{ 0xea2f6e60, __VMLINUX_SYMBOL_STR(xt_unregister_targets) },
	{ 0xbca31af2, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0x3ff62317, __VMLINUX_SYMBOL_STR(local_bh_disable) },
	{ 0x40a9b349, __VMLINUX_SYMBOL_STR(vzalloc) },
	{ 0x7c62d042, __VMLINUX_SYMBOL_STR(cpu_possible_mask) },
	{ 0xa45fc51b, __VMLINUX_SYMBOL_STR(nf_unregister_sockopt) },
	{ 0x799aca4, __VMLINUX_SYMBOL_STR(local_bh_enable) },
	{ 0x349bc014, __VMLINUX_SYMBOL_STR(xt_request_find_match) },
	{ 0xd7cb77a9, __VMLINUX_SYMBOL_STR(register_pernet_subsys) },
	{ 0x1a0c7788, __VMLINUX_SYMBOL_STR(xt_unregister_matches) },
	{ 0x1176e07f, __VMLINUX_SYMBOL_STR(__per_cpu_offset) },
	{ 0x64af4675, __VMLINUX_SYMBOL_STR(xt_request_find_target) },
	{ 0xf6ebc03b, __VMLINUX_SYMBOL_STR(net_ratelimit) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xb741373e, __VMLINUX_SYMBOL_STR(xt_check_match) },
	{ 0x74c134b9, __VMLINUX_SYMBOL_STR(__sw_hweight32) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x39888fb2, __VMLINUX_SYMBOL_STR(nf_register_sockopt) },
	{ 0x8c473b7, __VMLINUX_SYMBOL_STR(xt_alloc_table_info) },
	{ 0xff924d9c, __VMLINUX_SYMBOL_STR(skb_copy_bits) },
	{ 0xb28f5ef1, __VMLINUX_SYMBOL_STR(xt_free_table_info) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=x_tables";

