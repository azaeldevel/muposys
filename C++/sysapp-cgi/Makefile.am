
SUBDIRS = src 



# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(docdir)

databasedir = $(datarootdir)
database_DATA = database

install-data-hook:
	chmod a+rw $(datarootdir)/database