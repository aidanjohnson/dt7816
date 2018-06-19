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
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x7c9ad2eb, __VMLINUX_SYMBOL_STR(usb_wait_anchor_empty_timeout) },
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x8edb4a9f, __VMLINUX_SYMBOL_STR(snd_pcm_period_elapsed) },
	{ 0x84edca2d, __VMLINUX_SYMBOL_STR(usb_init_urb) },
	{ 0xc8b57c27, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0xea400b69, __VMLINUX_SYMBOL_STR(snd_card_create) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0x68913526, __VMLINUX_SYMBOL_STR(usb_kill_urb) },
	{ 0x33ba5cd4, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x857a1de, __VMLINUX_SYMBOL_STR(snd_card_disconnect) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x5d41c87c, __VMLINUX_SYMBOL_STR(param_ops_charp) },
	{ 0xdd0a2ba2, __VMLINUX_SYMBOL_STR(strlcat) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x9366262a, __VMLINUX_SYMBOL_STR(snd_pcm_hw_constraint_list) },
	{ 0xb223f9fb, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0xf48b3acf, __VMLINUX_SYMBOL_STR(snd_pcm_set_ops) },
	{ 0x3704802d, __VMLINUX_SYMBOL_STR(usb_set_interface) },
	{ 0x9cff053d, __VMLINUX_SYMBOL_STR(snd_card_free_when_closed) },
	{ 0x1a5d3abc, __VMLINUX_SYMBOL_STR(snd_pcm_lib_get_vmalloc_page) },
	{ 0x1049b573, __VMLINUX_SYMBOL_STR(usb_control_msg) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xdf219bfe, __VMLINUX_SYMBOL_STR(snd_pcm_lib_ioctl) },
	{ 0xa97c342f, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0x78cf4589, __VMLINUX_SYMBOL_STR(usb_kill_anchored_urbs) },
	{ 0x68a19092, __VMLINUX_SYMBOL_STR(_snd_pcm_lib_alloc_vmalloc_buffer) },
	{ 0xd62c833f, __VMLINUX_SYMBOL_STR(schedule_timeout) },
	{ 0x3507a132, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irq) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x499cb58c, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0x20b2bb2d, __VMLINUX_SYMBOL_STR(param_array_ops) },
	{ 0xa3e8bb7a, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0x1cfb04fa, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x33f9de6, __VMLINUX_SYMBOL_STR(snd_card_free) },
	{ 0xd98f6438, __VMLINUX_SYMBOL_STR(snd_card_register) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xfa228ab4, __VMLINUX_SYMBOL_STR(snd_pcm_new) },
	{ 0x49171fff, __VMLINUX_SYMBOL_STR(snd_pcm_lib_free_vmalloc_buffer) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x8be2d05b, __VMLINUX_SYMBOL_STR(usb_anchor_urb) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("usb:v04B4p0384d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v04B4p930Bd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v04B4p931Bd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v04B4p931Cd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v04B4p931Dd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v04B4p931Ed*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v04B4p931Fd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v04B4p9320d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v04B4p9321d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v249Cp9001d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v249Cp9002d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v249Cp9006d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v249Cp9008d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v249Cp931Cd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v249Cp932Cd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v245Fp931Cd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v25C6p9002d*dc*dsc*dp*ic*isc*ip*in*");
