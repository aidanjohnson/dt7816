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
	{ 0x609f1c7e, __VMLINUX_SYMBOL_STR(synchronize_net) },
	{ 0x402b8281, __VMLINUX_SYMBOL_STR(__request_module) },
	{ 0x20ad0d61, __VMLINUX_SYMBOL_STR(netlink_has_listeners) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xc5544ff6, __VMLINUX_SYMBOL_STR(nlmsg_notify) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xdc8cb9d7, __VMLINUX_SYMBOL_STR(unregister_pernet_subsys) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xd2936c14, __VMLINUX_SYMBOL_STR(ns_capable) },
	{ 0x171ffa4f, __VMLINUX_SYMBOL_STR(netlink_kernel_release) },
	{ 0x24f77905, __VMLINUX_SYMBOL_STR(netlink_rcv_skb) },
	{ 0x7b90e1b4, __VMLINUX_SYMBOL_STR(netlink_alloc_skb) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xc2cdbf1, __VMLINUX_SYMBOL_STR(synchronize_sched) },
	{ 0xe4cb61ae, __VMLINUX_SYMBOL_STR(netlink_unicast) },
	{ 0x4f391d0e, __VMLINUX_SYMBOL_STR(nla_parse) },
	{ 0xd7cb77a9, __VMLINUX_SYMBOL_STR(register_pernet_subsys) },
	{ 0xf2d257c0, __VMLINUX_SYMBOL_STR(netlink_set_err) },
	{ 0x2494f2e0, __VMLINUX_SYMBOL_STR(__netlink_kernel_create) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

