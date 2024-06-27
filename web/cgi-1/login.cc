
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



Login::Login() : CGI(Configuration().get_datasource())
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
	where = "name='";
	where += userstr;
	where += "' and ";
	where += "pwdtxt=";
	where += "'";
	where += password;
	where += "' and status = 3";

	//std::cout << where << "\n";

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
	//std::cout << "size : " << rsuser.size()  << "\n";

	if(rsuser.size() == 1) return true;

	return false;
}
int Login::main(std::ostream& out)
{
	contenttype(out,"text","html");
	Parameters params;
	try
	{
		if(check(params))
		{
			std::string url = "/muposys.html?user=";
			url += params.find("user");
			//out << "url : " << url << "\n";
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


