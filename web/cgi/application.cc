

#include "application.hh"


namespace mps
{

BodyApplication::BodyApplication(const GetParams& p) : params(p)
{
	
}
void BodyApplication::programs(std::ostream& out) 
{
	out << "\t\t\t<div id=\"logout\"><a href=\"logout.cgi\">" << "logout" << "</a></div>\n";
	out << "\t\t\t<div id=\"logout\"><a href=\"logout.cgi\">" << "logout" << "</a></div>\n";
	out << "\t\t\t<div id=\"logout\"><a href=\"logout.cgi\">" << "logout" << "</a></div>\n";
	out << "\t\t\t<div id=\"logout\"><a href=\"logout.cgi\">" << "logout" << "</a></div>\n";
}
void BodyApplication::panel(std::ostream& out)
{
	out << "\t\t\t<div id=\"logout\"><a href=\"logout.cgi\"></a></div>\n";

	out << "\t\t\t<div class=\"space\"></div>\n";
	
	out << "\t\t\t<div id=\"system\"><a href=\"system.html\"></a></div>\n";	
}
std::ostream& BodyApplication::print (std::ostream& out)
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

void BodyApplication::set(mps::Connector& c)
{
	connDB = &c;
}
void BodyApplication::set(Application& a)
{
	application = &a;
}




Application::~Application()
{
}
Application::Application(BodyApplication& b,const GetParams& p) : mps::Page(b,muposysdb::datconex),params(p)
{
	head.title = "Multi-Porpuse Software System";
	init();
}
Application::Application(BodyApplication& b,const std::string& t,const GetParams& p) : mps::Page(b,t,muposysdb::datconex),params(p)
{
	init();
}
void Application::init()
{
	head.charset("UTF-8");
	head.responsive("viewport","width=device-width, initial-scale=1");
	head.css("css/Mkos-Big-Sur/appearance/muposys.css");
	head.css("css/Mkos-Big-Sur/icons/application.css");
	//head.addscript("tests.js");
}
std::ostream& Application::print (std::ostream& out)
{
	mps::Page::print(out);
	
	return out;
}
int Application::main(std::ostream& out)
{
	contenttype(out,"text","html");
	
	if(not has_session())
	{
		head.redirect(0,"login.html?failure");
		head.print(out);
		return EXIT_SUCCESS;
	}
	
	this->print(out);

	return EXIT_SUCCESS;
}

}
