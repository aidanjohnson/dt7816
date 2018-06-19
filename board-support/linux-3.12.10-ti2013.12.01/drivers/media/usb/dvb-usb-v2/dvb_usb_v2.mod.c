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
	{ 0x2d3385d3, __VMLINUX_SYMBOL_STR(system_wq) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xf6d4d012, __VMLINUX_SYMBOL_STR(rc_unregister_device) },
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x7302371d, __VMLINUX_SYMBOL_STR(dvb_dmx_init) },
	{ 0xa0fbac79, __VMLINUX_SYMBOL_STR(wake_up_bit) },
	{ 0xd51c05b5, __VMLINUX_SYMBOL_STR(dvb_unregister_adapter) },
	{ 0xbc91824b, __VMLINUX_SYMBOL_STR(dev_set_drvdata) },
	{ 0x7f012393, __VMLINUX_SYMBOL_STR(dvb_frontend_suspend) },
	{ 0xd2217c63, __VMLINUX_SYMBOL_STR(dvb_register_frontend) },
	{ 0x497a62cf, __VMLINUX_SYMBOL_STR(dvb_frontend_resume) },
	{ 0x6b06fdce, __VMLINUX_SYMBOL_STR(delayed_work_timer_fn) },
	{ 0x68913526, __VMLINUX_SYMBOL_STR(usb_kill_urb) },
	{ 0xe748d08d, __VMLINUX_SYMBOL_STR(dvb_unregister_frontend) },
	{ 0x593a99b, __VMLINUX_SYMBOL_STR(init_timer_key) },
	{ 0x24d7b4eb, __VMLINUX_SYMBOL_STR(cancel_delayed_work_sync) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xa43e3b01, __VMLINUX_SYMBOL_STR(rc_allocate_device) },
	{ 0x2eea13d5, __VMLINUX_SYMBOL_STR(dvb_net_release) },
	{ 0xc4a6a709, __VMLINUX_SYMBOL_STR(i2c_add_adapter) },
	{ 0xa432424c, __VMLINUX_SYMBOL_STR(dvb_frontend_detach) },
	{ 0xdd0a2ba2, __VMLINUX_SYMBOL_STR(strlcat) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xd936296e, __VMLINUX_SYMBOL_STR(dvb_dmx_swfilter_raw) },
	{ 0x6637f527, __VMLINUX_SYMBOL_STR(rc_free_device) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0xf5b09563, __VMLINUX_SYMBOL_STR(dvb_dmxdev_release) },
	{ 0x51942af5, __VMLINUX_SYMBOL_STR(__mutex_init) },
	{ 0xd29c47a6, __VMLINUX_SYMBOL_STR(dvb_dmx_swfilter) },
	{ 0xaa6fac1b, __VMLINUX_SYMBOL_STR(dvb_net_init) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0x55fb4413, __VMLINUX_SYMBOL_STR(rc_register_device) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x9f038e56, __VMLINUX_SYMBOL_STR(usb_free_coherent) },
	{ 0xdbe7dd6c, __VMLINUX_SYMBOL_STR(dvb_dmx_release) },
	{ 0x35785cab, __VMLINUX_SYMBOL_STR(dvb_dmx_swfilter_204) },
	{ 0x999a475f, __VMLINUX_SYMBOL_STR(i2c_del_adapter) },
	{ 0xaa50d13e, __VMLINUX_SYMBOL_STR(_dev_info) },
	{ 0xa97c342f, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0x12a38747, __VMLINUX_SYMBOL_STR(usleep_range) },
	{ 0xe851bb05, __VMLINUX_SYMBOL_STR(queue_delayed_work_on) },
	{ 0x3bd1b1f6, __VMLINUX_SYMBOL_STR(msecs_to_jiffies) },
	{ 0x11b78479, __VMLINUX_SYMBOL_STR(usb_bulk_msg) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0x72f4f140, __VMLINUX_SYMBOL_STR(dvb_register_adapter) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0xa0ceef51, __VMLINUX_SYMBOL_STR(out_of_line_wait_on_bit) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x155a3d9f, __VMLINUX_SYMBOL_STR(request_firmware) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0xb81960ca, __VMLINUX_SYMBOL_STR(snprintf) },
	{ 0x82925eed, __VMLINUX_SYMBOL_STR(usb_alloc_coherent) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x4b9ab611, __VMLINUX_SYMBOL_STR(usb_free_urb) },
	{ 0x8b5187c3, __VMLINUX_SYMBOL_STR(release_firmware) },
	{ 0x148c8de9, __VMLINUX_SYMBOL_STR(usb_alloc_urb) },
	{ 0x79a4264a, __VMLINUX_SYMBOL_STR(dvb_dmxdev_init) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "C364630FC7E52C390F5F928");
