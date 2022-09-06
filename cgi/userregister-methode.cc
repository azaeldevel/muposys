
#include <apidb/muposysdb.hpp>

#include "http.hh"

enum StatusCode
{
	FAILCODE,
	SUCCEFULY,
	USER_ALREADY_EXISTE,	
	PASSWORD_NOT_MATCH,
	NOT_FOUND_NAME1,
	EMPTY_NAME1,
	FAIL_INSERT_NAME1,
	NOT_FOUND_NAME2,
	EMPTY_NAME2,
	NOT_FOUND_NAME3,
	EMPTY_NAME3,
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
	octetos::db::maria::Connector conn;
#elif defined MYSQL
	octetos::db::mysql::Connector conn;
#elif defined POSTGRESQL
	octetos::db::postgresql::Connector conn;
#else
	#error "Base dedatos desconocida."
#endif
	if(!conn.connect(muposysdb::datconex))
	{
		std::cout << "<h1>fallo la conexion</h1>\n";
	}
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
	if(psw.compare(pswconfirm) != 0)
	{
		std::cout << "<h1>Contraseñas incorrectas " << psw << " != " << pswconfirm << "</h1>\n";
		return PASSWORD_NOT_MATCH;
	}
	
	//creando person
	muposysdb::Persons person;	
	std::string name1 = **(cgi.getElement("name1")); 
	if(name1.empty())
	{
		std::cout << "<h1>Error : Nombre vacio</h1>\n";
		return EMPTY_NAME1;
	}
		
	//creating user
	std::string userstr = **(cgi.getElement("user"));
	if(userstr.empty())
	{
		std::cout << "<h1>Error : Usuario vacio</h1>\n";
		return FAIL_EMTY_USERNAME;
	}
	muposysdb::Entities ente1;
	if(not ente1.insert(conn))
	{
		std::cout << "<h1>Fallo insert ente</h1>\n";
		return FAIL_CREATE_REGISTER;
	}
	muposysdb::Persons per1;
	if(not per1.insert(conn,ente1,name1))
	{
		std::cout << "<h1>Fallo insert person</h1>\n";
		return FAIL_CREATE_REGISTER;
	}
	muposysdb::Users user;	
	if(not user.insert(conn,per1,name1))
	{
		std::cout << "<h1>Fallo insert user</h1>\n";
		return FAIL_CREATE_REGISTER;
	}
	else
	{
		std::cout << "<h1>Completado : insert user</h1>\n";
	}
	
	if(not user.upStatus(conn,"R"))
	{
		std::cout << "<h1>Fallo update status</h1>\n";
		return FAIL_ON_SAVE;
	}
	else
	{
		std::cout << "<h1>Completado : update status</h1>\n";
	}
	if(not user.upPwdtxt(conn,psw))
	{
		std::cout << "<h1>Fallo update password</h1>\n";
		return FAIL_ON_SAVE;
	}
	else
	{
		std::cout << "<h1>Completado : update password</h1>\n";
	}
	std::string name3 = **(cgi.getElement("name3")); 
	if(name3.empty())
	{
		std::cout << "<h1>Error : Nombre vacio</h1>\n";
		return EMPTY_NAME3;
	}	
	if(not user.getPerson().upName3(conn,name3))
	{
		std::cout << "<h1>Fallo update name3</h1>\n";
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
	conn.close();
	
	return SUCCEFULY;
}


int main()
{
	std::cout << "Content-type:text/html\r\n\r\n";
   	std::cout << "<html>\n";
   	std::cout << "<head>\n";
	cgicc::Cgicc cgi;
	bool accepted = false;
	int statuscode = 0;
	std::string typestr = **(cgi.getElement("type"));
	if(typestr.compare("register") == 0)
	{
		try
		{
			statuscode = validRegister(cgi);
		}
		catch(std::exception& ex)
		{
			std::cout << "<h1>" << ex.what() << "</h1>\n";
		}
	}
	else
	{
		std::cout << "<h1>No se detecto la bandera de registro</h1>\n";
	}
	if(statuscode == SUCCEFULY) 
	{
		//enviar correo electronico de confirmacion
		//ir a pagina de login
		std::cout << "<meta http-equiv=\"refresh\" content=\"0;url=/login.html\"/>\n";
	}
	
   	std::cout << "</head>\n";
   	std::cout << "<body>\n";	
	
	if(statuscode != SUCCEFULY)
	{
		std::cout << "<h1>Un error ocurrio</h1>\n";
	}
	else
	{
		std::cout << "<h1>Completado...</h1>\n";
	}
   	std::cout << "</body>\n";
   	std::cout << "</html>\n";
   	
	return 0;
}