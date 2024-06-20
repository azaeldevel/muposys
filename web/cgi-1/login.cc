
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
#include "../../core/1/core.hh"


namespace oct::mps::v1::server
{



Login::Login() : CGI(default_dtm0())
{
}
Login::~Login()
{
}

bool Login::check(const Parameters& params)
{
    //std::cout << "Login::check : Step 1.0<br>\n";
	std::string userstr, password;

	//std::cout << "Login::check : Step 1.1<br>\n";
	if(params.find("user")) userstr = params.find("user");
	//std::cout << "Login::check : Step 1.3<br>\n";
	if(params.find("psw")) password = params.find("psw");
	//std::cout << "Login::check : Step 1.4<br>\n";

	Configuration config(Configuration::default_file());
    //std::cout << config3.get_file_name() << "\n";
    cave1::mmsql::Data data = config.get_datasource();

    bool conectfl = false;
	cave1::mmsql::Connection conn;
	try
	{
		conectfl = conn.connect(data, true);
	}
	catch (const cave::ExceptionDriver& e)
	{
		std::cout << "Exception (cave testing) : " << e.what() << "\n";
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception (cave testing) : " << e.what() << "\n";
	}
	catch (const core::exception& e)
	{
		std::cout << "Exception (cave testing) : " << e.what() << "\n";
	}
	catch (...)
	{
	}

	std::string where;
	where = "name=";
	where += userstr;
	where += " and ";
	where += "pwdtxt=";
	where += "'";
	where += password;
	where += "' and status = 3";

	std::cout << where << "\n";

    std::vector<User> rsuser;
    try
    {
		 conn.select(rsuser,where.c_str());
	}
	catch (const cave::ExceptionDriver&)
	{
	    return false;
	}
	catch (...)
	{
	    return false;
	}

	if(rsuser.size() == 1) return true;

	return false;
}
bool Login::check(std::string& strs)
{
	std::cout << "Login::check : Step 1.0<br>\n";
	std::string userstr, password;

	PostParams postparams;
	std::cout << "Login::check : Step 1.1<br>\n";
	if(postparams.find("user")) userstr = postparams.find("user");
	std::cout << "Login::check : Step 1.3<br>\n";
	if(postparams.find("psw")) password = postparams.find("psw");
	std::cout << "Login::check : Step 1.4<br>\n";


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

	std::cout << "Login::check : Step 1.5<br>\n";
	return fluser;
}
int Login::main(std::ostream& out)
{
	contenttype(out,"text","html");
	std::string strsession;
	try
	{
		if(check(strsession))
		{
			std::string url = "application.cgi?session=" + strsession;
			out << "url : " << url << "\n";
			head.redirect(0,url.c_str());
		}
		else
		{
			out << "Location:/login.html?failure\n\n";
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
	}

	return EXIT_SUCCESS;
}








}


