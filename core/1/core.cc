
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
    #include <unistd.h>
    #include <sys/types.h>
    #include <pwd.h>
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

#include "core.hh"

namespace oct::mps::v1
{
    cave0::mmsql::Data default_dtm0()
    {
#ifdef MUPOSYS_CORE_V1_TDD
        return cave0::mmsql::Data ("localhost","develop","123456", "muposys-dev", 3306);
#else
        return cave0::mmsql::Data("192.168.1.102","muposys","123456", "muposys", 3306);
#endif
    }
    cave1::mmsql::Data default_dtm1()
    {
#ifdef MUPOSYS_CORE_V1_TDD
        return cave1::mmsql::Data ("localhost","develop","123456", "muposys-dev", 3306);
#else
        return cave1::mmsql::Data("192.168.1.102","muposys","123456", "muposys", 3306);
#endif
    }
    cave::mmsql::Data default_dtm()
    {
#ifdef MUPOSYS_CORE_V1_TDD
        return cave::mmsql::Data ("localhost","develop","123456", "muposys-dev", 3306);
#else
        return cave::mmsql::Data("192.168.1.102","muposys","123456", "muposys", 3306);
#endif
    }


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



        Person::Person(const char** s)
        {
            id = std::atoll(s[0]);
            name1 = s[1];
            name3 = s[2];
        }
        Person::Person(cave0::Row<char,cave0::mmsql::Data> s)
        {
            id = std::atoll(s[0]);
            name1 = s[1];
            name3 = s[2];
        }

        std::string Person::fields()
        {
            return "id,name1,name3";
        }

        std::string Person::table()
        {
            return "User";
        }
        bool Person::down(cave0::mmsql::Connection& conn)
        {
            cave0::mmsql::Result rs = conn.select("name1,name3", table(),"id = " + std::to_string(id));
            if(rs.size() > 0)
            {
                name1 = rs.next()[0];
                name3 = rs.next()[1];
                return true;
            }

            return false;
        }
        void Person::fullname(std::string& c)const
        {
            if(name1.empty()) return;
            c = name1;
            if(name3.empty()) return;
            c += " " + name3;
        }



        User::User(const char** s)
        {
            name = s[0];
            person.id = std::atoll(s[1]);
            name = s[2];
        }
        User::User(cave0::Row<char,cave0::mmsql::Data> s)
        {
            name = s[0];
            person.id = std::atoll(s[1]);
            name = s[2];
        }


        std::string User::fields()
        {
            return "id,person,name";
        }

        std::string User::table()
        {
            return "User";
        }







        Session::Session(const char** s)
        {
            id = std::atoi(s[0]);
            client = s[1];
            session = s[2];
        }
        Session::Session(cave0::Row<char,cave0::mmsql::Data> s)
        {
            id = std::atoi(s[0]);
            client = s[1];
            session = s[2];
        }
        std::string Session::fields()
        {
            return "id,client,session";
        }
        std::string Session::table()
        {
            return "Session";
        }
        cave0::mmsql::Result Session::remove(cave0::mmsql::Connection& conn)
        {
            return conn.remove(table(),"session = " + session);
        }
        cave0::mmsql::Result Session::insert(cave0::mmsql::Connection& conn,std::string const& client)
        {
            return conn.insert(std::string("client"),client,table());
        }
        cave0::mmsql::Result Session::upSession(cave0::mmsql::Connection& conn)
        {
            return conn.update("client = '" + client + "'", table());
        }
        bool Session::downSession(cave0::mmsql::Connection& conn)
        {
            cave0::mmsql::Result rs = conn.select("client = '" + client + "'", table(),"session = " + session);
            return rs;
        }





        Variable::Variable(const char** s)
        {
            id = std::atoi(s[0]);
            name = s[1];
            value = s[2];
            session = s[3];
        }
        Variable::Variable(cave0::Row<char,cave0::mmsql::Data> s)
        {
            id = std::atoi(s[0]);
            name = s[1];
            value = s[2];
            session = s[3];
        }
        std::string Variable::fields()
        {
            return "id,name,value,session";
        }
        std::string Variable::table()
        {
            return "Session";
        }
        cave0::mmsql::Result Variable::remove(cave0::mmsql::Connection& conn)
        {
            return conn.remove(table(),"session = " + session);
        }
        cave0::mmsql::Result Variable::insert(cave0::mmsql::Connection& conn)
        {
            RandomString ranstr(32,RandomString::md5);
            ranstr.generate();
            return conn.insert("name,value,session","'" + name + "','" + value + "','" + (const char*)ranstr + "'" ,table());
        }
        cave0::mmsql::Result Variable::upName(cave0::mmsql::Connection& conn)
        {
            return conn.update("name = '" + name + "'", table());
        }
        cave0::mmsql::Result Variable::upValue(cave0::mmsql::Connection& conn)
        {
            return conn.update("value = '" + value + "'", table());
        }
        cave0::mmsql::Result Variable::upSession(cave0::mmsql::Connection& conn)
        {
            return conn.update("session = '" + session + "'", table());
        }
        bool Variable::downValue(cave0::mmsql::Connection& conn)
        {
            cave0::mmsql::Result rs = conn.select("value", table(),"session = " + session);
            if(rs.size() > 0)
            {
                value = rs.next()[0];
                return true;
            }

            return false;
        }


