
noinst_LTLIBRARIES = libmuposys-http.la libmuposys-server.la

bin_PROGRAMS = login application logout userregister-methode


DBLIBS=
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

$(top_srcdir)/src/muposysdb.cpp : $(top_srcdir)/src/muposys.apidb
	$(top_srcdir)/src/building-apidb $(top_srcdir) 


BUILT_SOURCES = $(top_srcdir)/src/muposysdb.cpp

libmuposys_http_la_LDFLAGS = -static
libmuposys_http_la_SOURCES = http.cc http-db.cc
libmuposys_http_la_LDFLAGS = 
libmuposys_http_la_CXXFLAGS = $(DEFINES)
libmuposys_http_la_LIBADD = $(DBLIBS)

libmuposys_server_la_LDFLAGS = -static
libmuposys_server_la_SOURCES = server.cc server-elements.cc muposysdb.cpp
libmuposys_server_la_LDFLAGS = 
libmuposys_server_la_CXXFLAGS = $(SQLITE3_CFLAGS) $(CGICC_CFLAGS) $(OPENSSL_CFLAGS) $(DEFINES)
libmuposys_server_la_LIBADD =  libmuposys-http.la  $(SQLITE3_LIBS)  $(CGICC_LIBS) $(OPENSSL_LIBS) $(DBLIBS) 

login_SOURCES = login.cc muposysdb.cpp
login_LDADD =  libmuposys-http.la libmuposys-server.la $(DBLIBS) 
login_LDFLAGS = 
login_CXXFLAGS = $(DEFINES)

application_SOURCES = application.cc application-server.cc 
application_LDADD =   libmuposys-server.la $(DBLIBS)

logout_SOURCES = logout.cc  
logout_LDADD =   $(CGICC_LIBS) libmuposys-server.la $(DBLIBS)

userregister_methode_LDADD = $(CGICC_LIBS) $(DBLIBS) libmuposys-server.la 
userregister_methode_LDFLAGS = 
userregister_methode_CXXFLAGS = $(DEFINES)
userregister_methode_SOURCES = userregister-methode.cc 



