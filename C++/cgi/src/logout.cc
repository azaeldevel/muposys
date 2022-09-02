
#include <iostream>
#include "server.hh"
#include <cgicc/HTTPRedirectHeader.h>
#include <cgicc/HTTPHTMLHeader.h>

int main()
{
	std::cout << cgicc::HTTPHTMLHeader() << "\n";
	std::cout << "Step 1\n";
	muposys::http::db::Conector conn(muposys::http::db::database_file);
	muposys::http::db::Session session;
	conn.begin();
	std::cout << "Step 2\n";
	if(session.selectByRemoteAddr(conn,getenv("REMOTE_ADDR"))) 
	{
		std::cout << "Operation..\n";
		session.remove(conn);
		std::cout << "<head><meta http-equiv=\"refresh\" content=\"0;url=/application.cgi\"></head>\n";
	}
	conn.commit();
	conn.close();
	std::cout << "Step 3\n";
	return 0;		
}