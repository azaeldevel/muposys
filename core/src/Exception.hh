
#ifndef MUPOSYS_CORE_EXCEPTION_HH
#define MUPOSYS_CORE_EXCEPTION_HH

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
    #include <octetos/core/Exception-v3.hh>
#elif defined MSYS2
    #include <core/src/Exception-v3.hh>
#elif defined(_WIN32) || defined(_WIN64)
    #include <Exception-v3.hh>
#else
	#error "Plataforma desconocida"
#endif

namespace mps
{

class Exception : public oct::core::v3::Exception
{
public:
	enum ErrosCodes
	{
		NotYet,
		NotCopiableObject,
		NotVoidObject,
		Database_Error,

		top,
	};

public:
	Exception();
	Exception(const Exception&);
	Exception(Exception&&);

	Exception(unsigned int code);
	Exception(unsigned int code,const char* filename, unsigned int line);

	Exception(unsigned int code,const char* message);
	Exception(unsigned int code,const char* message,const char* filename, unsigned int line);

	Exception(const std::string& message);
	Exception(const std::string& message,const char* filename, unsigned int line);

	Exception(unsigned int code,const std::string& message);
	Exception(unsigned int code,const std::string& message,const char* filename, unsigned int line);

	Exception(const char* message);
	Exception(const char* message,const char* filename, unsigned int line);

	virtual ~Exception();

	virtual const char* what() const throw ();

private:
};


class ExceptionQuery : public oct::core::v3::Exception
{
public:

public:
	ExceptionQuery();
	ExceptionQuery(const Exception&);

	ExceptionQuery(const char* message);
	ExceptionQuery(const char* message,const char* filename, unsigned int line);

	virtual ~ExceptionQuery();

	//virtual const char* what() const throw ();

private:
};


}

#endif
