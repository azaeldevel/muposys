
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g


lib_LTLIBRARIES = libmuposys-apidb.la


LIB = $(OCTETOS_DB_LIBS)
FLAGS = $(OCTETOS_DB_FLAGS)


$(top_builddir)/muposysdb.cpp : Makefile.am
	$(top_srcdir)/building-apidb $(top_srcdir)  $(top_builddir)
	sed -i '1i #include "config.h" \n' $@


BUILT_SOURCES = $(top_builddir)/muposysdb.cpp 

libmuposys_apidb_la_CXXFLAGS = -I$(top_builddir) -I$(top_builddir) $(FLAGS)
libmuposys_apidb_la_SOURCES = $(top_builddir)/muposysdb.cpp 
libmuposys_apidb_la_LIBADD =  $(LIB)


pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = muposys-apidb.pc

EXTRA_DIST = muposys-apidb.pc.in

muposys_includedir = $(includedir)/muposys
muposys_include_HEADERS = $(top_builddir)/muposysdb.hpp