        CatalogItem::CatalogItem(const char** s)
        {
            id = std::atoll(s[0]);
            catalog = std::atoll(s[1]);
            number = s[2];
            brief = s[3];
            if(strcmp(s[4],"Y") == 0) active = true;
            else if(strcmp(s[4],"N") == 0) active = false;
            else active = false;
            value = std::atof(s[5]);
            type = std::atoi(s[6]);
        }
        CatalogItem::CatalogItem(const cave0::Row<char,cave0::mmsql::Data>& s)
        {
            id = std::atoll(s[0]);
            catalog = std::atoll(s[1]);
            number = s[2];
            brief = s[3];
            if(strcmp(s[4],"Y") == 0) active = true;
            else if(strcmp(s[4],"N") == 0) active = false;
            else active = false;
            value = std::atof(s[5]);
            type = std::atoi(s[6]);
        }
        CatalogItem::CatalogItem(const cave1::Row<char,cave1::mmsql::Data>& s)
        {
            id = std::atoll(s[0]);
            catalog = std::atoll(s[1]);
            number = s[2];
            brief = s[3];
            if(strcmp(s[4],"Y") == 0) active = true;
            else if(strcmp(s[4],"N") == 0) active = false;
            else active = false;
            value = std::atof(s[5]);
            type = std::atoi(s[6]);
        }
        CatalogItem::CatalogItem(const CatalogItem& s) : id(s.id),catalog(s.catalog),number(s.number),brief(s.brief),active(s.active),value(s.value),type(s.type)
        {
        }
        std::string CatalogItem::fields()
        {
            return "id,catalog,number,brief,active,value,presentation,type";
        }
        std::string CatalogItem::table()
        {
            return "CatalogItem";
        }

    CatalogItem& CatalogItem::operator =(const char** s)
	{
        id = std::atoll(s[0]);
        catalog = std::atoll(s[1]);
        number = s[2];
        brief = s[3];
        if(strcmp(s[4],"Y") == 0) active = true;
        else if(strcmp(s[4],"N") == 0) active = false;
        else active = false;
        value = std::atof(s[5]);
        type = std::atoi(s[6]);

		return *this;
	}
	/*std::string CatalogItem::insert_values()const
	{
	    std::string vals;
	    vals += "'" + name + "'";
	    vals += "," + std::to_string(major);
	    vals += "," + std::to_string(minor);

        return vals;
	}*/
	/*std::string CatalogItem::update_values()const
	{
	    std::string vals;
	    vals += "name = '" + name + "'";
	    vals += ",major = " + std::to_string(major);
	    vals += ",minor = " + std::to_string(minor);

        return vals;
	}*/
	std::string CatalogItem::update_values(const std::initializer_list<size_t>& list)const
	{
	    std::vector<std::string> vals(3);
	    vals[0] = "catalog = " + std::to_string(catalog);
	    vals[1] = "number = '" + number + "'";
	    vals[2] = "brief = '" + brief + "'";
	    vals[3] = "active = " + std::to_string(active);
	    vals[4] = "value = " + std::to_string(value);
	    vals[5] = "presentation = " + presentation + "'";
	    vals[6] = "type = " + std::to_string(type);

        std::string str;
        str = vals[std::data(list)[0]];
        for(size_t i = 1; i < list.size(); i++)
        {
            str += "," + vals[std::data(list)[i]];
        }

        return str;
	}
	std::string CatalogItem::select_fields()
	{
        return "id,catalog,number,brief,active,value,presentation,type";
	}
	std::string CatalogItem::select_fields(const std::initializer_list<size_t>& list)
	{
	    std::vector<std::string> vals(3);
	    vals[0] = "id";
	    vals[1] = "catalog ";
	    vals[2] = "number";
	    vals[3] = "brief";
	    vals[4] = "active";
	    vals[5] = "value";
	    vals[6] = "presentation";
	    vals[7] = "type";

        std::string str;
        str = vals[std::data(list)[0]];
        for(size_t i = 1; i < list.size(); i++)
        {
            str += "," + vals[std::data(list)[i]];
        }

        return str;
	}
	std::string CatalogItem::insert_fields()
	{
        return "catalog,number,brief,active,value,presentation,type";
	}
	std::string CatalogItem::identifier_name()
	{
        return "id";
	}
	std::string CatalogItem::identifier_value() const
	{
        return std::to_string(id);
	}


