
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
#include <cstring>
#include <fstream>
#include <filesystem>


#if __linux__
    #if defined LINUX_ARCH

    #elif defined LINUX_GENTOO

    #elif defined LINUX_DEBIAN

    #elif LINUX_MSYS2
        #include <mariadb/mysql.h>
        #error "Plataforma desconocida."
    #endif
#elif (defined(_WIN32) || defined(_WIN64))

#else
	#error "Plataforma desconocida."
#endif

#include <cave/0/mmsql.hh>
#include <cave/1/mmsql.hh>
#include <libconfig.h++>

namespace oct::mps::v1
{
    namespace cave0 = oct::cave::v0;
    namespace cave1 = oct::cave::v1;
    namespace cave = oct::cave::v1;
    namespace core = oct::core::v3;
    typedef unsigned long ID;

	cave0::mmsql::Data default_dtm0();
	cave1::mmsql::Data default_dtm1();
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


	enum class Crud
	{
		none,
		create,
		read,
		update,
		remove,
	};

    struct Person
    {
        ID id;
        std::string name1,name3; //person name

        Person() = default;
        Person(const char** s);
        Person(cave0::Row<char,cave0::mmsql::Data> s);

        static std::string fields();
        static std::string table();
        bool down(cave0::mmsql::Connection& conn);
        void fullname(std::string& c)const;
    };

    struct User
    {
        bool valid;
        ID id;
        Person person;
        std::string name; //person name

        User() = default;
        User(const char** s);
        User(cave0::Row<char,cave0::mmsql::Data> s);


        static std::string fields();
        static std::string table();

    };
    struct Session
    {
        ID id;
        std::string client,session;

        Session() = default;
        Session(const char** s);
        Session(cave0::Row<char,cave0::mmsql::Data> s);
        static std::string fields();
        static std::string table();
        cave0::mmsql::Result remove(cave0::mmsql::Connection& conn);
        cave0::mmsql::Result insert(cave0::mmsql::Connection& conn,std::string const& client);
        cave0::mmsql::Result upSession(cave0::mmsql::Connection& conn);
        bool downSession(cave0::mmsql::Connection& conn);

    };
    struct Variable
    {
        ID id;
        std::string name,value,session;

        Variable() = default;
        Variable(const char** s);
        Variable(cave0::Row<char,cave0::mmsql::Data> s);
        static std::string fields();
        static std::string table();
        cave0::mmsql::Result remove(cave0::mmsql::Connection& conn);
        cave0::mmsql::Result insert(cave0::mmsql::Connection& conn);
        cave0::mmsql::Result upName(cave0::mmsql::Connection& conn);
        cave0::mmsql::Result upValue(cave0::mmsql::Connection& conn);
        cave0::mmsql::Result upSession(cave0::mmsql::Connection& conn);
        bool downValue(cave0::mmsql::Connection& conn);
    };
    struct CatalogItem
    {
        ID id,catalog;
        std::string number,brief,presentation;
        bool active;
        float value;
        short type;

        CatalogItem() = default;
        CatalogItem(const char** s);
        CatalogItem(const cave0::Row<char,cave0::mmsql::Data>& s);
        CatalogItem(const cave1::Row<char,cave1::mmsql::Data>& s);
        CatalogItem(const CatalogItem& s);


        static std::string fields();
        static std::string table();

        CatalogItem& operator =(const char** s);
        //std::string insert_values()const;
        std::string update_values()const;
        std::string update_values(const std::initializer_list<size_t>& list)const;
        static std::string select_fields();
        static std::string select_fields(const std::initializer_list<size_t>& list);
        static std::string insert_fields();
        static std::string identifier_name();
        std::string identifier_value() const;

    };

    class Configuration
    {
    public:
        struct Version
        {
            int major;
            int minor;
            int patch;
            std::string prerelease;
            std::string build;
        };


    public:
        Configuration();
        Configuration(const std::filesystem::path& p);

        std::filesystem::path read(const std::filesystem::path& p);
        std::filesystem::path create();
        std::filesystem::path create(const std::filesystem::path& p);
        std::filesystem::path create(const std::filesystem::path& p,const std::string& server);
        std::filesystem::path create(const std::filesystem::path& p,const Version& server,const cave1::mmsql::Data& data);
        std::filesystem::path create(const std::filesystem::path& p,const Version& server,const cave0::mmsql::Data& data);

        void get_name(std::string&) const;
        void get_version(Version&)const;
        void get_datasource(cave1::mmsql::Data&)const;
        void get_datasource(cave0::mmsql::Data&)const;

    private:
        //std::fstream file;
        libconfig::Config config;
        libconfig::Setting& root;
    private:
        static const std::filesystem::path configure_directory;
        static const std::filesystem::path configure_file;
        static std::filesystem::path defaul_file();
        static std::filesystem::path defaul_derectory();

    };
}

namespace oct::mps::v2
{
    using namespace oct::mps::v1;
}

namespace mps = oct::mps::v1;

#endif
