
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g



bin_PROGRAMS = add.cgi user-permiss.cgi

if WITH_MARIADB
DBLIBS = $(OCTETOS_DB_MARIA_LIBS)
DBFLAGS = $(OCTETOS_DB_MARIA_CFLAGS) -DMARIADB
endif
if WITH_MYSQL
DBLIBS = $(OCTETOS_DB_MYSQL_LIBS)
DBFLAGS = $(OCTETOS_DB_MYSQL_CFLAGS) -DMYSQL
endif
if WITH_POSTGRESQL
DBLIBS = $(OCTETOS_DB_POSTGRESQL_LIBS)
DBFLAGS = $(OCTETOS_DB_POSTGRESQL_CFLAGS) -DPOSTGRESQL
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

LIB = $(DBLIBS) $(SQLITE3_LIBS) $(CGICC_LIBS)
FLAGS = $(DBFLAGS) $(SQLITE3_CFLAGS) $(CGICC_CFLAGS) $(DEFINESBD)

add_cgi_CXXFLAGS = $(FLAGS) -I$(top_builddir)
add_cgi_LDADD =  $(top_builddir)/cgi/libmuposys-server.la $(top_builddir)/apidb/libmuposys-db.la $(LIB) 
add_cgi_SOURCES = add-main.cc 

user_permiss_cgi_CXXFLAGS = $(FLAGS) -I$(top_builddir)
user_permiss_cgi_LDADD =  $(top_builddir)/cgi/libmuposys-server.la $(top_builddir)/apidb/libmuposys-db.la 
user_permiss_cgi_SOURCES = user-permiss-main.cc 




