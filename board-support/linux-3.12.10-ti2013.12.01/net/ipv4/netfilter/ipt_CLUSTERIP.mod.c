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
	{ 0x92c80041, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0x94b932f1, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0xf499fdb2, __VMLINUX_SYMBOL_STR(rcu_barrier_bh) },
	{ 0x69ba683, __VMLINUX_SYMBOL_STR(xt_unregister_target) },
	{ 0xf45a1013, __VMLINUX_SYMBOL_STR(nf_unregister_hook) },
	{ 0x3e300a64, __VMLINUX_SYMBOL_STR(proc_mkdir) },
	{ 0x3908c76c, __VMLINUX_SYMBOL_STR(nf_register_hook) },
	{ 0x5882e4bf, __VMLINUX_SYMBOL_STR(xt_register_target) },
	{ 0xdde0b0af, __VMLINUX_SYMBOL_STR(seq_open) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xf6ebc03b, __VMLINUX_SYMBOL_STR(net_ratelimit) },
	{ 0xff924d9c, __VMLINUX_SYMBOL_STR(skb_copy_bits) },
	{ 0xfc8b84a4, __VMLINUX_SYMBOL_STR(init_net) },
	{ 0x78f9b710, __VMLINUX_SYMBOL_STR(nf_ct_l3proto_try_module_get) },
	{ 0x9a2915f5, __VMLINUX_SYMBOL_STR(dev_mc_add) },
	{ 0xdd3916ac, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_bh) },
	{ 0xa1d55e90, __VMLINUX_SYMBOL_STR(_raw_spin_lock_bh) },
	{ 0xf9141363, __VMLINUX_SYMBOL_STR(proc_create_data) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xa6822854, __VMLINUX_SYMBOL_STR(dev_get_by_name) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x2a3aa678, __VMLINUX_SYMBOL_STR(_test_and_clear_bit) },
	{ 0xca54fee, __VMLINUX_SYMBOL_STR(_test_and_set_bit) },
	{ 0x996bdb64, __VMLINUX_SYMBOL_STR(_kstrtoul) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xfbc74f64, __VMLINUX_SYMBOL_STR(__copy_from_user) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x74c134b9, __VMLINUX_SYMBOL_STR(__sw_hweight32) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x2247cba2, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0xf29942b3, __VMLINUX_SYMBOL_STR(seq_putc) },
	{ 0xb9c81fa6, __VMLINUX_SYMBOL_STR(seq_release) },
	{ 0xbbcbd046, __VMLINUX_SYMBOL_STR(PDE_DATA) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xb602c57e, __VMLINUX_SYMBOL_STR(nf_ct_l3proto_module_put) },
	{ 0x59e2743e, __VMLINUX_SYMBOL_STR(call_rcu_bh) },
	{ 0xfba197b8, __VMLINUX_SYMBOL_STR(proc_remove) },
	{ 0x64a5f5cc, __VMLINUX_SYMBOL_STR(dev_mc_del) },
	{ 0x799aca4, __VMLINUX_SYMBOL_STR(local_bh_enable) },
	{ 0xd4d7a32, __VMLINUX_SYMBOL_STR(_atomic_dec_and_lock) },
	{ 0x3ff62317, __VMLINUX_SYMBOL_STR(local_bh_disable) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=x_tables,nf_conntrack";

