
#include <muposysdb.hpp>


#include "server.hh"

enum StatusCode
{
	SUCCEFULY,
	USER_ALREADY_EXISTE,	
	PASSWORD_NOT_MATCH,
	NOT_FOUND_NAME1,
	EMPTY_NAME1,
	FAIL_INSERT_NAME1,
	NOT_FOUND_NAME2,
	EMPTY_NAME2,
	FAIL_UPDATE_NAME2,
	FAIL_CREATE_REGISTER,
	FAIL_EMTY_USERNAME,
	FAIL_ON_SAVE,
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
	std::string username = (*it).getValue();
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
	std::string strnamewhere= "name = '";
	strnamewhere += username + "' and status = 'A'";
	std::vector<muposysdb::Users*>* usrlst = muposysdb::Users::select(conn,strnamewhere);
	if(usrlst->size() == 0)
	{
		std::cout << "<h1>no existe el usuario, proceso correcto</h1>\n";
	}
	else if(usrlst->size() >= 1) 
	{
		//hay muchas coincidencian, este es un error en el diseño de la base de 
		//datos, el nombre de usario deve cumpliar con la restricción de sér único.
		std::cout << "<h1>ya existe el usuario, proceso correcto</h1>\n";
		return USER_ALREADY_EXISTE;
	}
	
	//verificar contraseña
	std::string psw = **(cgi.getElement("psw")); 
	std::string pswconfirm = **(cgi.getElement("pswconfirm")); 
	if(psw.compare(pswconfirm) == 0)
	{
		std::cout << "<h1>Contraseñas correctas</h1>\n";
		return PASSWORD_NOT_MATCH;
	}
	//std::cout << "Contraseñas correctas<br>";
	
	
	//creando person
	muposysdb::Persons person;	
	std::string name1 = **(cgi.getElement("name1")); 
	if(name1.empty())
	{
		return EMPTY_NAME1;
	}
		
	//creating user
	std::string userstr = **(cgi.getElement("user"));
	if(userstr.empty())
	{
		return FAIL_EMTY_USERNAME;
	}
	muposysdb::Users user;	
	if(not user.insert(conn,name1,userstr))
	{
		std::cout << "<h1>Fallo insert user</h1>\n";
		return FAIL_CREATE_REGISTER;
	}
	else
	{
		std::cout << "<h1>Completado : insert user</h1>\n";
	}
	
	if(not user.updateStatus(conn,"R"))
	{
		std::cout << "<h1>Fallo update status</h1>\n";
		return FAIL_ON_SAVE;
	}
	else
	{
		std::cout << "<h1>Completado : update status</h1>\n";
	}
	if(not user.updatePwdtxt(conn,psw))
	{
		std::cout << "<h1>Fallo update password</h1>\n";
		return FAIL_ON_SAVE;
	}
	else
	{
		std::cout << "<h1>Completado : update password</h1>\n";
	}
	
	if(not conn.commit())
	{
		std::cout << "<h1>Fallo commit</h1>\n";
		return FAIL_ON_SAVE;
	}
	else
	{
		std::cout << "<h1>Completado commit</h1>\n";
	}
	delete usrlst;
	
	return SUCCEFULY;
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
	std::string typestr = **(cgi.getElement("register"));
	if(typestr.compare("register") == 0)
	{
		statuscode = validRegister(cgi);
	}	

	if(statuscode != SUCCEFULY)
	{
		std::cout << "<h1>Un error ocurrio</h1>\n";
	}
	else
	{
		std::cout << "<h1>Completado</h1>\n";
	}
	
   	std::cout << "</body>\n";
   	std::cout << "</html>\n";
   	
	return 0;
}