
#ifndef MUPOSYS_LOGIN_HH
#define MUPOSYS_LOGIN_HH


#include "html.hh"


namespace mps::server
{


class Logout : public mps::CGI
{
private:


public:
	Logout();
	virtual ~Logout();

	virtual int main(std::ostream& out = std::cout);
};


}



#endif
