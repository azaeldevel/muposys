
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

#include <random>

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

#include <cave/0/mmsql.hh>

namespace oct::mps::v1
{
    namespace cave = oct::cave::v0;

	cave::mmsql::Data default_dtm();



    class RandomString
	{
	public:
		enum Type
		{
			alpha,
			numeric,
			alphanumeric,
			md5
		};

	public:
		RandomString(unsigned short leng,Type);
		~RandomString();
		void generate();

		operator const char*() const;

	private:
		std::random_device generator;
		std::uniform_int_distribution<int>* number;
		unsigned short leng;
		char* buffer;
		Type type;

		char generate_md5();
	};

    struct Person
    {
        unsigned long id;

        std::string name1,name3; //person name

        Person() = default;
        Person(const char** s)
        {
            name1 = s[0];
        }
        Person(cave::Row<char,cave::mmsql::Data> s)
        {
            name1 = s[0];
        }

        static std::string fields()
        {
            return "id,name1,name3";
        }

        static std::string table()
        {
            return "User";
        }
    };
    struct User
    {
        bool valid;
        unsigned long id;
        Person person;
        std::string name; //person name

        User() = default;
        User(const char** s)
        {
            name = s[0];
        }
        User(cave::Row<char,cave::mmsql::Data> s)
        {
            name = s[0];
        }


        static std::string fields()
        {
            return "id,person,name";
        }

        static std::string table()
        {
            return "User";
        }
    };
    struct Session
    {
        unsigned long id;
        std::string client,session;

        Session() = default;
        Session(const char** s)
        {
            id = std::atoi(s[0]);
            client = s[1];
            session = s[2];
        }
        Session(cave::Row<char,cave::mmsql::Data> s)
        {
            id = std::atoi(s[0]);
            client = s[1];
            session = s[2];
        }
        static std::string fields()
        {
            return "id,client,session";
        }
        static std::string table()
        {
            return "Session";
        }
        cave::mmsql::Result remove(cave::mmsql::Connection& conn)
        {
            return conn.remove(table(),"session = " + session);
        }
        cave::mmsql::Result insert(cave::mmsql::Connection& conn,std::string const& client)
        {
            return conn.insert(std::string("client"),client,table());
        }
        cave::mmsql::Result upSession(cave::mmsql::Connection& conn,std::string const& client)
        {
            return conn.update("client = '" + client + "'", table());
        }
        bool select_session(cave::mmsql::Connection& conn)
        {
            cave::mmsql::Result rs = conn.select("client = '" + client + "'", table(),"session = " + session);
            return rs;
        }

    };
    struct Variable
    {
        unsigned long id;
        std::string name,value,session;

        Variable() = default;
        Variable(const char** s)
        {
            id = std::atoi(s[0]);
            name = s[1];
            value = s[2];
            session = s[3];
        }
        Variable(cave::Row<char,cave::mmsql::Data> s)
        {
            id = std::atoi(s[0]);
            name = s[1];
            value = s[2];
            session = s[3];
        }
        static std::string fields()
        {
            return "id,name,value,session";
        }
        static std::string table()
        {
            return "Session";
        }
        cave::mmsql::Result remove(cave::mmsql::Connection& conn)
        {
            return conn.remove(table(),"session = " + session);
        }
        cave::mmsql::Result insert(cave::mmsql::Connection& conn)
        {
            RandomString ranstr(32,RandomString::md5);
            ranstr.generate();
            return conn.insert("name,value,session","'" + name + "','" + value + "','" + (const char*)ranstr + "'" ,table());
        }
    };

}

#endif
