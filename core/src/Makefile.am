
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g


lib_LTLIBRARIES = libmuposys-core.la


LIBS = $(OCTETOS_LIBS)
FLAGS = $(OCTETOS_FLAGS)
if OCTETOS_DB_MEDIUMWORD
FLAGS += -DOCTETOS_DB_MEDIUMWORD -DLINUX_ARCH
endif
if OCTETOS_MUPOSYS_CORE_ARCH_LINUX_ARCH
FLAGS += -DOCTETOS_MUPOSYS_CORE_ARCH_LINUX_ARCH -DLINUX_ARCH
endif

$(top_builddir)/src/muposysdb.cpp : Makefile.am
	$(top_srcdir)/src/building-apidb $(top_srcdir)/src  $(top_builddir)/src
	sed -i '1i #include "config.h" \n' $@

BUILT_SOURCES = $(top_builddir)/src/muposysdb.cpp 

libmuposys_core_la_CXXFLAGS = -I$(top_builddir)/src $(FLAGS)
libmuposys_core_la_SOURCES = $(top_builddir)/src/muposysdb.cpp Exception.cc
libmuposys_core_la_LIBADD =  $(LIBS)

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = muposys-core.pc

EXTRA_DIST = muposys-core.pc.in

muposys_includedir = $(includedir)/muposys/core
muposys_include_HEADERS = $(top_builddir)/src/muposysdb.hpp apidb.hh Exception.hh


