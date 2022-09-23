
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g



bin_PROGRAMS = add.cgi user-permiss.cgi

LIB = $(OCTETOS_DB_LIBS) $(SQLITE3_LIBS) $(CGICC_LIBS)
FLAGS = $(OCTETOS_DB_FLAGS) $(SQLITE3_CFLAGS) $(CGICC_CFLAGS)


add_cgi_CXXFLAGS = $(FLAGS) -I$(top_builddir)
add_cgi_LDADD =  $(top_builddir)/cgi/libmuposys-cgi.la $(top_builddir)/apidb/libmuposys-apidb.la $(LIB) 
add_cgi_SOURCES = add-main.cc 

user_permiss_cgi_CXXFLAGS = $(FLAGS) -I$(top_builddir)
user_permiss_cgi_LDADD =  $(top_builddir)/cgi/libmuposys-cgi.la $(top_builddir)/apidb/libmuposys-apidb.la 
user_permiss_cgi_SOURCES = user-permiss-main.cc 




