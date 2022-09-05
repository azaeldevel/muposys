

SUBDIRS = src cgi tests

dist_doc_DATA = \
	README \
	COPYING \
	AUTHORS \
	ChangeLog \
	INSTALL \
	NEWS


INTLTOOL_FILES = intltool-extract.in \
	intltool-merge.in \
	intltool-update.in

EXTRA_DIST = \
	$(INTLTOOL_FILES)

DISTCLEANFILES = intltool-extract \
	intltool-merge \
	intltool-update \
	po/.intltool-merge-cache


# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(docdir)

cgidir=$(datarootdir)
cgi_DATA=cgi/http

htmldir=$(bindir)
html_DATA=html/login.html html/userregister.html html/index.html

cssdir=$(bindir)/css
css_DATA=html/css/application.css html/css/login.css html/css/theme.css

jsdir=$(bindir)/js
js_DATA=html/js/login.js html/js/sysapp.js


install-data-hook:
	chmod a+w $(DATABASE)
	chmod a+w $(bindir)/*.html
	chmod a+w -R $(bindir)/css
	chmod a+w -R $(bindir)/js
	chown $(USER_GROUP) $(DATABASE)
	chown $(USER_GROUP) $(bindir)/*.html
	chown $(USER_GROUP) -R $(bindir)/css
	chown $(USER_GROUP) -R $(bindir)/js

install-exec-hook:
	chown $(USER_GROUP) $(bindir)/*.cgi



