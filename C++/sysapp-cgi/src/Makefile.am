


bin_PROGRAMS = login.cgi 

login_cgi_SOURCES = login.cc login-server.cc db.cc http.cc server.cc server-elements.cc

login_cgi_LDFLAGS = -L$(top_srcdir)/lib

login_cgi_LDADD = $(CGICC_LIBS) $(SQLITE3_LIBS)  $(OPENSSL_LIBS) $(OCTETOS_DB_MYSQL_LIBS) -lsysappdb

login_cgi_CXXFLAGS = -I$(top_srcdir)/include $(CGICC_CFLAGS) $(SQLITE3_CFLAGS) $(OPENSSL_CFLAGS)  $(OCTETOS_DB_MYSQL_CFLAGS)

