#ifndef SYSAPP_HTTP_HH
#define SYSAPP_HTTP_HH

#include <openssl/md5.h>
#include <iostream>
#include <string.h>
#include <cgicc/Cgicc.h> 



namespace sysapp::http
{

cgicc::const_form_iterator search(cgicc::const_form_iterator first, cgicc::const_form_iterator last, const std::string& val);

class Session
{
private:	
	std::string host;
	std::string session;

public:
	const std::string& getSession() const;
	const std::string& getHost() const;
	Session(const std::string& id);	
};

}

#endif