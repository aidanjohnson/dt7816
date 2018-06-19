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
	{ 0xff178f6, __VMLINUX_SYMBOL_STR(__aeabi_idivmod) },
	{ 0xfbc74f64, __VMLINUX_SYMBOL_STR(__copy_from_user) },
	{ 0xd6ee688f, __VMLINUX_SYMBOL_STR(vmalloc) },
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x67c2fa54, __VMLINUX_SYMBOL_STR(__copy_to_user) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0xd2025d39, __VMLINUX_SYMBOL_STR(vc_resize) },
	{ 0xc8b57c27, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0x68913526, __VMLINUX_SYMBOL_STR(usb_kill_urb) },
	{ 0xaabfa73f, __VMLINUX_SYMBOL_STR(usb_deregister_dev) },
	{ 0x353e3fa5, __VMLINUX_SYMBOL_STR(__get_user_4) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x999e8297, __VMLINUX_SYMBOL_STR(vfree) },
	{ 0x28118cb6, __VMLINUX_SYMBOL_STR(__get_user_1) },
	{ 0x942089e4, __VMLINUX_SYMBOL_STR(vc_cons) },
	{ 0xc631580a, __VMLINUX_SYMBOL_STR(console_unlock) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xb223f9fb, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0xf7584a9c, __VMLINUX_SYMBOL_STR(find_font) },
	{ 0xd9d7910e, __VMLINUX_SYMBOL_STR(usb_register_dev) },
	{ 0xfbaaf01e, __VMLINUX_SYMBOL_STR(console_lock) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xbb72d4fe, __VMLINUX_SYMBOL_STR(__put_user_1) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0xa97c342f, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0xbc10dd97, __VMLINUX_SYMBOL_STR(__put_user_4) },
	{ 0x7bd3b321, __VMLINUX_SYMBOL_STR(usb_get_dev) },
	{ 0xbb9e326a, __VMLINUX_SYMBOL_STR(usb_put_dev) },
	{ 0xd62c833f, __VMLINUX_SYMBOL_STR(schedule_timeout) },
	{ 0x86a4889a, __VMLINUX_SYMBOL_STR(kmalloc_order_trace) },
	{ 0x3d877e, __VMLINUX_SYMBOL_STR(do_take_over_console) },
	{ 0x861ccbb8, __VMLINUX_SYMBOL_STR(usb_find_interface) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x499cb58c, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0xa3e8bb7a, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0xb9acd3d9, __VMLINUX_SYMBOL_STR(__put_user_2) },
	{ 0x1cfb04fa, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0x95dbe078, __VMLINUX_SYMBOL_STR(__get_user_2) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x99bb8806, __VMLINUX_SYMBOL_STR(memmove) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x4b9ab611, __VMLINUX_SYMBOL_STR(usb_free_urb) },
	{ 0x148c8de9, __VMLINUX_SYMBOL_STR(usb_alloc_urb) },
	{ 0xf80378d4, __VMLINUX_SYMBOL_STR(con_set_default_unimap) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("usb:v0711p0550d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0711p0900d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0711p0901d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0711p0902d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0711p0903d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0711p0918d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0711p0920d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0711p0950d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v182Dp021Cd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v182Dp0269d*dc*dsc*dp*ic*isc*ip*in*");
