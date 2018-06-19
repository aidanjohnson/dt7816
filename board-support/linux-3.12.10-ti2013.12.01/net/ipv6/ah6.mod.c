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
	{ 0x3ae59d62, __VMLINUX_SYMBOL_STR(xfrm6_rcv) },
	{ 0xd857e84d, __VMLINUX_SYMBOL_STR(xfrm6_find_1stfragopt) },
	{ 0xaa38dc66, __VMLINUX_SYMBOL_STR(inet6_del_protocol) },
	{ 0xfb5c58e, __VMLINUX_SYMBOL_STR(xfrm_unregister_type) },
	{ 0xb46351a0, __VMLINUX_SYMBOL_STR(inet6_add_protocol) },
	{ 0x3cb3dd34, __VMLINUX_SYMBOL_STR(xfrm_register_type) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x95c68e4a, __VMLINUX_SYMBOL_STR(__xfrm_state_destroy) },
	{ 0xbc5e0d0c, __VMLINUX_SYMBOL_STR(ip6_update_pmtu) },
	{ 0x28a7c637, __VMLINUX_SYMBOL_STR(ip6_redirect) },
	{ 0x643f723d, __VMLINUX_SYMBOL_STR(xfrm_state_lookup) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xe122af95, __VMLINUX_SYMBOL_STR(xfrm_aalg_get_byname) },
	{ 0x235c0137, __VMLINUX_SYMBOL_STR(crypto_ahash_setkey) },
	{ 0x63eea67, __VMLINUX_SYMBOL_STR(crypto_alloc_ahash) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x2b18d6e2, __VMLINUX_SYMBOL_STR(crypto_destroy_tfm) },
	{ 0xe920e47, __VMLINUX_SYMBOL_STR(xfrm_input_resume) },
	{ 0xd796878f, __VMLINUX_SYMBOL_STR(pskb_expand_head) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0x71bc64b4, __VMLINUX_SYMBOL_STR(__pskb_pull_tail) },
	{ 0x88a1fe4e, __VMLINUX_SYMBOL_STR(xfrm_output_resume) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xb2933465, __VMLINUX_SYMBOL_STR(crypto_ahash_digest) },
	{ 0x80b12177, __VMLINUX_SYMBOL_STR(skb_to_sgvec) },
	{ 0xf88c3301, __VMLINUX_SYMBOL_STR(sg_init_table) },
	{ 0x5515ca7f, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0x6c0b3471, __VMLINUX_SYMBOL_STR(skb_cow_data) },
	{ 0xa20ce1b8, __VMLINUX_SYMBOL_STR(net_msg_warn) },
	{ 0x99bb8806, __VMLINUX_SYMBOL_STR(memmove) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xf6ebc03b, __VMLINUX_SYMBOL_STR(net_ratelimit) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=xfrm_algo";

