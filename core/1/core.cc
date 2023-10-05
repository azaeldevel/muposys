
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



#include "core.hh"

namespace oct::mps::v1
{
    cave::mmsql::Data default_dtm()
    {
#ifdef MUPOSYS_CORE_V1_TDD
        return cave::mmsql::Data ("localhost","develop","123456", "muposys-dev", 3306);
#else
        return cave::mmsql::Data("localhost","muposys","123456", "muposys", 3306);
#endif
    }

}
