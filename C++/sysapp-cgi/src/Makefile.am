


bin_PROGRAMS = login.cgi 

login_cgi_SOURCES = login.cc db.cc

login_cgi_LDFLAGS = -L$(top_srcdir)/lib

login_cgi_LDADD = $(CGICC_LIBS) $(SQLITE3_LIBS)  $(OPENSSL_LIBS) -lsysappdb

login_cgi_CXXFLAGS = -I$(top_srcdir)/include $(CGICC_CFLAGS) $(SQLITE3_CFLAGS) $(OPENSSL_CFLAGS)

