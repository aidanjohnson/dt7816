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
	{ 0x13cffdee, __VMLINUX_SYMBOL_STR(drm_release) },
	{ 0x61ee57f5, __VMLINUX_SYMBOL_STR(drm_fb_helper_set_par) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xf9427374, __VMLINUX_SYMBOL_STR(dispc_request_irq) },
	{ 0xf88c3301, __VMLINUX_SYMBOL_STR(sg_init_table) },
	{ 0x93963a85, __VMLINUX_SYMBOL_STR(dss_feat_get_num_mgrs) },
	{ 0x9f823cea, __VMLINUX_SYMBOL_STR(dispc_mgr_is_enabled) },
	{ 0xc0af72f3, __VMLINUX_SYMBOL_STR(drm_crtc_helper_set_config) },
	{ 0x19677e4, __VMLINUX_SYMBOL_STR(drm_gem_put_pages) },
	{ 0xbe8860a8, __VMLINUX_SYMBOL_STR(dispc_mgr_go_busy) },
	{ 0xe52e3763, __VMLINUX_SYMBOL_STR(mem_map) },
	{ 0x1d4c9c9f, __VMLINUX_SYMBOL_STR(drm_framebuffer_reference) },
	{ 0x3c30f85e, __VMLINUX_SYMBOL_STR(drm_fb_helper_initial_config) },
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0xedd8a3bf, __VMLINUX_SYMBOL_STR(framebuffer_release) },
	{ 0x3f358d29, __VMLINUX_SYMBOL_STR(page_address) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x43a53735, __VMLINUX_SYMBOL_STR(__alloc_workqueue_key) },
	{ 0xef62248c, __VMLINUX_SYMBOL_STR(drm_mode_config_cleanup) },
	{ 0x55b9bb93, __VMLINUX_SYMBOL_STR(drm_flip_work_cleanup) },
	{ 0x116f9332, __VMLINUX_SYMBOL_STR(omap_dss_get_overlay_manager) },
	{ 0x64a22ff0, __VMLINUX_SYMBOL_STR(dispc_mgr_set_lcd_config) },
	{ 0xc8b57c27, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0xdb93b838, __VMLINUX_SYMBOL_STR(dispc_free_irq) },
	{ 0x655b8063, __VMLINUX_SYMBOL_STR(arm_dma_ops) },
	{ 0x45c85e7f, __VMLINUX_SYMBOL_STR(drm_mode_destroy) },
	{ 0x1b7fd59, __VMLINUX_SYMBOL_STR(dispc_read_irqstatus) },
	{ 0x547ce898, __VMLINUX_SYMBOL_STR(dispc_read_irqenable) },
	{ 0xa35444e4, __VMLINUX_SYMBOL_STR(dispc_write_irqenable) },
	{ 0xd5f97ee8, __VMLINUX_SYMBOL_STR(drm_property_create_range) },
	{ 0xed98d3e0, __VMLINUX_SYMBOL_STR(fb_sys_read) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0x506a5f37, __VMLINUX_SYMBOL_STR(drm_plane_init) },
	{ 0x9fc1617f, __VMLINUX_SYMBOL_STR(drm_helper_probe_single_connector_modes) },
	{ 0xddf31152, __VMLINUX_SYMBOL_STR(drm_gem_mmap_obj) },
	{ 0x2247cba2, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0xe2fae716, __VMLINUX_SYMBOL_STR(kmemdup) },
	{ 0xee2bc2d0, __VMLINUX_SYMBOL_STR(omapdss_is_initialized) },
	{ 0x5f87e351, __VMLINUX_SYMBOL_STR(drm_gem_free_mmap_offset) },
	{ 0x9b19203a, __VMLINUX_SYMBOL_STR(drm_vblank_cleanup) },
	{ 0x1ea132e, __VMLINUX_SYMBOL_STR(dispc_runtime_put) },
	{ 0x33ba5cd4, __VMLINUX_SYMBOL_STR(param_ops_bool) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0x50d5612e, __VMLINUX_SYMBOL_STR(dispc_mgr_get_sync_lost_irq) },
	{ 0xff1f75bf, __VMLINUX_SYMBOL_STR(drm_vblank_init) },
	{ 0x8dfd1e65, __VMLINUX_SYMBOL_STR(drm_encoder_init) },
	{ 0xb95beb55, __VMLINUX_SYMBOL_STR(drm_object_property_set_value) },
	{ 0x633fe25b, __VMLINUX_SYMBOL_STR(sys_copyarea) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xfc55d6db, __VMLINUX_SYMBOL_STR(__alloc_pages_nodemask) },
	{ 0x5689afe7, __VMLINUX_SYMBOL_STR(dispc_ovl_enable) },
	{ 0x3d9bfe9b, __VMLINUX_SYMBOL_STR(drm_gem_create_mmap_offset_size) },
	{ 0x7781b4da, __VMLINUX_SYMBOL_STR(__platform_driver_register) },
	{ 0x6ccf7bd7, __VMLINUX_SYMBOL_STR(__pv_phys_offset) },
	{ 0x5b414f30, __VMLINUX_SYMBOL_STR(drm_connector_cleanup) },
	{ 0x56bc2f15, __VMLINUX_SYMBOL_STR(dispc_ovl_set_channel_out) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x7cbe8095, __VMLINUX_SYMBOL_STR(dispc_mgr_set_timings) },
	{ 0xc6473a84, __VMLINUX_SYMBOL_STR(drm_vblank_count) },
	{ 0x4c511235, __VMLINUX_SYMBOL_STR(drm_edid_is_valid) },
	{ 0xc3325057, __VMLINUX_SYMBOL_STR(omap_dss_put_device) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0x576b86cd, __VMLINUX_SYMBOL_STR(drm_fb_helper_pan_display) },
	{ 0x60055baa, __VMLINUX_SYMBOL_STR(dispc_mgr_get_vsync_irq) },
	{ 0x85b1de08, __VMLINUX_SYMBOL_STR(drm_flip_work_queue) },
	{ 0xd66921ce, __VMLINUX_SYMBOL_STR(drm_handle_vblank) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0x88ab6fe3, __VMLINUX_SYMBOL_STR(kgdb_active) },
	{ 0x34d04659, __VMLINUX_SYMBOL_STR(kmap_atomic) },
	{ 0x8d1f8b8a, __VMLINUX_SYMBOL_STR(drm_helper_connector_dpms) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xa5a0628b, __VMLINUX_SYMBOL_STR(drm_fb_helper_restore_fbdev_mode) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0xfe40bf95, __VMLINUX_SYMBOL_STR(dss_feat_get_num_ovls) },
	{ 0xd8e14977, __VMLINUX_SYMBOL_STR(drm_mode_connector_attach_encoder) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x5eafb8e9, __VMLINUX_SYMBOL_STR(drm_mode_set_name) },
	{ 0x78f6258c, __VMLINUX_SYMBOL_STR(mutex_lock_interruptible) },
	{ 0x8dfe91a0, __VMLINUX_SYMBOL_STR(drm_helper_mode_fill_fb_struct) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x8f7df3a7, __VMLINUX_SYMBOL_STR(drm_object_attach_property) },
	{ 0xa763dc1f, __VMLINUX_SYMBOL_STR(drm_mode_duplicate) },
	{ 0x7a890c8, __VMLINUX_SYMBOL_STR(fb_alloc_cmap) },
	{ 0x71c90087, __VMLINUX_SYMBOL_STR(memcmp) },
	{ 0x3593eed2, __VMLINUX_SYMBOL_STR(omapdss_find_mgr_from_display) },
	{ 0x4c4fdc8, __VMLINUX_SYMBOL_STR(drm_gem_handle_create) },
	{ 0x8d7bc8ce, __VMLINUX_SYMBOL_STR(drm_gem_dumb_destroy) },
	{ 0xb17c0f91, __VMLINUX_SYMBOL_STR(vmap) },
	{ 0xfe67cbd6, __VMLINUX_SYMBOL_STR(kunmap) },
	{ 0xe6ffd094, __VMLINUX_SYMBOL_STR(omap_dss_get_next_device) },
	{ 0x18a268b2, __VMLINUX_SYMBOL_STR(drm_fb_helper_fill_var) },
	{ 0x2d770676, __VMLINUX_SYMBOL_STR(dispc_mgr_go) },
	{ 0xb8521fe, __VMLINUX_SYMBOL_STR(drm_send_vblank_event) },
	{ 0x16305289, __VMLINUX_SYMBOL_STR(warn_slowpath_null) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xddfe220f, __VMLINUX_SYMBOL_STR(drm_platform_exit) },
	{ 0xed93f29e, __VMLINUX_SYMBOL_STR(__kunmap_atomic) },
	{ 0x8c03d20c, __VMLINUX_SYMBOL_STR(destroy_workqueue) },
	{ 0x4c3b702e, __VMLINUX_SYMBOL_STR(drm_gem_object_release) },
	{ 0x730869c5, __VMLINUX_SYMBOL_STR(drm_framebuffer_unreference) },
	{ 0xbed18b93, __VMLINUX_SYMBOL_STR(platform_get_resource) },
	{ 0x9b187525, __VMLINUX_SYMBOL_STR(drm_read) },
	{ 0xe57e68bb, __VMLINUX_SYMBOL_STR(noop_llseek) },
	{ 0x1366a409, __VMLINUX_SYMBOL_STR(drm_add_edid_modes) },
	{ 0x3082a0b3, __VMLINUX_SYMBOL_STR(dss_feat_get_supported_color_modes) },
	{ 0xd6b8e852, __VMLINUX_SYMBOL_STR(request_threaded_irq) },
	{ 0xeae307aa, __VMLINUX_SYMBOL_STR(drm_sysfs_connector_remove) },
	{ 0x8e865d3c, __VMLINUX_SYMBOL_STR(arm_delay_ops) },
	{ 0x7a082438, __VMLINUX_SYMBOL_STR(fput) },
	{ 0x1cda0051, __VMLINUX_SYMBOL_STR(drm_debugfs_create_files) },
	{ 0x3bada2c5, __VMLINUX_SYMBOL_STR(drm_platform_init) },
	{ 0x1784f057, __VMLINUX_SYMBOL_STR(dispc_ovl_set_fifo_threshold) },
	{ 0x9745d638, __VMLINUX_SYMBOL_STR(drm_err) },
	{ 0x23daafc9, __VMLINUX_SYMBOL_STR(drm_connector_init) },
	{ 0x42160169, __VMLINUX_SYMBOL_STR(flush_workqueue) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0x306a1617, __VMLINUX_SYMBOL_STR(contig_page_data) },
	{ 0x5b2266c7, __VMLINUX_SYMBOL_STR(drm_gem_vm_open) },
	{ 0x19b912f8, __VMLINUX_SYMBOL_STR(drm_mode_connector_update_edid_property) },
	{ 0xe7e15910, __VMLINUX_SYMBOL_STR(dispc_clear_irqstatus) },
	{ 0x9d9e5d5f, __VMLINUX_SYMBOL_STR(drm_gem_vm_close) },
	{ 0x4ea1f5a2, __VMLINUX_SYMBOL_STR(drm_gem_object_free) },
	{ 0x7ee7f093, __VMLINUX_SYMBOL_STR(dispc_ovl_compute_fifo_thresholds) },
	{ 0xcdd158d, __VMLINUX_SYMBOL_STR(sg_alloc_table) },
	{ 0xdd74a2ec, __VMLINUX_SYMBOL_STR(drm_gem_prime_fd_to_handle) },
	{ 0xd4a5fa22, __VMLINUX_SYMBOL_STR(drm_framebuffer_remove) },
	{ 0x1db61e25, __VMLINUX_SYMBOL_STR(drm_plane_cleanup) },
	{ 0x22f53c27, __VMLINUX_SYMBOL_STR(drm_ioctl) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0x990b050a, __VMLINUX_SYMBOL_STR(drm_mode_create) },
	{ 0x40141e4f, __VMLINUX_SYMBOL_STR(drm_gem_mmap) },
	{ 0x85cd3250, __VMLINUX_SYMBOL_STR(__free_pages) },
	{ 0x92ec5d1b, __VMLINUX_SYMBOL_STR(dispc_mgr_enable) },
	{ 0xbbf94b7c, __VMLINUX_SYMBOL_STR(sys_fillrect) },
	{ 0x180d1e52, __VMLINUX_SYMBOL_STR(kmap) },
	{ 0x9793c93a, __VMLINUX_SYMBOL_STR(dispc_mgr_setup) },
	{ 0xd73c7afb, __VMLINUX_SYMBOL_STR(drm_framebuffer_unregister_private) },
	{ 0xb028fba, __VMLINUX_SYMBOL_STR(dss_feat_get_supported_outputs) },
	{ 0x3f1862b, __VMLINUX_SYMBOL_STR(drm_fb_helper_check_var) },
	{ 0x75f26a5b, __VMLINUX_SYMBOL_STR(drm_gem_private_object_init) },
	{ 0x3bd1b1f6, __VMLINUX_SYMBOL_STR(msecs_to_jiffies) },
	{ 0xe81ad8cb, __VMLINUX_SYMBOL_STR(drm_fb_helper_blank) },
	{ 0xd62c833f, __VMLINUX_SYMBOL_STR(schedule_timeout) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0x68b077dd, __VMLINUX_SYMBOL_STR(sys_imageblit) },
	{ 0xc2165d85, __VMLINUX_SYMBOL_STR(__arm_iounmap) },
	{ 0xbe8fb90c, __VMLINUX_SYMBOL_STR(dispc_mgr_get_framedone_irq) },
	{ 0x38a4f7ae, __VMLINUX_SYMBOL_STR(drm_format_num_planes) },
	{ 0x1698c419, __VMLINUX_SYMBOL_STR(fb_sys_write) },
	{ 0xa1ae85b6, __VMLINUX_SYMBOL_STR(drm_sysfs_connector_add) },
	{ 0xd4d6ba1f, __VMLINUX_SYMBOL_STR(drm_gem_object_lookup) },
	{ 0x5b92d1d3, __VMLINUX_SYMBOL_STR(drm_fb_helper_hotplug_event) },
	{ 0x11df7eae, __VMLINUX_SYMBOL_STR(drm_flip_work_commit) },
	{ 0xbafeee36, __VMLINUX_SYMBOL_STR(dispc_runtime_get) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x1c6d3294, __VMLINUX_SYMBOL_STR(drm_crtc_init) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x31c39ee3, __VMLINUX_SYMBOL_STR(drm_gem_prime_handle_to_fd) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0x9db8d444, __VMLINUX_SYMBOL_STR(drm_gem_object_init) },
	{ 0x12a7a29f, __VMLINUX_SYMBOL_STR(drm_encoder_cleanup) },
	{ 0x1a85aa8a, __VMLINUX_SYMBOL_STR(framebuffer_alloc) },
	{ 0xd599e1d7, __VMLINUX_SYMBOL_STR(vm_insert_mixed) },
	{ 0x70e39dae, __VMLINUX_SYMBOL_STR(dss_uninstall_mgr_ops) },
	{ 0x31d3cbc5, __VMLINUX_SYMBOL_STR(drm_crtc_cleanup) },
	{ 0x652c682f, __VMLINUX_SYMBOL_STR(drm_mode_config_init) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x94961283, __VMLINUX_SYMBOL_STR(vunmap) },
	{ 0xcf978f97, __VMLINUX_SYMBOL_STR(unmap_mapping_range) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x61acc54f, __VMLINUX_SYMBOL_STR(omap_dss_get_device) },
	{ 0x499cb58c, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0x1db7dc40, __VMLINUX_SYMBOL_STR(pgprot_kernel) },
	{ 0x3adc2f90, __VMLINUX_SYMBOL_STR(drm_debugfs_remove_files) },
	{ 0x79da9b7d, __VMLINUX_SYMBOL_STR(drm_fb_helper_fini) },
	{ 0x48537dcd, __VMLINUX_SYMBOL_STR(drm_modeset_lock_all) },
	{ 0xcbb77fcf, __VMLINUX_SYMBOL_STR(dma_buf_export_named) },
	{ 0x1cfb04fa, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0xded58f1, __VMLINUX_SYMBOL_STR(drm_flip_work_init) },
	{ 0xbf670952, __VMLINUX_SYMBOL_STR(dev_warn) },
	{ 0xfb961d14, __VMLINUX_SYMBOL_STR(__arm_ioremap) },
	{ 0x9cd60539, __VMLINUX_SYMBOL_STR(sg_free_table) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x3e884f4b, __VMLINUX_SYMBOL_STR(vm_get_page_prot) },
	{ 0xb4ce91dc, __VMLINUX_SYMBOL_STR(drm_mode_probed_add) },
	{ 0xb2d48a2e, __VMLINUX_SYMBOL_STR(queue_work_on) },
	{ 0x2fc77d31, __VMLINUX_SYMBOL_STR(drm_modeset_unlock_all) },
	{ 0xfa6be079, __VMLINUX_SYMBOL_STR(platform_get_irq) },
	{ 0xa548bc1c, __VMLINUX_SYMBOL_STR(drm_helper_disable_unused_functions) },
	{ 0x52ab03f9, __VMLINUX_SYMBOL_STR(drm_fb_helper_setcmap) },
	{ 0x35c39aa9, __VMLINUX_SYMBOL_STR(platform_driver_unregister) },
	{ 0xf863aa3, __VMLINUX_SYMBOL_STR(drm_framebuffer_init) },
	{ 0x498dcb5e, __VMLINUX_SYMBOL_STR(drm_ut_debug_printk) },
	{ 0x6dabf356, __VMLINUX_SYMBOL_STR(drm_kms_helper_poll_init) },
	{ 0x71658a05, __VMLINUX_SYMBOL_STR(dispc_ovl_setup) },
	{ 0x20700c2f, __VMLINUX_SYMBOL_STR(drm_gem_get_pages) },
	{ 0x6b469a8e, __VMLINUX_SYMBOL_STR(drm_fb_helper_fill_fix) },
	{ 0xac8f37b2, __VMLINUX_SYMBOL_STR(outer_cache) },
	{ 0x34a2ceaa, __VMLINUX_SYMBOL_STR(dss_install_mgr_ops) },
	{ 0x3ac1fef9, __VMLINUX_SYMBOL_STR(drm_mode_legacy_fb_format) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x1de9f3dd, __VMLINUX_SYMBOL_STR(omapdss_find_output_from_display) },
	{ 0xc692f423, __VMLINUX_SYMBOL_STR(drm_poll) },
	{ 0xd1d0158c, __VMLINUX_SYMBOL_STR(drm_mm_dump_table) },
	{ 0x79f95cd0, __VMLINUX_SYMBOL_STR(drm_fb_helper_init) },
	{ 0x7b33ad7d, __VMLINUX_SYMBOL_STR(drm_fb_helper_single_add_all_connectors) },
	{ 0xcb1beab5, __VMLINUX_SYMBOL_STR(drm_mode_vrefresh) },
	{ 0xf20dabd8, __VMLINUX_SYMBOL_STR(free_irq) },
	{ 0x1dfd2abf, __VMLINUX_SYMBOL_STR(drm_property_create_bitmask) },
	{ 0x74aa52f0, __VMLINUX_SYMBOL_STR(drm_open) },
	{ 0xed588a16, __VMLINUX_SYMBOL_STR(drm_kms_helper_poll_fini) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
	{ 0x83faa41c, __VMLINUX_SYMBOL_STR(drm_framebuffer_cleanup) },
	{ 0x70c3a44f, __VMLINUX_SYMBOL_STR(unregister_framebuffer) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=omapdss";
