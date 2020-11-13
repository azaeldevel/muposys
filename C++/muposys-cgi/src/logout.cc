
#include <iostream>
#include "server.hh"


int main()
{
	std::cout << "Content-type:text/html\r\n\r\n";
	std::cout << "<html>\n";
	std::cout << "<head>\n";
	std::cout << "<html>\n";
	std::cout << "<head>\n";
	std::cout << "<title>Terminado session</title>\n";
	cgicc::Cgicc cgi;
	cgicc::const_form_iterator it = muposys::http::search(cgi.getElements().begin(),cgi.getElements().end(),"session");
	if(it != cgi.getElements().end())
	{
		//std::cout << "Sessión : " << (*it).getValue() << "<br>\n";
		muposys::http::db::Conector connhttp("database");
		muposys::server::Login* login = new muposys::server::Login((*it).getValue());
		if(login->getSession().getSession().remove(connhttp))
		{
			std::cout << "<meta http-equiv=\"Refresh\" content=\"0;url=/login.html\"\n";
		   	
			//std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";					
		}
	}
	else
	{
		std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
	}
		
	std::cout << "</head>\n";
	std::cout << "<body>\n";
	std::cout << "</body>\n";
	std::cout << "</html>\n";
		   	
	return 0;		
}