

noinst_LTLIBRARIES = libmuposys-http.la libmuposys-server.la



bin_PROGRAMS = login application logout useradd

DBTYPE=
DBLIBS=
DBCFLAGS=
if WITH_MARIADB
DBTYPE=-DMARIADB
DBLIBS=$(OCTETOS_DB_MARIA_LIBS)
DBCFLAGS=$(OCTETOS_DB_MARIA__CFLAGS)
endif
if WITH_MYSQL
DBTYPE=-DMYSQL
DBLIBS=$(OCTETOS_DB_MYSQL_LIBS)
DBCFLAGS=$(OCTETOS_DB_MYSQL_CFLAGS)
endif
if WITH_POSTGRESQL
DBTYPE=-DPOSTGRESQL
DBLIBS=$(OCTETOS_DB_POSTGRESQL_LIBS)
DBCFLAGS=$(OCTETOS_DB_POSTGRESQL_CFLAGS)
endif

$(top_srcdir)/../apidb/libmuposysdb.a : $(top_srcdir)/../apidb/muposys.apidb
	cd $(top_srcdir)/../apidb/ && apidb-build -p $<
	cd $(top_srcdir)/../apidb && cmake . && make

$(top_builddir)/src/include/muposysdb.hpp : $(top_srcdir)/../apidb/libmuposysdb.a
	 cp $@ $(top_srcddir)/src/include/

$(top_builddir)/src/lib/libmuposysdb.a : $(top_srcdir)/../apidb/libmuposysdb.a
	cp $@ $(top_srcdir)/src/lib/

login.cc : $(top_builddir)/src/include/muposysdb.hpp $(top_builddir)/src/lib/libmuposysdb.a

libmuposys_http_la_LDFLAGS = -static
libmuposys_http_la_SOURCES = http.cc http-db.cc
libmuposys_http_la_LDFLAGS = -L$(top_srcdir)/lib
libmuposys_http_la_CXXFLAGS = -I$(top_srcdir)/include $(DBTYPE)
libmuposys_http_la_LIBADD = -lmuposysdb

libmuposys_server_la_LDFLAGS = -static
libmuposys_server_la_SOURCES = server.cc server-elements.cc
libmuposys_server_la_LDFLAGS = -L$(top_srcdir)/lib
libmuposys_server_la_CXXFLAGS = -I$(top_srcdir)/include $(SQLITE3_CFLAGS)  $(CGICC_CFLAGS) $(OPENSSL_CFLAGS) $(DBTYPE) $(DBCFLAGS)
libmuposys_server_la_LIBADD =   libmuposys-http.la -lmuposysdb  $(SQLITE3_LIBS)  $(CGICC_LIBS) $(OPENSSL_LIBS)  $(DBLIBS)



login_SOURCES = login.cc 
login_LDADD =   libmuposys-server.la  

application_SOURCES = application.cc application-server.cc 
application_LDADD =   libmuposys-server.la 

logout_SOURCES = logout.cc  
logout_LDADD =   $(CGICC_LIBS) libmuposys-server.la

useradd_LDADD =   $(CGICC_LIBS) $(DBLIBS) -lmuposysdb libmuposys-server.la 
useradd_LDFLAGS = -L$(top_srcdir)/lib
useradd_CXXFLAGS = -I$(top_srcdir)/include $(DBTYPE) $(DBCFLAGS)
useradd_SOURCES = useradd.cc
