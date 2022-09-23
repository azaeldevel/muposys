
#ifndef MUPOSYS_USER_PERMISSIONS_HH
#define MUPOSYS_USER_PERMISSIONS_HH


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
	
	Connector conn;
};

class UserPermission : public Application
{	
public:	
	UserPermission(BodyUserPermission& );
	~UserPermission();

	virtual int main(std::ostream& out = std::cout);
	
private:	
	cgicc::Cgicc formData;
	Connector connDB;
	//std::vector<muposysdb::Permissions*>* permisslst;
	std::vector<muposysdb::Users*>* userlst;

	bool methode(std::ostream& out);

};

}

#endif