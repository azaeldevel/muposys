
/*
 * Copyright (C) 2022 Azael R. <azael.devel@gmail.com>
 * 
 * octetos-cc is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * octetos-cc is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#include "Exception.hh"

namespace mps
{
	
Exception::Exception()
{
}
Exception::Exception(const Exception& e) : oct::core::v3::Exception(e)
{
}
Exception::Exception(Exception&& e) : oct::core::v3::Exception(e)
{
}


Exception::Exception(unsigned int c) : oct::core::v3::Exception(c)
{
}
Exception::Exception(unsigned int c,const char* s) : oct::core::v3::Exception(c,s)
{
}
Exception::Exception(unsigned int c,const char* fn, unsigned int l) : oct::core::v3::Exception(c,fn,l)
{
}
Exception::Exception(unsigned int c,const char* s,const char* fn, unsigned int l) : oct::core::v3::Exception(c,s,fn,l)
{
}

Exception::Exception(const std::string& m) : oct::core::v3::Exception(m)
{
}
Exception::Exception(const std::string& m,const char* f, unsigned int l) : oct::core::v3::Exception(m,f,l)
{
}

Exception::~Exception()
{
}


	
}
