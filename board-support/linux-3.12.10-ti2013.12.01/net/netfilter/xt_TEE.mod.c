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
	{ 0xea2f6e60, __VMLINUX_SYMBOL_STR(xt_unregister_targets) },
	{ 0xe5e0ca4a, __VMLINUX_SYMBOL_STR(xt_register_targets) },
	{ 0x83e60378, __VMLINUX_SYMBOL_STR(ip_local_out) },
	{ 0xddde3c32, __VMLINUX_SYMBOL_STR(ip_route_output_flow) },
	{ 0x2124474, __VMLINUX_SYMBOL_STR(ip_send_check) },
	{ 0xfc8b84a4, __VMLINUX_SYMBOL_STR(init_net) },
	{ 0x7cf6ca92, __VMLINUX_SYMBOL_STR(nf_conntrack_untracked) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x1c7674e8, __VMLINUX_SYMBOL_STR(ip6_local_out) },
	{ 0x9700966d, __VMLINUX_SYMBOL_STR(dst_release) },
	{ 0x25f1c0bb, __VMLINUX_SYMBOL_STR(ip6_route_output) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x2a18c74, __VMLINUX_SYMBOL_STR(nf_conntrack_destroy) },
	{ 0x70260a1b, __VMLINUX_SYMBOL_STR(__pskb_copy) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xd2da1048, __VMLINUX_SYMBOL_STR(register_netdevice_notifier) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d0d6206, __VMLINUX_SYMBOL_STR(unregister_netdevice_notifier) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=x_tables,nf_conntrack";

