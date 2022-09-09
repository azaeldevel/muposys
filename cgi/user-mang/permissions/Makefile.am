
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g



bin_PROGRAMS = add.cgi

add_cgi_CXXFLAGS = $(SQLITE3_CFLAGS) $(CGICC_CFLAGS) $(DEFINES) $(DEFINESBD)  -I$(top_builddir)
add_cgi_LDADD =  $(top_builddir)/cgi/libmuposys-http.la $(top_builddir)/cgi/libmuposys-html.la $(top_builddir)/cgi/libmuposys-server.la $(top_builddir)/apidb/libmuposys-db.la $(SQLITE3_LIBS)  $(CGICC_LIBS) $(DBLIBS) 
add_cgi_SOURCES = add-main.cc 