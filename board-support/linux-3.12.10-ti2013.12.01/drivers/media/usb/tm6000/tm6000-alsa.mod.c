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
	{ 0x20b2bb2d, __VMLINUX_SYMBOL_STR(param_array_ops) },
	{ 0xdf219bfe, __VMLINUX_SYMBOL_STR(snd_pcm_lib_ioctl) },
	{ 0x33ba5cd4, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0xbe437cbb, __VMLINUX_SYMBOL_STR(tm6000_unregister_extension) },
	{ 0xce0af939, __VMLINUX_SYMBOL_STR(tm6000_register_extension) },
	{ 0x71ad0c1e, __VMLINUX_SYMBOL_STR(tm6000_set_audio_bitrate) },
	{ 0x6b0d4353, __VMLINUX_SYMBOL_STR(tm6000_set_reg_mask) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xd98f6438, __VMLINUX_SYMBOL_STR(snd_card_register) },
	{ 0xf48b3acf, __VMLINUX_SYMBOL_STR(snd_pcm_set_ops) },
	{ 0xfa228ab4, __VMLINUX_SYMBOL_STR(snd_pcm_new) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xe5d585c2, __VMLINUX_SYMBOL_STR(snd_component_add) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
	{ 0xea400b69, __VMLINUX_SYMBOL_STR(snd_card_create) },
	{ 0x8790467f, __VMLINUX_SYMBOL_STR(snd_pcm_hw_constraint_integer) },
	{ 0xda26479b, __VMLINUX_SYMBOL_STR(snd_pcm_hw_constraint_pow2) },
	{ 0xd6ee688f, __VMLINUX_SYMBOL_STR(vmalloc) },
	{ 0x68a24153, __VMLINUX_SYMBOL_STR(snd_pcm_format_physical_width) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x1e1ff3f2, __VMLINUX_SYMBOL_STR(vmalloc_to_page) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x33f9de6, __VMLINUX_SYMBOL_STR(snd_card_free) },
	{ 0x6e88e56f, __VMLINUX_SYMBOL_STR(snd_pcm_link_rwlock) },
	{ 0x8edb4a9f, __VMLINUX_SYMBOL_STR(snd_pcm_period_elapsed) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x7b6646bb, __VMLINUX_SYMBOL_STR(_raw_read_lock) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=tm6000";

