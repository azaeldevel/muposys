
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
    cave0::mmsql::Data default_dtm0()
    {
#ifdef OCTETOS_MUPOSYS_V1_TDD
        return cave0::mmsql::Data ("localhost","develop","123456", "muposys-dev", 3306);
#else
        return cave0::mmsql::Data("localhost","muposys","mps-v1-896", "muposys", 3306);
#endif
    }
    cave1::mmsql::Data default_dtm1()
    {
#ifdef OCTETOS_MUPOSYS_V1_TDD
        return cave1::mmsql::Data ("localhost","develop","123456", "muposys-dev", 3306);
#else
        return cave1::mmsql::Data("localhost","muposys","mps-v1-896", "muposys", 3306);
#endif
    }
    cave::mmsql::Data default_dtm()
    {
#ifdef MUPOSYS_CORE_V1_TDD
        return cave::mmsql::Data ("localhost","develop","123456", "muposys-dev", 3306);
#else
        return cave::mmsql::Data("localhost","muposys","mps-v1-896", "muposys", 3306);
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
            id = std::atoll(s[0]);
            person.id = std::atoll(s[1]);
            name = s[2];
        }
        User::User(cave0::Row<char,cave0::mmsql::Data> s)
        {
            id = std::atoll(s[0]);
            person.id = std::atoll(s[1]);
            name = s[2];
        }
        User::User(cave1::Row<char,cave1::mmsql::Data> s)
        {
            id = std::atoll(s[0]);
            person.id = std::atoll(s[1]);
            name = s[2];
        }
        User::User(const User& u) : valid(u.valid),id(u.id),person(u.person),name(u.name)
        {
        }


        std::string User::fields()
        {
            return "id,person,name";
        }

        std::string User::table()
        {
            return "User";
        }

    User& User::operator =(const char** s)
	{
        id = std::atoll(s[0]);
        person.id = std::atoll(s[1]);
        name = s[2];

		return *this;
	}

	std::string User::update_values(const std::initializer_list<size_t>& list)const
	{
	    std::vector<std::string> vals(3);
	    vals[0] = "id = " + std::to_string(id);
	    vals[1] = "person = '" + std::to_string(person.id) + "'";
	    vals[2] = "name = '" + name + "'";

        std::string str;
        str = vals[std::data(list)[0]];
        for(size_t i = 1; i < list.size(); i++)
        {
            str += "," + vals[std::data(list)[i]];
        }

        return str;
	}
	std::string User::select_fields()
	{
        return "id,person,name";
	}
	std::string User::select_fields(const std::initializer_list<size_t>& list)
	{
	    std::vector<std::string> vals(3);
	    vals[0] = "id";
	    vals[1] = "person ";
	    vals[2] = "name";

        std::string str;
        str = vals[std::data(list)[0]];
        for(size_t i = 1; i < list.size(); i++)
        {
            str += "," + vals[std::data(list)[i]];
        }

        return str;
	}
	std::string User::insert_fields()
	{
        return "person,name";
	}
	std::string User::identifier_name()
	{
        return "id";
	}
	std::string User::identifier_value() const
	{
        return std::to_string(id);
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

    //AppData\Local\Microsoft\WindowsApps
    //const std::filesystem::path Configuration::configure_directory = ".muposys";
#ifdef OCTETOS_MUPOSYS_V1_TDD
    const std::filesystem::path Configuration::configure_file = "config-dev";
#else
    const std::filesystem::path Configuration::configure_file = "config";
#endif // MUPOSYS_CORE_V1_TDD

    std::filesystem::path Configuration::muposys_directory()
    {
        if(core::get_platform_type() == core::platform_type::linux)
        {
            return ".muposys";
        }
        else if(core::get_platform_type() == core::platform_type::linux)
        {
            return L"AppData/Local/muposys";
        }

        return "";
    }
	Configuration::Configuration()
	{
	}
	Configuration::Configuration(const std::filesystem::path& p) : core::Configuration(p)
	{
	    if(std::filesystem::exists(p)) open(p);
	    else create(p);
	}

	void Configuration::create()
	{
        std::filesystem::path fullname = defaul_file();
        //std::cout << fullname << "\n";
        if(std::filesystem::exists(fullname))
        {
            open(fullname);
        }
        else
        {
            if(std::filesystem::exists(defaul_derectory()))
            {
            }
            else
            {
                std::filesystem::create_directory(defaul_derectory());
            }

            return create(fullname);
        }
	}
    void Configuration::create(const std::filesystem::path& fullname)
	{
	    //std::cout << "archivo :" << fullname << "\n";
	    core::Configuration::create(fullname);
	    libconfig::Setting &root = getRoot();

	    libconfig::Setting &name_setting = lookup("name");
#ifdef OCTETOS_MUPOSYS_V1_TDD
        name_setting = "muposys(dev)";
#else
        name_setting = "muposys";
#endif
        root.add("decorated", libconfig::Setting::TypeString) = "Multi-Porpuse Software System";

        //version
        core::Semver version = get_version();
        version.major = 1;
        version.minor = 0;
        version.patch = 0;
        version.prerelease = "alpha";
        version.build = "v1";
        core::Configuration::write(version);

        //database
        libconfig::Setting &database = root.add("database", libconfig::Setting::TypeGroup);
        libconfig::Setting &mmsql = database.add("mmsql", libconfig::Setting::TypeGroup);
        mmsql.add("host", libconfig::Setting::TypeString) = "localhost";
        mmsql.add("port", libconfig::Setting::TypeInt) = 3306;
        mmsql.add("flags", libconfig::Setting::TypeInt) = 0;
#ifdef OCTETOS_MUPOSYS_V1_TDD
        mmsql.add("database", libconfig::Setting::TypeString) = "muposys-dev";
        mmsql.add("user", libconfig::Setting::TypeString) = "develop";
        mmsql.add("password", libconfig::Setting::TypeString) = "123456";
#else
        mmsql.add("database", libconfig::Setting::TypeString) = "muposys";
        mmsql.add("user", libconfig::Setting::TypeString) = "muposys";
        mmsql.add("password", libconfig::Setting::TypeString) = "mps-v1-896";
#endif


        save(fullname);
        open(fullname);
	}
    void Configuration::create(const std::filesystem::path& fullname,const std::string& server)
	{
	    create(fullname);
	    libconfig::Setting &root = getRoot();
        libconfig::Setting &mmsql = root.lookup("database")["mmsql"];
        mmsql["host"] = server;
	}
	void Configuration::create(const std::filesystem::path& p,const core::Semver& v,const cave1::mmsql::Data& dt)
	{
	    create(p);

        core::Configuration::write(v);
        write(dt);
	}

    const std::string& Configuration::get_decorated() const
    {
        return decorated;
    }

    std::filesystem::path Configuration::defaul_derectory()
    {
        std::filesystem::path home = core::get_user_directory();

        //configure directory
        return home/muposys_directory();
    }
    cave1::mmsql::Data Configuration::get_datasource()const
    {
        libconfig::Setting &mmsql = lookup("database")["mmsql"];
        //std::string str;
        cave1::mmsql::Data data;
        //str = (std::string)mmsql.lookup("host");
        //std::cout << "Host :" << str << "\n";
        data.set((std::string)mmsql.lookup("host"),(std::string)mmsql.lookup("user"),(std::string)mmsql.lookup("password"),(std::string)mmsql.lookup("database"),(int)mmsql.lookup("port"));

        return data;
    }
    void Configuration::write(const cave1::mmsql::Data& dt)
    {
	    libconfig::Setting &root = getRoot();
        libconfig::Setting &mmsql = root.lookup("database")["mmsql"];

        mmsql["host"] = dt.get_host().c_str();
        libconfig::Setting &user = mmsql["user"];
        user = dt.get_user().c_str();
        libconfig::Setting &port = mmsql["port"];
        port = (int)dt.get_port();
        libconfig::Setting &password = mmsql["password"];
        password = dt.get_password().c_str();
        libconfig::Setting &database = mmsql["database"];
        database = dt.get_database().c_str();
    }
    void Configuration::open()
    {
        core::Configuration::open(defaul_file());
    }
    void Configuration::open(const std::filesystem::path& p)
    {
        core::Configuration::open(p);
    }
    std::filesystem::path Configuration::defaul_file()
    {
        std::filesystem::path workdir;
#ifdef OCTETOS_MUPOSYS_V1_TDD
        workdir /= "bin";
        workdir /= "Debug";
        workdir /= configure_file;
#else
        workdir /= configure_file;
#endif // OCTETOS_MUPOSYS_V1_TDD
        //std::cout << "configure_file : " << workdir << "\n";
        return workdir;
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
            n = config.get_name();
            return n;
        }
        catch(const libconfig::SettingNotFoundException &nfex)
        {

        }

#ifdef OCTETOS_MUPOSYS_V1_TDD
            return "muposys(dev)";
#else
            return "muposys";
#endif // OCTETOS_MUPOSYS_V1_TDD
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
            n = config.get_decorated();
            return n;
        }
        catch(const libconfig::SettingNotFoundException &nfex)
        {

        }

        //valor por default
        return "Multi-Porpuse Software System";
    }
}
