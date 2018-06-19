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
	{ 0xea2f6e60, __VMLINUX_SYMBOL_STR(xt_unregister_targets) },
	{ 0x69ba683, __VMLINUX_SYMBOL_STR(xt_unregister_target) },
	{ 0xe5e0ca4a, __VMLINUX_SYMBOL_STR(xt_register_targets) },
	{ 0x5882e4bf, __VMLINUX_SYMBOL_STR(xt_register_target) },
	{ 0x2a18c74, __VMLINUX_SYMBOL_STR(nf_conntrack_destroy) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x3ddb0b92, __VMLINUX_SYMBOL_STR(nf_ct_timeout_put_hook) },
	{ 0x86d6d6a7, __VMLINUX_SYMBOL_STR(nf_ct_timeout_find_get_hook) },
	{ 0xb602c57e, __VMLINUX_SYMBOL_STR(nf_ct_l3proto_module_put) },
	{ 0xedb25af7, __VMLINUX_SYMBOL_STR(nf_conntrack_free) },
	{ 0x6fd2e9c, __VMLINUX_SYMBOL_STR(__nf_ct_l4proto_find) },
	{ 0xbca31af2, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0xd1abde20, __VMLINUX_SYMBOL_STR(nf_ct_helper_ext_add) },
	{ 0x25a2619, __VMLINUX_SYMBOL_STR(nf_conntrack_helper_try_module_get) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x5fdb7019, __VMLINUX_SYMBOL_STR(__nf_ct_ext_add_length) },
	{ 0xa0399b1d, __VMLINUX_SYMBOL_STR(nf_conntrack_alloc) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x78f9b710, __VMLINUX_SYMBOL_STR(nf_ct_l3proto_try_module_get) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x7cf6ca92, __VMLINUX_SYMBOL_STR(nf_conntrack_untracked) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=x_tables,nf_conntrack";

