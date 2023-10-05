
#ifndef MUPOSYS_LOGIN_HH
#define MUPOSYS_LOGIN_HH


#include "html.hh"


namespace oct::mps::v1
{


class Logout : public CGI
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
