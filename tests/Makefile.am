
check_PROGRAMS = v0
TESTS= $(check_PROGRAMS)

LIB = $(OCTETOS_DB_LIBS) $(SQLITE3_LIBS) $(CGICC_LIBS) $(CUNIT_LIBS)
FLAGS = $(OCTETOS_DB_CFLAGS) $(SQLITE3_CFLAGS) $(CGICC_CFLAGS) $(CUNIT_CFLAGS)

v0_LDFLAGS =
v0_LDADD = $(LIB) $(top_builddir)/apidb/libmuposys-apidb.la $(top_builddir)/cgi/libmuposys-cgi.la
v0_CPPFLAGS = $(FLAGS) -DOCTETOS_CORE_V0 -I$(top_srcdir)/src
v0_SOURCES = main.cc v0.cc
