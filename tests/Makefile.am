
check_PROGRAMS = v0
TESTS= $(check_PROGRAMS)

if WITH_MEDIUMWORD
DEFINESBD = -DOCTETOS_DB_MEDIUMWORD
endif
if WITH_HIGHWORD
DEFINESBD = -DOCTETOS_DB_HIGHWORD
endif
if WITH_LOWWORD
DEFINESBD = -DOCTETOS_DB_LOWWORD
endif


v0_LDFLAGS =
v0_LDADD = $(CUNIT_LIBS) $(LIBCONFIG_LIBS) $(SQLITE3_LIBS)  $(CGICC_LIBS) $(OPENSSL_LIBS) $(top_builddir)/cgi/libmuposys-http.la $(top_builddir)/cgi/libmuposys-server.la $(top_builddir)/cgi/libmuposys-html.la
v0_CPPFLAGS = $(CUNIT_CFLAGS) $(SQLITE3_CFLAGS) $(CGICC_CFLAGS) $(OPENSSL_CFLAGS) $(DEFINESBD) -DOCTETOS_CORE_V0 -I$(top_srcdir)/src
v0_SOURCES = main.cc v0.cc
		 
