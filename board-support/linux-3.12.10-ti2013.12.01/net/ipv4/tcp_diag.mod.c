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
	{ 0xf65cbda7, __VMLINUX_SYMBOL_STR(inet_diag_unregister) },
	{ 0x764e6fd, __VMLINUX_SYMBOL_STR(inet_diag_register) },
	{ 0xc4b0b0e4, __VMLINUX_SYMBOL_STR(inet_diag_dump_icsk) },
	{ 0xf265ac6, __VMLINUX_SYMBOL_STR(tcp_hashinfo) },
	{ 0xe66b3ee3, __VMLINUX_SYMBOL_STR(inet_diag_dump_one_icsk) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xd13ffc1b, __VMLINUX_SYMBOL_STR(tcp_get_info) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=inet_diag";

