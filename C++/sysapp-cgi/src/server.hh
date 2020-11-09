#ifndef SYSAPP_SERVER_HH
#define SYSAPP_SERVER_HH

#include <string>

#include "http.hh"

namespace sysapp::server
{

class Login
{
private:	
	sysapp::http::Session session;
	

public:
	bool check(const std::string&,const std::string&);
	const std::string& getSession()const;
};

}

#endif