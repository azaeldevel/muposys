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


	const std::string Buys::TABLE_NAME = "`Buys`";
	Buys::Buys()
	{
		doc = NULL;
	}
	Buys::Buys(int doc)
	{
		this->doc = new Entities(doc);
	}
	Buys::Buys(const Buys& obj)
	{
		this->doc = obj.doc;
		this->supplier = obj.supplier;
	}
	Buys::~Buys()
	{
		if(doc != NULL)
		{
			delete doc;
			doc = NULL;
		}
	}


	Entities& Buys::getDoc() const
	{
		return *doc;
	}

	Supplier& Buys::getSupplier() const
	{
		return *supplier;
	}

	int Buys::getDocValue() const
	{
		return (*doc).getID();
	}


	bool Buys::upSupplier(octetos::db::maria::Connector& connector,const Supplier& supplier)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "supplier = " + std::to_string(supplier.getSupplier().getID());
		sqlString = sqlString + " WHERE " +  "doc = " + std::to_string((*doc).getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}


	bool Buys::insert(octetos::db::maria::Connector& connector,int supplierNumber,const std::string& supplierNameShort)
	{
		this->doc = new Entities();
		if(this->doc->insert(connector) == false) return false;
		this->supplier = new Supplier();
		if(this->supplier->insert(connector,supplierNumber,supplierNameShort) == false) return false;
		std::string sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(doc,supplier)";
		sqlString = sqlString + " VALUES(" + std::to_string((*doc).getID()) + ","  + std::to_string((*supplier).getSupplier().getID()) +  ")";
		octetos::db::maria::Datresult dt;
		if(connector.insert(sqlString,dt))
		{
			return true;
		}
		return false;
	}
	bool Buys::insert(octetos::db::maria::Connector& connector,const Entities&  doc,const Supplier&  supplier)
	{
		std::string sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(doc,supplier)";
		sqlString = sqlString + " VALUES(" + std::to_string(doc.getID()) + ","  + std::to_string(supplier.getSupplier().getID()) +  ")";
		octetos::db::maria::Datresult dt;
		if(connector.insert(sqlString,dt))
		{
			this->doc = new Entities(doc);
			return true;
		}
		return false;
	}


	std::vector<Buys*>* Buys::select(octetos::db::maria::Connector& connector, const std::string& where, int leng, char order)
	{
		std::string sqlString = "SELECT doc FROM Buys WHERE ";
		sqlString += where;
		if(order == 'a' || order == 'A')
		{
			sqlString = sqlString + " ORDER BY doc ASC ";
		}
		else if(order == 'd' || order == 'D')
		{
			sqlString = sqlString + " ORDER BY doc DESC ";
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
			std::vector<Buys*>* tmpVc = new std::vector<Buys*>;
			while(dt.nextRow())
			{
				Buys* tmp = NULL;
				tmp = new Buys(dt.getint(0));
				tmpVc->push_back(tmp);
			}
			return tmpVc;
		}
		return NULL;
	}
	bool Buys::select(octetos::db::maria::Connector& connector,const Entities &doc)
	{
		std::string sqlString = "SELECT  doc";
		sqlString = sqlString + " FROM " + TABLE_NAME + " WHERE " +  "doc = " + std::to_string(doc.getID());
		octetos::db::maria::Datresult dat;
		bool retflag = connector.select(sqlString,dat);
		if(retflag)
		{
			this->doc = new Entities(doc);
		}
		return retflag;
	}




	bool Buys::remove(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "DELETE FROM Buys WHERE ";
		sqlString = sqlString +  "doc = " + std::to_string((*doc).getID());
		octetos::db::maria::Datresult dt;
		return connector.remove(sqlString,dt);
	}




	const std::string Catalog::TABLE_NAME = "`Catalog`";
	Catalog::Catalog()
	{
		item = NULL;
	}
	Catalog::Catalog(int item)
	{
		this->item = new Entities(item);
	}
	Catalog::Catalog(const Catalog& obj)
	{
		this->brief = obj.brief;
		this->factoryID = obj.factoryID;
		this->item = obj.item;
		this->mode = obj.mode;
		this->number = obj.number;
		this->providerID = obj.providerID;
		this->ref1 = obj.ref1;
		this->type = obj.type;
	}
	Catalog::~Catalog()
	{
		if(item != NULL)
		{
			delete item;
			item = NULL;
		}
	}


	const std::string& Catalog::getBrief() const
	{
		return brief;
	}

	const std::string& Catalog::getFactoryID() const
	{
		return factoryID;
	}

	Entities& Catalog::getItem() const
	{
		return *item;
	}

	const std::string& Catalog::getMode() const
	{
		return mode;
	}

	const std::string& Catalog::getNumber() const
	{
		return number;
	}

	const std::string& Catalog::getProviderID() const
	{
		return providerID;
	}

	const std::string& Catalog::getRef1() const
	{
		return ref1;
	}

	const std::string& Catalog::getType() const
	{
		return type;
	}

	int Catalog::getItemValue() const
	{
		return (*item).getID();
	}


	bool Catalog::upBrief(octetos::db::maria::Connector& connector,const std::string& brief)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "brief = " + "'" + brief + "'";
		sqlString = sqlString + " WHERE " +  "item = " + std::to_string((*item).getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}
	bool Catalog::upFactoryID(octetos::db::maria::Connector& connector,const std::string& factoryID)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "factoryID = " + "'" + factoryID + "'";
		sqlString = sqlString + " WHERE " +  "item = " + std::to_string((*item).getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}
	bool Catalog::upMode(octetos::db::maria::Connector& connector,const std::string& mode)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "mode = " + "'" + mode + "'";
		sqlString = sqlString + " WHERE " +  "item = " + std::to_string((*item).getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}
	bool Catalog::upNumber(octetos::db::maria::Connector& connector,const std::string& number)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "number = " + "'" + number + "'";
		sqlString = sqlString + " WHERE " +  "item = " + std::to_string((*item).getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}
	bool Catalog::upProviderID(octetos::db::maria::Connector& connector,const std::string& providerID)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "providerID = " + "'" + providerID + "'";
		sqlString = sqlString + " WHERE " +  "item = " + std::to_string((*item).getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}
	bool Catalog::upRef1(octetos::db::maria::Connector& connector,const std::string& ref1)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "ref1 = " + "'" + ref1 + "'";
		sqlString = sqlString + " WHERE " +  "item = " + std::to_string((*item).getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}
	bool Catalog::upType(octetos::db::maria::Connector& connector,const std::string& type)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "type = " + "'" + type + "'";
		sqlString = sqlString + " WHERE " +  "item = " + std::to_string((*item).getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}


	bool Catalog::insert(octetos::db::maria::Connector& connector,const std::string& number,const std::string& mode,const std::string& type,const std::string& brief)
	{
		this->item = new Entities();
		if(this->item->insert(connector) == false) return false;
		std::string sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(item,number,mode,type,brief)";
		sqlString = sqlString + " VALUES(" + std::to_string((*item).getID()) + ","  +  "'"  + number + "'" + ","  +  "'"  + mode + "'" + ","  +  "'"  + type + "'" + ","  +  "'"  + brief + "'" +  ")";
		octetos::db::maria::Datresult dt;
		if(connector.insert(sqlString,dt))
		{
			return true;
		}
		return false;
	}
	bool Catalog::insert(octetos::db::maria::Connector& connector,const Entities&  item,const std::string&  number,const std::string&  mode,const std::string&  type,const std::string&  brief)
	{
		std::string sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(item,number,mode,type,brief)";
		sqlString = sqlString + " VALUES(" + std::to_string(item.getID()) + ","  +  "'"  + number + "'" + ","  +  "'"  + mode + "'" + ","  +  "'"  + type + "'" + ","  +  "'"  + brief + "'" +  ")";
		octetos::db::maria::Datresult dt;
		if(connector.insert(sqlString,dt))
		{
			this->item = new Entities(item);
			return true;
		}
		return false;
	}


	std::vector<Catalog*>* Catalog::select(octetos::db::maria::Connector& connector, const std::string& where, int leng, char order)
	{
		std::string sqlString = "SELECT item FROM Catalog WHERE ";
		sqlString += where;
		if(order == 'a' || order == 'A')
		{
			sqlString = sqlString + " ORDER BY item ASC ";
		}
		else if(order == 'd' || order == 'D')
		{
			sqlString = sqlString + " ORDER BY item DESC ";
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
			std::vector<Catalog*>* tmpVc = new std::vector<Catalog*>;
			while(dt.nextRow())
			{
				Catalog* tmp = NULL;
				tmp = new Catalog(dt.getint(0));
				tmpVc->push_back(tmp);
			}
			return tmpVc;
		}
		return NULL;
	}
	bool Catalog::select(octetos::db::maria::Connector& connector,const Entities &item)
	{
		std::string sqlString = "SELECT  item";
		sqlString = sqlString + " FROM " + TABLE_NAME + " WHERE " +  "item = " + std::to_string(item.getID());
		octetos::db::maria::Datresult dat;
		bool retflag = connector.select(sqlString,dat);
		if(retflag)
		{
			this->item = new Entities(item);
		}
		return retflag;
	}


	bool Catalog::downBrief(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT brief  FROM Catalog WHERE ";
		sqlString = sqlString +  "item = " + std::to_string((*item).getID());
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			if(!dt.nextRow()) return false;
			brief = dt.getString(0);
			return true;
		}
		return false;
	}
	bool Catalog::downFactoryID(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT factoryID  FROM Catalog WHERE ";
		sqlString = sqlString +  "item = " + std::to_string((*item).getID());
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			if(!dt.nextRow()) return false;
			factoryID = dt.getString(0);
			return true;
		}
		return false;
	}
	bool Catalog::downMode(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT mode  FROM Catalog WHERE ";
		sqlString = sqlString +  "item = " + std::to_string((*item).getID());
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			if(!dt.nextRow()) return false;
			mode = dt.getString(0);
			return true;
		}
		return false;
	}
	bool Catalog::downNumber(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT number  FROM Catalog WHERE ";
		sqlString = sqlString +  "item = " + std::to_string((*item).getID());
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			if(!dt.nextRow()) return false;
			number = dt.getString(0);
			return true;
		}
		return false;
	}
	bool Catalog::downProviderID(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT providerID  FROM Catalog WHERE ";
		sqlString = sqlString +  "item = " + std::to_string((*item).getID());
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			if(!dt.nextRow()) return false;
			providerID = dt.getString(0);
			return true;
		}
		return false;
	}
	bool Catalog::downRef1(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT ref1  FROM Catalog WHERE ";
		sqlString = sqlString +  "item = " + std::to_string((*item).getID());
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			if(!dt.nextRow()) return false;
			ref1 = dt.getString(0);
			return true;
		}
		return false;
	}
	bool Catalog::downType(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT type  FROM Catalog WHERE ";
		sqlString = sqlString +  "item = " + std::to_string((*item).getID());
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			if(!dt.nextRow()) return false;
			type = dt.getString(0);
			return true;
		}
		return false;
	}


	bool Catalog::remove(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "DELETE FROM Catalog WHERE ";
		sqlString = sqlString +  "item = " + std::to_string((*item).getID());
		octetos::db::maria::Datresult dt;
		return connector.remove(sqlString,dt);
	}




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
	Entities::~Entities()
	{
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
			if(!dt.nextRow()) return false;
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




	const std::string Movements::TABLE_NAME = "`Movements`";
	Movements::Movements()
	{
		id = NULL;
	}
	Movements::Movements(int id)
	{
		this->id = new Entities(id);
	}
	Movements::Movements(const Movements& obj)
	{
		this->delta = obj.delta;
		this->direction = obj.direction;
		this->doc = obj.doc;
		this->id = obj.id;
		this->item = obj.item;
		this->source = obj.source;
	}
	Movements::~Movements()
	{
		if(id != NULL)
		{
			delete id;
			id = NULL;
		}
	}


	int Movements::getDelta() const
	{
		return delta;
	}

	const std::string& Movements::getDirection() const
	{
		return direction;
	}

	Entities& Movements::getDoc() const
	{
		return *doc;
	}

	Entities& Movements::getID() const
	{
		return *id;
	}

	Catalog& Movements::getItem() const
	{
		return *item;
	}

	int Movements::getSource() const
	{
		return source;
	}

	int Movements::getIDValue() const
	{
		return (*id).getID();
	}


	bool Movements::upDelta(octetos::db::maria::Connector& connector,int delta)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "delta = " + std::to_string(delta);
		sqlString = sqlString + " WHERE " +  "id = " + std::to_string((*id).getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}
	bool Movements::upDirection(octetos::db::maria::Connector& connector,const std::string& direction)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "direction = " + "'" + direction + "'";
		sqlString = sqlString + " WHERE " +  "id = " + std::to_string((*id).getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}
	bool Movements::upDoc(octetos::db::maria::Connector& connector,const Entities& doc)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "doc = " + std::to_string(doc.getID());
		sqlString = sqlString + " WHERE " +  "id = " + std::to_string((*id).getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}
	bool Movements::upItem(octetos::db::maria::Connector& connector,const Catalog& item)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "item = " + std::to_string(item.getItem().getID());
		sqlString = sqlString + " WHERE " +  "id = " + std::to_string((*id).getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}
	bool Movements::upSource(octetos::db::maria::Connector& connector,int source)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "source = " + std::to_string(source);
		sqlString = sqlString + " WHERE " +  "id = " + std::to_string((*id).getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}


	bool Movements::insert(octetos::db::maria::Connector& connector,int source,const std::string& itemNumber,const std::string& itemMode,const std::string& itemType,const std::string& itemBrief,int delta)
	{
		this->id = new Entities();
		if(this->id->insert(connector) == false) return false;
		this->item = new Catalog();
		if(this->item->insert(connector,itemNumber,itemMode,itemType,itemBrief) == false) return false;
		this->doc = new Entities();
		if(this->doc->insert(connector) == false) return false;
		std::string sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(id,source,item,delta,doc)";
		sqlString = sqlString + " VALUES(" + std::to_string((*id).getID()) + ","  + std::to_string(source) + ","  + std::to_string((*item).getItem().getID()) + ","  + std::to_string(delta) + ","  + std::to_string((*doc).getID()) +  ")";
		octetos::db::maria::Datresult dt;
		if(connector.insert(sqlString,dt))
		{
			return true;
		}
		return false;
	}
	bool Movements::insert(octetos::db::maria::Connector& connector,const Entities&  id,int source,const Catalog&  item,int delta,const Entities&  doc)
	{
		std::string sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(id,source,item,delta,doc)";
		sqlString = sqlString + " VALUES(" + std::to_string(id.getID()) + ","  + std::to_string(source) + ","  + std::to_string(item.getItem().getID()) + ","  + std::to_string(delta) + ","  + std::to_string(doc.getID()) +  ")";
		octetos::db::maria::Datresult dt;
		if(connector.insert(sqlString,dt))
		{
			this->id = new Entities(id);
			return true;
		}
		return false;
	}


	std::vector<Movements*>* Movements::select(octetos::db::maria::Connector& connector, const std::string& where, int leng, char order)
	{
		std::string sqlString = "SELECT id FROM Movements WHERE ";
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
			std::vector<Movements*>* tmpVc = new std::vector<Movements*>;
			while(dt.nextRow())
			{
				Movements* tmp = NULL;
				tmp = new Movements(dt.getint(0));
				tmpVc->push_back(tmp);
			}
			return tmpVc;
		}
		return NULL;
	}
	bool Movements::select(octetos::db::maria::Connector& connector,const Entities &id)
	{
		std::string sqlString = "SELECT  id";
		sqlString = sqlString + " FROM " + TABLE_NAME + " WHERE " +  "id = " + std::to_string(id.getID());
		octetos::db::maria::Datresult dat;
		bool retflag = connector.select(sqlString,dat);
		if(retflag)
		{
			this->id = new Entities(id);
		}
		return retflag;
	}


	bool Movements::downDelta(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT delta  FROM Movements WHERE ";
		sqlString = sqlString +  "id = " + std::to_string((*id).getID());
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			if(!dt.nextRow()) return false;
			delta = dt.getint(0);
			return true;
		}
		return false;
	}
	bool Movements::downDirection(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT direction  FROM Movements WHERE ";
		sqlString = sqlString +  "id = " + std::to_string((*id).getID());
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			if(!dt.nextRow()) return false;
			direction = dt.getString(0);
			return true;
		}
		return false;
	}
	bool Movements::downSource(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT source  FROM Movements WHERE ";
		sqlString = sqlString +  "id = " + std::to_string((*id).getID());
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			if(!dt.nextRow()) return false;
			source = dt.getint(0);
			return true;
		}
		return false;
	}


	bool Movements::remove(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "DELETE FROM Movements WHERE ";
		sqlString = sqlString +  "id = " + std::to_string((*id).getID());
		octetos::db::maria::Datresult dt;
		return connector.remove(sqlString,dt);
	}




	const std::string Persons::TABLE_NAME = "`Persons`";
	Persons::Persons()
	{
		ente = NULL;
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
	Persons::~Persons()
	{
		if(ente != NULL)
		{
			delete ente;
			ente = NULL;
		}
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

	Entities& Persons::getEnte() const
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
		if(connector.insert(sqlString,dt))
		{
			return true;
		}
		return false;
	}
	bool Persons::insert(octetos::db::maria::Connector& connector,const Entities&  ente,const std::string&  name1)
	{
		std::string sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(ente,name1)";
		sqlString = sqlString + " VALUES(" + std::to_string(ente.getID()) + ","  +  "'"  + name1 + "'" +  ")";
		octetos::db::maria::Datresult dt;
		if(connector.insert(sqlString,dt))
		{
			this->ente = new Entities(ente);
			return true;
		}
		return false;
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
			this->ente = new Entities(ente);
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
			if(!dt.nextRow()) return false;
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
			if(!dt.nextRow()) return false;
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
			if(!dt.nextRow()) return false;
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
			if(!dt.nextRow()) return false;
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
			if(!dt.nextRow()) return false;
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
			if(!dt.nextRow()) return false;
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
			if(!dt.nextRow()) return false;
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
			if(!dt.nextRow()) return false;
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




	const std::string Stock::TABLE_NAME = "`Stock`";
	Stock::Stock()
	{
		item = NULL;
	}
	Stock::Stock(int item)
	{
		this->item = new Catalog(item);
	}
	Stock::Stock(const Stock& obj)
	{
		this->item = obj.item;
		this->number = obj.number;
		this->position = obj.position;
		this->quantity = obj.quantity;
		this->warehouse = obj.warehouse;
	}
	Stock::~Stock()
	{
		if(item != NULL)
		{
			delete item;
			item = NULL;
		}
	}


	Catalog& Stock::getItem() const
	{
		return *item;
	}

	const std::string& Stock::getNumber() const
	{
		return number;
	}

	const std::string& Stock::getPosition() const
	{
		return position;
	}

	int Stock::getQuantity() const
	{
		return quantity;
	}

	const std::string& Stock::getWarehouse() const
	{
		return warehouse;
	}

	int Stock::getItemValue() const
	{
		return (*item).getItem().getID();
	}


	bool Stock::upNumber(octetos::db::maria::Connector& connector,const std::string& number)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "number = " + "'" + number + "'";
		sqlString = sqlString + " WHERE " +  "item = " + std::to_string((*item).getItem().getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}
	bool Stock::upPosition(octetos::db::maria::Connector& connector,const std::string& position)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "position = " + "'" + position + "'";
		sqlString = sqlString + " WHERE " +  "item = " + std::to_string((*item).getItem().getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}
	bool Stock::upQuantity(octetos::db::maria::Connector& connector,int quantity)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "quantity = " + std::to_string(quantity);
		sqlString = sqlString + " WHERE " +  "item = " + std::to_string((*item).getItem().getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}
	bool Stock::upWarehouse(octetos::db::maria::Connector& connector,const std::string& warehouse)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "warehouse = " + "'" + warehouse + "'";
		sqlString = sqlString + " WHERE " +  "item = " + std::to_string((*item).getItem().getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}


	bool Stock::insert(octetos::db::maria::Connector& connector,const std::string& itemNumber,const std::string& itemMode,const std::string& itemType,const std::string& itemBrief,const std::string& number)
	{
		this->item = new Catalog();
		if(this->item->insert(connector,itemNumber,itemMode,itemType,itemBrief) == false) return false;
		std::string sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(item,number)";
		sqlString = sqlString + " VALUES(" + std::to_string((*item).getItem().getID()) + ","  +  "'"  + number + "'" +  ")";
		octetos::db::maria::Datresult dt;
		if(connector.insert(sqlString,dt))
		{
			return true;
		}
		return false;
	}
	bool Stock::insert(octetos::db::maria::Connector& connector,const Catalog&  item,const std::string&  number)
	{
		std::string sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(item,number)";
		sqlString = sqlString + " VALUES(" + std::to_string(item.getItem().getID()) + ","  +  "'"  + number + "'" +  ")";
		octetos::db::maria::Datresult dt;
		if(connector.insert(sqlString,dt))
		{
			this->item = new Catalog(item);
			return true;
		}
		return false;
	}


	std::vector<Stock*>* Stock::select(octetos::db::maria::Connector& connector, const std::string& where, int leng, char order)
	{
		std::string sqlString = "SELECT item FROM Stock WHERE ";
		sqlString += where;
		if(order == 'a' || order == 'A')
		{
			sqlString = sqlString + " ORDER BY item ASC ";
		}
		else if(order == 'd' || order == 'D')
		{
			sqlString = sqlString + " ORDER BY item DESC ";
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
			std::vector<Stock*>* tmpVc = new std::vector<Stock*>;
			while(dt.nextRow())
			{
				Stock* tmp = NULL;
				tmp = new Stock(dt.getint(0));
				tmpVc->push_back(tmp);
			}
			return tmpVc;
		}
		return NULL;
	}
	bool Stock::select(octetos::db::maria::Connector& connector,const Catalog &item)
	{
		std::string sqlString = "SELECT  item";
		sqlString = sqlString + " FROM " + TABLE_NAME + " WHERE " +  "item = " + std::to_string(item.getItem().getID());
		octetos::db::maria::Datresult dat;
		bool retflag = connector.select(sqlString,dat);
		if(retflag)
		{
			this->item = new Catalog(item);
		}
		return retflag;
	}


	bool Stock::downNumber(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT number  FROM Stock WHERE ";
		sqlString = sqlString +  "item = " + std::to_string((*item).getItem().getID());
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			if(!dt.nextRow()) return false;
			number = dt.getString(0);
			return true;
		}
		return false;
	}
	bool Stock::downPosition(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT position  FROM Stock WHERE ";
		sqlString = sqlString +  "item = " + std::to_string((*item).getItem().getID());
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			if(!dt.nextRow()) return false;
			position = dt.getString(0);
			return true;
		}
		return false;
	}
	bool Stock::downQuantity(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT quantity  FROM Stock WHERE ";
		sqlString = sqlString +  "item = " + std::to_string((*item).getItem().getID());
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			if(!dt.nextRow()) return false;
			quantity = dt.getint(0);
			return true;
		}
		return false;
	}
	bool Stock::downWarehouse(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT warehouse  FROM Stock WHERE ";
		sqlString = sqlString +  "item = " + std::to_string((*item).getItem().getID());
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			if(!dt.nextRow()) return false;
			warehouse = dt.getString(0);
			return true;
		}
		return false;
	}


	bool Stock::remove(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "DELETE FROM Stock WHERE ";
		sqlString = sqlString +  "item = " + std::to_string((*item).getItem().getID());
		octetos::db::maria::Datresult dt;
		return connector.remove(sqlString,dt);
	}




	const std::string Supplier::TABLE_NAME = "`Supplier`";
	Supplier::Supplier()
	{
		supplier = NULL;
	}
	Supplier::Supplier(int supplier)
	{
		this->supplier = new Entities(supplier);
	}
	Supplier::Supplier(const Supplier& obj)
	{
		this->nameShort = obj.nameShort;
		this->number = obj.number;
		this->supplier = obj.supplier;
	}
	Supplier::~Supplier()
	{
		if(supplier != NULL)
		{
			delete supplier;
			supplier = NULL;
		}
	}


	const std::string& Supplier::getNameShort() const
	{
		return nameShort;
	}

	int Supplier::getNumber() const
	{
		return number;
	}

	Entities& Supplier::getSupplier() const
	{
		return *supplier;
	}

	int Supplier::getSupplierValue() const
	{
		return (*supplier).getID();
	}


	bool Supplier::upNameShort(octetos::db::maria::Connector& connector,const std::string& nameShort)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "nameShort = " + "'" + nameShort + "'";
		sqlString = sqlString + " WHERE " +  "supplier = " + std::to_string((*supplier).getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}
	bool Supplier::upNumber(octetos::db::maria::Connector& connector,int number)
	{
		std::string sqlString  = "";
		sqlString = "UPDATE " + TABLE_NAME;
		sqlString = sqlString +  " SET " +  "number = " + std::to_string(number);
		sqlString = sqlString + " WHERE " +  "supplier = " + std::to_string((*supplier).getID());
		octetos::db::maria::Datresult dt;
		return connector.update(sqlString,dt);
	}


	bool Supplier::insert(octetos::db::maria::Connector& connector,int number,const std::string& nameShort)
	{
		this->supplier = new Entities();
		if(this->supplier->insert(connector) == false) return false;
		std::string sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(supplier,number,nameShort)";
		sqlString = sqlString + " VALUES(" + std::to_string((*supplier).getID()) + ","  + std::to_string(number) + ","  +  "'"  + nameShort + "'" +  ")";
		octetos::db::maria::Datresult dt;
		if(connector.insert(sqlString,dt))
		{
			return true;
		}
		return false;
	}
	bool Supplier::insert(octetos::db::maria::Connector& connector,const Entities&  supplier,int number,const std::string&  nameShort)
	{
		std::string sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(supplier,number,nameShort)";
		sqlString = sqlString + " VALUES(" + std::to_string(supplier.getID()) + ","  + std::to_string(number) + ","  +  "'"  + nameShort + "'" +  ")";
		octetos::db::maria::Datresult dt;
		if(connector.insert(sqlString,dt))
		{
			this->supplier = new Entities(supplier);
			return true;
		}
		return false;
	}


	std::vector<Supplier*>* Supplier::select(octetos::db::maria::Connector& connector, const std::string& where, int leng, char order)
	{
		std::string sqlString = "SELECT supplier FROM Supplier WHERE ";
		sqlString += where;
		if(order == 'a' || order == 'A')
		{
			sqlString = sqlString + " ORDER BY supplier ASC ";
		}
		else if(order == 'd' || order == 'D')
		{
			sqlString = sqlString + " ORDER BY supplier DESC ";
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
			std::vector<Supplier*>* tmpVc = new std::vector<Supplier*>;
			while(dt.nextRow())
			{
				Supplier* tmp = NULL;
				tmp = new Supplier(dt.getint(0));
				tmpVc->push_back(tmp);
			}
			return tmpVc;
		}
		return NULL;
	}
	bool Supplier::select(octetos::db::maria::Connector& connector,const Entities &supplier)
	{
		std::string sqlString = "SELECT  supplier";
		sqlString = sqlString + " FROM " + TABLE_NAME + " WHERE " +  "supplier = " + std::to_string(supplier.getID());
		octetos::db::maria::Datresult dat;
		bool retflag = connector.select(sqlString,dat);
		if(retflag)
		{
			this->supplier = new Entities(supplier);
		}
		return retflag;
	}


	bool Supplier::downNameShort(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT nameShort  FROM Supplier WHERE ";
		sqlString = sqlString +  "supplier = " + std::to_string((*supplier).getID());
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			if(!dt.nextRow()) return false;
			nameShort = dt.getString(0);
			return true;
		}
		return false;
	}
	bool Supplier::downNumber(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "SELECT number  FROM Supplier WHERE ";
		sqlString = sqlString +  "supplier = " + std::to_string((*supplier).getID());
		octetos::db::maria::Datresult dt;
		bool flag = connector.select(sqlString,dt);
		if(flag)
		{
			if(!dt.nextRow()) return false;
			number = dt.getint(0);
			return true;
		}
		return false;
	}


	bool Supplier::remove(octetos::db::maria::Connector& connector)
	{
		std::string sqlString = "DELETE FROM Supplier WHERE ";
		sqlString = sqlString +  "supplier = " + std::to_string((*supplier).getID());
		octetos::db::maria::Datresult dt;
		return connector.remove(sqlString,dt);
	}




	const std::string Users::TABLE_NAME = "`Users`";
	Users::Users()
	{
		person = NULL;
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
	Users::~Users()
	{
		if(person != NULL)
		{
			delete person;
			person = NULL;
		}
	}


	const std::string& Users::getName() const
	{
		return name;
	}

	Persons& Users::getPerson() const
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
		if(connector.insert(sqlString,dt))
		{
			return true;
		}
		return false;
	}
	bool Users::insert(octetos::db::maria::Connector& connector,const Persons&  person,const std::string&  name)
	{
		std::string sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(person,name)";
		sqlString = sqlString + " VALUES(" + std::to_string(person.getEnte().getID()) + ","  +  "'"  + name + "'" +  ")";
		octetos::db::maria::Datresult dt;
		if(connector.insert(sqlString,dt))
		{
			this->person = new Persons(person);
			return true;
		}
		return false;
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
			this->person = new Persons(person);
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
			if(!dt.nextRow()) return false;
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
			if(!dt.nextRow()) return false;
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
			if(!dt.nextRow()) return false;
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
		ente = NULL;
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
	Versions::~Versions()
	{
		if(ente != NULL)
		{
			delete ente;
			ente = NULL;
		}
	}


	Entities& Versions::getEnte() const
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
		if(connector.insert(sqlString,dt))
		{
			return true;
		}
		return false;
	}
	bool Versions::insert(octetos::db::maria::Connector& connector,const Entities&  ente,unsigned char major)
	{
		std::string sqlString = "";
		sqlString = sqlString + "INSERT INTO "  + TABLE_NAME ; 
		sqlString = sqlString + "(ente,major)";
		sqlString = sqlString + " VALUES(" + std::to_string(ente.getID()) + ","  + std::to_string(major) +  ")";
		octetos::db::maria::Datresult dt;
		if(connector.insert(sqlString,dt))
		{
			this->ente = new Entities(ente);
			return true;
		}
		return false;
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
			this->ente = new Entities(ente);
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
			if(!dt.nextRow()) return false;
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
			if(!dt.nextRow()) return false;
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
			if(!dt.nextRow()) return false;
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
			if(!dt.nextRow()) return false;
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

