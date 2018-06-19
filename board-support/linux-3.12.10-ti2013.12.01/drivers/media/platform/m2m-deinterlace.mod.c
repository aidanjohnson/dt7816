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
	{ 0x33ba5cd4, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0x9be04d52, __VMLINUX_SYMBOL_STR(video_ioctl2) },
	{ 0x35c39aa9, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0x7781b4da, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0x6f6a3d1c, __VMLINUX_SYMBOL_STR(vb2_plane_cookie) },
	{ 0x7dc0b41, __VMLINUX_SYMBOL_STR(v4l2_m2m_next_buf) },
	{ 0x2e8a44e9, __VMLINUX_SYMBOL_STR(v4l2_m2m_streamon) },
	{ 0x1910a54b, __VMLINUX_SYMBOL_STR(vb2_dma_contig_memops) },
	{ 0x5f18405, __VMLINUX_SYMBOL_STR(vb2_queue_init) },
	{ 0x756e032c, __VMLINUX_SYMBOL_STR(v4l2_m2m_get_vq) },
	{ 0x43e61d1e, __VMLINUX_SYMBOL_STR(v4l2_m2m_ctx_init) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x356c3945, __VMLINUX_SYMBOL_STR(video_device_release) },
	{ 0x17eb0eee, __VMLINUX_SYMBOL_STR(v4l2_m2m_init) },
	{ 0x55602473, __VMLINUX_SYMBOL_STR(vb2_dma_contig_init_ctx) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0xcf18e3, __VMLINUX_SYMBOL_STR(__video_register_device) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0xa4f934f7, __VMLINUX_SYMBOL_STR(video_device_alloc) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0xe426c33e, __VMLINUX_SYMBOL_STR(v4l2_device_register) },
	{ 0x919cfc74, __VMLINUX_SYMBOL_STR(__dma_request_channel) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x8e511414, __VMLINUX_SYMBOL_STR(vb2_buffer_done) },
	{ 0x458b8928, __VMLINUX_SYMBOL_STR(v4l2_m2m_buf_remove) },
	{ 0xd389b887, __VMLINUX_SYMBOL_STR(v4l2_m2m_job_finish) },
	{ 0x641baa41, __VMLINUX_SYMBOL_STR(v4l2_m2m_poll) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x41a642c2, __VMLINUX_SYMBOL_STR(v4l2_m2m_mmap) },
	{ 0x73e06c24, __VMLINUX_SYMBOL_STR(v4l2_m2m_buf_queue) },
	{ 0xd47bd9c9, __VMLINUX_SYMBOL_STR(v4l2_m2m_ctx_release) },
	{ 0x15cc910, __VMLINUX_SYMBOL_STR(video_devdata) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0xd68d3509, __VMLINUX_SYMBOL_STR(v4l2_m2m_reqbufs) },
	{ 0x5ee926a6, __VMLINUX_SYMBOL_STR(v4l2_m2m_querybuf) },
	{ 0x92a18a1c, __VMLINUX_SYMBOL_STR(v4l2_m2m_qbuf) },
	{ 0xf48f2b5a, __VMLINUX_SYMBOL_STR(v4l2_m2m_dqbuf) },
	{ 0xb2ca03e1, __VMLINUX_SYMBOL_STR(v4l2_m2m_streamoff) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0xa4352668, __VMLINUX_SYMBOL_STR(dma_release_channel) },
	{ 0xe57f0426, __VMLINUX_SYMBOL_STR(vb2_dma_contig_cleanup_ctx) },
	{ 0x6f444176, __VMLINUX_SYMBOL_STR(v4l2_device_unregister) },
	{ 0x8a39eb7, __VMLINUX_SYMBOL_STR(video_unregister_device) },
	{ 0xc6fca5ad, __VMLINUX_SYMBOL_STR(v4l2_m2m_release) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=videobuf2-core,v4l2-mem2mem,videobuf2-dma-contig";


MODULE_INFO(srcversion, "9B833CDB8A1D3A05614524C");
