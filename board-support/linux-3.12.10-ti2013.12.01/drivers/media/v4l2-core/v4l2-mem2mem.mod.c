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
	{ 0x44cc5359, __VMLINUX_SYMBOL_STR(vb2_mmap) },
	{ 0xc8b57c27, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0x19d4fe28, __VMLINUX_SYMBOL_STR(vb2_create_bufs) },
	{ 0x33ba5cd4, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x7229198f, __VMLINUX_SYMBOL_STR(v4l2_event_pending) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xc2b28d33, __VMLINUX_SYMBOL_STR(vb2_qbuf) },
	{ 0xf5fcbf7e, __VMLINUX_SYMBOL_STR(vb2_querybuf) },
	{ 0x740fa6b0, __VMLINUX_SYMBOL_STR(vb2_streamon) },
	{ 0x15cc910, __VMLINUX_SYMBOL_STR(video_devdata) },
	{ 0x8aaad379, __VMLINUX_SYMBOL_STR(vb2_expbuf) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0x23e51904, __VMLINUX_SYMBOL_STR(vb2_reqbufs) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x64967d3b, __VMLINUX_SYMBOL_STR(vb2_dqbuf) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x499cb58c, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0x1cfb04fa, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x32be70ec, __VMLINUX_SYMBOL_STR(vb2_queue_release) },
	{ 0x22645c35, __VMLINUX_SYMBOL_STR(vb2_streamoff) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=videobuf2-core";

