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
	{ 0x621e1f91, __VMLINUX_SYMBOL_STR(crypto_unregister_template) },
	{ 0x19be1893, __VMLINUX_SYMBOL_STR(crypto_register_template) },
	{ 0x5e50578c, __VMLINUX_SYMBOL_STR(blkcipher_walk_done) },
	{ 0x8810ad5e, __VMLINUX_SYMBOL_STR(crypto_xor) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x5afb2628, __VMLINUX_SYMBOL_STR(blkcipher_walk_virt) },
	{ 0x69dd0da4, __VMLINUX_SYMBOL_STR(crypto_blkcipher_type) },
	{ 0xf56532b2, __VMLINUX_SYMBOL_STR(crypto_mod_put) },
	{ 0xaf4a457b, __VMLINUX_SYMBOL_STR(crypto_alloc_instance) },
	{ 0x13e00488, __VMLINUX_SYMBOL_STR(crypto_attr_alg2) },
	{ 0xd16712f3, __VMLINUX_SYMBOL_STR(crypto_check_attr_type) },
	{ 0xdf9ba487, __VMLINUX_SYMBOL_STR(crypto_spawn_tfm) },
	{ 0x2b18d6e2, __VMLINUX_SYMBOL_STR(crypto_destroy_tfm) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x3e55d0b5, __VMLINUX_SYMBOL_STR(crypto_drop_spawn) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

