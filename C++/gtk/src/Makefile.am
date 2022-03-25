

uidir = $(pkgdatadir)/ui
ui_DATA = muposys.ui


AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(MUPOSYS_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = muposys

muposys_SOURCES = main.cc
muposys_LDFLAGS = 
muposys_LDADD = $(MUPOSYS_LIBS)
if NATIVE_WIN32
muposys_LDFLAGS += -mwindows
endif



EXTRA_DIST = $(ui_DATA)

# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(pkgdatadir)

