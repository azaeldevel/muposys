
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
	muposys::http::Session* session;
	
	bool check()const;

public:
	Login();
	Login(const muposys::Body&);
	~Login();
	
	const std::string& getSessionID()const;
	muposys::http::Session& getSession();

	virtual int main(std::ostream& out = std::cout);
};

}



#endif