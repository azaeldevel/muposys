#ifndef SYSAPP_WEBSERVER_HH
#define SYSAPP_WEBSERVER_HH

#include <openssl/md5.h>
#include <iostream>
#include <string.h>
#include <cgicc/Cgicc.h> 

#include "db.hh"

namespace sysapp::http
{

class Session
{
private:
	cgicc::Cgicc formData;
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