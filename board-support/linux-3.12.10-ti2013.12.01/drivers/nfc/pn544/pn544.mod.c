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
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x4fde9511, __VMLINUX_SYMBOL_STR(nfc_hci_send_event) },
	{ 0x7f72278e, __VMLINUX_SYMBOL_STR(nfc_dep_link_is_up) },
	{ 0xef8d968e, __VMLINUX_SYMBOL_STR(nfc_hci_set_param) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x27b1ead1, __VMLINUX_SYMBOL_STR(nfc_hci_allocate_device) },
	{ 0xad83de93, __VMLINUX_SYMBOL_STR(nfc_tm_activated) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x80719a72, __VMLINUX_SYMBOL_STR(nfc_hci_get_clientdata) },
	{ 0x7f71571c, __VMLINUX_SYMBOL_STR(nfc_hci_send_cmd) },
	{ 0x5515ca7f, __VMLINUX_SYMBOL_STR(skb_push) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xe40dc473, __VMLINUX_SYMBOL_STR(skb_pull) },
	{ 0x2d056ff2, __VMLINUX_SYMBOL_STR(nfc_set_remote_general_bytes) },
	{ 0xf0bb3f56, __VMLINUX_SYMBOL_STR(nfc_hci_target_discovered) },
	{ 0x4f7c4101, __VMLINUX_SYMBOL_STR(nfc_hci_register_device) },
	{ 0x868b0fb4, __VMLINUX_SYMBOL_STR(nfc_get_local_general_bytes) },
	{ 0xaa70423c, __VMLINUX_SYMBOL_STR(nfc_hci_free_device) },
	{ 0x4059792f, __VMLINUX_SYMBOL_STR(print_hex_dump) },
	{ 0xd829a8ba, __VMLINUX_SYMBOL_STR(nfc_hci_unregister_device) },
	{ 0xb60ba5c9, __VMLINUX_SYMBOL_STR(kfree_skb) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x27d50b9, __VMLINUX_SYMBOL_STR(nfc_tm_data_received) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x99bb8806, __VMLINUX_SYMBOL_STR(memmove) },
	{ 0xec6b4cd4, __VMLINUX_SYMBOL_STR(nfc_hci_send_cmd_async) },
	{ 0x8ad2a6a2, __VMLINUX_SYMBOL_STR(nfc_hci_get_param) },
	{ 0x729cea1c, __VMLINUX_SYMBOL_STR(nfc_hci_set_clientdata) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=hci,nfc";