    const std::filesystem::path Configuration::configure_directory = ".muposys";
#ifdef MUPOSYS_CORE_V1_TDD
    const std::filesystem::path Configuration::configure_file = "config";
#elif
    const std::filesystem::path Configuration::configure_file = "config-dev";
#endif // MUPOSYS_CORE_V1_TDD

	Configuration::Configuration() : root(config.getRoot())
	{
	}
	Configuration::Configuration(const std::filesystem::path& p) : root(config.getRoot())
	{
	    if(not std::filesystem::exists(p)) read(p);
	    else create(p);
	}
	std::filesystem::path Configuration::create()
	{
        std::filesystem::path fullname = defaul_file();

        if(std::filesystem::exists(fullname))
        {
            read(fullname);
            return fullname;
        }
        else
        {
            return create(fullname);
        }
	}
    std::filesystem::path Configuration::create(const std::filesystem::path& fullname)
	{
            //
            root.add("name", libconfig::Setting::TypeString) = "muposys";
            root.add("decorated", libconfig::Setting::TypeString) = "Multi-Porpuse Software System";

            //version
            libconfig::Setting &version = root.add("version", libconfig::Setting::TypeGroup);
            version.add("major", libconfig::Setting::TypeInt) = 1;
            version.add("minor", libconfig::Setting::TypeInt) = 0;
            version.add("patch", libconfig::Setting::TypeInt) = 0;
            version.add("prerelease", libconfig::Setting::TypeString) = "alpha";
            version.add("build", libconfig::Setting::TypeString) = "v1";

            //database
            libconfig::Setting &database = root.add("database", libconfig::Setting::TypeGroup);
            libconfig::Setting &mmsql = database.add("mmsql", libconfig::Setting::TypeGroup);
            mmsql.add("host", libconfig::Setting::TypeString) = "localhost";
            mmsql.add("user", libconfig::Setting::TypeString) = "muposys";
            mmsql.add("database", libconfig::Setting::TypeString) = "muposys";
            mmsql.add("password", libconfig::Setting::TypeString) = "123456";
            mmsql.add("port", libconfig::Setting::TypeInt) = 3306;
            mmsql.add("flags", libconfig::Setting::TypeInt) = 0;

            config.writeFile(fullname.c_str());

        return fullname;
	}
    std::filesystem::path Configuration::create(const std::filesystem::path& fullname,const std::string& server)
	{
	    std::filesystem::path p = create(fullname);
        libconfig::Setting &database = root.add("database", libconfig::Setting::TypeGroup);
        libconfig::Setting &mmsql = database.add("mmsql", libconfig::Setting::TypeGroup);
        mmsql.add("host", libconfig::Setting::TypeString) = server;

        return fullname;
	}
	std::filesystem::path Configuration::create(const std::filesystem::path& p,const Version& v,const cave1::mmsql::Data& d)
	{
            root.add("name", libconfig::Setting::TypeString) = "muposys";

            //version
            libconfig::Setting &version = root.add("version", libconfig::Setting::TypeGroup);
            version.add("major", libconfig::Setting::TypeInt) = v.major;
            version.add("minor", libconfig::Setting::TypeInt) = v.minor;
            version.add("patch", libconfig::Setting::TypeInt) = v.patch;
            version.add("prerelease", libconfig::Setting::TypeString) = v.prerelease;
            version.add("build", libconfig::Setting::TypeString) = v.build;

            //database
            libconfig::Setting &database = root.add("database", libconfig::Setting::TypeGroup);
            libconfig::Setting &mmsql = database.add("mmsql", libconfig::Setting::TypeGroup);
            mmsql.add("host", libconfig::Setting::TypeString) = d.get_host();
            mmsql.add("user", libconfig::Setting::TypeString) = "muposys";
            mmsql.add("database", libconfig::Setting::TypeString) = "muposys";
            mmsql.add("password", libconfig::Setting::TypeString) = "123456";
            mmsql.add("port", libconfig::Setting::TypeInt) = 3306;
            mmsql.add("flags", libconfig::Setting::TypeInt) = 0;

            return p;
	}
	std::filesystem::path Configuration::create(const std::filesystem::path& p,const Version& v,const cave0::mmsql::Data& d)
	{
            root.add("name", libconfig::Setting::TypeString) = "muposys";

            //version
            libconfig::Setting &version = root.add("version", libconfig::Setting::TypeGroup);
            version.add("major", libconfig::Setting::TypeInt) = v.major;
            version.add("minor", libconfig::Setting::TypeInt) = v.minor;
            version.add("patch", libconfig::Setting::TypeInt) = v.patch;
            version.add("prerelease", libconfig::Setting::TypeString) = v.prerelease;
            version.add("build", libconfig::Setting::TypeString) = v.build;

            //database
            libconfig::Setting &database = root.add("database", libconfig::Setting::TypeGroup);
            libconfig::Setting &mmsql = database.add("mmsql", libconfig::Setting::TypeGroup);
            mmsql.add("host", libconfig::Setting::TypeString) = d.get_host();
            mmsql.add("user", libconfig::Setting::TypeString) = "muposys";
            mmsql.add("database", libconfig::Setting::TypeString) = "muposys";
            mmsql.add("password", libconfig::Setting::TypeString) = "123456";
            mmsql.add("port", libconfig::Setting::TypeInt) = 3306;
            mmsql.add("flags", libconfig::Setting::TypeInt) = 0;

            return p;
	}


