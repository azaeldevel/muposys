
#ifndef MUPOSYS_APIDB

#ifdef MUPOSYS_APIDB_ENABLE_TDD
	#include "muposysdb.hpp"
#else
	#include <muposys/muposysdb.hpp>
#endif

namespace mps
{

#if defined DATABASE_ENGINE_MARIA
	typedef octetos::db::maria::Connector Connector;
	typedef octetos::db::maria::Datconnect Datconnect;
#elif defined DATABASE_ENGINE_MYSQL
	typedef octetos::db::mysql::Connector Connector;
	typedef octetos::db::mysql::Datconnect Datconnect;
#elif defined DATABASE_ENGINE_POSTGRESQL
	typedef octetos::db::postgresql::Connector Connector;
	typedef octetos::db::mysql::Datconnect Datconnect;
#else
	typedef octetos::db::Connector Connector;
#endif

}
#endif