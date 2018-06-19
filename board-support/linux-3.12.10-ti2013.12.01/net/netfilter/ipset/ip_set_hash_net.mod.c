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
	{ 0xd0648ca, __VMLINUX_SYMBOL_STR(ip_set_type_unregister) },
	{ 0x9f38bcef, __VMLINUX_SYMBOL_STR(ip_set_type_register) },
	{ 0xcfc68341, __VMLINUX_SYMBOL_STR(synchronize_rcu_bh) },
	{ 0x799aca4, __VMLINUX_SYMBOL_STR(local_bh_enable) },
	{ 0x3bd1b1f6, __VMLINUX_SYMBOL_STR(msecs_to_jiffies) },
	{ 0x3ff62317, __VMLINUX_SYMBOL_STR(local_bh_disable) },
	{ 0xf6ebc03b, __VMLINUX_SYMBOL_STR(net_ratelimit) },
	{ 0x6344eaf6, __VMLINUX_SYMBOL_STR(ip_set_alloc) },
	{ 0x79aa04a2, __VMLINUX_SYMBOL_STR(get_random_bytes) },
	{ 0x593a99b, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0xbe2c0274, __VMLINUX_SYMBOL_STR(add_timer) },
	{ 0x8bd0a3fd, __VMLINUX_SYMBOL_STR(_raw_write_unlock_bh) },
	{ 0x85061b76, __VMLINUX_SYMBOL_STR(_raw_write_lock_bh) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x7924b6de, __VMLINUX_SYMBOL_STR(ip_set_hostmask_map) },
	{ 0xa2d623f3, __VMLINUX_SYMBOL_STR(ip_set_range_to_cidr) },
	{ 0xa293f8a6, __VMLINUX_SYMBOL_STR(ip_set_get_ipaddr4) },
	{ 0xde1c81f2, __VMLINUX_SYMBOL_STR(ip_set_get_extensions) },
	{ 0x9e98722b, __VMLINUX_SYMBOL_STR(ip_set_get_ipaddr6) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xd5f2172f, __VMLINUX_SYMBOL_STR(del_timer_sync) },
	{ 0x397f6231, __VMLINUX_SYMBOL_STR(ip_set_free) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x1fcf4d4b, __VMLINUX_SYMBOL_STR(_raw_read_unlock_bh) },
	{ 0xe11f3cbc, __VMLINUX_SYMBOL_STR(_raw_read_lock_bh) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x37befc70, __VMLINUX_SYMBOL_STR(jiffies_to_msecs) },
	{ 0x594ff15d, __VMLINUX_SYMBOL_STR(skb_trim) },
	{ 0x63096cbc, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x81fff2d1, __VMLINUX_SYMBOL_STR(ip_set_netmask_map) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=ip_set";

