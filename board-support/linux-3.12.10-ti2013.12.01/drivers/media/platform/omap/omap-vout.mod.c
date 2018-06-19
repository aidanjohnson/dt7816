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
	{ 0x69b6f8d9, __VMLINUX_SYMBOL_STR(omap_set_dma_transfer_params) },
	{ 0x9dea3e61, __VMLINUX_SYMBOL_STR(platform_driver_probe) },
	{ 0x67acc003, __VMLINUX_SYMBOL_STR(videobuf_mmap_free) },
	{ 0xc0a6a8c5, __VMLINUX_SYMBOL_STR(omap_set_dma_dest_burst_mode) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xf4a7fc6d, __VMLINUX_SYMBOL_STR(omapdss_compat_init) },
	{ 0x22e1ae6f, __VMLINUX_SYMBOL_STR(up_read) },
	{ 0xe52e3763, __VMLINUX_SYMBOL_STR(mem_map) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x3f358d29, __VMLINUX_SYMBOL_STR(page_address) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x116f9332, __VMLINUX_SYMBOL_STR(omap_dss_get_overlay_manager) },
	{ 0xffd2cf99, __VMLINUX_SYMBOL_STR(omap_dss_get_num_overlay_managers) },
	{ 0x356c3945, __VMLINUX_SYMBOL_STR(video_device_release) },
	{ 0x655b8063, __VMLINUX_SYMBOL_STR(arm_dma_ops) },
	{ 0x6f444176, __VMLINUX_SYMBOL_STR(v4l2_device_unregister) },
	{ 0xf6ac2d14, __VMLINUX_SYMBOL_STR(omap_dss_get_overlay) },
	{ 0xcd0d9f3f, __VMLINUX_SYMBOL_STR(videobuf_queue_cancel) },
	{ 0xee2bc2d0, __VMLINUX_SYMBOL_STR(omapdss_is_initialized) },
	{ 0x407a3275, __VMLINUX_SYMBOL_STR(omap_start_dma) },
	{ 0x17e9f0be, __VMLINUX_SYMBOL_STR(videobuf_streamon) },
	{ 0xcf18e3, __VMLINUX_SYMBOL_STR(__video_register_device) },
	{ 0x205ec8de, __VMLINUX_SYMBOL_STR(omap_dispc_register_isr) },
	{ 0x33ba5cd4, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0xebd4ed06, __VMLINUX_SYMBOL_STR(videobuf_queue_dma_contig_init) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x197dc3b3, __VMLINUX_SYMBOL_STR(omap_set_dma_src_burst_mode) },
	{ 0xd9f343b2, __VMLINUX_SYMBOL_STR(omapdss_get_version) },
	{ 0x6ccf7bd7, __VMLINUX_SYMBOL_STR(__pv_phys_offset) },
	{ 0xf6f3cef6, __VMLINUX_SYMBOL_STR(omap_vrfb_setup) },
	{ 0x455293f6, __VMLINUX_SYMBOL_STR(down_read) },
	{ 0xc52da066, __VMLINUX_SYMBOL_STR(omap_set_dma_dest_params) },
	{ 0xe426c33e, __VMLINUX_SYMBOL_STR(v4l2_device_register) },
	{ 0xc3325057, __VMLINUX_SYMBOL_STR(omap_dss_put_device) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xa4f934f7, __VMLINUX_SYMBOL_STR(video_device_alloc) },
	{ 0x4a39e5a1, __VMLINUX_SYMBOL_STR(omap_set_dma_src_params) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xb9a8f03b, __VMLINUX_SYMBOL_STR(omap_stop_dma) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xc0cf95f9, __VMLINUX_SYMBOL_STR(omap_vrfb_request_ctx) },
	{ 0xfc3d209d, __VMLINUX_SYMBOL_STR(videobuf_qbuf) },
	{ 0x8a39eb7, __VMLINUX_SYMBOL_STR(video_unregister_device) },
	{ 0xe6ffd094, __VMLINUX_SYMBOL_STR(omap_dss_get_next_device) },
	{ 0xfacd2e14, __VMLINUX_SYMBOL_STR(pgprot_user) },
	{ 0x5b3fb26f, __VMLINUX_SYMBOL_STR(videobuf_querybuf) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0x80d81308, __VMLINUX_SYMBOL_STR(omap_vrfb_release_ctx) },
	{ 0xa61e4362, __VMLINUX_SYMBOL_STR(omap_request_dma) },
	{ 0xe37d10ae, __VMLINUX_SYMBOL_STR(omap_dispc_unregister_isr) },
	{ 0x79ae86f6, __VMLINUX_SYMBOL_STR(find_vma) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x93fca811, __VMLINUX_SYMBOL_STR(__get_free_pages) },
	{ 0x15cc910, __VMLINUX_SYMBOL_STR(video_devdata) },
	{ 0xa5083cf1, __VMLINUX_SYMBOL_STR(get_user_pages) },
	{ 0xabe27502, __VMLINUX_SYMBOL_STR(v4l2_ctrl_query_fill) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x61fbc681, __VMLINUX_SYMBOL_STR(videobuf_dqbuf) },
	{ 0x4302d0eb, __VMLINUX_SYMBOL_STR(free_pages) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x4c33081d, __VMLINUX_SYMBOL_STR(omapdss_compat_uninit) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x55d549ff, __VMLINUX_SYMBOL_STR(remap_pfn_range) },
	{ 0x61acc54f, __VMLINUX_SYMBOL_STR(omap_dss_get_device) },
	{ 0x920eb90c, __VMLINUX_SYMBOL_STR(interruptible_sleep_on_timeout) },
	{ 0x8cd8c339, __VMLINUX_SYMBOL_STR(omap_free_dma) },
	{ 0x312bc183, __VMLINUX_SYMBOL_STR(videobuf_reqbufs) },
	{ 0xbf670952, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0x636b3461, __VMLINUX_SYMBOL_STR(omap_dss_get_num_overlays) },
	{ 0x35c39aa9, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x47c8baf4, __VMLINUX_SYMBOL_STR(param_ops_uint) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x1c483a9, __VMLINUX_SYMBOL_STR(v4l2_get_timestamp) },
	{ 0x9be04d52, __VMLINUX_SYMBOL_STR(video_ioctl2) },
	{ 0xd89decaf, __VMLINUX_SYMBOL_STR(videobuf_poll_stream) },
	{ 0xa48f5b09, __VMLINUX_SYMBOL_STR(omap_dma_set_global_params) },
	{ 0xd898e9dc, __VMLINUX_SYMBOL_STR(videobuf_streamoff) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=videobuf-core,omapdss,videobuf-dma-contig";

