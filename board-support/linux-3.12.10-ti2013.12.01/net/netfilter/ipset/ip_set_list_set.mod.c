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
	{ 0x593a99b, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0xc4634db4, __VMLINUX_SYMBOL_STR(ip_set_del) },
	{ 0x27b659a5, __VMLINUX_SYMBOL_STR(ip_set_add) },
	{ 0x62013789, __VMLINUX_SYMBOL_STR(ip_set_test) },
	{ 0xbe2c0274, __VMLINUX_SYMBOL_STR(add_timer) },
	{ 0x8bd0a3fd, __VMLINUX_SYMBOL_STR(_raw_write_unlock_bh) },
	{ 0x85061b76, __VMLINUX_SYMBOL_STR(_raw_write_lock_bh) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x4a945fec, __VMLINUX_SYMBOL_STR(ip_set_get_byname) },
	{ 0xde1c81f2, __VMLINUX_SYMBOL_STR(ip_set_get_extensions) },
	{ 0x3bd1b1f6, __VMLINUX_SYMBOL_STR(msecs_to_jiffies) },
	{ 0x99bb8806, __VMLINUX_SYMBOL_STR(memmove) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xd5f2172f, __VMLINUX_SYMBOL_STR(del_timer_sync) },
	{ 0xfda3ec7a, __VMLINUX_SYMBOL_STR(ip_set_put_byindex) },
	{ 0x37befc70, __VMLINUX_SYMBOL_STR(jiffies_to_msecs) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0x883d6572, __VMLINUX_SYMBOL_STR(ip_set_name_byindex) },
	{ 0x594ff15d, __VMLINUX_SYMBOL_STR(skb_trim) },
	{ 0x63096cbc, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=ip_set";

