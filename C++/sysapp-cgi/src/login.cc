
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



#include "http.hh"


int main ()
{
	std::cout << "Content-type:text/html\r\n\r\n";
   	std::cout << "<html>\n";
   	std::cout << "<head>\n";
   	std::cout << "<title>Preccesiong login..</title>\n";
   	std::cout << "</head>\n";
   	std::cout << "<body>\n";

   	/*cgicc::form_iterator fi = formData.getElement("user"); 
   	std::string u; 
   	if( !fi->isEmpty() && fi != (*formData).end()) {  
      std::cout << "Usuario : " << **fi << "<br>";  
      u = **fi;
   	} else {
      	std::cout << "No text entered for first name \n";  
   	}*/
   
   	
   	
   	sysapp::http::Session session;
   	
   	
   	std::cout << "<br>Host : " << session.getHost() << "<br>";
   	std::cout << "<br>MD5 : " << session.getMD5() << "<br>";
   	
   
   	std::cout << "<br/>\n";
   	std::cout << "</body>\n";
   	std::cout << "</html>\n";
   
   return 0;
}

