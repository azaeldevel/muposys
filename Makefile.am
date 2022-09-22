

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
html_DATA=html/login.html html/user-register.html html/index.html  html/user-mang.html

html_user_mang_permissionsdir=$(bindir)/user-mang/permissions
html_user_mang_permissions_DATA=html/user-mang/permissions/add.html

cssdir=$(bindir)/css
css_DATA=html/css/login.css html/css/user-mang.css

css_appearancedir=$(bindir)/css/appearance
css_appearance_DATA=html/css/appearance/muposys.css

css_iconsdir=$(bindir)/css/icons
css_icons_DATA=html/css/icons/Mkos-Big-Sur.css

jsdir=$(bindir)/js
js_DATA=html/js/login.js html/js/muposys.js

themedir=$(bindir)/js
theme_DATA=html/js/login.js

install-data-hook:
	chmod a+w $(DATABASE)
	chmod a+w $(bindir)/*.html
	chmod a+w -R $(bindir)/css
	chmod a+w -R $(bindir)/js
	chmod a+w -R $(bindir)/user-mang
	chown $(USER_GROUP) $(DATABASE)
	chown $(USER_GROUP) $(bindir)/*.html
	chown $(USER_GROUP) -R $(bindir)/css
	chown $(USER_GROUP) -R $(bindir)/js
	chown $(USER_GROUP) -R $(bindir)/user-mang
	mkdir -p $(bindir)/theme
	pwd
	tar -xf html/Mkos-Big-Sur.tar.xz -C $(bindir)/theme
	chown $(USER_GROUP) -R $(bindir)/theme
	mv $(bindir)/add.cgi $(bindir)/user-mang/permissions/
	mv $(bindir)/user-permiss.cgi $(bindir)/user-mang/permissions/

install-exec-hook:
	chown $(USER_GROUP) $(bindir)/*.cgi



