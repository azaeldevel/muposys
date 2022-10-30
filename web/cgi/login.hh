
#ifndef MUPOSYS_LOGIN_HH
#define MUPOSYS_LOGIN_HH


#include "html.hh"


namespace mps::server
{

class Login : public mps::CGI
{
private:
	
	bool check();

public:
	Login();
	~Login();
	
	virtual int main(std::ostream& out = std::cout);
};

}



#endif
