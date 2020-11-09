
#include <cgicc/Cgicc.h> 

#include "config.h"
#include "login-server.hh"


namespace sysapp
{


Login::Body::Body(const bool& f) : flagSession(f)
{

}
bool Login::Body::print(std::ostream& out)
{
	out << "<body>\n";	
		
	if(flagSession)
	{
		out << "<br>"<< PACKAGE_STRING << "<br>";
	}
	else
	{
		out << "<br>Usuario/Contraseña incorrectos<br>";
	}
	
	
	out << "</body>\n";
	
	return true;
}










	bool Login::print()
	{
		return buildHTML();
	}
	bool Login::buildHTML()
	{
		out << "<html>\n";
		
	   	buildHead();
	   	html->getBody()->print(out);
	   	
	   	out << "</html>\n";
	   	
	   	return true;
	}
	bool Login::buildHead()
	{
		out << "<head>\n";
	   	cgicc::Cgicc formData;   	
	   	cgicc::form_iterator itUser = formData.getElement("user"); 
	   	if( !itUser->isEmpty() && itUser != (*formData).end()) {  
		  //std::cout << "Usuario : " << **itUser << "<br>";  
	   	} else {
		  	//std::cout << "No text entered for first name \n";  
	   	}
	   	cgicc::form_iterator itPassword = formData.getElement("psw");  
	   	if( !itPassword->isEmpty() && itPassword != (*formData).end()) {  
		  	//std::cout << "Contraseña : " << **itPassword << "<br>"; 
	   	} else {
		  	//std::cout << "No text entered for first name \n";  
	   	}
	   	   	
	   	sysapp::server::Login login;
	   	flagSession = login.check(**itUser,**itPassword);
	   	std::string strredirect = "/sysapp.html?session=";
	   	strredirect += login.getSession();
	   		   		
	   	html->getHead()->print(out);  
	   	
	   	if(flagSession)
	   	{
	   		out << "<meta http-equiv=\"Refresh\" content=\"3;url=" << strredirect << "\"\n";
	   	}
	   	
	   	out << "</head>\n";
	   	
	   	return true;
	}
	
	
	

	Login::~Login()
	{
		delete html;
	}
	Login::Login()
	{
		html = (server::elements::HTML*)contentType(server::elements::ContentType::Text::html);	   
		html->getHead()->setTitle("Procesadon Sesión (nuevo)..");
		html->getHead()->addMetaCharset("UTF-8");
		html->setBody(new Body(flagSession));	
	}	
}