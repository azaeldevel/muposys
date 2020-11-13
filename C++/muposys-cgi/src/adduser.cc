
#include <iostream>
#include "server.hh"

bool validRegister()
{

}
int main()
{
	cgicc::Cgicc cgi;
	bool accepted = false;
	int errcode = 0;
	cgicc::const_form_iterator it = muposys::http::search(cgi.getElements().begin(),cgi.getElements().end(),"type");
	if(it != cgi.getElements().end())
	{
		//std::cout << "Sessión : " << (*it).getValue() << "<br>\n";
		muposys::http::db::Conector connhttp("database");
		muposys::server::Login* login = new muposys::server::Login((*it).getValue());
		if(login->getSession().getSession().remove(connhttp))
		{
								
		}
	}
	else
	{
		std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
	}
	
	if((*it).getValue().compare("register") == 0)
	{
		validRegister();
	}
	else
	{
	
	}
	
	if(accepted)
	{
		switch(errcode)
		{
			case 1:
			
			break;
			case 2:
			
			break;
		}
	}
		   	
	return 0;
}