
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




#include "login.hh"


namespace mps::server
{



Login::Login() : CGI(muposysdb::datconex)
{
}
Login::~Login()
{
}


bool Login::check()
{
	//std::cout << "Login::check : Step 1.0<br>\n";
	std::string userstr, password;
	//std::cout << "Login::check : Step 1.1<br>\n";
	try
	{
		//std::cout << "Login::check : Step 1.2<br>\n";
		cgicc::Cgicc cgi;
		//std::cout << "Login::check : Step 1.3<br>\n";
		//std::cout << "Login::check  : Step 2<br>\n";
		cgicc::form_iterator itUser = cgi.getElement("user");
		//std::cout << "Login::check  : Step 3<br>\n";
		//std::cout << "Login::check  : Step 4<br>\n";
		if(itUser != (*cgi).end()) 
		{
			//std::cout << "Usuario : " << **itUser << "<br>"; 
			userstr = **itUser;
		}
		else 
		{
			//std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>"; 
			return false;
		}
		
		//std::cout << "check : Step 5<br>\n";
		
		cgicc::form_iterator itPassword = cgi.getElement("psw");  
		if(itPassword != (*cgi).end()) 
		{
			//std::cout << "Contraseña : " << **itPassword << "<br>"; 
			password = **itPassword;
		}
		else 
		{
			//std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";  
			return false;
		}
	}
	catch(const std::exception& e)
	{
		//std::cout << "Fail : " << e.what() << __FILE__ << ":" << __LINE__<< "<br>";  
	}
	
	//std::cout << "check : Step 6<br>\n";	
	
	muposysdb::User* userbd;
	std::string strwhere = "name = ";
	strwhere += "'" + userstr + "' and status = 'autorizado'";
	std::vector<muposysdb::User*>* usrlst = muposysdb::User::select(connDB,strwhere);
	bool fluser;
	if(usrlst->size() == 0)
	{
		//no se encontro elusuario en la BD.
		//std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>"; 
		fluser = false;
	}
	else if(usrlst->size() > 1) 
	{
		//hay muchas coincidencian, este es un error en el diseño de la base de 
		//datos, el nombre de usario deve cumpliar con la restricción de sér único.
		//std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>"; 
		fluser = false;
	}
	else
	{
		userbd = usrlst->at(0);
		fluser = true;
	}
	
	//std::cout << "check : Step 4\n<br>";
	
	if(userbd->downName(connDB) and userbd->downPwdtxt(connDB))
	{
		if(userstr.compare(userbd->getName()) == 0  and password.compare(userbd->getPwdtxt()) == 0)
		{
			//std::cout << "check : Step\n<br>";
			if(register_session(userbd->getName().c_str()))
			{
				if(permission("login"))
				{
					//std::cout << "Step permission\n<br>";
					fluser = true;
				}
				else
				{
					//std::cout << "Not permission\n<br>";
					fluser = false;
				}
			}
			else
			{
				//std::cout << "Fallo registro de secion<br>";		
				fluser = false;
			}
		}
		else
		{
			if(userstr.compare(userbd->getName()) != 0) std::cout << userstr << " != " << userbd->getName () << "<br>";
			if(password.compare(userbd->getPwdtxt()) != 0)std::cout << password << " != " << userbd->getPwdtxt () << "<br>";
		}
	}
	if(usrlst)
	{
		for(auto u : *usrlst)
		{
			delete u;
		}
		delete usrlst;
	}
	return fluser;
}
int Login::main(std::ostream& out)
{
	mps::contenttype(out,"text","html");
	try
	{
		if(check())
		{
			//out << "Location:/application.cgi\n\n";
			head.redirect(0,"/application.cgi");
		}
		else
		{
			//out << "Location:/login.html?failure\n\n";
			head.redirect(0,"/login.html?failure");
		}
		head >> out;
	}
	catch(const std::exception& e)
	{
		std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";	
		//out << "Error : " << e.what() << "<br>\n";
		//head.redirect(0,"/login.html?error");
		//head.print(out);
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}
}


