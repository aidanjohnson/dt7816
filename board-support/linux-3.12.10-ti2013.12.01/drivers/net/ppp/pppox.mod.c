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
	{ 0xcf369001, __VMLINUX_SYMBOL_STR(release_sock) },
	{ 0x402b8281, __VMLINUX_SYMBOL_STR(__request_module) },
	{ 0xf9dc362a, __VMLINUX_SYMBOL_STR(ppp_unregister_channel) },
	{ 0x285cbdae, __VMLINUX_SYMBOL_STR(lock_sock_nested) },
	{ 0xbca31af2, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0xbc10dd97, __VMLINUX_SYMBOL_STR(__put_user_4) },
	{ 0x8f69f72e, __VMLINUX_SYMBOL_STR(sock_register) },
	{ 0x62737e1d, __VMLINUX_SYMBOL_STR(sock_unregister) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x4de39428, __VMLINUX_SYMBOL_STR(ppp_channel_index) },
	{ 0xf5afcd9d, __VMLINUX_SYMBOL_STR(try_module_get) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=ppp_generic";

