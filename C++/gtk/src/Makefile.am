
uidir = $(pkgdatadir)/ui
ui_DATA = sysapp.ui


AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(GTKMM_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = muposys

muposys_CXXFLAGS = -I$(top_srcdir)/libraries
muposys_CPPFLAGS = -I$(top_srcdir)/libraries 
muposys_LDFLAGS = -L$(top_srcdir)/libraries
muposys_LDADD = $(GTKMM_LIBS) $(OCTETOS_DB_MARIA_LIBS) -lmuposysdb
muposys_SOURCES = main.cc Login.cc




EXTRA_DIST = $(ui_DATA)

# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(pkgdatadir)

