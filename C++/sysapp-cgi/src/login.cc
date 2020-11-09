
/*
 * main.cc
 * Copyright (C) 2020 Azael R. <azael.devel@gmail.com>
 * 
 * sysapp-cgi is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * sysapp-cgi is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */



#include <cgicc/Cgicc.h> 


#include "server.hh"

namespace sysapp
{

class Login : public server::elements::Content
{
private:
	server::elements::HTML* html;
	bool flagSession;
	
	
	bool buildHead()
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
	   		out << "<meta http-equiv=\"Refresh\" content=\"5;url=" << strredirect << "\"\n";
	   	}
	   	
	   	out << "</head>\n";
	   	
	   	return true;
	}
	bool buildHTML()
	{
		out << "<html>\n";
		
	   	buildHead();
	   	
	   	out << "<body>\n";		
	   	
	   	if(not flagSession)
	   	{
	   		std::cout << "<br>Usuario/Contraseña incorrectos<br>";
	   	}
			
	   	
	   	out << "<br/>\n";
	   	out << "</body>\n";
	   	out << "</html>\n";
	   	
	   	return true;
	}
	
public:
	virtual bool print()
	{
		return buildHead();
	}
	
	Login()
	{
		html = (server::elements::HTML*)contentType(server::elements::ContentType::Text::html);	   
		html->getHead()->setTitle("Procesadon Sesión (nuevo)..");
		html->getHead()->addMetaCharset("UTF-8");	
	}
	~Login()
	{
		delete html;
	}
};

}

int main ()
{
	sysapp::Login login;
   	login.print();
   	
   	return 0;
}

