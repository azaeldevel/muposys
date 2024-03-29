
/*
 * Copyright (C) 2022 Azael R. <azael.devel@gmail.com>
 * 
 * octetos-saturno is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * octetos-saturno is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#include "Exception.hh"

namespace muposys
{
	
Exception::Exception()
{

}
Exception::Exception(unsigned int c) : oct::core::v3::Exception(c)
{
}
Exception::Exception(unsigned int c,const char* s) : oct::core::v3::Exception(c,s)
{
}
Exception::Exception(unsigned int c,const char* f, unsigned int l) : oct::core::v3::Exception(c,f,l)
{
}
Exception::Exception(unsigned int c,const char* s,const char* f, unsigned int l) : oct::core::v3::Exception(c,s,f,l)
{
}

const char* Exception::what () const throw ()
{
	switch(code())
	{
	case Errors::NO_ERROR:
		return "No error.";
	case Errors::FAIL_OPEN_DATABASE:
		return "Fallo al abrir la base de datos";
	case Errors::NOT_FOUND:
		return "No se encontro la tabla";
		
	default:
		return "Error desconocido.";
	}
	
	return "Error desconocido.";
}
	
}