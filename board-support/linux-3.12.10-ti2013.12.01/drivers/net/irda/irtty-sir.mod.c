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
	{ 0xa120d33c, __VMLINUX_SYMBOL_STR(tty_unregister_ldisc) },
	{ 0xadd8c681, __VMLINUX_SYMBOL_STR(tty_register_ldisc) },
	{ 0x83f1d8cd, __VMLINUX_SYMBOL_STR(sirdev_receive) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xf6ebc03b, __VMLINUX_SYMBOL_STR(net_ratelimit) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x7def77c4, __VMLINUX_SYMBOL_STR(sirdev_get_instance) },
	{ 0xa49bbc9c, __VMLINUX_SYMBOL_STR(tty_driver_flush_buffer) },
	{ 0xdd04395c, __VMLINUX_SYMBOL_STR(tty_chars_in_buffer) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0x3bd1b1f6, __VMLINUX_SYMBOL_STR(msecs_to_jiffies) },
	{ 0xd6c2e616, __VMLINUX_SYMBOL_STR(tty_encode_baud_rate) },
	{ 0x6ec63f26, __VMLINUX_SYMBOL_STR(tty_write_room) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x83211609, __VMLINUX_SYMBOL_STR(up_write) },
	{ 0xa958ed4, __VMLINUX_SYMBOL_STR(down_write) },
	{ 0x109de656, __VMLINUX_SYMBOL_STR(sirdev_put_instance) },
	{ 0x171d648, __VMLINUX_SYMBOL_STR(tty_mode_ioctl) },
	{ 0x67c2fa54, __VMLINUX_SYMBOL_STR(__copy_to_user) },
	{ 0x328a05f1, __VMLINUX_SYMBOL_STR(strncpy) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xbfe63280, __VMLINUX_SYMBOL_STR(sirdev_set_dongle) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x38ac8da, __VMLINUX_SYMBOL_STR(sirdev_write_complete) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=sir-dev";

