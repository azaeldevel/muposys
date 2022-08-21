
check_PROGRAMS = v0
TESTS= $(check_PROGRAMS)


v0_LDFLAGS =
v0_LDADD = $(CUNIT_LIBS) $(LIBCONFIG_LIBS) $(SQLITE3_LIBS)  $(CGICC_LIBS) $(OPENSSL_LIBS) $(top_builddir)/src/libmuposys-http.la $(top_builddir)/src/libmuposys-server.la
v0_CPPFLAGS = $(CUNIT_CFLAGS) $(SQLITE3_CFLAGS) $(CGICC_CFLAGS) $(OPENSSL_CFLAGS) -DOCTETOS_CORE_V0 -I$(top_srcdir)/src
v0_SOURCES = main.cc v0.cc
		 
