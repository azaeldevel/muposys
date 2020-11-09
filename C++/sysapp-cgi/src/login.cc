
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


#include "http.hh"
#include "server.hh"


int main ()
{
	std::cout << "Content-type:text/html\r\n\r\n";
   	std::cout << "<html>\n";
   	std::cout << "<head>\n";
   	std::cout << "<meta charset=\"utf-8\">\n";
   	std::cout << "<title>Procesadon Sesión..</title>\n";
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
   	bool flag = login.check(**itUser,**itPassword);
   	std::string strredirect = "/sysapp.html?session=";
   	strredirect += login.getSession();
   	
   	if(flag)
   	{
   		std::cout << "<meta http-equiv=\"Refresh\" content=\"1;url=" << strredirect << "\"\n";
   	}
   	
   	std::cout << "</head>\n";
   	std::cout << "<body>\n";
	
   	
   	if(not flag)
   	{
   		std::cout << "<br>Usuario/Contraseña incorrectos<br>";
   	}
		
   	
   	std::cout << "<br/>\n";
   	std::cout << "</body>\n";
   	std::cout << "</html>\n";
   
   return 0;
}

