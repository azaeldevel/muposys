


#include "config.h"
#include "application.hh"


namespace muposys
{

void BodyApplication::options(std::ostream& out)const
{		
	out << "\t\t\t<div id=\"logout\"><a href=\"/logout.cgi\"></a></div>\n";	
}
void BodyApplication::print(std::ostream& out)const
{		
	out << "\t<div id=\"menu\">\n";
		out << "\t\t<div id=\"options\">\n";
			this->options(out);
		out << "\t\t</div>\n";
	
		out << "\t\t<div id=\"panel\">\n";				
			out << "\t\t\t<div id=\"logout\"><a href=\"/logout.cgi\"></a></div>\n";
	
			out << "\t\t\t<div id=\"space\"></div>\n";

			out << "\t\t\t<div id=\"user\"><a href=\"/user-admin.html\"></a></div>\n";
			out << "\t\t\t<div id=\"system\"><a href=\"/system.html\"></a></div>\n";			
		out << "\t\t</div>\n";		
	out << "\t</div>\n";
}
Application2::~Application2()
{
}
Application2::Application2(const BodyApplication& b) : muposys::HTML(b)
{
	head.title = "Multi-Porpuse Software System";
	head.charset("UTF-8");
	head.responsive("viewport","width=device-width, initial-scale=1");
	head.css("/css/application.css");
	head.css("/css/Mkos-Big-Sur.css");
}
	
void Application2::print(std::ostream& out) const
{
	muposys::HTML::print(out);
}
void Application2::main()
{
	contenttype(std::cout,"text","html");
	doctype(std::cout,"html");
	
	muposys::http::db::Conector conn(muposys::http::db::database_file);
	muposys::http::db::Session session;
	
	if(not session.selectByRemoteAddr(conn,getenv("REMOTE_ADDR")))
	{
		head.redirect(0,"login.html");
	}
	
	print(std::cout);
}
}