
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
	mps::server::Login login;
	return login.main();
	/*
	printf("Content-type: text/html\n\n");
 	printf("<html><title>Hello</title><body>\n");
	
	std::cout << "Presesando...\n";
	mps::Parameters params(std::cin);

	
 	printf("<br><br>\n");
 	printf("</body></html>");
	*/	
}

