
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







#include "server.hh"



int main ()
{
	std::cout << "Content-type:text/html\r\n\r\n";
   	std::cout << "<html>\n";
   	std::cout << "<head>\n";
	
   	std::cout << "Step 1 : \n<br>";
	
   	cgicc::Cgicc formData;   	
	cgicc::form_iterator itUser = formData.getElement("user"); 
	if( !itUser->isEmpty() && itUser != (*formData).end()) 
	{
		std::cout << "Usuario : " << **itUser << "<br>";  
	}
	else 
	{
		std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";  
	}
	
   	std::cout << "Step 2 : \n<br>";
	
	cgicc::form_iterator itPassword = formData.getElement("psw");  
	if( !itPassword->isEmpty() && itPassword != (*formData).end()) 
	{
		std::cout << "Contraseña : " << **itPassword << "<br>"; 
	} 
	else 
	{
		std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";  
	}
	
   	std::cout << "Step 3 : \n<br>";
		   		   	
	muposys::server::Login login;
	bool flagSession = login.check(**itUser,**itPassword);
	std::string strredirect = "/cgi/application?session=";
	strredirect += login.getSessionID();
	
   	std::cout << "Step 4 : \n<br>";
		   	
	if(flagSession)
	{
		std::cout << "<meta http-equiv=\"Refresh\" content=\"0;url=" << strredirect << "\"\n";
	}
   	
   	std::cout << "</head>\n";
   	std::cout << "<body>\n";
   	std::cout << "</body>\n";
   	std::cout << "</html>\n";
		   	
	return 0;
}

