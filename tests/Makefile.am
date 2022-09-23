
check_PROGRAMS = v0
TESTS= $(check_PROGRAMS)

LIB = $(OCTETOS_DB_LIBS) $(SQLITE3_LIBS) $(CGICC_LIBS)
FLAGS = $(OCTETOS_DB_FLAGS) $(SQLITE3_CFLAGS) $(CGICC_CFLAGS)

v0_LDFLAGS =
v0_LDADD = $(LIB) $(top_builddir)/apidb/libmuposys-apidb.la $(top_builddir)/cgi/libmuposys-server.la
v0_CPPFLAGS = $(FLAGS) -DOCTETOS_CORE_V0 -I$(top_srcdir)/src
v0_SOURCES = main.cc v0.cc
		 
