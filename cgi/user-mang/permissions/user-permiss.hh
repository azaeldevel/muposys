
#ifndef MUPOSYS_USER_PERMISSIONS_HH
#define MUPOSYS_USER_PERMISSIONS_HH


#include "../../application.hh"

namespace muposys
{

class BodyUserPermission : public BodyApplication
{
private:
	
public:
	virtual void print(std::ostream& out) const;
	virtual void options(std::ostream& out) const;	
};

class UserPermission : public Application
{	
public:
	
	UserPermission(const BodyUserPermission& );
	~UserPermission();

private:	
	
};

}

#endif