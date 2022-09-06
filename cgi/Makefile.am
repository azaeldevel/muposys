
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g


noinst_LTLIBRARIES = libmuposys-http.la libmuposys-server.la libmuposys-html.la

if ENABLE_HOLE
MODULES=login.cgi logout.cgi userregister-methode.cgi application.cgi
else 
MODULES=login.cgi logout.cgi userregister-methode.cgi
endif

bin_PROGRAMS = $(MODULES)


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


$(top_builddir)/cgi/http : Makefile.am
	cp $(top_srcdir)/cgi/http $@

$(top_builddir)/tests/http : Makefile.am
	cp $(top_srcdir)/cgi/http $(top_builddir)/tests/

BUILT_SOURCES = $(top_builddir)/cgi/http $(top_builddir)/tests/http


libmuposys_http_la_LDFLAGS = -static
libmuposys_http_la_SOURCES = http.cc http-db.cc Exception.cc
libmuposys_http_la_CXXFLAGS = $(DEFINESBD)
libmuposys_http_la_LIBADD = $(DBLIBS)

libmuposys_server_la_CXXFLAGS = -I$(top_builddir) -I$(top_builddir)/src $(SQLITE3_CFLAGS) $(CGICC_CFLAGS) $(OPENSSL_CFLAGS) $(DEFINES) $(DEFINESBD)
libmuposys_server_la_LDFLAGS = -static
libmuposys_server_la_SOURCES = server.cc server-elements.cc 
libmuposys_server_la_LIBADD =  libmuposys-http.la  $(SQLITE3_LIBS)  $(CGICC_LIBS) $(OPENSSL_LIBS) $(DBLIBS) 


libmuposys_html_la_LDFLAGS = -static
libmuposys_html_la_SOURCES = html.cc
libmuposys_html_la_CXXFLAGS = $(DEFINESBD)
libmuposys_html_la_LIBADD = $(DBLIBS)

login_cgi_CXXFLAGS = $(SQLITE3_CFLAGS) $(CGICC_CFLAGS) $(DEFINES) $(DEFINESBD)  -I$(top_builddir)
login_cgi_LDADD =  libmuposys-http.la libmuposys-html.la $(top_builddir)/apidb/libmuposys-db.la $(SQLITE3_LIBS)  $(CGICC_LIBS) $(DBLIBS) 
login_cgi_SOURCES = login.cc 

if ENABLE_HOLE
application_cgi_SOURCES = application.cc application-server.cc 
application_cgi_LDADD =   libmuposys-server.la $(DBLIBS)
endif

logout_cgi_SOURCES = logout.cc  
logout_cgi_LDADD =   $(CGICC_LIBS) libmuposys-server.la $(DBLIBS)

userregister_methode_cgi_LDADD = $(SQLITE3_LIBS) $(CGICC_LIBS) $(DBLIBS) libmuposys-http.la $(top_builddir)/apidb/libmuposys-db.la 
userregister_methode_cgi_LDFLAGS = 
userregister_methode_cgi_CXXFLAGS = $(SQLITE3_CFLAGS) $(DEFINES) $(DEFINESBD)
userregister_methode_cgi_SOURCES = userregister-methode.cc 



