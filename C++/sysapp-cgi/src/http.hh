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
	char mdString[33];
	const char* host;
	unsigned char digest[MD5_DIGEST_LENGTH];
	
public:
	const char* getMD5() const;
	const char* getHost() const;
	Session();
	
};

}

#endif