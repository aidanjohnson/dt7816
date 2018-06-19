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
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x20b2bb2d, __VMLINUX_SYMBOL_STR(param_array_ops) },
	{ 0xda2478d0, __VMLINUX_SYMBOL_STR(param_ops_short) },
	{ 0xe7187fb7, __VMLINUX_SYMBOL_STR(em28xx_unregister_extension) },
	{ 0x1728c2ce, __VMLINUX_SYMBOL_STR(em28xx_register_extension) },
	{ 0xaa6fac1b, __VMLINUX_SYMBOL_STR(dvb_net_init) },
	{ 0x79a4264a, __VMLINUX_SYMBOL_STR(dvb_dmxdev_init) },
	{ 0x7302371d, __VMLINUX_SYMBOL_STR(dvb_dmx_init) },
	{ 0xd2217c63, __VMLINUX_SYMBOL_STR(dvb_register_frontend) },
	{ 0x72f4f140, __VMLINUX_SYMBOL_STR(dvb_register_adapter) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x7fc8652c, __VMLINUX_SYMBOL_STR(em28xx_tuner_callback) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x6e9dd606, __VMLINUX_SYMBOL_STR(__symbol_put) },
	{ 0x402b8281, __VMLINUX_SYMBOL_STR(__request_module) },
	{ 0x868784cb, __VMLINUX_SYMBOL_STR(__symbol_get) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xd51c05b5, __VMLINUX_SYMBOL_STR(dvb_unregister_adapter) },
	{ 0xa432424c, __VMLINUX_SYMBOL_STR(dvb_frontend_detach) },
	{ 0xe748d08d, __VMLINUX_SYMBOL_STR(dvb_unregister_frontend) },
	{ 0xdbe7dd6c, __VMLINUX_SYMBOL_STR(dvb_dmx_release) },
	{ 0xf5b09563, __VMLINUX_SYMBOL_STR(dvb_dmxdev_release) },
	{ 0x2eea13d5, __VMLINUX_SYMBOL_STR(dvb_net_release) },
	{ 0x4be7fb63, __VMLINUX_SYMBOL_STR(up) },
	{ 0xf473ffaf, __VMLINUX_SYMBOL_STR(down) },
	{ 0x87304c69, __VMLINUX_SYMBOL_STR(em28xx_init_usb_xfer) },
	{ 0x3704802d, __VMLINUX_SYMBOL_STR(usb_set_interface) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x96ab94f9, __VMLINUX_SYMBOL_STR(em28xx_stop_urbs) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x1e9f1a37, __VMLINUX_SYMBOL_STR(i2c_master_send) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x9f63cff3, __VMLINUX_SYMBOL_STR(em28xx_write_reg) },
	{ 0x781a35b4, __VMLINUX_SYMBOL_STR(em28xx_gpio_set) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xfe990052, __VMLINUX_SYMBOL_STR(gpio_free) },
	{ 0x403f9529, __VMLINUX_SYMBOL_STR(gpio_request_one) },
	{ 0xd68cdcef, __VMLINUX_SYMBOL_STR(em28xx_set_mode) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xd29c47a6, __VMLINUX_SYMBOL_STR(dvb_dmx_swfilter) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=em28xx";

