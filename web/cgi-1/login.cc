
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


namespace oct::mps::v1::server
{



Login::Login() : CGI(default_dtm0())
{
}
Login::~Login()
{
}


bool Login::check(std::string& strs)
{
	//std::cout << "Login::check : Step 1.0<br>\n";
	std::string userstr, password;
	//std::cout << "Login::check : Step 1.1<br>\n";

	PostParams postparams;
	if(postparams.find("user")) userstr = postparams.find("user");
	if(postparams.find("psw")) password = postparams.find("psw");

	//std::cout << "check : Step 6<br>\n";

	User* userbd;
	std::string strwhere = "name = ";
	strwhere += "'" + userstr + "' and status = 3";
	//std::vector<muposysdb::User*>* usrlst = muposysdb::User::select(connDB,strwhere);
	std::vector<User> usrlst;
    bool usrlst_flag = false;
    try
    {
 		 usrlst_flag = connDB.select(usrlst,strwhere);
	}
	catch (const cave0::ExceptionDriver&)
	{
	}
	catch (...)
	{
	}
	bool fluser = false;
	if(usrlst.size() == 0)
	{
		//no se encontro elusuario en la BD.
		//std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
	}
	else if(usrlst.size() > 1)
	{
		//hay muchas coincidencian, este es un error en el diseño de la base de
		//datos, el nombre de usario deve cumpliar con la restricción de sér único.
		//std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
	}
	else
	{
		userbd = &usrlst.at(0);
	}

	//std::cout << "check : Step 4\n<br>";

	//if(userbd->size() == 1)
	{
		if(userbd->valid and  usrlst_flag)
		{
			//std::cout << "check pass : Step\n<br>";
			if(create_session(userbd->name.c_str(),strs))
			{
				//std::cout << "Step login permission\n<br>";
				if(permission("login",userbd->name.c_str()))
				{
					//std::cout << "Step permission\n<br>";
					fluser = true;
				}
				else
				{
					//std::cout << "Not permission\n<br>";
				}
			}
			else
			{
				//std::cout << "Fallo registro de secion<br>";
			}
			//std::cout << "Done check \n<br>";
		}
		else
		{
			//if(userstr.compare(userbd->getName()) != 0) std::cout << userstr << " != " << userbd->getName () << "<br>";
			//if(password.compare(userbd->getPwdtxt()) != 0)std::cout << password << " != " << userbd->getPwdtxt () << "<br>";
		}
	}
	/*if(usrlst)
	{
		for(auto u : *usrlst)
		{
			delete u;
		}
		delete usrlst;
	}*/

	//std::cout << (fluser? "check pass" : "check fail") << "\n";
	return fluser;
}
int Login::main(std::ostream& out)
{
	/*mps::contenttype(out,"text","html");
	std::string strsession;
	try
	{
		if(check(strsession))
		{
			std::string url = "application.cgi?session=" + strsession;
			//out << "url : " << url << "\n";
			head.redirect(0,url.c_str());
		}
		else
		{
			//out << "Location:/login.html?failure\n\n";
			head.redirect(0,"login.html?failure");
		}
		head.print(out);
	}
	catch(const std::exception& e)
	{
		std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
		out << "Error : " << e.what() << "<br>\n";
		//head.redirect(0,"/login.html?error");
		//head.print(out);
		return EXIT_FAILURE;
	}*/

	return EXIT_SUCCESS;
}








}


