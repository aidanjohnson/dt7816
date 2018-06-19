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
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x9924c496, __VMLINUX_SYMBOL_STR(__usb_get_extra_descriptor) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0xadb3a34a, __VMLINUX_SYMBOL_STR(usb_hub_find_child) },
	{ 0x693efb09, __VMLINUX_SYMBOL_STR(power_supply_unregister) },
	{ 0x22cd06da, __VMLINUX_SYMBOL_STR(input_alloc_absinfo) },
	{ 0x4205ad24, __VMLINUX_SYMBOL_STR(cancel_work_sync) },
	{ 0x68913526, __VMLINUX_SYMBOL_STR(usb_kill_urb) },
	{ 0x8c346b86, __VMLINUX_SYMBOL_STR(power_supply_powers) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x7ccbce9f, __VMLINUX_SYMBOL_STR(usb_autopm_get_interface) },
	{ 0xb0cab2d5, __VMLINUX_SYMBOL_STR(sysfs_remove_group) },
	{ 0x7d11c268, __VMLINUX_SYMBOL_STR(jiffies) },
	{ 0x266e0d, __VMLINUX_SYMBOL_STR(input_mt_report_pointer_emulation) },
	{ 0xcdc2d251, __VMLINUX_SYMBOL_STR(input_set_abs_params) },
	{ 0xb79a5aed, __VMLINUX_SYMBOL_STR(input_event) },
	{ 0xdd0a2ba2, __VMLINUX_SYMBOL_STR(strlcat) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xb223f9fb, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0xce917ae3, __VMLINUX_SYMBOL_STR(sysfs_create_group) },
	{ 0x1049b573, __VMLINUX_SYMBOL_STR(usb_control_msg) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0xfc88fbae, __VMLINUX_SYMBOL_STR(input_set_capability) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xba1e33bf, __VMLINUX_SYMBOL_STR(input_mt_init_slots) },
	{ 0x9f038e56, __VMLINUX_SYMBOL_STR(usb_free_coherent) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0xa97c342f, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0xaa58a0ae, __VMLINUX_SYMBOL_STR(input_register_device) },
	{ 0x55e25a41, __VMLINUX_SYMBOL_STR(input_free_device) },
	{ 0xb678366f, __VMLINUX_SYMBOL_STR(int_sqrt) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xb297e0bc, __VMLINUX_SYMBOL_STR(input_mt_get_slot_by_key) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xa46f2f1b, __VMLINUX_SYMBOL_STR(kstrtouint) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x657c72c4, __VMLINUX_SYMBOL_STR(input_unregister_device) },
	{ 0xcfc59fe6, __VMLINUX_SYMBOL_STR(input_mt_report_slot_state) },
	{ 0xa3e8bb7a, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x82925eed, __VMLINUX_SYMBOL_STR(usb_alloc_coherent) },
	{ 0x4bd844b5, __VMLINUX_SYMBOL_STR(power_supply_register) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x4b9ab611, __VMLINUX_SYMBOL_STR(usb_free_urb) },
	{ 0x833c4c97, __VMLINUX_SYMBOL_STR(usb_autopm_put_interface) },
	{ 0x148c8de9, __VMLINUX_SYMBOL_STR(usb_alloc_urb) },
	{ 0x26a6901f, __VMLINUX_SYMBOL_STR(input_allocate_device) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

MODULE_ALIAS("usb:v056Ap0000d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0010d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0011d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0012d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0013d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0014d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0015d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0016d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0017d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0018d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0019d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0060d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0061d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0062d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0063d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0064d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0065d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0069d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap006Ad*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap006Bd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0020d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0021d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0022d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0023d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0024d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0030d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0031d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0032d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0033d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0034d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0035d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0037d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0038d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0039d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00C4d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00C0d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00C2d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0003d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0041d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0042d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0043d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0044d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0045d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0057d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0059d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap005Dd*dc*dsc*dp*ic03isc00ip00in*");
MODULE_ALIAS("usb:v056Ap005Bd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap005Ed*dc*dsc*dp*ic03isc00ip00in*");
MODULE_ALIAS("usb:v056Ap00B0d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00B1d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00B2d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00B3d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00B4d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00B5d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00B7d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00B8d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00B9d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00BAd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00BBd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00BCd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0026d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0027d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0028d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0029d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap002Ad*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap003Fd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00C5d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00C6d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00C7d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00CEd*dc*dsc*dp*ic03isc01ip02in*");
MODULE_ALIAS("usb:v056Ap0084d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00D0d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00D1d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00D2d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00D3d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00D4d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00D5d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00D6d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00D7d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00D8d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00DAd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00DBd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00DDd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00DEd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00DFd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00F0d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00CCd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0090d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0093d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0097d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap009Ad*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap009Fd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00E2d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00E3d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00E5d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00E6d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00ECd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00EDd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00EFd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0100d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0101d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap010Dd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap010Ed*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap010Fd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0300d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0301d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0304d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap4001d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap0047d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00F4d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00F8d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v056Ap00F6d*dc*dsc*dp*ic03isc00ip00in*");
MODULE_ALIAS("usb:v056Ap00FAd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v17EFp6004d*dc*dsc*dp*ic*isc*ip*in*");
