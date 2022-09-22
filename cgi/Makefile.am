
SUBDIRS = . user-mang 

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g


lib_LTLIBRARIES = libmuposys-server.la

if ENABLE_DEVEL
MODULES=login.cgi logout.cgi user-register.cgi application.cgi
else 
MODULES=login.cgi logout.cgi user-register.cgi 
endif

bin_PROGRAMS = $(MODULES)


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

$(top_builddir)/cgi/http : Makefile.am
	cp $(top_srcdir)/cgi/http $@

$(top_builddir)/tests/http : Makefile.am
	cp $(top_srcdir)/cgi/http $(top_builddir)/tests/

BUILT_SOURCES = $(top_builddir)/cgi/http $(top_builddir)/tests/http


libmuposys_server_la_CXXFLAGS = -I$(top_builddir) -I$(top_builddir)/src $(FLAGS) 
libmuposys_server_la_LDFLAGS = 
libmuposys_server_la_SOURCES = html.cc http.cc http-db.cc Exception.cc login.cc application.cc logout.cc user-mang/permissions/add.cc user-mang/permissions/user-permiss.cc
libmuposys_server_la_LIBADD =  $(LIB)


login_cgi_CXXFLAGS = $(FLAGS) -I$(top_builddir) 
login_cgi_LDADD =  libmuposys-server.la $(top_builddir)/apidb/libmuposys-apidb.la $(LIB) 
login_cgi_SOURCES = login-main.cc 

if ENABLE_DEVEL
application_cgi_SOURCES = application-main.cc
application_cgi_LDADD = libmuposys-server.la $(top_builddir)/apidb/libmuposys-apidb.la $(LIB)
application_cgi_CXXFLAGS = $(FLAGS) $(DBFLAGS) -I$(top_builddir)
endif

logout_cgi_SOURCES = logout-main.cc  
logout_cgi_LDADD = libmuposys-server.la $(top_builddir)/apidb/libmuposys-apidb.la $(LIB)
logout_cgi_CXXFLAGS = $(FLAGS) $(DBFLAGS) -I$(top_builddir)

user_register_cgi_LDADD = $(LIB) libmuposys-server.la $(top_builddir)/apidb/libmuposys-apidb.la 
user_register_cgi_LDFLAGS = 
user_register_cgi_CXXFLAGS = $(FLAGS) $(DBFLAGS)
user_register_cgi_SOURCES = user-register.cc 


pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = muposys-cgi.pc

EXTRA_DIST = muposys-cgi.pc.in

