
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
    cave0::mmsql::Data default_dtm()
    {
#ifdef MUPOSYS_CORE_V1_TDD
        return cave0::mmsql::Data ("localhost","develop","123456", "muposys-dev", 3306);
#else
        return cave0::mmsql::Data("localhost","muposys","123456", "muposys", 3306);
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

}
