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
	{ 0xb64de2d, __VMLINUX_SYMBOL_STR(kmem_cache_destroy) },
	{ 0x2bae5008, __VMLINUX_SYMBOL_STR(can_rx_register) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x60a13e90, __VMLINUX_SYMBOL_STR(rcu_barrier) },
	{ 0xc7a4fbed, __VMLINUX_SYMBOL_STR(rtnl_lock) },
	{ 0xb2038f57, __VMLINUX_SYMBOL_STR(skb_clone) },
	{ 0x87d204aa, __VMLINUX_SYMBOL_STR(skb_copy) },
	{ 0xe01682d0, __VMLINUX_SYMBOL_STR(__rtnl_register) },
	{ 0xd2da1048, __VMLINUX_SYMBOL_STR(register_netdevice_notifier) },
	{ 0x9d0d6206, __VMLINUX_SYMBOL_STR(unregister_netdevice_notifier) },
	{ 0x594ff15d, __VMLINUX_SYMBOL_STR(skb_trim) },
	{ 0xf1db1704, __VMLINUX_SYMBOL_STR(nla_memcpy) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0x63096cbc, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0x88b454fd, __VMLINUX_SYMBOL_STR(kmem_cache_free) },
	{ 0x17a66c39, __VMLINUX_SYMBOL_STR(dev_get_by_index) },
	{ 0xfc8b84a4, __VMLINUX_SYMBOL_STR(init_net) },
	{ 0x7da66c8d, __VMLINUX_SYMBOL_STR(can_send) },
	{ 0xc6cbbc89, __VMLINUX_SYMBOL_STR(capable) },
	{ 0xb0e93b81, __VMLINUX_SYMBOL_STR(kmem_cache_alloc) },
	{ 0x4f391d0e, __VMLINUX_SYMBOL_STR(nla_parse) },
	{ 0x6b2dc060, __VMLINUX_SYMBOL_STR(dump_stack) },
	{ 0x88e43e81, __VMLINUX_SYMBOL_STR(kmem_cache_create) },
	{ 0x579e0bf5, __VMLINUX_SYMBOL_STR(rtnl_unregister_all) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xe5a3cf98, __VMLINUX_SYMBOL_STR(can_rx_unregister) },
	{ 0x85670f1d, __VMLINUX_SYMBOL_STR(rtnl_is_locked) },
	{ 0x47c8baf4, __VMLINUX_SYMBOL_STR(param_ops_uint) },
	{ 0x8dd61422, __VMLINUX_SYMBOL_STR(__nlmsg_put) },
	{ 0x6e720ff2, __VMLINUX_SYMBOL_STR(rtnl_unlock) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=can";

