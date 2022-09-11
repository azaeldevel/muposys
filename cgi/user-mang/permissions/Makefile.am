
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g



bin_PROGRAMS = add.cgi

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

add_cgi_CXXFLAGS = $(SQLITE3_CFLAGS) $(CGICC_CFLAGS) $(DEFINES) $(DEFINESBD)  -I$(top_builddir)
add_cgi_LDADD =  $(top_builddir)/cgi/libmuposys-http.la $(top_builddir)/cgi/libmuposys-html.la $(top_builddir)/cgi/libmuposys-server.la $(top_builddir)/apidb/libmuposys-db.la $(SQLITE3_LIBS)  $(CGICC_LIBS) $(DBLIBS) 
add_cgi_SOURCES = add-main.cc 