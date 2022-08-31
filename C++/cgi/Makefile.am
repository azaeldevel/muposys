
SUBDIRS = src tests 



# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(docdir)

databasedir = $(datarootdir)
database_DATA = database

install-data-hook:
	chmod a+w $(datarootdir)/database

