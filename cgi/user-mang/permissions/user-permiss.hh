
#ifndef MUPOSYS_USER_PERMISSIONS_HH
#define MUPOSYS_USER_PERMISSIONS_HH


#include "../../application.hh"

namespace muposys
{

class BodyUserPermission : public BodyApplication
{
private:	
public:
	BodyUserPermission();

	virtual void print(std::ostream& out) const;

};

class UserPermission : public Application
{	
public:	
	UserPermission(const BodyUserPermission& );
	~UserPermission();

	virtual int main(std::ostream& out = std::cout);
	
private:	
	cgicc::Cgicc formData;
	bool cgi;
};

}

#endif