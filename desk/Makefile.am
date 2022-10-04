

uidir = $(pkgdatadir)/ui
ui_DATA = desk.ui

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	-DPROGRAMNAME_LOCALEDIR=\"${PROGRAMNAME_LOCALEDIR}\" \
	$(GTK_CFLAGS)

AM_CFLAGS = -g -Wall

bin_PROGRAMS = desk 

lib_LTLIBRARIES = libmuposys-desk.la

LIBS = $(OCTETOS_DB_LIBS) $(GTK_LIBS) $(top_builddir)/apidb/libmuposys-apidb.la
FLAGS = $(OCTETOS_DB_CFLAGS) $(SQLITE3_CFLAGS) $(CGICC_CFLAGS)

resources.c : $(top_srcdir)/desk/resources.xml $(top_srcdir)/desk/desk.ui
	glib-compile-resources --c-name rc_xml_muposys --target=resources.c --generate-source $(top_srcdir)/desk/resources.xml --sourcedir $(top_srcdir)/desk/

desk_LDADD = $(LIBS)
desk_CXXFLAGS = $(FLAGS)
desk_SOURCES = desk.cc desk.hh desk-main.cc resources.c

libmuposys_desk_la_CXXFLAGS = $(FLAGS) 
libmuposys_desk_la_LDFLAGS = 
libmuposys_desk_la_SOURCES = desk.cc desk.hh 
libmuposys_desk_la_LIBADD =  $(LIBS)


EXTRA_DIST = $(ui_DATA)

uninstall-local:
	-rm -r $(uidir)
	-rm -r $(pkgdatadir)

