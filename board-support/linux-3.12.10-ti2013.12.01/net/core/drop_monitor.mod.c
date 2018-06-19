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
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0x4205ad24, __VMLINUX_SYMBOL_STR(cancel_work_sync) },
	{ 0xd5f2172f, __VMLINUX_SYMBOL_STR(del_timer_sync) },
	{ 0x9d0d6206, __VMLINUX_SYMBOL_STR(unregister_netdevice_notifier) },
	{ 0xfe7c4287, __VMLINUX_SYMBOL_STR(nr_cpu_ids) },
	{ 0x7c62d042, __VMLINUX_SYMBOL_STR(cpu_possible_mask) },
	{ 0x1176e07f, __VMLINUX_SYMBOL_STR(__per_cpu_offset) },
	{ 0xd3f57a2, __VMLINUX_SYMBOL_STR(_find_next_bit_le) },
	{ 0x593a99b, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0x71469208, __VMLINUX_SYMBOL_STR(genl_unregister_family) },
	{ 0xd2da1048, __VMLINUX_SYMBOL_STR(register_netdevice_notifier) },
	{ 0x6bd4521c, __VMLINUX_SYMBOL_STR(__genl_register_family_with_ops) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xbca31af2, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0xc2cdbf1, __VMLINUX_SYMBOL_STR(synchronize_sched) },
	{ 0xc11bd00f, __VMLINUX_SYMBOL_STR(tracepoint_probe_unregister) },
	{ 0xfa012fe7, __VMLINUX_SYMBOL_STR(tracepoint_probe_register) },
	{ 0xf5afcd9d, __VMLINUX_SYMBOL_STR(try_module_get) },
	{ 0xbe2c0274, __VMLINUX_SYMBOL_STR(add_timer) },
	{ 0x14036fd5, __VMLINUX_SYMBOL_STR(__nla_reserve_nohdr) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xfc8b84a4, __VMLINUX_SYMBOL_STR(init_net) },
	{ 0x455c3bc1, __VMLINUX_SYMBOL_STR(netlink_broadcast) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x8834396c, __VMLINUX_SYMBOL_STR(mod_timer) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xa9351993, __VMLINUX_SYMBOL_STR(nla_reserve) },
	{ 0xc14f06c3, __VMLINUX_SYMBOL_STR(genlmsg_put) },
	{ 0xc3e596f0, __VMLINUX_SYMBOL_STR(__alloc_skb) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x9469482, __VMLINUX_SYMBOL_STR(kfree_call_rcu) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

