
#include <muposysdb.hpp>
#include "cgicc/Cgicc.h"
#include "cgicc/HTTPHTMLHeader.h"
#include "cgicc/HTMLClasses.h"

#include "server.hh"



namespace muposys::server
{







bool Login::methode() const
{  	
	cgicc::Cgicc formData;   	
	cgicc::form_iterator itUser = formData.getElement("user"); 
	if( !itUser->isEmpty() && itUser != (*formData).end()) 
	{
		//std::cout << "Usuario : " << **itUser << "<br>";  
	}
	else 
	{
		std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";  
	}
	
   	//std::cout << "Step 2 : \n<br>";
	
	cgicc::form_iterator itPassword = formData.getElement("psw");  
	if( !itPassword->isEmpty() && itPassword != (*formData).end()) 
	{
		//std::cout << "Contrasena : " << **itPassword << "<br>"; 
	} 
	else 
	{
		std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";  
	}
	
   	//std::cout << "Step 3 : \n<br>";
		   		   	
	return check(**itUser,**itPassword);   	 	
}
muposys::http::Session& Login::getSession()
{
	return *session;
}
Login::Login()
{
	session = new muposys::http::Session;
}
Login::Login(const muposys::Body& b) : muposys::HTML(b)
{
	session = new muposys::http::Session;
}
Login::~Login()
{
	if(session) delete session;
}
const std::string& Login::getSessionID()const
{
	return session->getSessionID();
}
bool Login::check(const std::string& userstr,const std::string& password) const
{
#if defined MARIADB
	octetos::db::maria::Connector conn;
#elif defined MYSQL
	octetos::db::mysql::Connector conn;
#elif defined POSTGRESQL
	octetos::db::postgresql::Connector conn;
#else
	#error "Base de datos desconocida."
#endif

	//std::cout << "check : Step 1\n<br>";
	
	conn.connect(muposysdb::datconex);
	
	muposysdb::Users* userbd;
	std::string strwhere = "name = ";
	strwhere += "'" + userstr + "' and status = 'A'";
	std::vector<muposysdb::Users*>* usrlst = muposysdb::Users::select(conn,strwhere);
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
	//std::cout << "check : Step 2\n<br>";
	if(userbd->checkpass(conn))
	{
		//std::cout << "userbd ID : " << userbd->getUser().getPerson().getID() << "<br>";
		//std::cout << "userbd name : " << userbd->getName () << "<br>";
		//std::cout << "userbd password : " << userbd->getPwdtxt () << "<br>";
		if(userstr.compare(userbd->getName()) == 0  and password.compare(userbd->getPwdtxt()) == 0)
		{
			//std::cout << "Descargo : " << user.getRomoteAddress() << "<br>";
			muposys::http::db::Conector connhttp(muposys::http::db::database_file);
			if(session->addregister(connhttp))
			{
				std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
			}
			muposys::http::db::Variable var;
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
void Login::print(std::ostream& out) const
{
	muposys::HTML::print(out);
}
void Login::main()
{
	contenttype(std::cout,"text","html");
	doctype(std::cout,"html");
	if(methode())
	{
		head.redirect(0,"/application.cgi");
	}
	print(std::cout);
}


} 
