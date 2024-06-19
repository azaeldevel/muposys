
#ifndef MUPOSYS_LOGIN_HH
#define MUPOSYS_LOGIN_HH


#include "html.hh"

namespace oct::mps::v1::server
{

class Login : public CGI
{
private:

	bool check(std::string&);

public:
	Login();
	~Login();

	bool check(const Parameters&);

	virtual int main(std::ostream& out = std::cout);


};

}



#endif
