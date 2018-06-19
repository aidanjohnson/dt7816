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
	{ 0x5b73b59e, __VMLINUX_SYMBOL_STR(team_mode_unregister) },
	{ 0x95155681, __VMLINUX_SYMBOL_STR(team_mode_register) },
	{ 0x9daedd2b, __VMLINUX_SYMBOL_STR(team_option_inst_set_change) },
	{ 0x52df0b4f, __VMLINUX_SYMBOL_STR(team_options_register) },
	{ 0xa76510d8, __VMLINUX_SYMBOL_STR(team_options_unregister) },
	{ 0xe2ea17e8, __VMLINUX_SYMBOL_STR(dev_kfree_skb_any) },
	{ 0xc11126ee, __VMLINUX_SYMBOL_STR(dev_queue_xmit) },
	{ 0xad01eef1, __VMLINUX_SYMBOL_STR(netpoll_send_skb_on_dev) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=team";

