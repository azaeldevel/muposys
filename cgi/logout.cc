
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


namespace muposys::server
{

Logout::Logout()
{
}
Logout::~Logout()
{
}
bool Logout::check() const
{
	muposys::http::db::Conector conn(muposys::http::db::database_file);
	muposys::http::db::Session session;
	conn.begin();
	if(session.selectByRemote(conn,getenv("REMOTE_ADDR"))) 
	{
		session.remove(conn);
		conn.commit();
		conn.close();
		return true;
	}
	conn.close();
	return false;
}
void Logout::print(std::ostream& out) const
{
	muposys::HTML::print(out);
}
int Logout::main(std::ostream& out)
{
	contenttype(std::cout,"text","html");
	doctype(std::cout,"html");
	if(check()) head.redirect(0,"/login.html");
	print(std::cout);

	return EXIT_SUCCESS;
}
}


