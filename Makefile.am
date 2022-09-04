

SUBDIRS = src cgi tests po

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

install-data-hook:
	chmod a+w $(DATABASE)
	chown $(USER_GROUP) $(DATABASE)

install-exec-hook:
	chown $(USER_GROUP) $(bindir)/*.cgi



