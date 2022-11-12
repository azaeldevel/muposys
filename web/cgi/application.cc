

#include "application.hh"


namespace mps
{


void BodyApplication::programs(std::ostream& out) 
{
	out << "\t\t\t<div id=\"logout\"><a href=\"/logout.cgi\">" << "logout" << "</a></div>\n";
	out << "\t\t\t<div id=\"logout\"><a href=\"/logout.cgi\">" << "logout" << "</a></div>\n";
	out << "\t\t\t<div id=\"logout\"><a href=\"/logout.cgi\">" << "logout" << "</a></div>\n";
	out << "\t\t\t<div id=\"logout\"><a href=\"/logout.cgi\">" << "logout" << "</a></div>\n";
}
void BodyApplication::panel(std::ostream& out)
{
	out << "\t\t\t<div id=\"logout\"><a href=\"/logout.cgi\"></a></div>\n";

	out << "\t\t\t<div class=\"space\"></div>\n";
	
	out << "\t\t\t<div id=\"system\"><a href=\"/system.html\"></a></div>\n";	
}
std::ostream& BodyApplication::operator >> (std::ostream& out)
{
	out << "\t<div id=\"menu\">\n";		

		out << "\t\t<div id=\"panel\">\n";
			this->panel(out);
		out << "\t\t</div>\n";	

		out << "\t\t<div class=\"space\"></div>\n";

		out << "\t\t<div id=\"programs\">\n";
			this->programs(out);
		out << "\t\t</div>\n";

	out << "\t</div>\n";
	
	return out;
}





Application::~Application()
{
}
Application::Application(BodyApplication& b) : mps::Page(b,muposysdb::datconex)
{
	head.title = "Multi-Porpuse Software System";
	head.charset("UTF-8");
	head.responsive("viewport","width=device-width, initial-scale=1");
	head.css("/css/Mkos-Big-Sur/appearance/muposys.css");
	head.css("/css/Mkos-Big-Sur/icons/application.css");
}
Application::Application(BodyApplication& b,const std::string& t) : mps::Page(b,t,muposysdb::datconex)
{
	head.charset("UTF-8");
	head.responsive("viewport","width=device-width, initial-scale=1");
	head.css("/css/Mkos-Big-Sur/appearance/muposys.css");
	head.css("/css/Mkos-Big-Sur/icons/application.css");
}
std::ostream& Application::operator >> (std::ostream& out)
{
	mps::Page::operator >>(out);
	
	return out;
}
int Application::main(std::ostream& out)
{
	contenttype(out,"text","html");
	
	if(not has_session())
	{
		head.redirect(0,"/login.html?failure");
		head >> out;
		return EXIT_SUCCESS;
	}
	
	(*this) >> out;

	return EXIT_SUCCESS;
}

}
