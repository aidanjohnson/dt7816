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
	{ 0x630eb517, __VMLINUX_SYMBOL_STR(dib7000m_pid_filter_ctrl) },
	{ 0x402b8281, __VMLINUX_SYMBOL_STR(__request_module) },
	{ 0x1250aaee, __VMLINUX_SYMBOL_STR(kmalloc_caches) },
	{ 0xf9a482f9, __VMLINUX_SYMBOL_STR(msleep) },
	{ 0xd3aee98e, __VMLINUX_SYMBOL_STR(dib7000p_ctrl_timf) },
	{ 0x1a8ab5c1, __VMLINUX_SYMBOL_STR(dib8000_pid_filter) },
	{ 0xaa51ccb7, __VMLINUX_SYMBOL_STR(dib8000_get_i2c_master) },
	{ 0x72921fbb, __VMLINUX_SYMBOL_STR(dib8000_pwm_agc_reset) },
	{ 0xa89c2835, __VMLINUX_SYMBOL_STR(dib7000p_pid_filter_ctrl) },
	{ 0xf17be6ad, __VMLINUX_SYMBOL_STR(dibx000_i2c_set_speed) },
	{ 0xb6b46a7c, __VMLINUX_SYMBOL_STR(param_ops_int) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0x69bde0c9, __VMLINUX_SYMBOL_STR(dib8000_get_slave_frontend) },
	{ 0x963136be, __VMLINUX_SYMBOL_STR(dib7000p_set_agc1_min) },
	{ 0x36606dc0, __VMLINUX_SYMBOL_STR(dvb_usb_device_exit) },
	{ 0xdf7a3cb3, __VMLINUX_SYMBOL_STR(dib8000_i2c_enumeration) },
	{ 0x258c36ac, __VMLINUX_SYMBOL_STR(dib0090_gain_control) },
	{ 0x92dba6f2, __VMLINUX_SYMBOL_STR(dvb_usb_device_init) },
	{ 0x8169d80e, __VMLINUX_SYMBOL_STR(i2c_transfer) },
	{ 0x4ef56405, __VMLINUX_SYMBOL_STR(dib8096p_tuner_sleep) },
	{ 0xf7802486, __VMLINUX_SYMBOL_STR(__aeabi_uidivmod) },
	{ 0x2dd102c4, __VMLINUX_SYMBOL_STR(dib8000_pid_filter_ctrl) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xe7625861, __VMLINUX_SYMBOL_STR(dib0070_wbd_offset) },
	{ 0xadfb4ab7, __VMLINUX_SYMBOL_STR(dib0090_get_wbd_target) },
	{ 0x709ea375, __VMLINUX_SYMBOL_STR(dib0090_dcc_freq) },
	{ 0xe707d823, __VMLINUX_SYMBOL_STR(__aeabi_uidiv) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0xb864ba80, __VMLINUX_SYMBOL_STR(dib3000mc_get_tuner_i2c_master) },
	{ 0xda2478d0, __VMLINUX_SYMBOL_STR(param_ops_short) },
	{ 0xb223f9fb, __VMLINUX_SYMBOL_STR(usb_deregister) },
	{ 0x78f6258c, __VMLINUX_SYMBOL_STR(mutex_lock_interruptible) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0xc1b51153, __VMLINUX_SYMBOL_STR(dib7000p_pid_filter) },
	{ 0x859c8888, __VMLINUX_SYMBOL_STR(dib8000_set_wbd_ref) },
	{ 0x4799dd9, __VMLINUX_SYMBOL_STR(dib7090_slave_reset) },
	{ 0xa13244bd, __VMLINUX_SYMBOL_STR(rc_keydown) },
	{ 0x5d0da7df, __VMLINUX_SYMBOL_STR(dib0090_get_current_gain) },
	{ 0x1049b573, __VMLINUX_SYMBOL_STR(usb_control_msg) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0xb48de7e6, __VMLINUX_SYMBOL_STR(dib8000_set_gpio) },
	{ 0x2196324, __VMLINUX_SYMBOL_STR(__aeabi_idiv) },
	{ 0x868784cb, __VMLINUX_SYMBOL_STR(__symbol_get) },
	{ 0x7d69db8e, __VMLINUX_SYMBOL_STR(dib8000_update_pll) },
	{ 0xeae16a02, __VMLINUX_SYMBOL_STR(dib8096p_get_i2c_tuner) },
	{ 0x50838ec8, __VMLINUX_SYMBOL_STR(dib8000_get_adc_power) },
	{ 0xa317c75f, __VMLINUX_SYMBOL_STR(dib7000p_set_wbd_ref) },
	{ 0xa97c342f, __VMLINUX_SYMBOL_STR(usb_submit_urb) },
	{ 0x11b78479, __VMLINUX_SYMBOL_STR(usb_bulk_msg) },
	{ 0x5b3bda67, __VMLINUX_SYMBOL_STR(dib7000p_i2c_enumeration) },
	{ 0xf4279b7b, __VMLINUX_SYMBOL_STR(dib8000_ctrl_timf) },
	{ 0xf81d5279, __VMLINUX_SYMBOL_STR(dib7000pc_detection) },
	{ 0xb8a069c7, __VMLINUX_SYMBOL_STR(kmem_cache_alloc_trace) },
	{ 0x65d24247, __VMLINUX_SYMBOL_STR(dib3000mc_i2c_enumeration) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x28f40641, __VMLINUX_SYMBOL_STR(dib7000m_pid_filter) },
	{ 0xdc6a40fb, __VMLINUX_SYMBOL_STR(dib7000p_update_pll) },
	{ 0x9d669763, __VMLINUX_SYMBOL_STR(memcpy) },
	{ 0x20b2bb2d, __VMLINUX_SYMBOL_STR(param_array_ops) },
	{ 0x639a281b, __VMLINUX_SYMBOL_STR(dib0090_pwm_gain_reset) },
	{ 0x6f3e4e60, __VMLINUX_SYMBOL_STR(dib7090_get_adc_power) },
	{ 0xa3e8bb7a, __VMLINUX_SYMBOL_STR(usb_register_driver) },
	{ 0xf33bbb54, __VMLINUX_SYMBOL_STR(dib7090_tuner_sleep) },
	{ 0xdc9bb744, __VMLINUX_SYMBOL_STR(dib8000_set_slave_frontend) },
	{ 0x155a3d9f, __VMLINUX_SYMBOL_STR(request_firmware) },
	{ 0x176c2d00, __VMLINUX_SYMBOL_STR(dib8000_set_tune_state) },
	{ 0x4e807ca8, __VMLINUX_SYMBOL_STR(dib0090_set_dc_servo) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x6e9dd606, __VMLINUX_SYMBOL_STR(__symbol_put) },
	{ 0x19438495, __VMLINUX_SYMBOL_STR(dvb_usb_get_hexline) },
	{ 0x5eb278ba, __VMLINUX_SYMBOL_STR(dib7000p_get_i2c_master) },
	{ 0x47ae413d, __VMLINUX_SYMBOL_STR(dib0090_set_tune_state) },
	{ 0xca165d5b, __VMLINUX_SYMBOL_STR(dib0070_ctrl_agc_filter) },
	{ 0x5c984726, __VMLINUX_SYMBOL_STR(dev_get_drvdata) },
	{ 0x4b9ab611, __VMLINUX_SYMBOL_STR(usb_free_urb) },
	{ 0x92a7a5d1, __VMLINUX_SYMBOL_STR(dib7090_get_i2c_tuner) },
	{ 0xcc469e97, __VMLINUX_SYMBOL_STR(dib7000m_get_i2c_master) },
	{ 0xe58b3886, __VMLINUX_SYMBOL_STR(dib0090_get_tune_state) },
	{ 0x678d0f81, __VMLINUX_SYMBOL_STR(dib7000p_set_gpio) },
	{ 0x148c8de9, __VMLINUX_SYMBOL_STR(usb_alloc_urb) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=dib7000m,dib7000p,dib8000,dibx000_common,dvb-usb,dib0090,dib0070,dib3000mc";

MODULE_ALIAS("usb:v10B8p1E14d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10B8p1E78d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p9941d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p9950d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p7050d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v07CApA807d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v185Bp1E78d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1584p6003d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0413p6F00d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p7060d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v07CApB808d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2304p022Cd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0CCDp005Ad*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p9580d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10B8p1EF0d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10B8p1EBCd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2304p0228d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10B8p1EBEd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2304p0229d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v185Bp1E80d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v07CApB568d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1044p7001d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v05D8p810Fd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0B05p171Fd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0B05p173Fd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p7070d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p7080d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0CCDp0058d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2304p022Ed*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2304p0236d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2304p0237d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1164p1EDCd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0CCDp0060d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0CCDp0078d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0413p6F01d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p5200d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040p8400d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1044p7002d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1164p1F08d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0B05p1736d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2304p023Ad*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2304p023Bd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0CCDp0062d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0CCDp0081d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1415p0003d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1164p2EDCd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040pB200d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2040pB210d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1164p0871d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0FD9p0021d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0FD9p0020d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0413p60F6d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0CCDp10A0d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0CCDp10A1d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1164p1EFCd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1164p1E8Cd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2304p0243d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2013p0245d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2013p0248d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10B8p1E80d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0CCDp00ABd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10B8p1F98d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10B8p1F90d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1554p5010d3F00dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1554p5010d3[0-9a-0]*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1554p5010d[0-2]*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1E59p0002d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2304p0245d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2304p0248d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10B8p1FA0d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0FD9p0011d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10B8p2383d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10B8p1FA8d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10B8p2384d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10B8p1BB2d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10B8p1BB4d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v14F7p0004d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v1660p1921d*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2304p023Dd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2304p023Ed*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10B8p1E6Ed*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v10B8p1F9Cd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v0FD9p003Fd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2013p025Cd*dc*dsc*dp*ic*isc*ip*in*");
MODULE_ALIAS("usb:v2013p025Dd*dc*dsc*dp*ic*isc*ip*in*");

MODULE_INFO(srcversion, "B8FCA02442E495555F5B020");
