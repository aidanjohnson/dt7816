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

MODULE_INFO(staging, "Y");

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xb5c97a0d, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x2e5810c6, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr1) },
	{ 0xc8b57c27, __VMLINUX_SYMBOL_STR(autoremove_wake_function) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0xbd59f360, __VMLINUX_SYMBOL_STR(kthread_create_on_node) },
	{ 0x275ef902, __VMLINUX_SYMBOL_STR(__init_waitqueue_head) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x347badfd, __VMLINUX_SYMBOL_STR(dev_err) },
	{ 0x51d559d1, __VMLINUX_SYMBOL_STR(_raw_spin_unlock_irqrestore) },
	{ 0x27e1a049, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x20c55ae0, __VMLINUX_SYMBOL_STR(sscanf) },
	{ 0x90a20675, __VMLINUX_SYMBOL_STR(kthread_stop) },
	{ 0x7a082438, __VMLINUX_SYMBOL_STR(fput) },
	{ 0x4059792f, __VMLINUX_SYMBOL_STR(print_hex_dump) },
	{ 0x1000e51, __VMLINUX_SYMBOL_STR(schedule) },
	{ 0x26021bc4, __VMLINUX_SYMBOL_STR(wake_up_process) },
	{ 0x9c0bd51f, __VMLINUX_SYMBOL_STR(_raw_spin_lock) },
	{ 0x598542b2, __VMLINUX_SYMBOL_STR(_raw_spin_lock_irqsave) },
	{ 0x343a0573, __VMLINUX_SYMBOL_STR(kernel_recvmsg) },
	{ 0xd85cd67e, __VMLINUX_SYMBOL_STR(__wake_up) },
	{ 0xb3f7646e, __VMLINUX_SYMBOL_STR(kthread_should_stop) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x499cb58c, __VMLINUX_SYMBOL_STR(prepare_to_wait) },
	{ 0x5952aaf, __VMLINUX_SYMBOL_STR(fget) },
	{ 0x1cfb04fa, __VMLINUX_SYMBOL_STR(finish_wait) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x99bb8806, __VMLINUX_SYMBOL_STR(memmove) },
	{ 0x8d2e268b, __VMLINUX_SYMBOL_STR(param_ops_ulong) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "32E792436B6624A4571E3DC");
