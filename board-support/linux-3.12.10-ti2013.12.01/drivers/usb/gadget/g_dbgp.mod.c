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
	{ 0x91147b85, __VMLINUX_SYMBOL_STR(gserial_connect) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xc29551e3, __VMLINUX_SYMBOL_STR(dev_printk) },
	{ 0x43968ab8, __VMLINUX_SYMBOL_STR(usb_gadget_unregister_driver) },
	{ 0x48d88451, __VMLINUX_SYMBOL_STR(usb_ep_autoconfig_reset) },
	{ 0x993db83b, __VMLINUX_SYMBOL_STR(usb_ep_autoconfig) },
	{ 0x7bbc252f, __VMLINUX_SYMBOL_STR(gserial_disconnect) },
	{ 0x33bfdca2, __VMLINUX_SYMBOL_STR(gserial_alloc_line) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x588f2a3b, __VMLINUX_SYMBOL_STR(usb_gadget_probe_driver) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xb6652875, __VMLINUX_SYMBOL_STR(gserial_free_line) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=u_serial,libcomposite";

