
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g


noinst_LTLIBRARIES = libmuposys-db.la



if WITH_MARIADB
DBLIBS = $(OCTETOS_DB_MARIA_LIBS)
DEFINES = $(OCTETOS_DB_MARIA_CFLAGS) -DMARIADB
endif
if WITH_MYSQL
DBLIBS = $(OCTETOS_DB_MYSQL_LIBS)
DEFINES = $(OCTETOS_DB_MYSQL_CFLAGS) -DMYSQL
endif
if WITH_POSTGRESQL
DBLIBS = $(OCTETOS_DB_POSTGRESQL_LIBS)
DEFINES = $(OCTETOS_DB_POSTGRESQL_CFLAGS) -DPOSTGRESQL
endif


if WITH_MEDIUMWORD
DEFINESBD = -DOCTETOS_DB_MEDIUMWORD
endif
if WITH_HIGHWORD
DEFINESBD = -DOCTETOS_DB_HIGHWORD
endif
if WITH_LOWWORD
DEFINESBD = -DOCTETOS_DB_LOWWORD
endif


$(top_builddir)/apidb/muposysdb.cpp : Makefile.am
	$(top_srcdir)/apidb/building-apidb $(top_srcdir)  $(top_builddir)/apidb
	sed -i '1i #include "config.h" \n' $@


BUILT_SOURCES = $(top_builddir)/apidb/muposysdb.cpp 

libmuposys_db_la_CXXFLAGS = -I$(top_builddir) -I$(top_builddir)/src $(OPENSSL_CFLAGS) $(DEFINES) $(DEFINESBD)
libmuposys_db_la_LDFLAGS = -static
libmuposys_db_la_SOURCES = $(top_builddir)/apidb/muposysdb.cpp 
libmuposys_db_la_LIBADD =  $(OPENSSL_LIBS) $(DBLIBS) 




