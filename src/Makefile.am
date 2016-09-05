# libsysconfcpus: adjust number of CPUs reported by sysconf()
# Copyright (C) 2008-2009 Kevin Pulo
# 
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
# 
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
# 
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
# 
# Contact:
# Kevin Pulo
# kev@pulo.com.au

AUTOMAKE_OPTIONS = 1.4 foreign

CFLAGS += -Wall
#CFLAGS += -Werror


lib_LTLIBRARIES = libsysconfcpus.la
libsysconfcpus_la_SOURCES = libsysconfcpus.c
libsysconfcpus_la_CFLAGS = -O1
libsysconfcpus_la_LIBADD = -ldl

bin_PROGRAMS = test-sysconfcpus
test_sysconfcpus_SOURCES = test-sysconfcpus.c
test_sysconfcpus_CFLAGS = -O1



#dist_man_MANS = libsysconfcpus.1 sysconfcpus.1 sysconfcpus-debug.1

nodist_bin_SCRIPTS  = sysconfcpus
nodist_bin_SCRIPTS += sysconfcpus-debug

dist_noinst_DATA  = sysconfcpus.in
dist_noinst_DATA += sysconfcpus-debug.in

edit = $(SED) \
	-e 's,@bindir\@,$(bindir),g' \
	-e 's,@mandir\@,$(mandir),g' \
	-e 's,@libdir\@,$(libdir),g' \
	-e 's,@datadir\@,$(datadir),g' \
	-e 's,@localstatedir\@,$(localstatedir),g' \
	-e 's,@version\@,$(PACKAGE_VERSION),g'

DISTCLEANFILES  = sysconfcpus
DISTCLEANFILES += sysconfcpus-debug

sysconfcpus:: Makefile $(srcdir)/sysconfcpus.in
	rm -f sysconfcpus sysconfcpus.tmp && \
	$(edit) $(srcdir)/sysconfcpus.in >sysconfcpus.tmp && \
	mv sysconfcpus.tmp sysconfcpus

sysconfcpus-debug:: Makefile $(srcdir)/sysconfcpus-debug.in
	rm -f sysconfcpus-debug sysconfcpus-debug.tmp && \
	$(edit) $(srcdir)/sysconfcpus-debug.in >sysconfcpus-debug.tmp && \
	mv sysconfcpus-debug.tmp sysconfcpus-debug


