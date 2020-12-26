
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

DBLIBS = 
DEFINES = -DLINUX_DEBIAN
if WITH_MARIADB
DBLIBS += $(OCTETOS_DB_MARIA_LIBS)
DEFINES += $(OCTETOS_DB_MARIA_CFLAGS) -DMARIADB
endif
if WITH_MYSQL
DBLIBS += $(OCTETOS_DB_MYSQL_LIBS)
DEFINES += $(OCTETOS_DB_MYSQL_CFLAGS) -DMYSQL
endif
if WITH_POSTGRESQL
DBLIBS += $(OCTETOS_DB_POSTGRESQL_LIBS)
DEFINES += $(OCTETOS_DB_POSTGRESQL_CFLAGS) -DPOSTGRESQL
endif


bin_PROGRAMS = muposys

muposys_SOURCES = main.cc Login.cc muposysdb.cpp Main.cc

muposys_LDFLAGS = 
muposys_CXXFLAGS = $(GTKMM_CFLAGS) $(OCTETOS_DB_MARIA_CFLAGS) $(DEFINES)
muposys_LDADD = $(GTKMM_LIBS) $(DBLIBS)


EXTRA_DIST = $(ui_DATA)

# Remove ui directory on uninstall
uninstall-local:
	-rm -r $(uidir)
	-rm -r $(pkgdatadir)

