

AC_INIT(muposys-cgi, 0.8.0-alpha, azael.devel@gmail.com)

AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([subdir-objects])

AM_SILENT_RULES([yes])

AC_PROG_CXX


LT_INIT


PKG_CHECK_MODULES(CGICC, [cgicc])

PKG_CHECK_MODULES(SQLITE3, [sqlite3])

PKG_CHECK_MODULES(OPENSSL, [openssl])

PKG_CHECK_MODULES(OCTETOS_CORE, [octetos-core])

PKG_CHECK_MODULES(OCTETOS_DB_ABSTRACT, [octetos-db-abstract])


AC_ARG_ENABLE([os],[AS_HELP_STRING([--enable-os],[Enable configuration for particular OS])])
	case $enableval in
	  	archlinux)
			AC_DEFINE([LINUX_ARCH], [], [Enable configuration for Arch-Linux])
			AC_SUBST([DATABASE],["/srv/database"])
			AC_DEFINE_UNQUOTED([DATABASE], ["$DATABASE"] ,[Full path for database file])
		;;
	  	debian) 
			AC_DEFINE([LINUX_DEBIAN], [], [Enable configuration for Debian])
		;;
	  	*) 
			AC_MSG_ERROR([unknown option '$enable_os' for --enable-os]) 

		;;
	esac




AM_CONDITIONAL(WITH_TESTS, test x"$with_tests" = "xyes")
AC_ARG_WITH([tests], AS_HELP_STRING([--with-tests], [Compilando con soporte para Tests]))
if test "x$with_tests" = "xyes"; then 
	PKG_CHECK_MODULES(CUNIT,cunit)
fi


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


AM_CONDITIONAL(WITH_MEDIUMWORD, test x"$with_mediumword" = "xyes")
AC_ARG_WITH([mediumword], AS_HELP_STRING([--with-mediumword], [Define el tamno de los datos usados.]))

AM_CONDITIONAL(WITH_HIGHWORD, test x"$with_mediumword" = "xyes")
AC_ARG_WITH([mediumword], AS_HELP_STRING([--with-highword], [Define el tamno de los datos usados.]))

AM_CONDITIONAL(WITH_LOWWORD, test x"$with_mediumword" = "xyes")
AC_ARG_WITH([mediumword], AS_HELP_STRING([--with-lowword], [Define el tamno de los datos usados.]))


AC_OUTPUT([
Makefile
src/Makefile
tests/Makefile
])
