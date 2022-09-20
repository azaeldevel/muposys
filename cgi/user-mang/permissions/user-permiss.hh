
#ifndef MUPOSYS_USER_PERMISSIONS_HH
#define MUPOSYS_USER_PERMISSIONS_HH


#include <apidb/muposysdb.hpp>

#include "../../application.hh"

namespace muposys
{

class BodyUserPermission : public BodyApplication
{
public:
	BodyUserPermission();
	~BodyUserPermission();


	virtual void print(std::ostream& out) const;

private:
	std::vector<muposysdb::Users*>* userlst;
	std::vector<muposysdb::Permissions*>* permisslst;
	
#if defined MARIADB
	octetos::db::maria::Connector conn;
#elif defined MYSQL
	octetos::db::mysql::Connector conn;
#elif defined POSTGRESQL
	octetos::db::postgresql::Connector conn;
#else
	#error "Base de datos desconocida."
#endif
};

class UserPermission : public Application
{	
public:	
	UserPermission(BodyUserPermission& );
	~UserPermission();

	virtual int main(std::ostream& out = std::cout);
	
private:	
	cgicc::Cgicc formData;
#if defined MARIADB
	octetos::db::maria::Connector connDB;
#elif defined MYSQL
	octetos::db::mysql::Connector connDB;
#elif defined POSTGRESQL
	octetos::db::postgresql::Connector connDB;
#else
	#error "Base de datos desconocida."
#endif
	//std::vector<muposysdb::Permissions*>* permisslst;
	std::vector<muposysdb::Users*>* userlst;

	bool methode(std::ostream& out);

};

}

#endif