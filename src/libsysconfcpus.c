/* libsysconfcpus: adjust number of CPUs reported by sysconf()
 * Copyright (C) 2008-2009 Kevin Pulo
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * 
 * Contact:
 * Kevin Pulo
 * kev@pulo.com.au
 */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

/* Using _GNU_SOURCE as the manpage suggests can be problematic.
 * We only want the GNU extensions for dlfcn.h, not others like stdio.h.
 * But dlfcn.h checks __USE_GNU, not _GNU_SOURCE.  __USE_GNU is set by
 * features.h when _GNU_SOURCE is set, but features.h has already been loaded
 * by stdio.h, so it doesn't get loaded again.  Ugh.  Setting _GNU_SOURCE
 * earlier drags in other junk (eg. dprintf).  Simplest is just to use
 * __USE_GNU directly.
 */
#define __USE_GNU
#include <dlfcn.h>
#undef __USE_GNU

#include <unistd.h>



static int debug = 0;

static const char libsysconfcpus_debug_envvar[] = "LIBSYSCONFCPUS_DEBUG";

static int do_debug() {
	return (debug || getenv(libsysconfcpus_debug_envvar));
}

static void debugprintf(char *fmt, ...) {
	va_list ap;
	if (do_debug()) {
		va_start(ap, fmt);
		vfprintf(stderr, fmt, ap);
		va_end(ap);
		fflush(stderr);
	}
}





static void _libsysconfcpus_init(void) __attribute__((constructor));
static void _libsysconfcpus_fini(void) __attribute__((destructor));

static void _libsysconfcpus_init(void) {
	debugprintf("libsysconfcpus: starting up\n");
}

static void _libsysconfcpus_fini(void) {
	debugprintf("libsysconfcpus: shutting down\n");
}



static const char libsysconfcpus_envvar[] = "LIBSYSCONFCPUS";
static const char libsysconfcpus_conf_envvar[] = "LIBSYSCONFCPUS_CONF";
static const char libsysconfcpus_onln_envvar[] = "LIBSYSCONFCPUS_ONLN";

long sysconf(int name) {
	static void *libc_handle = NULL;
	static long (*underlying)(int name);
	long retval;
	long v;
	const char *env;
	const char *envvar;
	const char *envvar_use;
	const char *err;
	char *endptr;

	debugprintf("libsysconfcpus: sysconf(%d): entered\n", name);

	if (!libc_handle) {
#if defined(RTLD_NEXT)
		libc_handle = RTLD_NEXT;
#else
		libc_handle = dlopen("libc.so.6", RTLD_LAZY);
#endif
		debugprintf("libsysconfcpus: sysconf: libc_handle = 0x%x\n", libc_handle);
		if (!libc_handle) {
			fprintf(stderr, "libsysconfcpus: Error: Unable to find libc.so: %s\n", dlerror());
			exit(1);
		}

		dlerror();
		underlying = dlsym(libc_handle, "sysconf");
		debugprintf("libsysconfcpus: sysconf: underlying = 0x%x\n", underlying);
		err = dlerror();
		if (err) {
			debugprintf("libsysconfcpus: sysconf: err = \"%s\"\n", err);
		}
		if (!underlying || err) {
			fprintf(stderr, "libsysconfcpus: Error: Unable to find the underlying sysconf(): %s\n", dlerror());
			exit(1);
		}
	}

	debugprintf("libsysconfcpus: about to call underlying sysconf()\n");
	retval = (*underlying)(name);
	debugprintf("libsysconfcpus: underlying sysconf(%d) = %ld\n", name, retval);

	envvar = NULL;
	switch (name) {
		case _SC_NPROCESSORS_CONF:
			debugprintf("libsysconfcpus: sysconf(_SC_NPROCESSORS_CONF)\n");
			envvar = libsysconfcpus_conf_envvar;
			break;
		case _SC_NPROCESSORS_ONLN:
			debugprintf("libsysconfcpus: sysconf(_SC_NPROCESSORS_ONLN)\n");
			envvar = libsysconfcpus_onln_envvar;
			break;
	}
	if (envvar) {
		envvar_use = envvar;
		env = getenv(envvar_use);
		if (!env) {
			envvar_use = libsysconfcpus_envvar;
			env = getenv(envvar_use);
		}
		if (env) {
			debugprintf("libsysconfcpus: $%s = \"%s\"\n", envvar_use, env);
			v = strtol(env, &endptr, 10);
			if (endptr == env) {
				debugprintf("libsysconfcpus: Warning: $%s does not contain a number, cannot override\n", envvar_use);
			} else {
				retval = v;
			}
		} else {
			debugprintf("libsysconfcpus: Warning: neither $%s nor $%s are set, cannot override\n", envvar, libsysconfcpus_envvar);
		}
	}

	debugprintf("libsysconfcpus: sysconf(%d) = %ld\n", name, retval);

	return retval;
}
