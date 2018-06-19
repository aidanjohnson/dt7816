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
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x3b79fa87, __VMLINUX_SYMBOL_STR(nf_unregister_hooks) },
	{ 0xdc8cb9d7, __VMLINUX_SYMBOL_STR(unregister_pernet_subsys) },
	{ 0xad44eec5, __VMLINUX_SYMBOL_STR(nf_register_hooks) },
	{ 0xd7cb77a9, __VMLINUX_SYMBOL_STR(register_pernet_subsys) },
	{ 0x8539e264, __VMLINUX_SYMBOL_STR(nf_xfrm_me_harder) },
	{ 0xa06af5d5, __VMLINUX_SYMBOL_STR(ip_route_me_harder) },
	{ 0x9700966d, __VMLINUX_SYMBOL_STR(dst_release) },
	{ 0x26e106e3, __VMLINUX_SYMBOL_STR(__nf_ct_kill_acct) },
	{ 0x2f2af5fb, __VMLINUX_SYMBOL_STR(nf_nat_setup_info) },
	{ 0x2ead6cfd, __VMLINUX_SYMBOL_STR(nf_nat_packet) },
	{ 0x6e007468, __VMLINUX_SYMBOL_STR(ipt_do_table) },
	{ 0xc1912d0c, __VMLINUX_SYMBOL_STR(nf_nat_icmp_reply_translation) },
	{ 0x5fdb7019, __VMLINUX_SYMBOL_STR(__nf_ct_ext_add_length) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x134af262, __VMLINUX_SYMBOL_STR(ipt_register_table) },
	{ 0x22c69a33, __VMLINUX_SYMBOL_STR(ipt_alloc_initial_table) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x3b59b6f4, __VMLINUX_SYMBOL_STR(ipt_unregister_table) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=nf_nat,nf_conntrack,ip_tables,nf_nat_ipv4";

