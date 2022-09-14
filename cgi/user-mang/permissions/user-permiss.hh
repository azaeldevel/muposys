
#ifndef MUPOSYS_USER_PERMISSIONS_HH
#define MUPOSYS_USER_PERMISSIONS_HH


#include "../../application.hh"

namespace muposys
{

class BodyUserPermission : public BodyApplication
{
private:	
public:
};

class UserPermission : public Application
{	
public:	
	UserPermission(const BodyUserPermission& );
	~UserPermission();

	virtual int main(std::ostream& out = std::cout);
	
private:	
	
};

}

#endif