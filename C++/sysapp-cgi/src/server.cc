
#include <sysappdb.hpp>


#include "server.hh"



namespace sysapp::server
{

bool Login::check(const std::string& userstr,const std::string& password)
{
	octetos::db::mysql::Connector conn;
	conn.connect(sysappdb::datconex);
	
	sysappdb::Users user(1);
	
	if(user.checkpass(conn))
	{
		if(userstr.compare(user.getName()) == 0  and password.compare(user.getPwdtxt()) == 0)
		{
			conn.close();
			return true;
		}
		else
		{
			conn.close();
			return false;
		}
	}
	else
	{
		conn.close();
		return false;
	}
}


} 