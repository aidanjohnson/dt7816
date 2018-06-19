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
	{ 0x69ba683, __VMLINUX_SYMBOL_STR(xt_unregister_target) },
	{ 0xa9c6a267, __VMLINUX_SYMBOL_STR(nf_log_unregister) },
	{ 0xdc8cb9d7, __VMLINUX_SYMBOL_STR(unregister_pernet_subsys) },
	{ 0x346fd450, __VMLINUX_SYMBOL_STR(nf_log_register) },
	{ 0x5882e4bf, __VMLINUX_SYMBOL_STR(xt_register_target) },
	{ 0xd7cb77a9, __VMLINUX_SYMBOL_STR(register_pernet_subsys) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0xbe2c0274, __VMLINUX_SYMBOL_STR(add_timer) },
	{ 0xff924d9c, __VMLINUX_SYMBOL_STR(skb_copy_bits) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
	{ 0x4cdb3178, __VMLINUX_SYMBOL_STR(ns_to_timeval) },
	{ 0x2447533c, __VMLINUX_SYMBOL_STR(ktime_get_real) },
	{ 0x8dd61422, __VMLINUX_SYMBOL_STR(__nlmsg_put) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xc3e596f0, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0x795cd955, __VMLINUX_SYMBOL_STR(nf_log_set) },
	{ 0x2494f2e0, __VMLINUX_SYMBOL_STR(__netlink_kernel_create) },
	{ 0x593a99b, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x171ffa4f, __VMLINUX_SYMBOL_STR(netlink_kernel_release) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x64759384, __VMLINUX_SYMBOL_STR(nf_log_unset) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xdd3916ac, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_bh) },
	{ 0xa1d55e90, __VMLINUX_SYMBOL_STR(_raw_spin_lock_bh) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x455c3bc1, __VMLINUX_SYMBOL_STR(netlink_broadcast) },
	{ 0xc996d097, __VMLINUX_SYMBOL_STR(del_timer) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=x_tables";

