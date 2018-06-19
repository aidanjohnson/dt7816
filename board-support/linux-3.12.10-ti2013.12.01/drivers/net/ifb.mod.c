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
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0xd63271fb, __VMLINUX_SYMBOL_STR(eth_validate_addr) },
	{ 0xab4aa62b, __VMLINUX_SYMBOL_STR(rtnl_link_unregister) },
	{ 0x6e720ff2, __VMLINUX_SYMBOL_STR(rtnl_unlock) },
	{ 0xdcba543d, __VMLINUX_SYMBOL_STR(__rtnl_link_unregister) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0xc24d24cf, __VMLINUX_SYMBOL_STR(register_netdevice) },
	{ 0xfb4628f9, __VMLINUX_SYMBOL_STR(alloc_netdev_mqs) },
	{ 0x46f5606c, __VMLINUX_SYMBOL_STR(__rtnl_link_register) },
	{ 0xc7a4fbed, __VMLINUX_SYMBOL_STR(rtnl_lock) },
	{ 0xe94f1e83, __VMLINUX_SYMBOL_STR(free_netdev) },
	{ 0x79aa04a2, __VMLINUX_SYMBOL_STR(get_random_bytes) },
	{ 0xf1ef0fc0, __VMLINUX_SYMBOL_STR(ether_setup) },
	{ 0xfaef0ed, __VMLINUX_SYMBOL_STR(__tasklet_schedule) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0x36026fb7, __VMLINUX_SYMBOL_STR(__netif_schedule) },
	{ 0x2a3aa678, __VMLINUX_SYMBOL_STR(_test_and_clear_bit) },
	{ 0xe937e5af, __VMLINUX_SYMBOL_STR(dev_get_by_index_rcu) },
	{ 0xafcc3435, __VMLINUX_SYMBOL_STR(netif_receive_skb) },
	{ 0xe40dc473, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0xc11126ee, __VMLINUX_SYMBOL_STR(dev_queue_xmit) },
	{ 0x50d6202a, __VMLINUX_SYMBOL_STR(consume_skb) },
	{ 0x18bd76a4, __VMLINUX_SYMBOL_STR(_raw_spin_trylock) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x9545af6d, __VMLINUX_SYMBOL_STR(tasklet_init) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0x82072614, __VMLINUX_SYMBOL_STR(tasklet_kill) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

