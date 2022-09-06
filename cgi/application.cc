


#include "config.h"
#include "application.hh"


namespace muposys
{

void BodyApplication::print(std::ostream& out)const
{		
	muposys::http::db::Conector conn(muposys::http::db::database_file);
	muposys::http::db::Session session;
		
	out << "<div id=\"menu\">";
		
		
			out << "<div id=\"panel\">";			
				
				out << "<div id=\"logout\"><a href=\"/logout.cgi\" > ";
				
				out << "</a></div>\n";
				out << "<div id=\"space\">";
				
				out << "</div></a>\n";

				out << "<div id=\"user\">";
					out << "<div id=\"photo\">"; //"</div>\n";
						out << "<div id=\"name\">";						
						muposys::http::db::Variable var;
						if(var.select(conn,session,"user"))
						{
							out << var.getValue();				
						}						
						out << "</div>\n";
					out << "</div>\n";
				out << "</div>\n";
				out << "<div id=\"system\"><a href=\"/system.html\" >";
				
				out << "</a></div>\n";			
			
			out << "</div>\n";
		
	out << "</div>\n";
	conn.close();
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