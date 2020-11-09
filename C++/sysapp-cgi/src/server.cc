
#include <sysappdb.hpp>


#include "server.hh"



namespace sysapp::server
{

const char* Login::getSessionID()const
{
	return session.getMD5();
}
bool Login::check(const std::string& userstr,const std::string& password)
{
	octetos::db::mysql::Connector conn;
	conn.connect(sysappdb::datconex);
	
	sysappdb::Users* userbd;
	std::vector<sysappdb::Users*>* usrlst = sysappdb::Users::selecrUserByName(conn,userstr);
	if(usrlst->size() == 0)
	{
		//no se encontro elusuario en la BD.
		return false;
	}
	else if(usrlst->size() > 1) 
	{
		//hay muchas coincidencian, este es un error en el diseño de la base de 
		//datos, el nombre de usario deve cumpliar con la restricción de sér único.
		return false;
	}
	else
	{
		userbd = usrlst->at(0);
	}
	
	if(userbd->checkpass(conn))
	{
		if(userstr.compare(userbd->getName()) == 0  and password.compare(userbd->getPwdtxt()) == 0)
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