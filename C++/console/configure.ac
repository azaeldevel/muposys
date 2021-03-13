
AC_INIT(console, 0.1.0-alpha,azael.devel@gmail.com)

AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.11])

AM_SILENT_RULES([yes])

AC_PROG_CXX



AC_ARG_WITH([debian], AS_HELP_STRING([--with-debian], [Soporta para Debian]))
AM_CONDITIONAL(WITH_DEBIAN, test x"$with_debian" = "xyes")




LT_INIT

PKG_CHECK_MODULES(OCTETOS_DB_ABSTRACT, [octetos-db-abstract])

AC_ARG_WITH([mariadb], AS_HELP_STRING([--with-mariadb], [Soporta para MariDB.]))
if test "x$with_mariadb" = "xyes"; then 
	PKG_CHECK_MODULES(MARIADB, [libmariadb])
	PKG_CHECK_MODULES(OCTETOS_DB_MARIA, [octetos-db-maria])
fi
AM_CONDITIONAL(WITH_MARIADB, test x"$with_mariadb" = "xyes")


AC_OUTPUT([
Makefile
src/Makefile

])
