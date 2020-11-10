

noinst_LTLIBRARIES = libsysapp-http.la libsysapp-server.la



bin_PROGRAMS = login application


libsysapp_http_la_LDFLAGS = -static
libsysapp_http_la_SOURCES = http.cc http-db.cc
libsysapp_http_la_LDFLAGS = -L$(top_srcdir)/lib
libsysapp_http_la_CXXFLAGS = -I$(top_srcdir)/include
libsysapp_http_la_LIBADD = -lsysappdb

libsysapp_server_la_LDFLAGS = -static
libsysapp_server_la_SOURCES = login-server.cc server.cc server-elements.cc
libsysapp_server_la_LDFLAGS = -L$(top_srcdir)/lib
libsysapp_server_la_CXXFLAGS = -I$(top_srcdir)/include $(SQLITE3_CFLAGS) $(OCTETOS_DB_MYSQL_CFLAGS) $(CGICC_CFLAGS) $(OPENSSL_CFLAGS)
libsysapp_server_la_LIBADD =   libsysapp-http.la -lsysappdb  $(SQLITE3_LIBS) $(OCTETOS_DB_MYSQL_LIBS) $(CGICC_LIBS) $(OPENSSL_LIBS)  

login_SOURCES = login.cc 
login_LDADD =   libsysapp-server.la  

application_SOURCES = application.cc application-server.cc 
application_LDADD =   libsysapp-server.la 