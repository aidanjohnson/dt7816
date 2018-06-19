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
	{ 0xaa9087c0, __VMLINUX_SYMBOL_STR(param_ops_string) },
	{ 0x33ba5cd4, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0xe9ad6a69, __VMLINUX_SYMBOL_STR(configfs_unregister_subsystem) },
	{ 0xd721ccd9, __VMLINUX_SYMBOL_STR(unregister_console) },
	{ 0x9d0d6206, __VMLINUX_SYMBOL_STR(unregister_netdevice_notifier) },
	{ 0x86df82cd, __VMLINUX_SYMBOL_STR(register_console) },
	{ 0x7948a97f, __VMLINUX_SYMBOL_STR(configfs_register_subsystem) },
	{ 0x6c575715, __VMLINUX_SYMBOL_STR(config_group_init) },
	{ 0x85df9b6c, __VMLINUX_SYMBOL_STR(strsep) },
	{ 0x3ca22c57, __VMLINUX_SYMBOL_STR(netpoll_parse_options) },
	{ 0xd2da1048, __VMLINUX_SYMBOL_STR(register_netdevice_notifier) },
	{ 0x28b56ff7, __VMLINUX_SYMBOL_STR(__netpoll_cleanup) },
	{ 0x5ac15bae, __VMLINUX_SYMBOL_STR(kstrtou16) },
	{ 0x25c677c4, __VMLINUX_SYMBOL_STR(mac_pton) },
	{ 0xb1c3a01a, __VMLINUX_SYMBOL_STR(oops_in_progress) },
	{ 0x480ba01d, __VMLINUX_SYMBOL_STR(netpoll_send_udp) },
	{ 0x390442c2, __VMLINUX_SYMBOL_STR(config_item_get) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xbef02275, __VMLINUX_SYMBOL_STR(config_item_init_type_name) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x621f31fa, __VMLINUX_SYMBOL_STR(netpoll_setup) },
	{ 0x65abc752, __VMLINUX_SYMBOL_STR(netpoll_print_options) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x373db350, __VMLINUX_SYMBOL_STR(kstrtoint) },
	{ 0xd9ce8f0c, __VMLINUX_SYMBOL_STR(strnlen) },
	{ 0x1b6314fd, __VMLINUX_SYMBOL_STR(in_aton) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xe57878a1, __VMLINUX_SYMBOL_STR(in6_pton) },
	{ 0xa3131f6, __VMLINUX_SYMBOL_STR(strnchr) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x6b5bd820, __VMLINUX_SYMBOL_STR(netpoll_cleanup) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x4740f7f6, __VMLINUX_SYMBOL_STR(config_item_put) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

