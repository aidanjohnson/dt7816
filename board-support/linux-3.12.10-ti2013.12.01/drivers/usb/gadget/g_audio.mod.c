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
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x8d224de9, __VMLINUX_SYMBOL_STR(usb_free_all_descriptors) },
	{ 0xc0e95803, __VMLINUX_SYMBOL_STR(usb_add_config) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x8edb4a9f, __VMLINUX_SYMBOL_STR(snd_pcm_period_elapsed) },
	{ 0xea400b69, __VMLINUX_SYMBOL_STR(snd_card_create) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x8790467f, __VMLINUX_SYMBOL_STR(snd_pcm_hw_constraint_integer) },
	{ 0x7781b4da, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x5d41c87c, __VMLINUX_SYMBOL_STR(param_ops_charp) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x993db83b, __VMLINUX_SYMBOL_STR(usb_ep_autoconfig) },
	{ 0xf48b3acf, __VMLINUX_SYMBOL_STR(snd_pcm_set_ops) },
	{ 0xf5231b9f, __VMLINUX_SYMBOL_STR(snd_pcm_lib_free_pages) },
	{ 0xbadfd0e, __VMLINUX_SYMBOL_STR(platform_device_unregister) },
	{ 0xdf219bfe, __VMLINUX_SYMBOL_STR(snd_pcm_lib_ioctl) },
	{ 0xc8585c07, __VMLINUX_SYMBOL_STR(snd_pcm_lib_malloc_pages) },
	{ 0xcf1aa0cf, __VMLINUX_SYMBOL_STR(usb_composite_overwrite_options) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x1dba1f67, __VMLINUX_SYMBOL_STR(usb_composite_probe) },
	{ 0x103019c, __VMLINUX_SYMBOL_STR(usb_add_function) },
	{ 0xb8581aed, __VMLINUX_SYMBOL_STR(platform_device_register) },
	{ 0x28ce7192, __VMLINUX_SYMBOL_STR(config_ep_by_speed) },
	{ 0xd28defee, __VMLINUX_SYMBOL_STR(usb_composite_unregister) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x68a24153, __VMLINUX_SYMBOL_STR(snd_pcm_format_physical_width) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x3aa4302b, __VMLINUX_SYMBOL_STR(usb_string_ids_tab) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x131d8fcf, __VMLINUX_SYMBOL_STR(usb_assign_descriptors) },
	{ 0xfb4ee8ea, __VMLINUX_SYMBOL_STR(snd_pcm_lib_preallocate_pages_for_all) },
	{ 0x2e23ffa6, __VMLINUX_SYMBOL_STR(usb_interface_id) },
	{ 0x33f9de6, __VMLINUX_SYMBOL_STR(snd_card_free) },
	{ 0xd98f6438, __VMLINUX_SYMBOL_STR(snd_card_register) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xfa228ab4, __VMLINUX_SYMBOL_STR(snd_pcm_new) },
	{ 0xafad493b, __VMLINUX_SYMBOL_STR(param_ops_ushort) },
	{ 0x35c39aa9, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0x47c8baf4, __VMLINUX_SYMBOL_STR(param_ops_uint) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=libcomposite";

