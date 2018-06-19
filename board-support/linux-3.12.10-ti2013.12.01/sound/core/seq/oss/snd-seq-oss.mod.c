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
	{ 0xff178f6, __VMLINUX_SYMBOL_STR(__aeabi_idivmod) },
	{ 0xfbc74f64, __VMLINUX_SYMBOL_STR(__copy_from_user) },
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x67c2fa54, __VMLINUX_SYMBOL_STR(__copy_to_user) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xc8b57c27, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0x1a724fcc, __VMLINUX_SYMBOL_STR(snd_seq_kernel_client_ctl) },
	{ 0x59eb74ae, __VMLINUX_SYMBOL_STR(snd_midi_event_encode_byte) },
	{ 0x938e2186, __VMLINUX_SYMBOL_STR(snd_seq_kernel_client_write_poll) },
	{ 0x4205ad24, __VMLINUX_SYMBOL_STR(cancel_work_sync) },
	{ 0x353e3fa5, __VMLINUX_SYMBOL_STR(__get_user_4) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x2ae14b8e, __VMLINUX_SYMBOL_STR(snd_seq_create_kernel_client) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x1cdc0812, __VMLINUX_SYMBOL_STR(snd_midi_event_decode) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xb11ba32d, __VMLINUX_SYMBOL_STR(snd_midi_event_new) },
	{ 0x7b8699eb, __VMLINUX_SYMBOL_STR(snd_seq_event_port_detach) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xc622fb29, __VMLINUX_SYMBOL_STR(snd_seq_device_unregister_driver) },
	{ 0x3061c52d, __VMLINUX_SYMBOL_STR(snd_use_lock_sync_helper) },
	{ 0x8df3789f, __VMLINUX_SYMBOL_STR(snd_oss_info_register) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xe57e68bb, __VMLINUX_SYMBOL_STR(noop_llseek) },
	{ 0xed42580b, __VMLINUX_SYMBOL_STR(snd_midi_event_no_status) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0x4b015768, __VMLINUX_SYMBOL_STR(snd_iprintf) },
	{ 0xbca31af2, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0xea0e5748, __VMLINUX_SYMBOL_STR(snd_midi_event_free) },
	{ 0xbc10dd97, __VMLINUX_SYMBOL_STR(__put_user_4) },
	{ 0x45a5a168, __VMLINUX_SYMBOL_STR(snd_seq_device_register_driver) },
	{ 0xd62c833f, __VMLINUX_SYMBOL_STR(schedule_timeout) },
	{ 0x4253038b, __VMLINUX_SYMBOL_STR(snd_register_oss_device) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x3a57f235, __VMLINUX_SYMBOL_STR(snd_seq_autoload_unlock) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x8c4423a3, __VMLINUX_SYMBOL_STR(snd_unregister_oss_device) },
	{ 0x68d686fc, __VMLINUX_SYMBOL_STR(snd_seq_kernel_client_enqueue_blocking) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9edeb917, __VMLINUX_SYMBOL_STR(snd_seq_root) },
	{ 0x626a991, __VMLINUX_SYMBOL_STR(snd_info_free_entry) },
	{ 0x499cb58c, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0x3fb4d161, __VMLINUX_SYMBOL_STR(snd_seq_kernel_client_dispatch) },
	{ 0x1cfb04fa, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0xb90668b2, __VMLINUX_SYMBOL_STR(snd_seq_autoload_lock) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x6bb71038, __VMLINUX_SYMBOL_STR(snd_seq_delete_kernel_client) },
	{ 0x88d9d6a8, __VMLINUX_SYMBOL_STR(snd_info_create_module_entry) },
	{ 0xb8e448a0, __VMLINUX_SYMBOL_STR(snd_seq_set_queue_tempo) },
	{ 0xeb0632db, __VMLINUX_SYMBOL_STR(snd_info_register) },
	{ 0xf5afcd9d, __VMLINUX_SYMBOL_STR(try_module_get) },
	{ 0xcac0a3be, __VMLINUX_SYMBOL_STR(snd_seq_kernel_client_enqueue) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=snd-seq,snd-seq-midi-event,snd-seq-device";

