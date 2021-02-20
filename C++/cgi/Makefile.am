
SUBDIRS = src 



# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(docdir)

databasedir = $(datarootdir)
database_DATA = database

install-data-hook:
	chown apache:apache -R /var/www/localhost
	chmod -R u+w /var/www/localhost