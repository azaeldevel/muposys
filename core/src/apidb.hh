
#ifndef MUPOSYS_CORE_APIDB_HH
#define MUPOSYS_CORE_APIDB_HH

#ifdef MUPOSYS_CORE_ENABLE_TDD
	#include <muposysdb.hpp>
#else
	#if __linux__
        #include <muposys/core/muposysdb.hpp>
    #elif MSYS2
        #include <muposysdb.hpp>
        #include <apidb.hh>
    #else
        #error "Plataforma desconocida."
    #endif
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
	typedef octetos::db::Datconnect Datconnect;
#endif

}


#endif