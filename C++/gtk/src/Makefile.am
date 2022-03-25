

uidir = $(pkgdatadir)/ui
ui_DATA = muposys.ui


AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	-DPROGRAMNAME_LOCALEDIR=\"${PROGRAMNAME_LOCALEDIR}\" \
	$(MUPOSYS_CFLAGS)

AM_CFLAGS = -g -Wall

bin_PROGRAMS = muposys mias

resources.c : $(top_srcdir)/src/resources.xml $(top_srcdir)/src/muposys.ui
	glib-compile-resources --target=resources.c --generate-source $(top_srcdir)/src/resources.xml --sourcedir $(top_srcdir)/src/

muposys_SOURCES = resources.c muposys.cc muposys-main.cc
muposys_LDFLAGS = 
muposys_LDADD = $(MUPOSYS_LIBS)
if NATIVE_WIN32
muposys_LDFLAGS += -mwindows
endif

mias_SOURCES = resources.c muposys.cc mias.cc
mias_LDFLAGS = 
mias_LDADD = $(MUPOSYS_LIBS)
if NATIVE_WIN32
mias_LDFLAGS += -mwindows
endif


EXTRA_DIST = $(ui_DATA)

# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(pkgdatadir)

