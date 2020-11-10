#ifndef SYSAPP_HTTP_HH
#define SYSAPP_HTTP_HH

#include <openssl/md5.h>
#include <iostream>
#include <string.h>




namespace sysapp::http
{

class Session
{
private:	
	std::string host;
	std::string session;

public:
	const std::string& getSession() const;
	const std::string& getHost() const;
	Session();
	
};

}

#endif