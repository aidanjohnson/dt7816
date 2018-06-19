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
	{ 0x47581c02, __VMLINUX_SYMBOL_STR(w1_unregister_family) },
	{ 0x9fb12980, __VMLINUX_SYMBOL_STR(w1_register_family) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x76f1ebd7, __VMLINUX_SYMBOL_STR(w1_reset_bus) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0xaf17c477, __VMLINUX_SYMBOL_STR(w1_next_pullup) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0xe9e89624, __VMLINUX_SYMBOL_STR(w1_write_8) },
	{ 0x8ffdb3b8, __VMLINUX_SYMBOL_STR(crc16) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xe1d05a93, __VMLINUX_SYMBOL_STR(w1_read_block) },
	{ 0xd932221c, __VMLINUX_SYMBOL_STR(w1_write_block) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x2c997392, __VMLINUX_SYMBOL_STR(w1_reset_select_slave) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x28118cb6, __VMLINUX_SYMBOL_STR(__get_user_1) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xbb72d4fe, __VMLINUX_SYMBOL_STR(__put_user_1) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=wire";

