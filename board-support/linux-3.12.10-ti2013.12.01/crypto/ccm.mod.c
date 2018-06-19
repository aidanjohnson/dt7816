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
	{ 0x3ac51006, __VMLINUX_SYMBOL_STR(crypto_aead_setauthsize) },
	{ 0x676586f7, __VMLINUX_SYMBOL_STR(crypto_nivaead_type) },
	{ 0x78f9f822, __VMLINUX_SYMBOL_STR(crypto_grab_aead) },
	{ 0xdf9ba487, __VMLINUX_SYMBOL_STR(crypto_spawn_tfm) },
	{ 0x2b18d6e2, __VMLINUX_SYMBOL_STR(crypto_destroy_tfm) },
	{ 0xe52e3763, __VMLINUX_SYMBOL_STR(mem_map) },
	{ 0x6ccf7bd7, __VMLINUX_SYMBOL_STR(__pv_phys_offset) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0xf88c3301, __VMLINUX_SYMBOL_STR(sg_init_table) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xa1c76e0a, __VMLINUX_SYMBOL_STR(_cond_resched) },
	{ 0x3db91586, __VMLINUX_SYMBOL_STR(scatterwalk_done) },
	{ 0xed93f29e, __VMLINUX_SYMBOL_STR(__kunmap_atomic) },
	{ 0x8810ad5e, __VMLINUX_SYMBOL_STR(crypto_xor) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xab18e6bd, __VMLINUX_SYMBOL_STR(scatterwalk_map) },
	{ 0xd5152710, __VMLINUX_SYMBOL_STR(sg_next) },
	{ 0x599d0cb6, __VMLINUX_SYMBOL_STR(scatterwalk_start) },
	{ 0x91dda801, __VMLINUX_SYMBOL_STR(scatterwalk_map_and_copy) },
	{ 0x9a11a0fc, __VMLINUX_SYMBOL_STR(crypto_attr_alg_name) },
	{ 0x9d74c5a0, __VMLINUX_SYMBOL_STR(crypto_aead_type) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xf56532b2, __VMLINUX_SYMBOL_STR(crypto_mod_put) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x71a437f9, __VMLINUX_SYMBOL_STR(crypto_grab_skcipher) },
	{ 0x10d718a1, __VMLINUX_SYMBOL_STR(crypto_init_spawn) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x4af3845c, __VMLINUX_SYMBOL_STR(crypto_alg_mod_lookup) },
	{ 0x124f2056, __VMLINUX_SYMBOL_STR(crypto_get_attr_type) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x3e55d0b5, __VMLINUX_SYMBOL_STR(crypto_drop_spawn) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

