#include <mysql/mysql.h>
#include "sysappdb.hpp"

namespace sysappdb
{


	const std::string Persons::TABLE_NAME = "`Persons`";
	const std::string& Persons::getCountry() const
	{
		return country;
	}
	std::string Persons::getCountryString() const 
	{
		return country;
	}
	bool Persons::updateCountry(octetos::db::mysql::Connector& connector,const std::string& country)
	{
		std::string sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET country = '" + country + "'";
		sqlString = sqlString + " WHERE "  + "id = " +  std::to_string(id);
		octetos::db::mysql::Datresult dt56239;
		return connector.execute(sqlString,dt56239);
	}
	int Persons::getID() const
	{
		return id;
	}
	int Persons::getKeyID() const
	{
		return id;
	}
	std::string Persons::getIDString() const 
	{
		return std::to_string(id);
	}
	const std::string& Persons::getName1() const
	{
		return name1;
	}
	std::string Persons::getName1String() const 
	{
		return name1;
	}
	bool Persons::updateName1(octetos::db::mysql::Connector& connector,const std::string& name1)
	{
		std::string sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET name1 = '" + name1 + "'";
		sqlString = sqlString + " WHERE "  + "id = " +  std::to_string(id);
		octetos::db::mysql::Datresult dt56239;
		return connector.execute(sqlString,dt56239);
	}
	const std::string& Persons::getName2() const
	{
		return name2;
	}
	std::string Persons::getName2String() const 
	{
		return name2;
	}
	bool Persons::updateName2(octetos::db::mysql::Connector& connector,const std::string& name2)
	{
		std::string sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET name2 = '" + name2 + "'";
		sqlString = sqlString + " WHERE "  + "id = " +  std::to_string(id);
		octetos::db::mysql::Datresult dt56239;
		return connector.execute(sqlString,dt56239);
	}
	const std::string& Persons::getName3() const
	{
		return name3;
	}
	std::string Persons::getName3String() const 
	{
		return name3;
	}
	bool Persons::updateName3(octetos::db::mysql::Connector& connector,const std::string& name3)
	{
		std::string sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET name3 = '" + name3 + "'";
		sqlString = sqlString + " WHERE "  + "id = " +  std::to_string(id);
		octetos::db::mysql::Datresult dt56239;
		return connector.execute(sqlString,dt56239);
	}
	const std::string& Persons::getName4() const
	{
		return name4;
	}
	std::string Persons::getName4String() const 
	{
		return name4;
	}
	bool Persons::updateName4(octetos::db::mysql::Connector& connector,const std::string& name4)
	{
		std::string sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET name4 = '" + name4 + "'";
		sqlString = sqlString + " WHERE "  + "id = " +  std::to_string(id);
		octetos::db::mysql::Datresult dt56239;
		return connector.execute(sqlString,dt56239);
	}
	Persons::Persons(int id)
	{
		this->id = id;
	}
	Persons::Persons(const Persons& obj)
	{
		this->country = obj.country;
		this->id = obj.id;
		this->name1 = obj.name1;
		this->name2 = obj.name2;
		this->name3 = obj.name3;
		this->name4 = obj.name4;
	}
	Persons::Persons()
	{
	}
	bool Persons::insert(octetos::db::mysql::Connector& connector,std::string name1)
	{
		octetos::db::mysql::Datresult dt;
		std::string sqlString = "";
		sqlString = sqlString + "INSERT INTO " + TABLE_NAME ; 
		sqlString = sqlString + "(name1)";
		sqlString = sqlString + " VALUES(" + "'" + name1 + "'"  + ")";
		this->id =  connector.insert(sqlString,dt);
		if(this->id > 0) return true;
		else return false;
		return false;
	}
	std::vector<Persons*>* Persons::select(octetos::db::mysql::Connector& connector, const std::string& where, int leng)
	{
		std::string sqlString = "SELECT id FROM Persons WHERE " + where ;
		if(leng > 0)
		{
			sqlString += " LIMIT  "  + std::to_string(leng);
		}
		octetos::db::mysql::Datresult dt;
		bool flag = connector.execute(sqlString,dt);
		if(flag)
		{
			std::vector<Persons*>* tmpVc = new std::vector<Persons*>;
			while(dt.nextRow())
			{
				Persons* tmp = NULL;
				tmp = new Persons(dt.getint(0));
				tmpVc->push_back(tmp);
			}
			return tmpVc;
		}
		return NULL;
	}



