
SUBDIRS = . user-mang 

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g


lib_LTLIBRARIES = libmuposys-cgi.la

if ENABLE_DEVEL
MODULES=login.cgi logout.cgi user-register.cgi application.cgi
else 
MODULES=login.cgi logout.cgi user-register.cgi 
endif

bin_PROGRAMS = $(MODULES)

LIB = $(OCTETOS_DB_LIBS) $(SQLITE3_LIBS) $(CGICC_LIBS)
FLAGS = $(OCTETOS_DB_FLAGS) $(SQLITE3_CFLAGS) $(CGICC_CFLAGS)

$(top_builddir)/cgi/http : Makefile.am
	cp $(top_srcdir)/cgi/http $@

$(top_builddir)/tests/http : Makefile.am
	cp $(top_srcdir)/cgi/http $(top_builddir)/tests/

BUILT_SOURCES = $(top_builddir)/cgi/http $(top_builddir)/tests/http


libmuposys_cgi_la_CXXFLAGS = -I$(top_builddir) -I$(top_builddir)/src $(FLAGS) 
libmuposys_cgi_la_LDFLAGS = 
libmuposys_cgi_la_SOURCES = html.cc http.cc http-db.cc Exception.cc login.cc application.cc logout.cc user-mang/permissions/add.cc user-mang/permissions/user-permiss.cc
libmuposys_cgi_la_LIBADD =  $(LIB)


login_cgi_CXXFLAGS = $(FLAGS) -I$(top_builddir) 
login_cgi_LDADD =  libmuposys-cgi.la $(top_builddir)/apidb/libmuposys-apidb.la $(LIB) 
login_cgi_SOURCES = login-main.cc 

if ENABLE_DEVEL
application_cgi_SOURCES = application-main.cc
application_cgi_LDADD = libmuposys-cgi.la $(top_builddir)/apidb/libmuposys-apidb.la $(LIB)
application_cgi_CXXFLAGS = $(FLAGS) $(DBFLAGS) -I$(top_builddir)
endif

logout_cgi_SOURCES = logout-main.cc  
logout_cgi_LDADD = libmuposys-cgi.la $(top_builddir)/apidb/libmuposys-apidb.la $(LIB)
logout_cgi_CXXFLAGS = $(FLAGS) $(DBFLAGS) -I$(top_builddir)

user_register_cgi_LDADD = $(LIB) libmuposys-cgi.la $(top_builddir)/apidb/libmuposys-apidb.la 
user_register_cgi_LDFLAGS = 
user_register_cgi_CXXFLAGS = $(FLAGS) $(DBFLAGS)
user_register_cgi_SOURCES = user-register.cc 


pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = muposys-cgi.pc

EXTRA_DIST = muposys-cgi.pc.in

muposys_includedir = $(includedir)/muposys
muposys_include_HEADERS = Exception.hh http.hh http-db.hh html.hh login.hh application.hh logout.hh


