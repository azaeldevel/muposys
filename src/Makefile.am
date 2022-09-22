
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = muposys

muposys_SOURCES = \
	main.cc

muposys_LDFLAGS = 

muposys_LDADD = 


if NATIVE_WIN32
muposys_LDFLAGS += -mwindows
endif
