
#include <muposysdb.hpp>


#include "server.hh"

enum StatusCode
{
	SUCCEFULY,
	USER_ALREADY_EXISTE,
	
	PASSWORD_NOT_MATCH,
};
/**
*@brief Realiza el registro de un uevo usario
*return 0 si es completado satisfactoriamente, 1 contraseñas no coinciden, 2 el usuario ya existe
*/
int validRegister(cgicc::Cgicc& cgi)
{
	cgicc::const_form_iterator it;
	
	//verificar si existe usuario
	it = muposys::http::search(cgi.getElements().begin(),cgi.getElements().end(),"user");
#if defined MARIADB
	octetos::db::mariadb::Connector conn;
#elif defined MYSQL
	octetos::db::mysql::Connector conn;
#elif defined POSTGRESQL
	octetos::db::postgresql::Connector conn;
#else
	#error "Base dedatos desconocida."
#endif
	conn.connect(muposysdb::datconex);
	muposysdb::Users* userbd;
	std::vector<muposysdb::Users*>* usrlst = muposysdb::Users::selecrUserByName(conn,(*it).getValue());
	if(usrlst->size() == 0)
	{
		//no existe el usuario, proceso correcto		
	}
	else if(usrlst->size() > 1) 
	{
		//hay muchas coincidencian, este es un error en el diseño de la base de 
		//datos, el nombre de usario deve cumpliar con la restricción de sér único.
		return USER_ALREADY_EXISTE;
	}
	else
	{
		userbd = usrlst->at(0);
	}
	delete usrlst;
	conn.close();
	std::cout << "Nombre de usuario disponoble<br>";
	
	
	//verificar contraseña
	it = muposys::http::search(cgi.getElements().begin(),cgi.getElements().end(),"psw");
	std::string psw = (*it).getValue();
	it = muposys::http::search(cgi.getElements().begin(),cgi.getElements().end(),"pswconfirm");
	std::string pswconfirm = (*it).getValue();
	if(psw.compare(pswconfirm) == 0)
	{
		return PASSWORD_NOT_MATCH;
	}
	std::cout << "Contraseñas correctas<br>";
	
	return 0;
}


int main()
{

	std::cout << "Content-type:text/html\r\n\r\n";
   	std::cout << "<html>\n";
   	std::cout << "<head>\n";
   	std::cout << "</head>\n";
   	std::cout << "<body>\n";
   	
	cgicc::Cgicc cgi;
	bool accepted = false;
	int statuscode = 0;
	cgicc::const_form_iterator it = muposys::http::search(cgi.getElements().begin(),cgi.getElements().end(),"type");
	if(it != cgi.getElements().end())
	{
		if((*it).getValue().compare("register") == 0)
		{
			statuscode = validRegister(cgi);
		}
		else
		{
		
		}
	}
	else
	{
		std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
	}
	
	
   	std::cout << "</body>\n";
   	std::cout << "</html>\n";
   	
	return 0;
}