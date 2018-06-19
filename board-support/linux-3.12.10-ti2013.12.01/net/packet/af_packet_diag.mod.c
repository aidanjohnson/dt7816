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
	{ 0xc4c56719, __VMLINUX_SYMBOL_STR(sock_diag_put_meminfo) },
	{ 0x27f15ec9, __VMLINUX_SYMBOL_STR(from_kuid_munged) },
	{ 0xc7a4fbed, __VMLINUX_SYMBOL_STR(rtnl_lock) },
	{ 0xcdb2955d, __VMLINUX_SYMBOL_STR(sock_diag_unregister) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xc10df545, __VMLINUX_SYMBOL_STR(sock_diag_put_filterinfo) },
	{ 0xf2e604ec, __VMLINUX_SYMBOL_STR(sock_i_ino) },
	{ 0x21b8a9d5, __VMLINUX_SYMBOL_STR(fanout_mutex) },
	{ 0x594ff15d, __VMLINUX_SYMBOL_STR(skb_trim) },
	{ 0x5ecec97c, __VMLINUX_SYMBOL_STR(sock_diag_register) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x63096cbc, __VMLINUX_SYMBOL_STR(nla_put) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x62b6220a, __VMLINUX_SYMBOL_STR(nla_reserve_nohdr) },
	{ 0xd14bc4d9, __VMLINUX_SYMBOL_STR(sock_diag_save_cookie) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x8dd61422, __VMLINUX_SYMBOL_STR(__nlmsg_put) },
	{ 0x6e720ff2, __VMLINUX_SYMBOL_STR(rtnl_unlock) },
	{ 0xfc70e345, __VMLINUX_SYMBOL_STR(sock_i_uid) },
	{ 0x11815a9b, __VMLINUX_SYMBOL_STR(__netlink_dump_start) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

