
check_PROGRAMS = v0
TESTS= $(check_PROGRAMS)

LIB = $(OCTETOS_LIBS) $(OCTETOS_DB_LIBS) $(TDD_LIBS)
FLAGS = $(OCTETOS_CFLAGS) $(OCTETOS_DB_CFLAGS) $(TDD_CFLAGS)
if OCTETOS_DB_MEDIUMWORD
FLAGS += -DOCTETOS_DB_MEDIUMWORD
endif
if DATABASE_ENGINE_MARIA
FLAGS += -DDATABASE_ENGINE_MARIA
endif
if MUPOSYS_APIDB_ENABLE_TDD
FLAGS += -DMUPOSYS_APIDB_ENABLE_TDD -DMUPOSYS_APIDB_ENABLE_TDD_V0
endif

v0_LDFLAGS =
v0_LDADD = $(LIB) $(top_builddir)/src/libmuposys-apidb.la
v0_CXXFLAGS = $(FLAGS) -I$(top_builddir)/src -I$(top_srcdir)/src
v0_SOURCES = main.cc v0.cc
