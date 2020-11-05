
SUBDIRS = src 

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

databasedir = $(datarootdir)
database_DATA = database

install-data-hook:
	chmod a+rw $(datarootdir)/database