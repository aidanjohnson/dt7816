#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.arch = MODULE_ARCH_INIT,
};

MODULE_INFO(intree, "Y");

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xb5c97a0d, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x3f358d29, __VMLINUX_SYMBOL_STR(page_address) },
	{ 0x655b8063, __VMLINUX_SYMBOL_STR(arm_dma_ops) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xcb50ee2c, __VMLINUX_SYMBOL_STR(async_tx_submit) },
	{ 0x5b6c00e6, __VMLINUX_SYMBOL_STR(xor_blocks) },
	{ 0x7505bdef, __VMLINUX_SYMBOL_STR(memchr_inv) },
	{ 0x2db2fa0f, __VMLINUX_SYMBOL_STR(__async_tx_find_channel) },
	{ 0xbd1ad42, __VMLINUX_SYMBOL_STR(async_tx_quiesce) },
	{ 0x1e047854, __VMLINUX_SYMBOL_STR(warn_slowpath_fmt) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=async_tx,xor";

