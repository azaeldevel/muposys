
#ifndef MUPOSYS_LOGIN_HH
#define MUPOSYS_LOGIN_HH

#include "http.hh"
#include "html.hh"


namespace muposys::server
{

class Login : public muposys::CGI
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