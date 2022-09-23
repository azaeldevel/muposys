
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g


lib_LTLIBRARIES = libmuposys-apidb.la


LIB = $(OCTETOS_DB_LIBS) $(SQLITE3_LIBS) $(CGICC_LIBS)
FLAGS = $(OCTETOS_DB_FLAGS) $(SQLITE3_CFLAGS) $(CGICC_CFLAGS)


$(top_builddir)/apidb/muposysdb.cpp : Makefile.am
	$(top_srcdir)/apidb/building-apidb $(top_srcdir)  $(top_builddir)/apidb
	sed -i '1i #include "config.h" \n' $@


BUILT_SOURCES = $(top_builddir)/apidb/muposysdb.cpp 

libmuposys_apidb_la_CXXFLAGS = -I$(top_builddir) -I$(top_builddir)/src $(FLAGS)
libmuposys_apidb_la_SOURCES = $(top_builddir)/apidb/muposysdb.cpp 
libmuposys_apidb_la_LIBADD =  $(LIB)


pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = muposys-apidb.pc

EXTRA_DIST = muposys-apidb.pc.in

muposys_includedir = $(includedir)/muposys/apidb
muposys_include_HEADERS = $(top_builddir)/apidb/muposysdb.hpp


