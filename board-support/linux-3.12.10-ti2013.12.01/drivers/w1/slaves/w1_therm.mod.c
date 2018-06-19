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
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x7c2f2afb, __VMLINUX_SYMBOL_STR(w1_calc_crc8) },
	{ 0xbf670952, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0xe1d05a93, __VMLINUX_SYMBOL_STR(w1_read_block) },
	{ 0xcc5005fe, __VMLINUX_SYMBOL_STR(msleep_interruptible) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xaf17c477, __VMLINUX_SYMBOL_STR(w1_next_pullup) },
	{ 0x9183ed81, __VMLINUX_SYMBOL_STR(w1_read_8) },
	{ 0xe9e89624, __VMLINUX_SYMBOL_STR(w1_write_8) },
	{ 0x2c997392, __VMLINUX_SYMBOL_STR(w1_reset_select_slave) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x78f6258c, __VMLINUX_SYMBOL_STR(mutex_lock_interruptible) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=wire";

