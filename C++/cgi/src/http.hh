#ifndef SYSAPP_HTTP_HH
#define SYSAPP_HTTP_HH

#include <openssl/md5.h>
#include <iostream>
#include <string.h>
#include <cgicc/Cgicc.h> 


#include "http-db.hh"

namespace muposys::http
{

cgicc::const_form_iterator search(cgicc::const_form_iterator first, cgicc::const_form_iterator last, const std::string& val);

class Session
{
private:	
	std::string host;
	//std::string session;
	muposys::http::db::Session session;
	
public:
	const std::string& getSessionID() const;
	const std::string& getHost() const;
	[[deprecated("Use constructor vacio de preferencia.")]] Session(const std::string& id);	
	Session();
	muposys::http::db::Session& getSession();
	bool addregister(muposys::http::db::Conector&);
};

}

#endif