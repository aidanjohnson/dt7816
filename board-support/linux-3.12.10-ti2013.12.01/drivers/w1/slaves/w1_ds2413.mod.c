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
	{ 0x47581c02, __VMLINUX_SYMBOL_STR(w1_unregister_family) },
	{ 0x9fb12980, __VMLINUX_SYMBOL_STR(w1_register_family) },
	{ 0xe9e89624, __VMLINUX_SYMBOL_STR(w1_write_8) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x84db8b20, __VMLINUX_SYMBOL_STR(w1_reset_resume_command) },
	{ 0x9183ed81, __VMLINUX_SYMBOL_STR(w1_read_8) },
	{ 0xd932221c, __VMLINUX_SYMBOL_STR(w1_write_block) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x2c997392, __VMLINUX_SYMBOL_STR(w1_reset_select_slave) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=wire";

