#if defined LINUX_ARCH
	#include <mysql/mysql.h>
#elif defined LINUX_GENTOO
	#include <mariadb/mysql.h>
#elif defined LINUX_DEBIAN
	#include <mariadb/mysql.h>
#elif defined WINDOWS_MINGW && defined BUILDING_DLL
	#include <mariadb/mysql.h>
#else
	#error "Plataforma desconocida."
#endif
#include "muposysdb.hpp"

namespace muposysdb
{


	const std::string Entities::TABLE_NAME = "`Entities`";
	Entities::Entities()
	{
	}
	Entities::Entities(int id)
	{
		this->id = id;
	}
	Entities::Entities(const Entities& obj)
	{
		this->id = obj.id;
		this->md5sum = obj.md5sum;
	}


	int Entities::getID() const 
	{
		return id;
	}
	const std::string& Entities::getMd5sum() const 
	{
		return md5sum;
	}


	bool Entities::updateMd5sum(octetos::db::maria::Connector& connector,const std::string& md5sum)
	{
		std::string sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET md5sum = '" + md5sum + "'";
		sqlString = sqlString + " WHERE id = " + std::to_string(id);
		octetos::db::maria::Datresult dat;
		return connector.update(sqlString,dat);
	}


	bool Entities::insert(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "";
		sqlString = sqlString + "INSERT INTO " + TABLE_NAME ; 
		sqlString = sqlString + "()";
		sqlString = sqlString + " VALUES(" + ")";
		octetos::db::maria::Datresult dt;
		std::cout << sqlString << std::endl;
		if(connector.insert(sqlString,dt))
		{
			id = connector.last_inserted_id();
			if(id > 0) return true;
		}
		return false;
	}


	bool Entities::select(octetos::db::maria::Connector& connector,int id)
	{
		std::string sql = "SELECT  id";
		sql = sql + " FROM " + TABLE_NAME  + " WHERE id = " + std::to_string(id);
		octetos::db::maria::Datresult dat;
		bool retflag = connector.select(sql,dat);
		if(retflag)
		{
			this->id = id;
		}
		return retflag;
	}
	std::vector<Entities*>* Entities::select(octetos::db::maria::Connector& connector, const std::string& where, int leng)
	{
		std::string sqlString = "SELECT id FROM Entities WHERE ";
		sqlString += where;
		if(leng > 0)
		{
			sqlString += " LIMIT  ";
			sqlString += std::to_string(leng);
 		}
		octetos::db::maria::Datresult dt;
		bool flag = connector.execute(sqlString,dt);
		if(flag)
		{
			std::vector<Entities*>* tmpVc = new std::vector<Entities*>;
			while(dt.nextRow())
			{
				Entities* tmp = NULL;
				tmp = new Entities(dt.getint(0));
				tmpVc->push_back(tmp);
			}
			return tmpVc;
		}
		return NULL;
	}


	bool Entities::downMd5sum(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT md5sum ";
		sqlString = sqlString + " FROM Entities WHERE ";
		sqlString = sqlString + "id = " + std::to_string(id);
		octetos::db::maria::Datresult dt;
		bool flag = connector.execute(sqlString,dt);
		if(flag)
		{
			md5sum = dt.getString(0);
			return true;
		}
		return false;
	}




	const std::string Persons::TABLE_NAME = "`Persons`";
	Persons::Persons()
	{
	}
	Persons::Persons(int person)
	{
		this->person = new Entities(person);
	}
	Persons::Persons(const Persons& obj)
	{
		this->age = obj.age;
		this->canyonLength = obj.canyonLength;
		this->canyonNumber = obj.canyonNumber;
		this->gender = obj.gender;
		this->name1 = obj.name1;
		this->name2 = obj.name2;
		this->name3 = obj.name3;
		this->name4 = obj.name4;
		this->person = obj.person;
	}


	float Persons::getAge() const 
	{
		return age;
	}
	float Persons::getCanyonLength() const 
	{
		return canyonLength;
	}
	float Persons::getCanyonNumber() const 
	{
		return canyonNumber;
	}
	const std::string& Persons::getGender() const 
	{
		return gender;
	}
	const std::string& Persons::getName1() const 
	{
		return name1;
	}
	const std::string& Persons::getName2() const 
	{
		return name2;
	}
	const std::string& Persons::getName3() const 
	{
		return name3;
	}
	const std::string& Persons::getName4() const 
	{
		return name4;
	}
	const Entities& Persons::getPerson() const 
	{
		return *person;
	}


