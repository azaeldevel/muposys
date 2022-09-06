

SUBDIRS = apidb src cgi tests

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

themedir=$(bindir)/js
theme_DATA=html/js/login.js html/js/sysapp.js

install-data-hook:
	chmod a+w $(DATABASE)
	chmod a+w $(bindir)/*.html
	chmod a+w -R $(bindir)/css
	chmod a+w -R $(bindir)/js
	chown $(USER_GROUP) $(DATABASE)
	chown $(USER_GROUP) $(bindir)/*.html
	chown $(USER_GROUP) -R $(bindir)/css
	chown $(USER_GROUP) -R $(bindir)/js
	mkdir -p $(datarootdir)/theme/gnome-2
	mkdir -p $(bindir)/theme/gnome-2
	tar -xjf $(top_srcdir)/html/gnome-icon-theme-2.91.93.tar.bz2 -C $(datarootdir)/theme/gnome-2 --strip-components=1
	cp -r $(datarootdir)/theme/gnome-2/gnome/* $(bindir)/theme/gnome-2
	chown $(USER_GROUP) -R $(bindir)/theme/gnome-2
	rm -r $(datarootdir)/theme/gnome-2

install-exec-hook:
	chown $(USER_GROUP) $(bindir)/*.cgi



