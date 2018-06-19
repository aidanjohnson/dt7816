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
	{ 0x69ba683, __VMLINUX_SYMBOL_STR(xt_unregister_target) },
	{ 0xa9c6a267, __VMLINUX_SYMBOL_STR(nf_log_unregister) },
	{ 0xdc8cb9d7, __VMLINUX_SYMBOL_STR(unregister_pernet_subsys) },
	{ 0x346fd450, __VMLINUX_SYMBOL_STR(nf_log_register) },
	{ 0x5882e4bf, __VMLINUX_SYMBOL_STR(xt_register_target) },
	{ 0xd7cb77a9, __VMLINUX_SYMBOL_STR(register_pernet_subsys) },
	{ 0x92e7a4b1, __VMLINUX_SYMBOL_STR(nf_log_packet) },
	{ 0xfc8b84a4, __VMLINUX_SYMBOL_STR(init_net) },
	{ 0xdd3916ac, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_bh) },
	{ 0x508cd864, __VMLINUX_SYMBOL_STR(ipv6_skip_exthdr) },
	{ 0xa1d55e90, __VMLINUX_SYMBOL_STR(_raw_spin_lock_bh) },
	{ 0x795cd955, __VMLINUX_SYMBOL_STR(nf_log_set) },
	{ 0x64759384, __VMLINUX_SYMBOL_STR(nf_log_unset) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xff924d9c, __VMLINUX_SYMBOL_STR(skb_copy_bits) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=x_tables";