	bool Persons::updateAge(octetos::db::maria::Connector& connector,float age)
	{
		std::string sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET age = " + std::to_string(age);
		sqlString = sqlString + " WHERE person = " + std::to_string((*person).getID());
		octetos::db::maria::Datresult dat;
		return connector.update(sqlString,dat);
	}
	bool Persons::updateCanyonLength(octetos::db::maria::Connector& connector,float canyonLength)
	{
		std::string sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET canyonLength = " + std::to_string(canyonLength);
		sqlString = sqlString + " WHERE person = " + std::to_string((*person).getID());
		octetos::db::maria::Datresult dat;
		return connector.update(sqlString,dat);
	}
	bool Persons::updateCanyonNumber(octetos::db::maria::Connector& connector,float canyonNumber)
	{
		std::string sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET canyonNumber = " + std::to_string(canyonNumber);
		sqlString = sqlString + " WHERE person = " + std::to_string((*person).getID());
		octetos::db::maria::Datresult dat;
		return connector.update(sqlString,dat);
	}
	bool Persons::updateGender(octetos::db::maria::Connector& connector,const std::string& gender)
	{
		std::string sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET gender = '" + gender + "'";
		sqlString = sqlString + " WHERE person = " + std::to_string((*person).getID());
		octetos::db::maria::Datresult dat;
		return connector.update(sqlString,dat);
	}
	bool Persons::updateName1(octetos::db::maria::Connector& connector,const std::string& name1)
	{
		std::string sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET name1 = '" + name1 + "'";
		sqlString = sqlString + " WHERE person = " + std::to_string((*person).getID());
		octetos::db::maria::Datresult dat;
		return connector.update(sqlString,dat);
	}
	bool Persons::updateName2(octetos::db::maria::Connector& connector,const std::string& name2)
	{
		std::string sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET name2 = '" + name2 + "'";
		sqlString = sqlString + " WHERE person = " + std::to_string((*person).getID());
		octetos::db::maria::Datresult dat;
		return connector.update(sqlString,dat);
	}
	bool Persons::updateName3(octetos::db::maria::Connector& connector,const std::string& name3)
	{
		std::string sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET name3 = '" + name3 + "'";
		sqlString = sqlString + " WHERE person = " + std::to_string((*person).getID());
		octetos::db::maria::Datresult dat;
		return connector.update(sqlString,dat);
	}
	bool Persons::updateName4(octetos::db::maria::Connector& connector,const std::string& name4)
	{
		std::string sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET name4 = '" + name4 + "'";
		sqlString = sqlString + " WHERE person = " + std::to_string((*person).getID());
		octetos::db::maria::Datresult dat;
		return connector.update(sqlString,dat);
	}


	bool Persons::insert(octetos::db::maria::Connector& connector,const std::string& name1)
	{
		this->person = new Entities();
		if(person->insert(connector) == false) return false;
		std::string sqlString = "";
		sqlString = sqlString + "INSERT INTO " + TABLE_NAME ; 
		sqlString = sqlString + "(person,name1)";
		sqlString = sqlString + " VALUES(" + std::to_string((*person).getID()) + ","  + "'" + name1 + "'" + ")";
		octetos::db::maria::Datresult dt;
		std::cout << sqlString << std::endl;
		if(connector.insert(sqlString,dt)) return true;
		return false;
	}


