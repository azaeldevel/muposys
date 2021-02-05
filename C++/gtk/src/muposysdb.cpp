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

	int Entities::getIDValue() const
	{
		return id;
	}


	bool Entities::upMd5sum(octetos::db::maria::Connector& connector,const std::string& md5sum)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "md5sum = " + "'" + md5sum + "'";
		sqlString = sqlString + " WHERE " +  "id = " + std::to_string(id);
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}


	bool Entities::insert(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "()";
		sqlString = sqlString + " VALUES(" +  ")";
		octetos::db::maria::Datresult dt;
		if(connector.insert(sqlString,dt))
		{
			id = connector.last_inserted_id();
			if(id > 0) return true;
		}
		return false;
	}


	std::vector<Entities*>* Entities::select(octetos::db::maria::Connector& connector, const std::string& where, int leng, char order)
	{
		std::string sqlString = "SELECT id FROM Entities WHERE ";
		sqlString += where;
		if(order == 'a' || order == 'A')
		{
			sqlString = sqlString + " ORDER BY id ASC ";
		}
		else if(order == 'd' || order == 'D')
		{
			sqlString = sqlString + " ORDER BY id DESC ";
		}
		if(leng > 0)
		{
			sqlString += " LIMIT ";
			sqlString += std::to_string(leng);
		}
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
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
	bool Entities::select(octetos::db::maria::Connector& connector,int id)
	{
		std::string sqlString = "SELECT  id";
		sqlString = sqlString + " FROM " + TABLE_NAME + " WHERE " +  "id = " + std::to_string(id);
		octetos::db::maria::Datresult dat;
		bool retflag = connector.select(sqlString,dat);
		if(retflag)
		{
			this->id = id;
		}
		return retflag;
	}


	bool Entities::downMd5sum(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT md5sum  FROM Entities WHERE ";
		sqlString = sqlString +  "id = " + std::to_string(id);
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			md5sum = dt.getString(0);
			return true;
		}
		return false;
	}


	bool Entities::remove(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "DELETE FROM Entities WHERE ";
		sqlString = sqlString +  "id = " + std::to_string(id);
		octetos::db::maria::Datresult dt;
		return connector.remove(sqlString,dt);
	}




	const std::string Persons::TABLE_NAME = "`Persons`";
	Persons::Persons()
	{
	}
	Persons::Persons(int ente)
	{
		this->ente = new Entities(ente);
	}
	Persons::Persons(const Persons& obj)
	{
		this->age = obj.age;
		this->canyonLength = obj.canyonLength;
		this->canyonNumber = obj.canyonNumber;
		this->ente = obj.ente;
		this->gender = obj.gender;
		this->name1 = obj.name1;
		this->name2 = obj.name2;
		this->name3 = obj.name3;
		this->name4 = obj.name4;
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

	const Entities& Persons::getEnte() const
	{
		return *ente;
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

	int Persons::getEnteValue() const
	{
		return (*ente).getID();
	}


	bool Persons::upAge(octetos::db::maria::Connector& connector,float age)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "age = " + std::to_string(age);
		sqlString = sqlString + " WHERE " +  "ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}
	bool Persons::upCanyonLength(octetos::db::maria::Connector& connector,float canyonLength)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "canyonLength = " + std::to_string(canyonLength);
		sqlString = sqlString + " WHERE " +  "ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}
	bool Persons::upCanyonNumber(octetos::db::maria::Connector& connector,float canyonNumber)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "canyonNumber = " + std::to_string(canyonNumber);
		sqlString = sqlString + " WHERE " +  "ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}
	bool Persons::upGender(octetos::db::maria::Connector& connector,const std::string& gender)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "gender = " + "'" + gender + "'";
		sqlString = sqlString + " WHERE " +  "ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}
	bool Persons::upName1(octetos::db::maria::Connector& connector,const std::string& name1)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "name1 = " + "'" + name1 + "'";
		sqlString = sqlString + " WHERE " +  "ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}
	bool Persons::upName2(octetos::db::maria::Connector& connector,const std::string& name2)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "name2 = " + "'" + name2 + "'";
		sqlString = sqlString + " WHERE " +  "ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}
	bool Persons::upName3(octetos::db::maria::Connector& connector,const std::string& name3)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "name3 = " + "'" + name3 + "'";
		sqlString = sqlString + " WHERE " +  "ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}
	bool Persons::upName4(octetos::db::maria::Connector& connector,const std::string& name4)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "name4 = " + "'" + name4 + "'";
		sqlString = sqlString + " WHERE " +  "ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}


	bool Persons::insert(octetos::db::maria::Connector& connector,const std::string& name1)
	{
		this->ente = new Entities();
		if(this->ente->insert(connector) == false) return false;
		std::string sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(ente,name1)";
		sqlString = sqlString + " VALUES(" + std::to_string((*ente).getID()) + ","  +  "'"  + name1 + "'" +  ")";
		octetos::db::maria::Datresult dt;
		return connector.insert(sqlString,dt);
	}
	bool Persons::insert(octetos::db::maria::Connector& connector,const Entities&  ente,const std::string& name1)
	{
		std::string sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(ente,name1)";
		sqlString = sqlString + " VALUES(" + std::to_string(ente.getID()) + ","  +  "'"  + name1 + "'" +  ")";
		octetos::db::maria::Datresult dt;
		return connector.insert(sqlString,dt);
	}


	std::vector<Persons*>* Persons::select(octetos::db::maria::Connector& connector, const std::string& where, int leng, char order)
	{
		std::string sqlString = "SELECT ente FROM Persons WHERE ";
		sqlString += where;
		if(order == 'a' || order == 'A')
		{
			sqlString = sqlString + " ORDER BY ente ASC ";
		}
		else if(order == 'd' || order == 'D')
		{
			sqlString = sqlString + " ORDER BY ente DESC ";
		}
		if(leng > 0)
		{
			sqlString += " LIMIT ";
			sqlString += std::to_string(leng);
		}
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
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
		std::string sqlString = "SELECT ente FROM Persons WHERE ";
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
	bool Persons::select(octetos::db::maria::Connector& connector,const Entities &ente)
	{
		std::string sqlString = "SELECT  ente";
		sqlString = sqlString + " FROM " + TABLE_NAME + " WHERE " +  "ente = " + std::to_string(ente.getID());
		octetos::db::maria::Datresult dat;
		bool retflag = connector.select(sqlString,dat);
		if(retflag)
		{
			this->ente = new Entities();
		}
		return retflag;
	}


	bool Persons::downAge(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT age  FROM Persons WHERE ";
		sqlString = sqlString +  "ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			age = dt.getfloat(0);
			return true;
		}
		return false;
	}
	bool Persons::downCanyonLength(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT canyonLength  FROM Persons WHERE ";
		sqlString = sqlString +  "ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			canyonLength = dt.getfloat(0);
			return true;
		}
		return false;
	}
	bool Persons::downCanyonNumber(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT canyonNumber  FROM Persons WHERE ";
		sqlString = sqlString +  "ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			canyonNumber = dt.getfloat(0);
			return true;
		}
		return false;
	}
	bool Persons::downGender(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT gender  FROM Persons WHERE ";
		sqlString = sqlString +  "ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			gender = dt.getString(0);
			return true;
		}
		return false;
	}
	bool Persons::downName1(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT name1  FROM Persons WHERE ";
		sqlString = sqlString +  "ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			name1 = dt.getString(0);
			return true;
		}
		return false;
	}
	bool Persons::downName2(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT name2  FROM Persons WHERE ";
		sqlString = sqlString +  "ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			name2 = dt.getString(0);
			return true;
		}
		return false;
	}
	bool Persons::downName3(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT name3  FROM Persons WHERE ";
		sqlString = sqlString +  "ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			name3 = dt.getString(0);
			return true;
		}
		return false;
	}
	bool Persons::downName4(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT name4  FROM Persons WHERE ";
		sqlString = sqlString +  "ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			name4 = dt.getString(0);
			return true;
		}
		return false;
	}


	bool Persons::remove(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "DELETE FROM Persons WHERE ";
		sqlString = sqlString +  "ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dt;
		return connector.remove(sqlString,dt);
	}




	const std::string SoftwareProjects::TABLE_NAME = "`SoftwareProjects`";
	SoftwareProjects::SoftwareProjects()
	{
	}
	SoftwareProjects::SoftwareProjects(int ente)
	{
		this->ente = new Entities(ente);
	}
	SoftwareProjects::SoftwareProjects(const SoftwareProjects& obj)
	{
		this->brief = obj.brief;
		this->ente = obj.ente;
		this->name = obj.name;
	}


	const std::string& SoftwareProjects::getBrief() const
	{
		return brief;
	}

	const Entities& SoftwareProjects::getEnte() const
	{
		return *ente;
	}

	const std::string& SoftwareProjects::getName() const
	{
		return name;
	}

	int SoftwareProjects::getEnteValue() const
	{
		return (*ente).getID();
	}


	bool SoftwareProjects::upBrief(octetos::db::maria::Connector& connector,const std::string& brief)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "brief = " + "'" + brief + "'";
		sqlString = sqlString + " WHERE " +  "ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}
	bool SoftwareProjects::upName(octetos::db::maria::Connector& connector,const std::string& name)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "name = " + "'" + name + "'";
		sqlString = sqlString + " WHERE " +  "ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}


	bool SoftwareProjects::insert(octetos::db::maria::Connector& connector,const std::string& name)
	{
		this->ente = new Entities();
		if(this->ente->insert(connector) == false) return false;
		std::string sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(ente,name)";
		sqlString = sqlString + " VALUES(" + std::to_string((*ente).getID()) + ","  +  "'"  + name + "'" +  ")";
		octetos::db::maria::Datresult dt;
		return connector.insert(sqlString,dt);
	}
	bool SoftwareProjects::insert(octetos::db::maria::Connector& connector,const Entities&  ente,const std::string& name)
	{
		std::string sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(ente,name)";
		sqlString = sqlString + " VALUES(" + std::to_string(ente.getID()) + ","  +  "'"  + name + "'" +  ")";
		octetos::db::maria::Datresult dt;
		return connector.insert(sqlString,dt);
	}


	std::vector<SoftwareProjects*>* SoftwareProjects::select(octetos::db::maria::Connector& connector, const std::string& where, int leng, char order)
	{
		std::string sqlString = "SELECT ente FROM SoftwareProjects WHERE ";
		sqlString += where;
		if(order == 'a' || order == 'A')
		{
			sqlString = sqlString + " ORDER BY ente ASC ";
		}
		else if(order == 'd' || order == 'D')
		{
			sqlString = sqlString + " ORDER BY ente DESC ";
		}
		if(leng > 0)
		{
			sqlString += " LIMIT ";
			sqlString += std::to_string(leng);
		}
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			std::vector<SoftwareProjects*>* tmpVc = new std::vector<SoftwareProjects*>;
			while(dt.nextRow())
			{
				SoftwareProjects* tmp = NULL;
				tmp = new SoftwareProjects(dt.getint(0));
				tmpVc->push_back(tmp);
			}
			return tmpVc;
		}
		return NULL;
	}
	bool SoftwareProjects::select(octetos::db::maria::Connector& connector,const Entities &ente)
	{
		std::string sqlString = "SELECT  ente";
		sqlString = sqlString + " FROM " + TABLE_NAME + " WHERE " +  "ente = " + std::to_string(ente.getID());
		octetos::db::maria::Datresult dat;
		bool retflag = connector.select(sqlString,dat);
		if(retflag)
		{
			this->ente = new Entities();
		}
		return retflag;
	}


	bool SoftwareProjects::downBrief(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT brief  FROM SoftwareProjects WHERE ";
		sqlString = sqlString +  "ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			brief = dt.getString(0);
			return true;
		}
		return false;
	}
	bool SoftwareProjects::downName(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT name  FROM SoftwareProjects WHERE ";
		sqlString = sqlString +  "ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			name = dt.getString(0);
			return true;
		}
		return false;
	}


	bool SoftwareProjects::remove(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "DELETE FROM SoftwareProjects WHERE ";
		sqlString = sqlString +  "ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dt;
		return connector.remove(sqlString,dt);
	}




	const std::string SoftwareRQs::TABLE_NAME = "`SoftwareRQs`";
	SoftwareRQs::SoftwareRQs()
	{
	}
	SoftwareRQs::SoftwareRQs(int project,int number)
	{
		this->project = new SoftwareProjects(project);
		this->number = number;
	}
	SoftwareRQs::SoftwareRQs(const SoftwareRQs& obj)
	{
		this->name = obj.name;
		this->number = obj.number;
		this->origin = obj.origin;
		this->priority = obj.priority;
		this->project = obj.project;
		this->type = obj.type;
	}


	const std::string& SoftwareRQs::getName() const
	{
		return name;
	}

	int SoftwareRQs::getNumber() const
	{
		return number;
	}

	const std::string& SoftwareRQs::getOrigin() const
	{
		return origin;
	}

	int SoftwareRQs::getPriority() const
	{
		return priority;
	}

	const SoftwareProjects& SoftwareRQs::getProject() const
	{
		return *project;
	}

	const std::string& SoftwareRQs::getType() const
	{
		return type;
	}

	int SoftwareRQs::getProjectValue() const
	{
		return (*project).getEnte().getID();
	}
	int SoftwareRQs::getNumberValue() const
	{
		return number;
	}


	bool SoftwareRQs::upName(octetos::db::maria::Connector& connector,const std::string& name)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "name = " + "'" + name + "'";
		sqlString = sqlString + " WHERE " +  "project = " + std::to_string((*project).getEnte().getID()) + " and " +  "number = " + std::to_string(number);
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}
	bool SoftwareRQs::upOrigin(octetos::db::maria::Connector& connector,const std::string& origin)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "origin = " + "'" + origin + "'";
		sqlString = sqlString + " WHERE " +  "project = " + std::to_string((*project).getEnte().getID()) + " and " +  "number = " + std::to_string(number);
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}
	bool SoftwareRQs::upPriority(octetos::db::maria::Connector& connector,int priority)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "priority = " + std::to_string(priority);
		sqlString = sqlString + " WHERE " +  "project = " + std::to_string((*project).getEnte().getID()) + " and " +  "number = " + std::to_string(number);
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}
	bool SoftwareRQs::upType(octetos::db::maria::Connector& connector,const std::string& type)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "type = " + "'" + type + "'";
		sqlString = sqlString + " WHERE " +  "project = " + std::to_string((*project).getEnte().getID()) + " and " +  "number = " + std::to_string(number);
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}


	bool SoftwareRQs::insert(octetos::db::maria::Connector& connector,const std::string& projectName,const std::string& name,int priority)
	{
		this->project = new SoftwareProjects();
		if(this->project->insert(connector,projectName) == false) return false;
		std::string sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(project,number,name,priority)";
		sqlString = sqlString + " VALUES(" + std::to_string((*project).getEnte().getID()) + ","  + std::to_string(number) + ","  +  "'"  + name + "'" + ","  + std::to_string(priority) +  ")";
		octetos::db::maria::Datresult dt;
		if(connector.insert(sqlString,dt)) return true;
		return false;
	}
	bool SoftwareRQs::insert(octetos::db::maria::Connector& connector,const SoftwareProjects&  project,int number,const std::string& name,int priority)
	{
		std::string sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(project,number,name,priority)";
		sqlString = sqlString + " VALUES(" + std::to_string(project.getEnte().getID()) + ","  + std::to_string(number) + ","  +  "'"  + name + "'" + ","  + std::to_string(priority) +  ")";
		octetos::db::maria::Datresult dt;
		if(connector.insert(sqlString,dt)) return true;
		return false;
	}


	std::vector<SoftwareRQs*>* SoftwareRQs::select(octetos::db::maria::Connector& connector, const std::string& where, int leng, char order)
	{
		std::string sqlString = "SELECT project,number FROM SoftwareRQs WHERE ";
		sqlString += where;
		if(order == 'a' || order == 'A')
		{
			sqlString = sqlString + " ORDER BY project,number ASC ";
		}
		else if(order == 'd' || order == 'D')
		{
			sqlString = sqlString + " ORDER BY project,number DESC ";
		}
		if(leng > 0)
		{
			sqlString += " LIMIT ";
			sqlString += std::to_string(leng);
		}
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			std::vector<SoftwareRQs*>* tmpVc = new std::vector<SoftwareRQs*>;
			while(dt.nextRow())
			{
				SoftwareRQs* tmp = NULL;
				tmp = new SoftwareRQs(dt.getint(0),dt.getint(1));
				tmpVc->push_back(tmp);
			}
			return tmpVc;
		}
		return NULL;
	}
	bool SoftwareRQs::select(octetos::db::maria::Connector& connector,const SoftwareProjects &project,int number)
	{
		std::string sqlString = "SELECT  project, number";
		sqlString = sqlString + " FROM " + TABLE_NAME + " WHERE " +  "project = " + std::to_string(project.getEnte().getID()) + " and " +  "number = " + std::to_string(number);
		octetos::db::maria::Datresult dat;
		bool retflag = connector.select(sqlString,dat);
		if(retflag)
		{
			this->project = new SoftwareProjects();
			this->number = number;
		}
		return retflag;
	}


	bool SoftwareRQs::downName(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT name  FROM SoftwareRQs WHERE ";
		sqlString = sqlString +  "project = " + std::to_string((*project).getEnte().getID()) + " and " +  "number = " + std::to_string(number);
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			name = dt.getString(0);
			return true;
		}
		return false;
	}
	bool SoftwareRQs::downNumber(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT number  FROM SoftwareRQs WHERE ";
		sqlString = sqlString +  "project = " + std::to_string((*project).getEnte().getID()) + " and " +  "number = " + std::to_string(number);
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			number = dt.getint(0);
			return true;
		}
		return false;
	}
	bool SoftwareRQs::downOrigin(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT origin  FROM SoftwareRQs WHERE ";
		sqlString = sqlString +  "project = " + std::to_string((*project).getEnte().getID()) + " and " +  "number = " + std::to_string(number);
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			origin = dt.getString(0);
			return true;
		}
		return false;
	}
	bool SoftwareRQs::downPriority(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT priority  FROM SoftwareRQs WHERE ";
		sqlString = sqlString +  "project = " + std::to_string((*project).getEnte().getID()) + " and " +  "number = " + std::to_string(number);
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			priority = dt.getint(0);
			return true;
		}
		return false;
	}
	bool SoftwareRQs::downType(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT type  FROM SoftwareRQs WHERE ";
		sqlString = sqlString +  "project = " + std::to_string((*project).getEnte().getID()) + " and " +  "number = " + std::to_string(number);
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			type = dt.getString(0);
			return true;
		}
		return false;
	}


	bool SoftwareRQs::remove(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "DELETE FROM SoftwareRQs WHERE ";
		sqlString = sqlString +  "project = " + std::to_string((*project).getEnte().getID()) + " and " +  "number = " + std::to_string(number);
		octetos::db::maria::Datresult dt;
		return connector.remove(sqlString,dt);
	}




	const std::string Users::TABLE_NAME = "`Users`";
	Users::Users()
	{
	}
	Users::Users(int person)
	{
		this->person = new Persons(person);
	}
	Users::Users(const Users& obj)
	{
		this->name = obj.name;
		this->person = obj.person;
		this->pwdtxt = obj.pwdtxt;
		this->status = obj.status;
	}


	const std::string& Users::getName() const
	{
		return name;
	}

	const Persons& Users::getPerson() const
	{
		return *person;
	}

	const std::string& Users::getPwdtxt() const
	{
		return pwdtxt;
	}

	const std::string& Users::getStatus() const
	{
		return status;
	}

	int Users::getPersonValue() const
	{
		return (*person).getEnte().getID();
	}


	bool Users::upName(octetos::db::maria::Connector& connector,const std::string& name)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "name = " + "'" + name + "'";
		sqlString = sqlString + " WHERE " +  "person = " + std::to_string((*person).getEnte().getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}
	bool Users::upPwdtxt(octetos::db::maria::Connector& connector,const std::string& pwdtxt)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "pwdtxt = " + "'" + pwdtxt + "'";
		sqlString = sqlString + " WHERE " +  "person = " + std::to_string((*person).getEnte().getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}
	bool Users::upStatus(octetos::db::maria::Connector& connector,const std::string& status)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "status = " + "'" + status + "'";
		sqlString = sqlString + " WHERE " +  "person = " + std::to_string((*person).getEnte().getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}


	bool Users::insert(octetos::db::maria::Connector& connector,const std::string& personName1,const std::string& name)
	{
		this->person = new Persons();
		if(this->person->insert(connector,personName1) == false) return false;
		std::string sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(person,name)";
		sqlString = sqlString + " VALUES(" + std::to_string((*person).getEnte().getID()) + ","  +  "'"  + name + "'" +  ")";
		octetos::db::maria::Datresult dt;
		return connector.insert(sqlString,dt);
	}
	bool Users::insert(octetos::db::maria::Connector& connector,const Persons&  person,const std::string& name)
	{
		std::string sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(person,name)";
		sqlString = sqlString + " VALUES(" + std::to_string(person.getEnte().getID()) + ","  +  "'"  + name + "'" +  ")";
		octetos::db::maria::Datresult dt;
		return connector.insert(sqlString,dt);
	}


	std::vector<Users*>* Users::select(octetos::db::maria::Connector& connector, const std::string& where, int leng, char order)
	{
		std::string sqlString = "SELECT person FROM Users WHERE ";
		sqlString += where;
		if(order == 'a' || order == 'A')
		{
			sqlString = sqlString + " ORDER BY person ASC ";
		}
		else if(order == 'd' || order == 'D')
		{
			sqlString = sqlString + " ORDER BY person DESC ";
		}
		if(leng > 0)
		{
			sqlString += " LIMIT ";
			sqlString += std::to_string(leng);
		}
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
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
		std::string sqlString = "SELECT person FROM Users WHERE ";
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
	bool Users::select(octetos::db::maria::Connector& connector,const Persons &person)
	{
		std::string sqlString = "SELECT  person";
		sqlString = sqlString + " FROM " + TABLE_NAME + " WHERE " +  "person = " + std::to_string(person.getEnte().getID());
		octetos::db::maria::Datresult dat;
		bool retflag = connector.select(sqlString,dat);
		if(retflag)
		{
			this->person = new Persons();
		}
		return retflag;
	}


	bool Users::checkpass(octetos::db::maria::Connector& connector)
	{ 
		std::string sqlString = "SELECT name,pwdtxt FROM Users WHERE ";
		sqlString = sqlString + "person = " +  "'" + std::to_string((*person).getEnte().getID()) + "'";
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
		std::string sqlString = "SELECT name  FROM Users WHERE ";
		sqlString = sqlString +  "person = " + std::to_string((*person).getEnte().getID());
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			name = dt.getString(0);
			return true;
		}
		return false;
	}
	bool Users::downPwdtxt(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT pwdtxt  FROM Users WHERE ";
		sqlString = sqlString +  "person = " + std::to_string((*person).getEnte().getID());
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			pwdtxt = dt.getString(0);
			return true;
		}
		return false;
	}
	bool Users::downStatus(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT status  FROM Users WHERE ";
		sqlString = sqlString +  "person = " + std::to_string((*person).getEnte().getID());
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			status = dt.getString(0);
			return true;
		}
		return false;
	}


	bool Users::remove(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "DELETE FROM Users WHERE ";
		sqlString = sqlString +  "person = " + std::to_string((*person).getEnte().getID());
		octetos::db::maria::Datresult dt;
		return connector.remove(sqlString,dt);
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

	int Versions::getEnteValue() const
	{
		return (*ente).getID();
	}


	bool Versions::upMajor(octetos::db::maria::Connector& connector,unsigned char major)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "major = " + std::to_string(major);
		sqlString = sqlString + " WHERE " +  "ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}
	bool Versions::upMinor(octetos::db::maria::Connector& connector,unsigned char minor)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "minor = " + std::to_string(minor);
		sqlString = sqlString + " WHERE " +  "ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}
	bool Versions::upName(octetos::db::maria::Connector& connector,const std::string& name)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "name = " + "'" + name + "'";
		sqlString = sqlString + " WHERE " +  "ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}
	bool Versions::upPatch(octetos::db::maria::Connector& connector,unsigned char patch)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "patch = " + std::to_string(patch);
		sqlString = sqlString + " WHERE " +  "ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}


	bool Versions::insert(octetos::db::maria::Connector& connector,unsigned char major)
	{
		this->ente = new Entities();
		if(this->ente->insert(connector) == false) return false;
		std::string sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(ente,major)";
		sqlString = sqlString + " VALUES(" + std::to_string((*ente).getID()) + ","  + std::to_string(major) +  ")";
		octetos::db::maria::Datresult dt;
		return connector.insert(sqlString,dt);
	}
	bool Versions::insert(octetos::db::maria::Connector& connector,const Entities&  ente,unsigned char major)
	{
		std::string sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(ente,major)";
		sqlString = sqlString + " VALUES(" + std::to_string(ente.getID()) + ","  + std::to_string(major) +  ")";
		octetos::db::maria::Datresult dt;
		return connector.insert(sqlString,dt);
	}


	std::vector<Versions*>* Versions::select(octetos::db::maria::Connector& connector, const std::string& where, int leng, char order)
	{
		std::string sqlString = "SELECT ente FROM Versions WHERE ";
		sqlString += where;
		if(order == 'a' || order == 'A')
		{
			sqlString = sqlString + " ORDER BY ente ASC ";
		}
		else if(order == 'd' || order == 'D')
		{
			sqlString = sqlString + " ORDER BY ente DESC ";
		}
		if(leng > 0)
		{
			sqlString += " LIMIT ";
			sqlString += std::to_string(leng);
		}
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
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
	bool Versions::select(octetos::db::maria::Connector& connector,const Entities &ente)
	{
		std::string sqlString = "SELECT  ente";
		sqlString = sqlString + " FROM " + TABLE_NAME + " WHERE " +  "ente = " + std::to_string(ente.getID());
		octetos::db::maria::Datresult dat;
		bool retflag = connector.select(sqlString,dat);
		if(retflag)
		{
			this->ente = new Entities();
		}
		return retflag;
	}


	bool Versions::downMajor(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT major  FROM Versions WHERE ";
		sqlString = sqlString +  "ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			major = dt.getchar(0);
			return true;
		}
		return false;
	}
	bool Versions::downMinor(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT minor  FROM Versions WHERE ";
		sqlString = sqlString +  "ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			minor = dt.getchar(0);
			return true;
		}
		return false;
	}
	bool Versions::downName(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT name  FROM Versions WHERE ";
		sqlString = sqlString +  "ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			name = dt.getString(0);
			return true;
		}
		return false;
	}
	bool Versions::downPatch(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT patch  FROM Versions WHERE ";
		sqlString = sqlString +  "ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			patch = dt.getchar(0);
			return true;
		}
		return false;
	}


	bool Versions::remove(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "DELETE FROM Versions WHERE ";
		sqlString = sqlString +  "ente = " + std::to_string((*ente).getID());
		octetos::db::maria::Datresult dt;
		return connector.remove(sqlString,dt);
	}





}

