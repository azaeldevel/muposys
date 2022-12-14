
#ifndef MUPOSYS_LOGIN_HH
#define MUPOSYS_LOGIN_HH


#include "html.hh"


namespace mps
{


class Logout : public mps::CGI
{
private:
	const Params& params;

public:
	Logout(const Params&);
	virtual ~Logout();

	virtual int main(std::ostream& out = std::cout);
};


}



#endif
