#ifndef CRAFTD_UTIL_H
#define CRAFTD_UTIL_H

/*
 * Copyright (c) 2010 Kevin M. Bowling, <kevin.bowling@kev009.com>, USA
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <config.h>

#include <errno.h>
#include <stdint.h>
#include <syslog.h>
#include <stdarg.h>

#include <event2/event.h>
#include <event2/buffer.h>

#include "bstrlib.h"

/**
 * Define MC data types 
 */
typedef int8_t MCbyte;
typedef int16_t MCshort;
typedef int32_t MCint;
typedef int64_t MClong;
typedef float MCfloat;
typedef double MCdouble;


/**
 * Global logging and error handling macros
 */
/* Function pointer to the current syslog() style logging routine */
void (*LOG)(int, const char *, ...);
int (*LOG_setlogmask)(int);

/* Console logging routines with syslog() style interface */
void log_console(int priority, const char *format, ...);
int log_console_setlogmask(int mask);

/* Trace logging wrapper */
#ifdef TRACE
#define LOGT(...) \
  do { LOG(__VA_ARGS__); } while (0)
#else
#define LOGT(...) \
  do { ; } while(0)
#endif

/* Fatal errors */
#define PERR(msg) \
  do { perror(msg); exit(EXIT_FAILURE); } while (0)
#define ERR(...) \
  do { LOG(LOG_CRIT, __VA_ARGS__); exit(EXIT_FAILURE); } while (0)

/* Override libevent error reporting to use our interface */
void ev_log_callback(int severity, const char *msg);

/* Public mcstring functiions */
int ismc_utf8(const char *str);
bstring getMCString(struct evbuffer *buf, int16_t len);

/* Public utility functions */
char *itoa(int value, char *result, int base);

/* Public memory management wrappers */
void *Malloc(size_t size);
void *Calloc(size_t num, size_t size);
void *Realloc(void *ptr, size_t size);

/* Daemonize implementation */
int CRAFTD_daemonize(int nochdir, int noclose);

/* Public evbuffer utility */
int CRAFTD_evbuffer_copyout_from(struct evbuffer *b, void *buf,
                             size_t len, struct evbuffer_ptr *ptr);

#endif
