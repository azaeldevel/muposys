
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)/muposys/desk"\" \
	-DPROGRAMNAME_LOCALEDIR=\"${PROGRAMNAME_LOCALEDIR}\" \
	$(GTK_CFLAGS)

AM_CFLAGS = -g -Wall

bin_PROGRAMS = muposys-desk 

lib_LTLIBRARIES = libmuposys-desk.la


LIBS = $(OCTETOS_DB_LIBS) $(GTK_LIBS) $(APIDB_LIBS) $(OCTETOS_LIBS)
FLAGS = $(OCTETOS_DB_CFLAGS)  $(GTK_CFLAGS) $(APIDB_CFLAGS) $(OCTETOS_CFLAGS)
if MUPOSYS_DESK_ENABLE_TDD
FLAGS += -DMUPOSYS_DESK_ENABLE_TDD
endif
if OCTETOS_DB_MEDIUMWORD
FLAGS += -DOCTETOS_DB_MEDIUMWORD
endif
if DATABASE_ENGINE_MARIA
FLAGS += -DDATABASE_ENGINE_MARIA
endif

muposys-glade.c : $(top_srcdir)/resources.xml $(top_srcdir)/desk.ui
	glib-compile-resources --generate-header --c-name rc_glade_muposys --target=muposys-glade.hh   --sourcedir=$(top_srcdir) $(top_srcdir)/resources.xml
	glib-compile-resources --generate-source --c-name rc_glade_muposys --target=muposys-glade.c   --sourcedir=$(top_srcdir) $(top_srcdir)/resources.xml
	
libmuposys_desk_la_CXXFLAGS = $(FLAGS) 
libmuposys_desk_la_LDFLAGS = 
libmuposys_desk_la_SOURCES = desk.cc desk.hh desk-TableSaling.cc
libmuposys_desk_la_LIBADD =  $(LIBS)

muposys_desk_LDADD = $(LIBS) libmuposys-desk.la
muposys_desk_CXXFLAGS = $(FLAGS)
muposys_desk_SOURCES = desk-main.cc 

muposysdir = $(datadir)/muposys/desk
muposys_DATA = muposys-desk.ui
muposys_includedir = $(includedir)/muposys
muposys_include_HEADERS = desk.hh
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = muposys-desk.pc

EXTRA_DIST = $(muposys_DATA)

uninstall-local:
	-rm -r $(muposysdir)
