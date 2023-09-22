
#ifndef MUPOSYS_CORE_V1_HH
#define MUPOSYS_CORE_V1_HH

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



#if __linux__
    #if defined LINUX_ARCH
        #include <mysql/mysql.h>
    #elif defined LINUX_GENTOO
        #include <mariadb/mysql.h>
    #elif defined LINUX_DEBIAN
        #include <mariadb/mysql.h>
    #elif LINUX_MSYS2
        #include <mariadb/mysql.h>
        #error "Plataforma desconocida."
    #endif
#elif (defined(_WIN32) || defined(_WIN64))
        #include <mysql/mysql.h>
#else
	#error "Plataforma desconocida."
#endif

#include <cave/src/mmsql.hh>
namespace cave = oct::cave::v0;

namespace mps::v1
{
	cave::mmsql::Data default_dtm();

}

#endif
