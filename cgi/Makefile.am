
SUBDIRS = . user-mang 

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g


lib_LTLIBRARIES = libmuposys-http.la libmuposys-server.la libmuposys-html.la

if ENABLE_HOLE
MODULES=login.cgi logout.cgi user-register.cgi application.cgi
else 
MODULES=login.cgi logout.cgi user-register.cgi 
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
libmuposys_server_la_SOURCES = login.cc application.cc logout.cc
libmuposys_server_la_LIBADD =  libmuposys-http.la  libmuposys-html.la  $(SQLITE3_LIBS)  $(CGICC_LIBS) $(OPENSSL_LIBS) $(DBLIBS) 

libmuposys_html_la_LDFLAGS = -static
libmuposys_html_la_SOURCES = html.cc
libmuposys_html_la_CXXFLAGS = $(DEFINESBD)
libmuposys_html_la_LIBADD = $(DBLIBS)

login_cgi_CXXFLAGS = $(SQLITE3_CFLAGS) $(CGICC_CFLAGS) $(DEFINES) $(DEFINESBD)  -I$(top_builddir)
login_cgi_LDADD =  libmuposys-http.la libmuposys-html.la libmuposys-server.la $(top_builddir)/apidb/libmuposys-db.la $(SQLITE3_LIBS)  $(CGICC_LIBS) $(DBLIBS) 
login_cgi_SOURCES = login-main.cc 

if ENABLE_HOLE
application_cgi_SOURCES = application-main.cc
application_cgi_LDADD = libmuposys-html.la libmuposys-http.la libmuposys-server.la $(DBLIBS)  $(SQLITE3_LIBS)  $(CGICC_LIBS) 
application_cgi_CXXFLAGS = $(SQLITE3_CFLAGS) $(CGICC_CFLAGS) $(DEFINES) $(DEFINESBD)  -I$(top_builddir)
endif

logout_cgi_SOURCES = logout-main.cc  
logout_cgi_LDADD =   libmuposys-http.la libmuposys-html.la libmuposys-server.la $(top_builddir)/apidb/libmuposys-db.la $(SQLITE3_LIBS)  $(CGICC_LIBS) $(DBLIBS)
logout_cgi_CXXFLAGS = $(SQLITE3_CFLAGS) $(CGICC_CFLAGS) $(DEFINES) $(DEFINESBD)  -I$(top_builddir)

user_register_cgi_LDADD = $(SQLITE3_LIBS) $(CGICC_LIBS) $(DBLIBS) libmuposys-http.la $(top_builddir)/apidb/libmuposys-db.la 
user_register_cgi_LDFLAGS = 
user_register_cgi_CXXFLAGS = $(SQLITE3_CFLAGS) $(DEFINES) $(DEFINESBD)
user_register_cgi_SOURCES = user-register.cc 



