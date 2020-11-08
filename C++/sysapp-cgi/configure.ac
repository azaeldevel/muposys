

AC_INIT(sysapp-cgi, 0.1.0-alpha)

AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.11])

AM_SILENT_RULES([yes])

AC_PROG_CXX








LT_INIT

PKG_CHECK_MODULES(CGICC, [cgicc])

PKG_CHECK_MODULES(SQLITE3, [sqlite3])

PKG_CHECK_MODULES(OPENSSL, [openssl])

PKG_CHECK_MODULES(OCTETOS_DB_MYSQL, [octetos-db-mysql])

AC_OUTPUT([
Makefile
src/Makefile

])
