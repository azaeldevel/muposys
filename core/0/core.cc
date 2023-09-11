
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

namespace mps
{


	RandomString::RandomString(unsigned short l,Type t) : leng(l),type(t)
	{
		buffer = new char[l + 1];
		switch(t)
		{
		case Type::md5:
			number = new std::uniform_int_distribution<int>(0,15);
			break;
		default:
			//throw Exception(Exception::NotYet,__FILE__,__LINE__);
			;
		}
	}

	RandomString::~RandomString()
	{
		delete[] buffer;
		delete number;
	}

	void RandomString::generate()
	{
		switch(type)
		{
		case Type::md5:
			for(unsigned int i = 0; i < leng; i++)
			{
				buffer[i] = generate_md5();
			}
			break;
        default:
            ;
		}
		buffer[leng] = '\0'; // leng + 1 => i
	}

	char RandomString::generate_md5()
	{
		switch(number->operator()(generator))
		{
			case 0: return '0';
			case 1: return '1';
			case 2: return '2';
			case 3: return '3';
			case 4: return '4';
			case 5: return '5';
			case 6: return '6';
			case 7: return '7';
			case 8: return '8';
			case 9: return '9';
			case 10: return 'a';
			case 11: return 'b';
			case 12: return 'c';
			case 13: return 'd';
			case 14: return 'e';
			case 15: return 'f';
		}

		return '0';
	}

	RandomString:: operator const char *() const
	{
		return buffer;
	}

}
