#ifndef _ERRNO_H

#include <uapi/asm-generic/errno.h>
#include <uapi/asm-generic/errno-base.h>
extern int errno;

#define __set_errno(val) do { errno = val; } while (0)

#endif /* _ERRNO_H */
