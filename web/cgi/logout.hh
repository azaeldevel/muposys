
#ifndef MUPOSYS_LOGIN_HH
#define MUPOSYS_LOGIN_HH

#include "http.hh"
#include "html.hh"
#include <muposys/apidb.hh>

namespace muposys::server
{


class Logout : public muposys::CGI
{
private:	
public:
	Logout();
	virtual ~Logout();
	
	virtual int main(std::ostream& out = std::cout);
};


}



#endif
