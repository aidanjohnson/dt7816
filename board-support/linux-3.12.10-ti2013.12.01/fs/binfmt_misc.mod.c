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
	{ 0xf866a7c7, __VMLINUX_SYMBOL_STR(kill_litter_super) },
	{ 0xe57e68bb, __VMLINUX_SYMBOL_STR(noop_llseek) },
	{ 0x7a2d97, __VMLINUX_SYMBOL_STR(default_llseek) },
	{ 0xbfd69f01, __VMLINUX_SYMBOL_STR(simple_statfs) },
	{ 0x7dc3609c, __VMLINUX_SYMBOL_STR(unregister_filesystem) },
	{ 0xb36ce2e7, __VMLINUX_SYMBOL_STR(unregister_binfmt) },
	{ 0x447bb629, __VMLINUX_SYMBOL_STR(__register_binfmt) },
	{ 0x1a92170e, __VMLINUX_SYMBOL_STR(register_filesystem) },
	{ 0x146b7fa, __VMLINUX_SYMBOL_STR(d_instantiate) },
	{ 0x646f02dd, __VMLINUX_SYMBOL_STR(iput) },
	{ 0x7979ef2d, __VMLINUX_SYMBOL_STR(simple_pin_fs) },
	{ 0x87153bcb, __VMLINUX_SYMBOL_STR(current_fs_time) },
	{ 0xe953b21f, __VMLINUX_SYMBOL_STR(get_next_ino) },
	{ 0xadae7dae, __VMLINUX_SYMBOL_STR(new_inode) },
	{ 0x9482d681, __VMLINUX_SYMBOL_STR(lookup_one_len) },
	{ 0xc8339e24, __VMLINUX_SYMBOL_STR(string_unescape) },
	{ 0x20000329, __VMLINUX_SYMBOL_STR(simple_strtoul) },
	{ 0x349cba85, __VMLINUX_SYMBOL_STR(strchr) },
	{ 0x5f754e5a, __VMLINUX_SYMBOL_STR(memset) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0x491069b1, __VMLINUX_SYMBOL_STR(mutex_unlock) },
	{ 0xd4672ae5, __VMLINUX_SYMBOL_STR(mutex_lock) },
	{ 0x8cb6a962, __VMLINUX_SYMBOL_STR(lockref_get) },
	{ 0x676bbc0f, __VMLINUX_SYMBOL_STR(_set_bit) },
	{ 0x49ebacbd, __VMLINUX_SYMBOL_STR(_clear_bit) },
	{ 0xfbc74f64, __VMLINUX_SYMBOL_STR(__copy_from_user) },
	{ 0xdcb0349b, __VMLINUX_SYMBOL_STR(sys_close) },
	{ 0x4df53202, __VMLINUX_SYMBOL_STR(search_binary_handler) },
	{ 0xad8537fe, __VMLINUX_SYMBOL_STR(prepare_binprm) },
	{ 0x3d315771, __VMLINUX_SYMBOL_STR(kernel_read) },
	{ 0xfa2a45e, __VMLINUX_SYMBOL_STR(__memzero) },
	{ 0x5449ae05, __VMLINUX_SYMBOL_STR(open_exec) },
	{ 0x6984f51a, __VMLINUX_SYMBOL_STR(bprm_change_interp) },
	{ 0xf7dfc0f7, __VMLINUX_SYMBOL_STR(copy_strings_kernel) },
	{ 0x7a082438, __VMLINUX_SYMBOL_STR(fput) },
	{ 0x2870ab05, __VMLINUX_SYMBOL_STR(would_dump) },
	{ 0xf9708ca0, __VMLINUX_SYMBOL_STR(fd_install) },
	{ 0xa843805a, __VMLINUX_SYMBOL_STR(get_unused_fd_flags) },
	{ 0xa397b65c, __VMLINUX_SYMBOL_STR(remove_arg_zero) },
	{ 0x73e20c1c, __VMLINUX_SYMBOL_STR(strlcpy) },
	{ 0xe2d5255a, __VMLINUX_SYMBOL_STR(strcmp) },
	{ 0x9f984513, __VMLINUX_SYMBOL_STR(strrchr) },
	{ 0x7b6646bb, __VMLINUX_SYMBOL_STR(_raw_read_lock) },
	{ 0x37a0cba, __VMLINUX_SYMBOL_STR(kfree) },
	{ 0x72602934, __VMLINUX_SYMBOL_STR(clear_inode) },
	{ 0x4302d0eb, __VMLINUX_SYMBOL_STR(free_pages) },
	{ 0xe914e41e, __VMLINUX_SYMBOL_STR(strcpy) },
	{ 0x91715312, __VMLINUX_SYMBOL_STR(sprintf) },
	{ 0x93fca811, __VMLINUX_SYMBOL_STR(__get_free_pages) },
	{ 0x528c709d, __VMLINUX_SYMBOL_STR(simple_read_from_buffer) },
	{ 0x97255bdf, __VMLINUX_SYMBOL_STR(strlen) },
	{ 0xdf1acdaa, __VMLINUX_SYMBOL_STR(simple_release_fs) },
	{ 0x7bf11e89, __VMLINUX_SYMBOL_STR(dput) },
	{ 0x1ace3f1d, __VMLINUX_SYMBOL_STR(d_drop) },
	{ 0xcb16ccd8, __VMLINUX_SYMBOL_STR(drop_nlink) },
	{ 0x1ea06663, __VMLINUX_SYMBOL_STR(_raw_write_lock) },
	{ 0xe893fe03, __VMLINUX_SYMBOL_STR(simple_fill_super) },
	{ 0x61095033, __VMLINUX_SYMBOL_STR(mount_single) },
	{ 0xefd6cf06, __VMLINUX_SYMBOL_STR(__aeabi_unwind_cpp_pr0) },
	{ 0x11089ac7, __VMLINUX_SYMBOL_STR(_ctype) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";

