

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

resources.c : $(top_srcdir)/desk/resources.xml $(top_srcdir)/desk/desk.ui
	glib-compile-resources --target=resources.c --generate-source $(top_srcdir)/desk/resources.xml --sourcedir $(top_srcdir)/desk/

desk_LDADD = $(GTK_LIBS)
desk_CXXFLAGS = $(GTK_CFLAGS)
desk_SOURCES = resources.c desk.cc desk.hh desk-main.cc

EXTRA_DIST = $(ui_DATA)

uninstall-local:
	-rm -r $(uidir)
	-rm -r $(pkgdatadir)

