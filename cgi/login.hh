
#ifndef MUPOSYS_LOGIN_HH
#define MUPOSYS_LOGIN_HH

#include "http.hh"
#include "html.hh"
#include <apidb/muposysdb.hpp>

namespace muposys::server
{

class Login : public muposys::CGI
{
private:
	
	bool check();

public:
	Login();
	Login(const muposys::Body&);
	~Login();
	
	virtual int main(std::ostream& out = std::cout);
};

}



#endif