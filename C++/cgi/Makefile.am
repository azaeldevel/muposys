
SUBDIRS = src tests 



# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(docdir)

databasedir=$(datarootdir)
database_DATA=database/http

install-data-hook:
	chmod a+w $(DATABASE)
	chown $(USER_GROUP) $(DATABASE)

install-exec-hook:
	chown $(USER_GROUP) $(bindir)/*.cgi
	

