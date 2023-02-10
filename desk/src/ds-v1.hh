
#ifndef MUPOSYS_DATASOURCE_HH
#define MUPOSYS_DATASOURCE_HH

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
    #include <cave/maria.hh>
#elif defined(_WIN32) || defined(_WIN64)
    #include <cave/src/maria.hh>
#else
	#error "Plataforma desconocida."
#endif

namespace mps::v1
{
    static const cave_current::OCTETOS_CAVE_DRIVER::Data ds("localhost","muposys","123456","muposys");

}

#endif
