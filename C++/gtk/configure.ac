dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(muposys, 0.1)

AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.11])

AM_SILENT_RULES([yes])

AC_PROG_CXX




dnl ***************************************************************************
dnl Internationalization
dnl ***************************************************************************
IT_PROG_INTLTOOL([0.35.0])

GETTEXT_PACKAGE=muposys
AC_SUBST(GETTEXT_PACKAGE)
AC_DEFINE_UNQUOTED(GETTEXT_PACKAGE,"$GETTEXT_PACKAGE", [GETTEXT package name])
AM_GLIB_GNU_GETTEXT





LT_INIT


PKG_CHECK_MODULES(GTKMM, [gtkmm-3.0 ])

PKG_CHECK_MODULES(OCTETOS_DB_ABSTRACT, [octetos-db-abstract ])

PKG_CHECK_MODULES(OCTETOS_DB_MARIA, [octetos-db-maria ])

AC_ARG_WITH([mysql], AS_HELP_STRING([--with-mysql], [Soporta para MySQL.]))
if test "x$with_mysql" = "xyes"; then 
	PKG_CHECK_MODULES(OCTETOS_DB_MYSQL, [octetos-db-mysql])
fi
AM_CONDITIONAL(WITH_MYSQL, test x"$with_mysql" = "xyes")

AC_ARG_WITH([mariadb], AS_HELP_STRING([--with-mariadb], [Soporta para MariDB.]))
if test "x$with_mariadb" = "xyes"; then 
	PKG_CHECK_MODULES(OCTETOS_DB_MARIA, [octetos-db-maria])
fi
AM_CONDITIONAL(WITH_MARIADB, test x"$with_mariadb" = "xyes")


AC_ARG_WITH([postgresql], AS_HELP_STRING([--with-postgresql], [Soporta para PostgreSQL.]))
if test "x$with_postgresql" = "xyes"; then 
	PKG_CHECK_MODULES(OCTETOS_DB_POSTGRESQL, [octetos-db-postgresql])
fi
AM_CONDITIONAL(WITH_POSTGRESQL, test x"$with_postgresql" = "xyes")


AC_OUTPUT([
Makefile
src/Makefile
po/Makefile.in
])