	const std::string Users::TABLE_NAME = "`Users`";
	const std::string& Users::getName() const
	{
		return name;
	}
	std::string Users::getNameString() const 
	{
		return name;
	}
	bool Users::updateName(octetos::db::mysql::Connector& connector,const std::string& name)
	{
		std::string sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET name = '" + name + "'";
		sqlString = sqlString + " WHERE "  + "person = " +  std::to_string(person);
		octetos::db::mysql::Datresult dt56239;
		return connector.execute(sqlString,dt56239);
	}
	int Users::getPerson() const
	{
		return person;
	}
	int Users::getKeyPerson() const
	{
		return person;
	}
	std::string Users::getPersonString() const 
	{
		return std::to_string(person);
	}
	const std::string& Users::getPwdtxt() const
	{
		return pwdtxt;
	}
	std::string Users::getPwdtxtString() const 
	{
		return pwdtxt;
	}
	bool Users::updatePwdtxt(octetos::db::mysql::Connector& connector,const std::string& pwdtxt)
	{
		std::string sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET pwdtxt = '" + pwdtxt + "'";
		sqlString = sqlString + " WHERE "  + "person = " +  std::to_string(person);
		octetos::db::mysql::Datresult dt56239;
		return connector.execute(sqlString,dt56239);
	}
	Users::Users(int person)
	{
		this->person = person;
	}
	Users::Users(const Users& obj)
	{
		this->name = obj.name;
		this->person = obj.person;
		this->pwdtxt = obj.pwdtxt;
	}
	Users::Users()
	{
	}
	bool Users::insert(octetos::db::mysql::Connector& connector,std::string name)
	{
		octetos::db::mysql::Datresult dt;
		std::string sqlString = "";
		sqlString = sqlString + "INSERT INTO " + TABLE_NAME ; 
		sqlString = sqlString + "(name)";
		sqlString = sqlString + " VALUES(" + "'" + name + "'"  + ")";
		this->person =  connector.insert(sqlString,dt);
		if(this->person > 0) return true;
		else return false;
		return false;
	}
	bool Users::checkpass(octetos::db::mysql::Connector& connector)
	{ 
		std::string sqlString = "SELECT name,pwdtxt FROM Users WHERE person = '" + std::to_string(person) + "'";
		octetos::db::mysql::Datresult dt;
		bool flag = connector.execute(sqlString,dt);
		if(flag)
		{

			while (dt.nextRow()) 
			{
					this->name =  dt.getString(0);
					this->pwdtxt =  dt.getString(1);
			}
			return true;
		}
		else
		{
			return false;
		}
	} 
	std::vector<Users*>* Users::select(octetos::db::mysql::Connector& connector, const std::string& where, int leng)
	{
		std::string sqlString = "SELECT person FROM Users WHERE " + where ;
		if(leng > 0)
		{
			sqlString += " LIMIT  "  + std::to_string(leng);
		}
		octetos::db::mysql::Datresult dt;
		bool flag = connector.execute(sqlString,dt);
		if(flag)
		{
			std::vector<Users*>* tmpVc = new std::vector<Users*>;
			while(dt.nextRow())
			{
				Users* tmp = NULL;
				tmp = new Users(dt.getint(0));
				tmpVc->push_back(tmp);
			}
			return tmpVc;
		}
		return NULL;
	}




}

