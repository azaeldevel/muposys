
#include "html.hh"

namespace muposys
{
void contenttype(std::ostream& out,const char* content,const char* type)
{
	out << "content-type: " << content << "/" << type << "\n\n";
}
void doctype(std::ostream& out,const char * type)
{
	out << "<!DOCTYPE " << type << ">\n";
}

	
void meta::print(std::ostream& out) const
{
	out << "<meta ";
	if(not charset.empty())
	{
		out << "charset = \"" + charset + "\" ";
	}
	if(not content.empty())
	{
		out << "content = \"" + content + "\" ";
	}
	if(not http_equiv.empty())
	{
		out << "http-equiv = \"" + http_equiv + "\" ";
	}
	if(not name.empty())
	{
		out << "name = \"" + name + "\" ";
	}
	out << ">\n";
}


void Head::print(std::ostream& out) const
{
	out << "<head>\n";
	for(const meta& m : metas)
	{
		m.print(out);
		out << "\n";
	}
	out << "</head>\n";
}
void Head::redirect(unsigned short time,const std::string& url)
{
	metas.resize(metas.size() + 1);
	metas.resize(1);//crea uno objeto con el contructor por defualt
	metas.back().content = std::to_string(time) + "; url = '" + url + "'";
	metas.back().http_equiv = "refresh";	
}


HTML::HTML() : body(NULL)
{
}
HTML::HTML(const Body& b) : body(&b)
{

}
void HTML::print(std::ostream& out) const
{
	out << "<html>\n";
	head.print(out);
	if(body) body->print(out);
	out << "</html>\n";
}

}