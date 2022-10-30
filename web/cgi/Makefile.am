
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g


lib_LTLIBRARIES = libmuposys-cgi.la

LIBS = $(OCTETOS_DB_LIBS) $(APIDB_LIBS) $(MUPOSYS_LIBS)
FLAGS = $(OCTETOS_DB_CFLAGS)  $(APIDB_CFLAGS) $(MUPOSYS_CFLAGS)
if MUPOSYS_WEB_ENABLE_TDD
FLAGS += -DMUPOSYS_WEB_ENABLE_TDD
endif
if OCTETOS_DB_MEDIUMWORD
FLAGS += -DOCTETOS_DB_MEDIUMWORD
endif
if DATABASE_ENGINE_MARIA
FLAGS += -DDATABASE_ENGINE_MARIA
endif

if MUPOSYS_WEB_ENABLE_RUNNABLE
bin_PROGRAMS = login.cgi logout.cgi application.cgi
else
bin_PROGRAMS = login.cgi logout.cgi 
endif



libmuposys_cgi_la_CXXFLAGS = -I$(top_builddir) -I$(top_builddir)/src $(FLAGS) 
libmuposys_cgi_la_LDFLAGS = 
libmuposys_cgi_la_SOURCES = html.cc login.cc application.cc logout.cc Exception.cc
libmuposys_cgi_la_LIBADD =  $(LIB)


login_cgi_CXXFLAGS = $(FLAGS) -I$(top_builddir) 
login_cgi_LDADD =  libmuposys-cgi.la $(LIB) 
login_cgi_SOURCES = login-main.cc 

if MUPOSYS_WEB_ENABLE_RUNNABLE
application_cgi_SOURCES = application-main.cc
application_cgi_LDADD = libmuposys-cgi.la $(LIB)
application_cgi_CXXFLAGS = $(FLAGS) $(DBFLAGS) -I$(top_builddir)
endif

logout_cgi_SOURCES = logout-main.cc  
logout_cgi_LDADD = libmuposys-cgi.la $(LIB)
logout_cgi_CXXFLAGS = $(FLAGS) $(DBFLAGS) -I$(top_builddir)

user_register_cgi_LDADD = $(LIB) libmuposys-cgi.la
user_register_cgi_LDFLAGS = 
user_register_cgi_CXXFLAGS = $(FLAGS) $(DBFLAGS)
user_register_cgi_SOURCES = user-register.cc 


pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = muposys-cgi.pc

EXTRA_DIST = muposys-cgi.pc.in

muposys_includedir = $(includedir)/muposys
muposys_include_HEADERS = Exception.hh http.hh http-db.hh html.hh login.hh application.hh logout.hh


