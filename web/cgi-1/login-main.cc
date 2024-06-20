
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

namespace mps = oct::mps::v1;

int main ()
{
	mps::server::Login login;
	return login.main();


	/*std::cout << "Content-type:text/html\r\n\r\n";
    std::cout << "<html>\n";
    std::cout << "<head>\n";
    std::cout << "<title>Hello World - First CGI Program</title>\n";
    std::cout << "</head>\n";
    std::cout << "<body>\n";

    std::string strin;
    std::cin >> strin;
    std::cout << "<h2>";
    std::cout << strin;*/
    /*
    mps::Parameters params(std::cin);
    std::cout << params.size() << "<br>";
    for(auto const& s : params)
    {
        std::cout << s.first << " => " << s.second << "<br>";
    }
    */
    /*std::cout << "</h2>\n";
    std::cout << "</body>\n";
    std::cout << "</html>\n";*/

    return 0;
}

