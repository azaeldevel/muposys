#include "config.h"
#include "application-server.hh"


namespace sysapp
{


Application::Body::Body()
{

}
bool Application::Body::print(std::ostream& out)
{		
	sysapp::server::Login* login;
	cgicc::Cgicc cgi;
	//bool flagserror = false;
	cgicc::const_form_iterator it = sysapp::http::search(cgi.getElements().begin(),cgi.getElements().end(),"session");
	if(it != cgi.getElements().end())
	{
		//std::cout << "Sessión : " << (*it).getValue() << "<br>\n";
		login = new sysapp::server::Login((*it).getValue());
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
	return buildHTML();
}
	bool Application::buildHTML()
	{
		out << "<html>\n";
		
	   	buildHead();
	   	
		out << "<body>\n";
	   	html->getBody()->print(out);
		out << "</body>\n";
	   	
	   	out << "</html>\n";
	   	
	   	return true;
	}
	bool Application::buildHead()
	{
		out << "<head>\n";
	   	
	   	html->getHead()->print(out); 
	   	
	   	out << "</head>\n";
	   	
	   	return true;
	}
	
	
	

	Application::~Application()
	{
		delete html;
	}
	Application::Application():server::elements::Html(getDefaultOutput())
	{
		html = (server::elements::Html*)contentType(server::elements::ContentType::Text::html);	   
		html->getHead()->setTitle("System Application");
		html->getHead()->addMetaCharset("UTF-8");
		html->getHead()->addMetaName("viewport","width=device-width, initial-scale=1");
		html->getHead()->addCSS("/css/application.css");
		html->setBody(new Body());	
	}	
}