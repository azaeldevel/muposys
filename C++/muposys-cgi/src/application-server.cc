#include "config.h"
#include "application-server.hh"


namespace muposys
{


Application::Body::Body() 
{

}
bool Application::Body::print(std::ostream& out)
{		
	muposys::server::Login* login;
	cgicc::Cgicc cgi;
	//bool flagserror = false;
	cgicc::const_form_iterator it = muposys::http::search(cgi.getElements().begin(),cgi.getElements().end(),"session");
	if(it != cgi.getElements().end())
	{
		//std::cout << "Sessión : " << (*it).getValue() << "<br>\n";
		login = new muposys::server::Login((*it).getValue());
	}
	else
	{
		std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
	}
	
	
	
	
	out << "<div id=\"menu\">";
	
	
		out << "<div id=\"user\">";			
			
			out << "<div id=\"logout\"><a href=\"/cgi/logout?session=" << (*it).getValue() <<  "\" > ";
			
			out << "</a></div>\n";
			out << "<div id=\"space\">";
			
			out << "</div></a>\n";
			out << "<div id=\"photo\"><a href=\"#/user.html\" > ";
			/*sysapp::http::db::Conector connhttp("database");
			sysapp::http::db::Variable var;
			if(var.select(connhttp,login->getSession().getSession(),"user"))
			{
				out << var.getValue();				
			}
			else
			{
				flagserror = true;
			}
			connhttp.close();*/
			out << "</a></div>\n";
			out << "<div id=\"system\"><a href=\"/system.html\" >";
			
			out << "</a></div>\n";			
		
		out << "</div>\n";
	
	out << "</div>\n";
	
	/*if(flagserror)
	{
		std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
	}*/
				
	delete login;
	return true;
}










bool Application::print()
{
	ContentType::print();
	
	return buildHTML();
}
	bool Application::buildHTML()
	{
		out << "<html>\n";
		
	   	buildHead();
	   	
		out << "<body>\n";
	   	getBody()->print(out);
		out << "</body>\n";
	   	
	   	out << "</html>\n";
	   	
	   	return true;
	}
	bool Application::buildHead()
	{
		out << "<head>\n";
	   	
	   	getHead()->print(out); 
	   	
	   	out << "</head>\n";
	   	
	   	return true;
	}
	
	
	

	Application::~Application()
	{
		
	}
	Application::Application() : server::elements::Window(getDefaultOutput(),new Body())
	{
		setContentType(server::elements::ContentType::Text::html);	
		std::string title =  "System Application - ";
		title += PACKAGE_VERSION;
		getHead()->setTitle(title);
		getHead()->addMetaCharset("UTF-8");
		getHead()->addMetaName("viewport","width=device-width, initial-scale=1");
		getHead()->addCSS("/css/application.css");

	}	
}