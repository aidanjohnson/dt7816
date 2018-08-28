#ifndef __AIO_SYSCALLS__
#define __AIO_SYSCALLS__
/*
 *	Prototypes for APIs used for Asynchronous IO (AIO). These invoke syscalls
 *  in the Linux kernel instead of using libaio
 * 
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
#include <unistd.h>
#include <sys/syscall.h>	/* for __NR_* definitions */
#include <linux/aio_abi.h>	/* for AIO types and constants */
#pragma GCC diagnostic ignored "-Wunused-function"

static inline int io_setup(unsigned nr, aio_context_t *ctxp)
{
    return syscall(__NR_io_setup, nr, ctxp);
}

static inline int io_destroy(aio_context_t ctx) 
{
    return syscall(__NR_io_destroy, ctx);
}

static inline int io_submit(aio_context_t ctx, long nr,  struct iocb **iocbpp) 
{
    return syscall(__NR_io_submit, ctx, nr, iocbpp);
}

static inline int io_getevents(aio_context_t ctx, long min_nr, long max_nr,
    struct io_event *events, struct timespec *timeout)
{
    return syscall(__NR_io_getevents, ctx, min_nr, max_nr, events, timeout);
}    

static inline int io_cancel(aio_context_t ctx, struct iocb *iocb,
                 struct io_event *result)
{
    return syscall(__NR_io_cancel, ctx, iocb, result);
} 

static int eventfd(int count) 
{
	return syscall(__NR_eventfd, count);
}

#endif
