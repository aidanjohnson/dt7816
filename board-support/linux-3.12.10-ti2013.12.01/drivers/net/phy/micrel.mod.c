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
	{ 0x69a3950e, __VMLINUX_SYMBOL_STR(genphy_read_status) },
	{ 0xadef0258, __VMLINUX_SYMBOL_STR(genphy_config_aneg) },
	{ 0xf1452e68, __VMLINUX_SYMBOL_STR(phy_drivers_unregister) },
	{ 0x85b322f9, __VMLINUX_SYMBOL_STR(phy_drivers_register) },
	{ 0xdac11bae, __VMLINUX_SYMBOL_STR(of_property_read_u32_array) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0xf0157367, __VMLINUX_SYMBOL_STR(mdiobus_write) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x5955e84a, __VMLINUX_SYMBOL_STR(mdiobus_read) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("mdio:????????????0010000101100001000?");
MODULE_ALIAS("mdio:????????00100010000101100010????");
MODULE_ALIAS("mdio:????????001000100001011000011010");
MODULE_ALIAS("mdio:????????00100010000101110010????");
MODULE_ALIAS("mdio:????????001000100001010101010101");
MODULE_ALIAS("mdio:????????001000100001010101010110");
MODULE_ALIAS("mdio:????????00100010000101010001????");
MODULE_ALIAS("mdio:????????00100010000101010101????");
MODULE_ALIAS("mdio:????????00100010000101010111????");
MODULE_ALIAS("mdio:????????00100010000101010110????");
MODULE_ALIAS("mdio:????????00001110011100100011????");
MODULE_ALIAS("mdio:????????00100010000101000011????");
