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
#include <unistd.h>

int main(int argc, char *argv[]) {
	long num_configured;
	long num_online;

	num_configured = sysconf(_SC_NPROCESSORS_CONF);
	printf("sysconf(_SC_NPROCESSORS_CONF) = %ld\n", num_configured);

	num_online = sysconf(_SC_NPROCESSORS_ONLN);
	printf("sysconf(_SC_NPROCESSORS_ONLN) = %ld\n", num_online);

	return 0;
}

