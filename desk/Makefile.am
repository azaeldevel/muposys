
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)/muposys/desk"\" \
	-DPROGRAMNAME_LOCALEDIR=\"${PROGRAMNAME_LOCALEDIR}\" \
	$(GTK_CFLAGS)

AM_CFLAGS = -g -Wall

bin_PROGRAMS = muposys-desk 

lib_LTLIBRARIES = libmuposys-desk.la


LIBS = $(OCTETOS_DB_LIBS) $(GTK_LIBS) $(APIDB_LIBS)
FLAGS = $(OCTETOS_DB_CFLAGS)  $(GTK_CFLAGS) $(APIDB_CFLAGS)


resources.c : $(top_srcdir)/resources.xml $(top_srcdir)/desk.ui
	glib-compile-resources -C g++ --generate-header --c-name rc_xml_muposys --target=muposys-xml.hh   --sourcedir=$(top_srcdir) $(top_srcdir)/resources.xml
	glib-compile-resources --generate-source --c-name rc_xml_muposys --target=resources.c   --sourcedir=$(top_srcdir) $(top_srcdir)/resources.xml

muposys_desk_LDADD = $(LIBS)
muposys_desk_CXXFLAGS = $(FLAGS)
muposys_desk_SOURCES = desk.cc desk.hh desk-main.cc

libmuposys_desk_la_CXXFLAGS = $(FLAGS) 
libmuposys_desk_la_LDFLAGS = 
libmuposys_desk_la_SOURCES = desk.cc desk.hh
libmuposys_desk_la_LIBADD =  $(LIBS)

muposysdir = $(datadir)/muposys/desk
muposys_DATA = muposys-desk.ui
muposys_includedir = $(includedir)/muposys/desk
muposys_include_HEADERS = desk.hh
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = muposys-desk.pc

EXTRA_DIST = $(muposys_DATA)




uninstall-local:
	-rm -r $(muposysdir)

