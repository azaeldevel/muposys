
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


#include "logout.hh"


namespace oct::mps::v1
{

Logout::Logout(const Params& p) : CGI(default_dtm0()), params(p)
{

}
Logout::~Logout()
{
}


int Logout::main(std::ostream& out)
{
	contenttype(out,"text","html");
	//out << "Logout testing..\n";
	try
	{
		if(has_session())
		{
			remove_session(params.session.c_str());
		}
		head.redirect(0,"login.html");
		head.print(out);
	}
	catch(const std::exception& e)
	{
		head.redirect(0,"login.html?error");
		head.print(out);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
}


