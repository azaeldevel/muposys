
#include <iostream>
#include "server.hh"
#include "cgicc/HTTPHTMLHeader.h"

int main()
{
	std::cout << cgicc::HTTPHTMLHeader() << "\n";
	muposys::http::db::Conector conn(muposys::http::db::database_file);
	muposys::http::db::Session session;
	conn.begin();
	if(session.selectByRemoteAddr(conn,getenv("REMOTE_ADDR"))) 
	{
		session.remove(conn);
		std::cout << "<meta http-equiv=\"refresh\" content=\"0;url=login.html\"\n";
	}
	conn.commit();
	conn.close();
		   	
	return 0;		
}