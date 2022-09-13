


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
	
		out << "\t\t<div id=\"panel\">\n";				
			out << "\t\t\t<div id=\"logout\"><a href=\"/logout.cgi\"></a></div>\n";
	
			out << "\t\t\t<div class=\"space\"></div>\n";

			out << "\t\t\t<div id=\"user\"><a href=\"/user-mang.html\"></a></div>\n";
			out << "\t\t\t<div id=\"system\"><a href=\"/system.html\"></a></div>\n";			
		out << "\t\t</div>\n";	

		out << "\t\t<div class=\"space\"></div>\n";

	
		out << "\t\t<div id=\"options\">\n";
			this->options(out);
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
	head.css("/css/appearance/muposys.css");
	head.css("/css/icons/Mkos-Big-Sur.css");
}
	
void Application2::print(std::ostream& out) const
{
	muposys::HTML::print(out);
}
int Application2::main(std::ostream& out)
{	
	cgicc::HTTPContentHeader header("text/html");
	header.render(out);
	
	muposys::http::db::Conector conn(muposys::http::db::database_file);
	muposys::http::Session session;	
	if(not session.load(conn))
	{
		cgicc::HTTPRedirectHeader headerRedirect("/login.html?failure");
		headerRedirect.render(out);
		return EXIT_SUCCESS;
	}
	
	print(std::cout);

	return EXIT_SUCCESS;
}
}