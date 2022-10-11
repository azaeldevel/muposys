
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g


lib_LTLIBRARIES = libmuposys-apidb.la


LIB = $(OCTETOS_LIBS)
FLAGS = $(OCTETOS_FLAGS)
if OCTETOS_DB_MEDIUMWORD
FLAGS += -DOCTETOS_DB_MEDIUMWORD
endif

$(top_builddir)/src/muposysdb.cpp : Makefile.am
	$(top_srcdir)/src/building-apidb $(top_srcdir)/src  $(top_builddir)/src
	sed -i '1i #include "config.h" \n' $@


BUILT_SOURCES = $(top_builddir)/src/muposysdb.cpp 

libmuposys_apidb_la_CXXFLAGS = -I$(top_builddir)/src $(FLAGS)
libmuposys_apidb_la_SOURCES = $(top_builddir)/src/muposysdb.cpp 
libmuposys_apidb_la_LIBADD =  $(LIB)


pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = muposys-apidb.pc

EXTRA_DIST = muposys-apidb.pc.in

muposys_includedir = $(includedir)/muposys
muposys_include_HEADERS = $(top_builddir)/src/muposysdb.hpp


