#ifndef SYSAPP_HTTP_HH
#define SYSAPP_HTTP_HH

#include <openssl/md5.h>
#include <iostream>
#include <string.h>


#include "db.hh"

namespace sysapp::http
{

class Session
{
private:	
	std::string host;
	unsigned char digest[MD5_DIGEST_LENGTH];
	std::string session;

public:
	const std::string& getSession() const;
	const std::string& getHost() const;
	Session();
	
};

}

#endif