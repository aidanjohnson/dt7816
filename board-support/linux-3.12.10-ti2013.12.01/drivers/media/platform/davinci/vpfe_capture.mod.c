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
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x715c156a, __VMLINUX_SYMBOL_STR(videobuf_mmap_mapper) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x356c3945, __VMLINUX_SYMBOL_STR(video_device_release) },
	{ 0x6f444176, __VMLINUX_SYMBOL_STR(v4l2_device_unregister) },
	{ 0x2342f1ae, __VMLINUX_SYMBOL_STR(v4l2_prio_open) },
	{ 0xb06e89d8, __VMLINUX_SYMBOL_STR(videobuf_dma_contig_free) },
	{ 0x17e9f0be, __VMLINUX_SYMBOL_STR(videobuf_streamon) },
	{ 0xcf18e3, __VMLINUX_SYMBOL_STR(__video_register_device) },
	{ 0xebd4ed06, __VMLINUX_SYMBOL_STR(videobuf_queue_dma_contig_init) },
	{ 0x6da625c4, __VMLINUX_SYMBOL_STR(videobuf_iolock) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x7781b4da, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0xe426c33e, __VMLINUX_SYMBOL_STR(v4l2_device_register) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x8f591e02, __VMLINUX_SYMBOL_STR(videobuf_to_dma_contig) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xa4f934f7, __VMLINUX_SYMBOL_STR(video_device_alloc) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x78f6258c, __VMLINUX_SYMBOL_STR(mutex_lock_interruptible) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xb77b0159, __VMLINUX_SYMBOL_STR(v4l2_prio_init) },
	{ 0xfc3d209d, __VMLINUX_SYMBOL_STR(videobuf_qbuf) },
	{ 0x8a39eb7, __VMLINUX_SYMBOL_STR(video_unregister_device) },
	{ 0xcda04a5b, __VMLINUX_SYMBOL_STR(v4l2_prio_close) },
	{ 0x328a05f1, __VMLINUX_SYMBOL_STR(strncpy) },
	{ 0x5b3fb26f, __VMLINUX_SYMBOL_STR(videobuf_querybuf) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xbed18b93, __VMLINUX_SYMBOL_STR(platform_get_resource) },
	{ 0xd6b8e852, __VMLINUX_SYMBOL_STR(request_threaded_irq) },
	{ 0xbca31af2, __VMLINUX_SYMBOL_STR(module_put) },
	{ 0x15cc910, __VMLINUX_SYMBOL_STR(video_devdata) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x61fbc681, __VMLINUX_SYMBOL_STR(videobuf_dqbuf) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x312bc183, __VMLINUX_SYMBOL_STR(videobuf_reqbufs) },
	{ 0x356c917f, __VMLINUX_SYMBOL_STR(v4l2_i2c_new_subdev_board) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x35c39aa9, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0xf412b8a2, __VMLINUX_SYMBOL_STR(i2c_get_adapter) },
	{ 0x47c8baf4, __VMLINUX_SYMBOL_STR(param_ops_uint) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x1c483a9, __VMLINUX_SYMBOL_STR(v4l2_get_timestamp) },
	{ 0x9be04d52, __VMLINUX_SYMBOL_STR(video_ioctl2) },
	{ 0xd89decaf, __VMLINUX_SYMBOL_STR(videobuf_poll_stream) },
	{ 0xf5afcd9d, __VMLINUX_SYMBOL_STR(try_module_get) },
	{ 0xf20dabd8, __VMLINUX_SYMBOL_STR(free_irq) },
	{ 0xd898e9dc, __VMLINUX_SYMBOL_STR(videobuf_streamoff) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=videobuf-core,videobuf-dma-contig";