	bool Persons::select(octetos::db::maria::Connector& connector,const Entities& person)
	{
		std::string sql = "SELECT  person";
		sql = sql + " FROM " + TABLE_NAME  + " WHERE person = " + std::to_string(person.getID());
		octetos::db::maria::Datresult dat;
		bool retflag = connector.select(sql,dat);
		if(retflag)
		{
			this->person = new Entities(person);
		}
		return retflag;
	}
	std::vector<Persons*>* Persons::select(octetos::db::maria::Connector& connector, const std::string& where, int leng)
	{
		std::string sqlString = "SELECT person FROM Persons WHERE ";
		sqlString += where;
		if(leng > 0)
		{
			sqlString += " LIMIT  ";
			sqlString += std::to_string(leng);
 		}
		octetos::db::maria::Datresult dt;
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
	std::vector<Persons*>* Persons::selectByName(octetos::db::maria::Connector& connector,const std::string& name1,const std::string& name2, int leng)
	{
		std::string sqlString = "SELECT person FROM Persons WHERE ";
		sqlString = sqlString + "name1 = " + "'" + name1 + "'" + " and ";
		sqlString = sqlString + "name2 = " + "'" + name2 + "'";
		if(leng > 0)
		{
			sqlString += " LIMIT  " + std::to_string(leng);
		}
		octetos::db::maria::Datresult dt;
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
		else
		{
			return NULL;
		}
	}


	bool Persons::downAge(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT age ";
		sqlString = sqlString + " FROM Persons WHERE ";
		sqlString = sqlString + "person = " +  "'" + std::to_string((*person).getID()) + "'";
		octetos::db::maria::Datresult dt;
		bool flag = connector.execute(sqlString,dt);
		if(flag)
		{
			age = dt.getfloat(0);
			return true;
		}
		return false;
	}
	bool Persons::downCanyonLength(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT canyonLength ";
		sqlString = sqlString + " FROM Persons WHERE ";
		sqlString = sqlString + "person = " +  "'" + std::to_string((*person).getID()) + "'";
		octetos::db::maria::Datresult dt;
		bool flag = connector.execute(sqlString,dt);
		if(flag)
		{
			canyonLength = dt.getfloat(0);
			return true;
		}
		return false;
	}
	bool Persons::downCanyonNumber(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT canyonNumber ";
		sqlString = sqlString + " FROM Persons WHERE ";
		sqlString = sqlString + "person = " +  "'" + std::to_string((*person).getID()) + "'";
		octetos::db::maria::Datresult dt;
		bool flag = connector.execute(sqlString,dt);
		if(flag)
		{
			canyonNumber = dt.getfloat(0);
			return true;
		}
		return false;
	}
	bool Persons::downGender(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT gender ";
		sqlString = sqlString + " FROM Persons WHERE ";
		sqlString = sqlString + "person = " +  "'" + std::to_string((*person).getID()) + "'";
		octetos::db::maria::Datresult dt;
		bool flag = connector.execute(sqlString,dt);
		if(flag)
		{
			gender = dt.getString(0);
			return true;
		}
		return false;
	}
	bool Persons::downName1(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT name1 ";
		sqlString = sqlString + " FROM Persons WHERE ";
		sqlString = sqlString + "person = " +  "'" + std::to_string((*person).getID()) + "'";
		octetos::db::maria::Datresult dt;
		bool flag = connector.execute(sqlString,dt);
		if(flag)
		{
			name1 = dt.getString(0);
			return true;
		}
		return false;
	}
	bool Persons::downName2(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT name2 ";
		sqlString = sqlString + " FROM Persons WHERE ";
		sqlString = sqlString + "person = " +  "'" + std::to_string((*person).getID()) + "'";
		octetos::db::maria::Datresult dt;
		bool flag = connector.execute(sqlString,dt);
		if(flag)
		{
			name2 = dt.getString(0);
			return true;
		}
		return false;
	}
	bool Persons::downName3(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT name3 ";
		sqlString = sqlString + " FROM Persons WHERE ";
		sqlString = sqlString + "person = " +  "'" + std::to_string((*person).getID()) + "'";
		octetos::db::maria::Datresult dt;
		bool flag = connector.execute(sqlString,dt);
		if(flag)
		{
			name3 = dt.getString(0);
			return true;
		}
		return false;
	}
	bool Persons::downName4(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT name4 ";
		sqlString = sqlString + " FROM Persons WHERE ";
		sqlString = sqlString + "person = " +  "'" + std::to_string((*person).getID()) + "'";
		octetos::db::maria::Datresult dt;
		bool flag = connector.execute(sqlString,dt);
		if(flag)
		{
			name4 = dt.getString(0);
			return true;
		}
		return false;
	}




	const std::string Users::TABLE_NAME = "`Users`";
	Users::Users()
	{
	}
	Users::Users(int user)
	{
		this->user = new Persons(user);
	}
	Users::Users(const Users& obj)
	{
		this->name = obj.name;
		this->pwdtxt = obj.pwdtxt;
		this->status = obj.status;
		this->user = obj.user;
	}


	const std::string& Users::getName() const 
	{
		return name;
	}
	const std::string& Users::getPwdtxt() const 
	{
		return pwdtxt;
	}
	const std::string& Users::getStatus() const 
	{
		return status;
	}
	const Persons& Users::getUser() const 
	{
		return *user;
	}


	bool Users::updateName(octetos::db::maria::Connector& connector,const std::string& name)
	{
		std::string sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET name = '" + name + "'";
		sqlString = sqlString + " WHERE user = " + std::to_string((*user).getPerson().getID());
		octetos::db::maria::Datresult dat;
		return connector.update(sqlString,dat);
	}
	bool Users::updatePwdtxt(octetos::db::maria::Connector& connector,const std::string& pwdtxt)
	{
		std::string sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET pwdtxt = '" + pwdtxt + "'";
		sqlString = sqlString + " WHERE user = " + std::to_string((*user).getPerson().getID());
		octetos::db::maria::Datresult dat;
		return connector.update(sqlString,dat);
	}
	bool Users::updateStatus(octetos::db::maria::Connector& connector,const std::string& status)
	{
		std::string sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET status = '" + status + "'";
		sqlString = sqlString + " WHERE user = " + std::to_string((*user).getPerson().getID());
		octetos::db::maria::Datresult dat;
		return connector.update(sqlString,dat);
	}


	bool Users::insert(octetos::db::maria::Connector& connector,const std::string& userName1,const std::string& name)
	{
		this->user = new Persons();
		if(user->insert(connector,userName1) == false) return false;
		std::string sqlString = "";
		sqlString = sqlString + "INSERT INTO " + TABLE_NAME ; 
		sqlString = sqlString + "(user,name)";
		sqlString = sqlString + " VALUES(" + std::to_string((*user).getPerson().getID()) + ","  + "'" + name + "'" + ")";
		octetos::db::maria::Datresult dt;
		std::cout << sqlString << std::endl;
		if(connector.insert(sqlString,dt)) return true;
		return false;
	}


	bool Users::select(octetos::db::maria::Connector& connector,const Persons& user)
	{
		std::string sql = "SELECT  user";
		sql = sql + " FROM " + TABLE_NAME  + " WHERE user = " + std::to_string(user.getPerson().getID());
		octetos::db::maria::Datresult dat;
		bool retflag = connector.select(sql,dat);
		if(retflag)
		{
			this->user = new Persons(user);
		}
		return retflag;
	}
	std::vector<Users*>* Users::select(octetos::db::maria::Connector& connector, const std::string& where, int leng)
	{
		std::string sqlString = "SELECT user FROM Users WHERE ";
		sqlString += where;
		if(leng > 0)
		{
			sqlString += " LIMIT  ";
			sqlString += std::to_string(leng);
 		}
		octetos::db::maria::Datresult dt;
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
	std::vector<Users*>* Users::selecrUserByName(octetos::db::maria::Connector& connector,const std::string& name, int leng)
	{
		std::string sqlString = "SELECT user FROM Users WHERE ";
		sqlString = sqlString + "name = " + "'" + name + "'";
		if(leng > 0)
		{
			sqlString += " LIMIT  " + std::to_string(leng);
		}
		octetos::db::maria::Datresult dt;
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
		else
		{
			return NULL;
		}
	}


	bool Users::checkpass(octetos::db::maria::Connector& connector)
	{ 
		std::string sqlString = "SELECT name,pwdtxt FROM Users WHERE ";
		sqlString = sqlString + "user = " +  "'" + std::to_string((*user).getPerson().getID()) + "'";
		octetos::db::maria::Datresult dt;
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
	bool Users::downName(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT name ";
		sqlString = sqlString + " FROM Users WHERE ";
		sqlString = sqlString + "user = " +  "'" + std::to_string((*user).getPerson().getID()) + "'";
		octetos::db::maria::Datresult dt;
		bool flag = connector.execute(sqlString,dt);
		if(flag)
		{
			name = dt.getString(0);
			return true;
		}
		return false;
	}
	bool Users::downPwdtxt(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT pwdtxt ";
		sqlString = sqlString + " FROM Users WHERE ";
		sqlString = sqlString + "user = " +  "'" + std::to_string((*user).getPerson().getID()) + "'";
		octetos::db::maria::Datresult dt;
		bool flag = connector.execute(sqlString,dt);
		if(flag)
		{
			pwdtxt = dt.getString(0);
			return true;
		}
		return false;
	}
	bool Users::downStatus(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT status ";
		sqlString = sqlString + " FROM Users WHERE ";
		sqlString = sqlString + "user = " +  "'" + std::to_string((*user).getPerson().getID()) + "'";
		octetos::db::maria::Datresult dt;
		bool flag = connector.execute(sqlString,dt);
		if(flag)
		{
			status = dt.getString(0);
			return true;
		}
		return false;
	}




	const std::string Versions::TABLE_NAME = "`Versions`";
	Versions::Versions()
	{
	}
	Versions::Versions(int ente)
	{
		this->ente = new Entities(ente);
	}
	Versions::Versions(const Versions& obj)
	{
		this->ente = obj.ente;
		this->major = obj.major;
		this->minor = obj.minor;
		this->name = obj.name;
		this->patch = obj.patch;
	}


	const Entities& Versions::getEnte() const 
	{
		return *ente;
	}
	unsigned char Versions::getMajor() const 
	{
		return major;
	}
	unsigned char Versions::getMinor() const 
	{
		return minor;
	}
	const std::string& Versions::getName() const 
	{
		return name;
	}
	unsigned char Versions::getPatch() const 
	{
		return patch;
	}


	bool Versions::updateMajor(octetos::db::maria::Connector& connector,unsigned char major)
	{
		std::string sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET major = " + std::to_string(major);
		sqlString = sqlString + " WHERE ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dat;
		return connector.update(sqlString,dat);
	}
	bool Versions::updateMinor(octetos::db::maria::Connector& connector,unsigned char minor)
	{
		std::string sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET minor = " + std::to_string(minor);
		sqlString = sqlString + " WHERE ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dat;
		return connector.update(sqlString,dat);
	}
	bool Versions::updateName(octetos::db::maria::Connector& connector,const std::string& name)
	{
		std::string sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET name = '" + name + "'";
		sqlString = sqlString + " WHERE ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dat;
		return connector.update(sqlString,dat);
	}
	bool Versions::updatePatch(octetos::db::maria::Connector& connector,unsigned char patch)
	{
		std::string sqlString = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString + " SET patch = " + std::to_string(patch);
		sqlString = sqlString + " WHERE ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dat;
		return connector.update(sqlString,dat);
	}


	bool Versions::insert(octetos::db::maria::Connector& connector,unsigned char major)
	{
		this->ente = new Entities();
		if(ente->insert(connector) == false) return false;
		std::string sqlString = "";
		sqlString = sqlString + "INSERT INTO " + TABLE_NAME ; 
		sqlString = sqlString + "(ente,major)";
		sqlString = sqlString + " VALUES(" + std::to_string((*ente).getID()) + ","  + std::to_string(major) + ")";
		octetos::db::maria::Datresult dt;
		std::cout << sqlString << std::endl;
		if(connector.insert(sqlString,dt)) return true;
		return false;
	}


	bool Versions::select(octetos::db::maria::Connector& connector,const Entities& ente)
	{
		std::string sql = "SELECT  ente";
		sql = sql + " FROM " + TABLE_NAME  + " WHERE ente = " + std::to_string(ente.getID());
		octetos::db::maria::Datresult dat;
		bool retflag = connector.select(sql,dat);
		if(retflag)
		{
			this->ente = new Entities(ente);
		}
		return retflag;
	}
	std::vector<Versions*>* Versions::select(octetos::db::maria::Connector& connector, const std::string& where, int leng)
	{
		std::string sqlString = "SELECT ente FROM Versions WHERE ";
		sqlString += where;
		if(leng > 0)
		{
			sqlString += " LIMIT  ";
			sqlString += std::to_string(leng);
 		}
		octetos::db::maria::Datresult dt;
		bool flag = connector.execute(sqlString,dt);
		if(flag)
		{
			std::vector<Versions*>* tmpVc = new std::vector<Versions*>;
			while(dt.nextRow())
			{
				Versions* tmp = NULL;
				tmp = new Versions(dt.getint(0));
				tmpVc->push_back(tmp);
			}
			return tmpVc;
		}
		return NULL;
	}


	bool Versions::downMajor(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT major ";
		sqlString = sqlString + " FROM Versions WHERE ";
		sqlString = sqlString + "ente = " +  "'" + std::to_string((*ente).getID()) + "'";
		octetos::db::maria::Datresult dt;
		bool flag = connector.execute(sqlString,dt);
		if(flag)
		{
			major = dt.getuchar(0);
			return true;
		}
		return false;
	}
	bool Versions::downMinor(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT minor ";
		sqlString = sqlString + " FROM Versions WHERE ";
		sqlString = sqlString + "ente = " +  "'" + std::to_string((*ente).getID()) + "'";
		octetos::db::maria::Datresult dt;
		bool flag = connector.execute(sqlString,dt);
		if(flag)
		{
			minor = dt.getuchar(0);
			return true;
		}
		return false;
	}
	bool Versions::downName(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT name ";
		sqlString = sqlString + " FROM Versions WHERE ";
		sqlString = sqlString + "ente = " +  "'" + std::to_string((*ente).getID()) + "'";
		octetos::db::maria::Datresult dt;
		bool flag = connector.execute(sqlString,dt);
		if(flag)
		{
			name = dt.getString(0);
			return true;
		}
		return false;
	}
	bool Versions::downPatch(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT patch ";
		sqlString = sqlString + " FROM Versions WHERE ";
		sqlString = sqlString + "ente = " +  "'" + std::to_string((*ente).getID()) + "'";
		octetos::db::maria::Datresult dt;
		bool flag = connector.execute(sqlString,dt);
		if(flag)
		{
			patch = dt.getuchar(0);
			return true;
		}
		return false;
	}





}

