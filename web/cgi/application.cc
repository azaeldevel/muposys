

#include "application.hh"


namespace mps
{


void BodyApplication::programs(std::ostream& out)const
{		
	out << "\t\t\t<div id=\"logout\"><a href=\"/logout.cgi\"></a></div>\n";
}
void BodyApplication::panel(std::ostream& out)const
{		
	out << "\t\t\t<div id=\"logout\"><a href=\"/logout.cgi\"></a></div>\n";

	out << "\t\t\t<div class=\"space\"></div>\n";
	
	out << "\t\t\t<div id=\"system\"><a href=\"/system.html\"></a></div>\n";	
}
void BodyApplication::print(std::ostream& out) const
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
}





Application::~Application()
{
}
Application::Application(BodyApplication& b) : mps::Page(b)
{
	/*
	head.title = "Multi-Porpuse Software System";
	head.charset("UTF-8");
	head.responsive("viewport","width=device-width, initial-scale=1");
	head.css("/css/Mkos-Big-Sur/appearance/muposys.css");
	head.css("/css/Mkos-Big-Sur/icons/application.css");
	*/
}
Application::Application(BodyApplication& b,const std::string& t) : mps::Page(b,t)
{
	head.charset("UTF-8");
	head.responsive("viewport","width=device-width, initial-scale=1");
	head.css("/css/Mkos-Big-Sur/appearance/muposys.css");
	head.css("/css/Mkos-Big-Sur/icons/application.css");
}
void Application::print(std::ostream& out) const
{
	mps::Page::print(out);
}
int Application::main(std::ostream& out)
{
	//contenttype(out,"text","html");
	
	/*
	if(not has_session())
	{
		head.redirect(0,"/login.html?failure");
		head.print(out);
		return EXIT_SUCCESS;
	}
	*/
	
	//print(out);

	return EXIT_SUCCESS;
}

}
