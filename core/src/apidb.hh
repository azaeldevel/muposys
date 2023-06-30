
#ifndef MUPOSYS_CORE_APIDB_HH
#define MUPOSYS_CORE_APIDB_HH

/*
 * Copyright (C) 2022 Azael R. <azael.devel@gmail.com>
 *
 * muposys is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * muposys is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#ifdef __linux__
    #ifdef CODEBLOCKS
        #include <muposys/desk/bin/Debug/apidb/muposysdb.hpp>
    #elif  defined MUPOSYS_CORE_ENABLE_TDD
        #include <src/muposysdb.hpp>
    #else
		#include <muposys/core/muposysdb.hpp>
    #endif
#elif defined(_WIN32) || defined(_WIN64)
   #include <cave/src/maria.hh>
#else
        #error "Plataforma desconocida."
#endif
namespace mps
{

#if defined DATABASE_ENGINE_MARIA
	typedef octetos::db::maria::Connector Connector;
	typedef octetos::db::maria::Datconnect Datconnect;
	typedef octetos::db::maria::Datresult Datresult;
#elif defined DATABASE_ENGINE_MYSQL
	typedef octetos::db::mysql::Connector Connector;
	typedef octetos::db::mysql::Datconnect Datconnect;
	typedef octetos::db::mysql::Datresult Datresult;
#elif defined DATABASE_ENGINE_POSTGRESQL
	typedef octetos::db::postgresql::Connector Connector;
	typedef octetos::db::postgresql::Datconnect Datconnect;
	typedef octetos::db::postgresql::Datresult Datresult;
#else
	typedef octetos::db::Connector Connector;
	typedef octetos::db::Datconnect Datconnect;
	typedef octetos::db::Datresult Datresult;
#endif

}


#endif
