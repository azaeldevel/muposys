dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(muposys, 0.1.0-alpha)

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

PKG_CHECK_MODULES(OCTETOS_DB_MARIA, [octetos-db-maria ])



AC_OUTPUT([
Makefile
src/Makefile
po/Makefile.in
])
