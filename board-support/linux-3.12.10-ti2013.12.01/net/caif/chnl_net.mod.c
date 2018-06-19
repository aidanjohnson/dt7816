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
	{ 0xfb3dec2b, __VMLINUX_SYMBOL_STR(unregister_netdevice_queue) },
	{ 0xab4aa62b, __VMLINUX_SYMBOL_STR(rtnl_link_unregister) },
	{ 0x1ac8eab4, __VMLINUX_SYMBOL_STR(rtnl_link_register) },
	{ 0xc24d24cf, __VMLINUX_SYMBOL_STR(register_netdevice) },
	{ 0x6aa0ac2d, __VMLINUX_SYMBOL_STR(netdev_state_change) },
	{ 0xe94f1e83, __VMLINUX_SYMBOL_STR(free_netdev) },
	{ 0xb7b6874e, __VMLINUX_SYMBOL_STR(caif_free_client) },
	{ 0x5bc60d2f, __VMLINUX_SYMBOL_STR(netif_rx_ni) },
	{ 0xfcd5641, __VMLINUX_SYMBOL_STR(netif_rx) },
	{ 0xff924d9c, __VMLINUX_SYMBOL_STR(skb_copy_bits) },
	{ 0x4a237e57, __VMLINUX_SYMBOL_STR(cfpkt_tonative) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x1446b60a, __VMLINUX_SYMBOL_STR(caif_client_register_refcnt) },
	{ 0x36026fb7, __VMLINUX_SYMBOL_STR(__netif_schedule) },
	{ 0x2a3aa678, __VMLINUX_SYMBOL_STR(_test_and_clear_bit) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x799aca4, __VMLINUX_SYMBOL_STR(local_bh_enable) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x3ff62317, __VMLINUX_SYMBOL_STR(local_bh_disable) },
	{ 0x7785cc9a, __VMLINUX_SYMBOL_STR(dev_close) },
	{ 0x328a05f1, __VMLINUX_SYMBOL_STR(strncpy) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xc8b57c27, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0xc7a4fbed, __VMLINUX_SYMBOL_STR(rtnl_lock) },
	{ 0x1cfb04fa, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0xd62c833f, __VMLINUX_SYMBOL_STR(schedule_timeout) },
	{ 0x499cb58c, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x6e720ff2, __VMLINUX_SYMBOL_STR(rtnl_unlock) },
	{ 0xf724ee1, __VMLINUX_SYMBOL_STR(dev_set_mtu) },
	{ 0x17a66c39, __VMLINUX_SYMBOL_STR(dev_get_by_index) },
	{ 0x59e61283, __VMLINUX_SYMBOL_STR(caif_connect_client) },
	{ 0x988b4005, __VMLINUX_SYMBOL_STR(caif_disconnect_client) },
	{ 0x6b2dc060, __VMLINUX_SYMBOL_STR(dump_stack) },
	{ 0x85670f1d, __VMLINUX_SYMBOL_STR(rtnl_is_locked) },
	{ 0x2a09f713, __VMLINUX_SYMBOL_STR(cfpkt_fromnative) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0x63096cbc, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=caif";

