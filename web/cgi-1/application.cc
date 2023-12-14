

#include "application.hh"


namespace oct::mps::v1
{

BodyApplication::BodyApplication(const Params& p) : params(p)
{

}
void BodyApplication::programs(std::ostream& out)
{
	/*
	out << "\t\t\t<div id=\"logout\"><a href=\"logout.cgi?session=" << params.session << "\">" << "logout" << "</a></div>\n";
	out << "\t\t\t<div id=\"logout\"><a href=\"logout.cgi?session=" << params.session << "\">" << "logout" << "</a></div>\n";
	out << "\t\t\t<div id=\"logout\"><a href=\"logout.cgi?session=" << params.session << "\">" << "logout" << "</a></div>\n";
	out << "\t\t\t<div id=\"logout\"><a href=\"logout.cgi?session=" << params.session << "\">" << "logout" << "</a></div>\n";
	*/
}
void BodyApplication::panel(std::ostream& out)
{
	out << "\t\t\t<div id=\"logout\"><a href=\"logout.cgi?session=" << params.session << "\"></a></div>\n";

	//out << "\t\t\t<div class=\"space\"></div>\n";

	out << "\t\t\t<div id=\"system\"><a href=\"system.html?session=" << params.session << "\"></a></div>\n";
}
std::ostream& BodyApplication::print (std::ostream& out)
{
	out << "\t<div id=\"menu\">\n";

		out << "\t\t<div id=\"panel\">\n";
			this->panel(out);
		out << "\t\t</div>\n";

		//out << "\t\t<div class=\"space\"></div>\n";

		out << "\t\t<div id=\"programs\">\n";
			this->programs(out);
		out << "\t\t</div>\n";

	out << "\t</div>\n";

	return out;
}

void BodyApplication::set(cave0::mmsql::Connection& c)
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
Application::Application(BodyApplication& b,const Params& p) : Page(b,default_dtm0()),params(p)
{
	head.title = "Multi-Porpuse Software System";
	init();
}
Application::Application(BodyApplication& b,const std::string& t,const Params& p) : Page(b,t,default_dtm0()),params(p)
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
	Page::print(out);

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
