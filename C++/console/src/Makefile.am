
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g


DBLIBS= $(MARIADB_LIBS) $(OCTETOS_DB_ABSTRACT_LIBS)
DEFINES = -DLINUX_DEBIAN $(MARIADB_CFLAGS) $(OCTETOS_DB_ABSTRACT_CFLAGS)
if WITH_MARIADB
DBLIBS += $(OCTETOS_DB_MARIA_LIBS)
DEFINES += $(OCTETOS_DB_MARIA_CFLAGS) -DMARIADB
endif


$(top_srcdir)/src/muposysdb.cpp : $(top_srcdir)/src/muposys.apidb
	$(top_srcdir)/src/building-apidb $(top_srcdir) 


bin_PROGRAMS = muposys




muposys_SOURCES = muposysdb.cpp main.cc commands.cc operations-db.cc
muposys_LDFLAGS = 
muposys_LDADD = $(DBLIBS)
muposys_CXXFLAGS = $(DEFINES)

