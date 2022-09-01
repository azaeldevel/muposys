#include "config.h"
#include "application-server.hh"


namespace muposys
{


	Application::Body::Body() 
	{

	}
	bool Application::Body::print(std::ostream& out)
	{		
		//muposys::server::Login* login;
		cgicc::Cgicc cgi;
		//bool flagserror = false;
		/*cgicc::const_form_iterator it = muposys::http::search(cgi.getElements().begin(),cgi.getElements().end(),"session");
		if(it != cgi.getElements().end())
		{
			//std::cout << "Sessión : " << (*it).getValue() << "<br>\n";
			login = new muposys::server::Login((*it).getValue());
		}
		else
		{
			std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
		}*/
		
		muposys::http::db::Conector conn(muposys::http::db::database_file);
		muposys::http::db::Session session;
		if(not session.selectByRemoteAddr(conn,getenv("REMOTE_ADDR")))
		{
			std::cout << "<meta http-equiv=\"refresh\" content=\"0;url=login.html\"\n";
		}
		conn.close();
		
		out << "<div id=\"menu\">";
		
		
			out << "<div id=\"user\">";			
				
				out << "<div id=\"logout\"><a href=\"/logout.cgi\" > ";
				
				out << "</a></div>\n";
				out << "<div id=\"space\">";
				
				out << "</div></a>\n";
				out << "<div id=\"photo\"><a href=\"#/user.html\" > ";
				/*
				sysapp::http::db::Conector connhttp(muposys::http::db::database_file);
				sysapp::http::db::Variable var;
				if(var.select(connhttp,login->getSession().getSession(),"user"))
				{
					out << var.getValue();				
				}
				else
				{
					flagserror = true;
				}
				connhttp.close();
				*/
				out << "</a></div>\n";
				out << "<div id=\"system\"><a href=\"/system.html\" >";
				
				out << "</a></div>\n";			
			
			out << "</div>\n";
		
		out << "</div>\n";
		
		/*if(flagserror)
		{
			std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
		}*/
					
		//delete login;
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