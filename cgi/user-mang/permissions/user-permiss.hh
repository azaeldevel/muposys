
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
	UserPermission(const BodyUserPermission& );
	~UserPermission();

	virtual int main(std::ostream& out = std::cout);
	
private:	
	cgicc::Cgicc formData;


};

}

#endif