    void Configuration::get_name(std::string& str) const
    {
        str = (std::string)config.lookup("name");
    }
    void Configuration::get_decorated(std::string& str) const
    {
        str = (std::string)config.lookup("decorated");
    }
    void Configuration::get_version(Version& v)const
    {
        const libconfig::Setting &root = config.getRoot();
        const libconfig::Setting &version = root["version"];
        v.major = version.lookup("major");
        v.minor = version.lookup("minor");
        v.patch = version.lookup("patch");
        v.prerelease = (std::string)version.lookup("prerelease");
        v.build = (std::string)version.lookup("build");

    }
    std::filesystem::path Configuration::read(const std::filesystem::path& p)
    {
        config.readFile(p);
        return p;
    }
    std::filesystem::path Configuration::defaul_file()
    {
	    //home directory
        struct passwd *pw = getpwuid(getuid());
        std::filesystem::path home = pw->pw_dir;

        //configure directory
        return home/configure_directory/configure_file;
    }
    std::filesystem::path Configuration::defaul_derectory()
    {
	    //home directory
        struct passwd *pw = getpwuid(getuid());
        std::filesystem::path home = pw->pw_dir;

        //configure directory
        return home/configure_directory;
    }
    void Configuration::get_datasource(cave1::mmsql::Data& data)const
    {
        libconfig::Setting &database = root.add("database", libconfig::Setting::TypeGroup);
        libconfig::Setting &mmsql = database.add("mmsql", libconfig::Setting::TypeGroup);
        data.set((std::string)mmsql.lookup("host"),(std::string)mmsql.lookup("user"),(std::string)mmsql.lookup("password"),(std::string)mmsql.lookup("database"),(unsigned int)mmsql.lookup("port"));
    }
    void Configuration::get_datasource(cave0::mmsql::Data& data)const
    {
        /*libconfig::Setting &database = root.add("database", libconfig::Setting::TypeGroup);
        libconfig::Setting &mmsql = database.add("mmsql", libconfig::Setting::TypeGroup);
        data.set((std::string)mmsql.lookup("host"),(std::string)mmsql.lookup("user"),(std::string)mmsql.lookup("password"),(std::string)mmsql.lookup("database"),(unsigned int)mmsql.lookup("port"));*/
    }



    //const char* name = "muposys";
    //const char* decorated = "Systema Software de Multi-Proposito";

    std::string get_name()
    {
        Configuration config;
        config.create();
        std::string n;

        //read from database


        //read from config file
        try
        {
            config.get_name(n);
            return n;
        }
        catch(const libconfig::SettingNotFoundException &nfex)
        {

        }

        //valor por default
        return name;
    }
    std::string get_decorated()
    {
        Configuration config;
        config.create();
        std::string n;

        //read from database


        //read from config file
        try
        {
            config.get_decorated(n);
            return n;
        }
        catch(const libconfig::SettingNotFoundException &nfex)
        {

        }

        //valor por default
        return decorated;
    }
}
