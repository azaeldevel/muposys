
#include <sysappdb.hpp>


#include "server.hh"



namespace sysapp::server
{


const sysapp::http::Session& Login::getSession()const
{
	return *session;
}
Login::Login(const std::string& s)
{
	session = new sysapp::http::Session(s);
}
Login::Login()
{
	session = new sysapp::http::Session("");
}
const std::string& Login::getSessionID()const
{
	return session->getSessionID();
}
bool Login::check(const std::string& userstr,const std::string& password)
{
#if defined MARIADB
	octetos::db::mariadb::Connector conn;
#elif defined MYSQL
	octetos::db::mysql::Connector conn;
#elif defined POSTGRESQL
	octetos::db::postgresql::Connector conn;
#else
	#error "Base dedatos desconocida."
#endif

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
			//std::cout << "Descargo : " << user.getRomoteAddress() << "<br>";
			sysapp::http::db::Conector connhttp("database");
			sysapp::http::db::Variable var;
			if(var.insert(connhttp,session->getSession(),"user",userbd->getName()))
			{
				
			}
			else
			{
				std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
			}
			connhttp.close();
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
