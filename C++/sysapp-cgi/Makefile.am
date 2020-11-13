
SUBDIRS = src 



# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(docdir)

databasedir = $(datarootdir)
database_DATA = database

install-data-hook:
	chown www-data:www-data -R /var/www
	chmod u+w /var/www