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

AC_PREREQ(2.5)
AC_INIT(libsysconfcpus, [0.5], [kev@pulo.com.au])
AC_CONFIG_SRCDIR([src/libsysconfcpus.c])
AM_INIT_AUTOMAKE
AM_CONFIG_HEADER([config.h])

# Check for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_SED

# Choose shared library using libtool.
AC_ENABLE_SHARED
AC_DISABLE_STATIC
AM_PROG_LIBTOOL

# Check for standard headers, etc.
AC_HEADER_STDC
AC_C_CONST

AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
