
SUBDIRS = src 

if MUPOSYS_APIDB_ENABLE_TDD
SUBDIRS +=  tests
endif

dist_doc_DATA = \
	README \
	COPYING \
	AUTHORS \
	ChangeLog \
	INSTALL \
	NEWS



# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(docdir)
