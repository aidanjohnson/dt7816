/*****************************************************************************
 * Miscelleneous APIs, used in DT78XX embedded application 
 * 
 * Copyright (C) 2015 Data Translation Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * You are free to use this source code under the terms of the GNU General
 * Public License, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <termios.h>    /* termios tcsetattr tcgetattr TCSANOW */
#include <sys/ioctl.h>  /* ioctl FIONREAD ICANON ECHO */
#include <unistd.h>
#ifndef  __cplusplus
#define __USE_GNU   (1)
#endif
#include <signal.h>
#include <fcntl.h>

static int g_initialized = 0;
static struct termios g_original_tty;

/*****************************************************************************
 * Register a signal handler for a specific signal
 * See http://www.gnu.org/software/libc/manual/html_node/Signal-Handling.html
 */
int sigaction_register(int sig, void (* handler)(int))
{
    struct sigaction act;
    int err;
    
    memset (&act, 0, sizeof(act));
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    err = sigaction(sig, &act, NULL);
    if (err)
        perror("sigaction");
    return err;
}

/*****************************************************************************
 * Register a signal handler for a specific signal for the specified file
 */
int file_sigaction_register(int fd, int sig, void (* handler)(int))
{
    int err;
    if ((err = fcntl(fd, F_SETOWN, getpid())) < 0)
    {
        perror("F_SETOWN");
        return err;
    }
    //Get & set the flags
    int oflags = fcntl(fd, F_GETFL);
    if ((err = fcntl(fd, F_SETFL, oflags | FASYNC)) < 0)
    {
        perror("F_SETFL");
        return err;
    }
    if ((err = fcntl(fd, F_SETSIG, sig)) < 0)
    {
        perror("F_SETFL");
        return err;
    }
    err = sigaction_register(sig, handler);
    return err;
}

/*****************************************************************************
 * APIs to perform non-blocking input from stdin
 */
/* Call this just when main() does its initialization. */
/* Note: kbhit will call this if it hasn't been done yet. */
static void kbinit()
{
  struct termios tty;
  tcgetattr(fileno(stdin), &g_original_tty);
  tty = g_original_tty;

  /* Disable ICANON line buffering, and ECHO. */
  tty.c_lflag &= ~ICANON;
  tty.c_lflag &= ~ECHO;
  tcsetattr(fileno(stdin), TCSANOW, &tty);

  /* Decouple the FILE*'s internal buffer. */
  /* Rely on the OS buffer, probably 8192 bytes. */
  setbuf(stdin, NULL);
  g_initialized = 1;
}

int kbhit() 
{
    if(!g_initialized)
        kbinit();

    int bytesWaiting;
    ioctl(fileno(stdin), FIONREAD, &bytesWaiting);
    return bytesWaiting;
}


/* Call this just before main() quits, to restore TTY settings! */
void kbfini()
{
  if(g_initialized)
  {
    tcsetattr(fileno(stdin), TCSANOW, &g_original_tty);
    g_initialized = 0;
  }
}

