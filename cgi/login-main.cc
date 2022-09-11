
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


int main ()
{
	/*
	muposys::http::db::Conector conn(muposys::http::db::database_file);
	muposys::http::db::Session session;
	conn.begin();
	if(session.selectByRemoteAddr(conn,getenv("REMOTE_ADDR"))) session.remove(conn);
	conn.commit();
	conn.close();
	*/
	muposys::server::Login login;
	return login.main();
}

