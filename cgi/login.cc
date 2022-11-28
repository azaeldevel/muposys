
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


namespace muposys::server
{


Login::Login() : CGI(http::db::Conector::database_file,muposysdb::datconex)
{
}
Login::~Login()
{
}


bool Login::check()
{
	
	if(has_session()) 
	{
		connHttp.begin();
		remove_session();
		connHttp.commit();
	}

	
	//std::cout << "Step 1\n<br>";
	cgicc::Cgicc formData;   	
	std::string userstr, password;
	cgicc::form_iterator itUser = formData.getElement("user"); 
	if( !itUser->isEmpty() && itUser != (*formData).end()) 
	{
		//std::cout << "Usuario : " << **itUser << "<br>"; 
		userstr = **itUser;
	}
	else 
	{
		//std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>"; 
		return false;
	}
		
	cgicc::form_iterator itPassword = formData.getElement("psw");  
	if( !itPassword->isEmpty() && itPassword != (*formData).end()) 
	{
		//std::cout << "Contrasena : " << **itPassword << "<br>"; 
		password = **itPassword;
	} 
	else 
	{
		//std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";  
		return false;
	}
	
	//Connector conn;	
	connDB.connect(muposysdb::datconex);
		
	muposysdb::User* userbd;
	std::string strwhere = "name = ";
	strwhere += "'" + userstr + "' and status = 'A'";
	std::vector<muposysdb::User*>* usrlst = muposysdb::User::select(connDB,strwhere);
	if(usrlst->size() == 0)
	{
		//no se encontro elusuario en la BD.
		return false;
	}
	else if(usrlst->size() > 1) 
	{
		//hay muchas coincidencian, este es un error en el diseño de la base de 
		//datos, el nombre de usario deve cumpliar con la restricción de sér único.
		return false;
	}
	else
	{
		userbd = usrlst->at(0);
	}
	//std::cout << "check : Step 2\n<br>";
	if(userbd->downName(connDB) and userbd->downPwdtxt(connDB))
	{
		//std::cout << "userbd ID : " << userbd->getUser().getPerson().getID() << "<br>";
		//std::cout << "check : Step 2.1\n<br>";
		//std::cout << "userbd name : " << userbd->getName () << "<br>";
		//std::cout << "userbd password : " << userbd->getPwdtxt () << "<br>";
		if(userstr.compare(userbd->getName()) == 0  and password.compare(userbd->getPwdtxt()) == 0)
		{
			std::cout << "check : Step\n<br>";
			//std::cout << "password valided\n<br>";
			//std::cout << "Descargo : " << user.getRomoteAddress() << "<br>";			
			//muposys::http::db::Conector connhttp(muposys::http::db::database_file);
			//muposys::http::Session session;
			if(not register_session(userbd->getName().c_str()))
			{
				return false;
			}
			std::cout << "Step login\n<br>";
						
			if(not permission("login"))
			{
				delete usrlst->front();
				delete usrlst;
				//std::cout << "NO tinen permiso<br>\n";
				return false;
			}
			std::cout << "Step permission\n<br>";
			
			delete usrlst->front();
			delete usrlst;
						
			return true;
		}
		else
		{
			//std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";			
			if(userstr.compare(userbd->getName()) != 0) std::cout << userstr << " != " << userbd->getName () << "<br>";
			if(password.compare(userbd->getPwdtxt()) != 0)std::cout << password << " != " << userbd->getPwdtxt () << "<br>";
		}
	}

	delete usrlst->front();
	delete usrlst;
	return false;
}

int Login::main(std::ostream& out)
{
	muposys::contenttype(out,"text","html");
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
		head.print(out);
	}
	catch(const std::exception& e)
	{
		//std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";	
		//out << "Error : " << e.what() << "<br>\n";
		head.redirect(0,"/login.html?error");
		head.print(out);
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}
}


