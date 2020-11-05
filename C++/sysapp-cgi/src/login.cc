
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

#include <iostream>
#include <vector>  
#include <string>  
#include <stdio.h>  
#include <stdlib.h> 



#include <cgicc/CgiDefs.h> 
#include <cgicc/Cgicc.h> 
#include <cgicc/HTTPHTMLHeader.h> 
#include <cgicc/HTMLClasses.h>  

#include "db.hh"

   
using namespace std;
using namespace cgicc;

int main () {
	
	Cgicc formData;
	
	cout << "Content-type:text/html\r\n\r\n";
   	cout << "<html>\n";
   	cout << "<head>\n";
   	cout << "<title>Using GET and POST Methods</title>\n";
   	cout << "</head>\n";
   	cout << "<body>\n";

   	form_iterator fi = formData.getElement("user"); 
   	std::string u; 
   	if( !fi->isEmpty() && fi != (*formData).end()) {  
      cout << "Usuario : " << **fi << "<br>";  
      u = **fi;
   	} else {
      	cout << "No text entered for first name " << endl;  
   	}
   
   	const char* host = getenv("REMOTE_ADDR");
   	//const char *host = "host6";
   	//std::cout << "<br>Host : " << host << "\n";
   	//std::cout << "<br>REMOTE USER : " << getenv("REMOTE_USER") << "\n";
   	sysapp::db::sqlite::Conector conn("database");
   	//std::string var = "REMOTE_USER=";
   	//var+=u;
	//setenv("REMOTE_USER",u.c_str(),1);
   	sysapp::db::sqlite::User user;
   	conn.begin();
   	if(user.selectByRemoteAddr(conn,host))//existe?
   	{
  		if(user.downloadIDs(conn))
  		{
  			std::cout << "Descargo : " << user.getRomoteAddress() << "<br>";
  		}
  		else
  		{
  			std::cout << "Fallo Descarga<br>";
  		}
   	}
   	else
   	{
   		if(user.inserteRemoteAddr(conn,host))
   		{
   			std::cout << "Inserted addr: " << user.getID() << "<br>";
   			if(user.updateSession(conn,host))
   			{
   				std::cout << "updates session : " << host << "<br>";
   			}
   			else
   			{
   				std::cout << "Fail update session : "<< "(" << conn.getErrorCode() << ") " << conn.getErrorMessage() << "<br>";
   			}
   		}
   		else
   		{
  			std::cout << "Fail insert : " << conn.getErrorMessage() << "<br>";
  		}
   	}
   	conn.commit();
   	conn.close();
   
   	cout << "<br/>\n";
   	cout << "</body>\n";
   	cout << "</html>\n";
   
   return 0;
}

