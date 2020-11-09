

#include "server.hh"

namespace sysapp::server::elements
{





std::ostream& Container::getOut()
{
	return out;
}
Container::Container(std::ostream& o) : out(o)
{
	
}
std::ostream& Container::getDefaultOutput()
{
	return std::cout;
}
















ContentType::ContentType(std::ostream& out) : Container(out)
{
	
}









void HTML::setBody(Body* b)
{
	body = b;
}
bool HTML::print()
{
	bool rethead = head.print(out);
	if(not rethead) return false;
	
	if(body)
	{
		bool retbody = body->print(out);	
		if(not retbody) return false;
	}
	
	return true;
}
HTML::HTML(std::ostream& out) : ContentType(out)
{
	body = NULL;
}
Head* HTML::getHead()
{
	return &head;
}
Body* HTML::getBody()
{
	return body;
}









ContentType* Content::contentType(ContentType::Text type)
{
	ContentType* content = NULL;
	out << "Content-type:";
	switch(type)
	{
		case ContentType::Text::html:
			content = new HTML(out);
			out << "text/html";
		break;
		case ContentType::Text::plain:
			return NULL;//aun no hay soporte
		break;
		default:
			return NULL;
	};
	
	out << "\r\n\r\n";
	
	return content;
}

/**
*\brief Por defualt usa la salida estandard
*/
Content::Content() : out(std::cout)
{}













bool Head::print(std::ostream& out)
{
	//titulo
	out << "<title> " << title << "</title>\n";
	
	//seccion meta
	for(const std::string& str : meta)
	{
		out << str <<"\n";
	}

	return true;
}
void Head::setTitle(const std::string& t)
{
	title = t;
}
bool Head::addMetaName(const std::string& name, const std::string& content)
{
	std::string str = "<meta ";
	str += "name=\"";
	str += name;
	str += "\"";
	str += "content=\"";
	str += content;
	str += "\"";
	str += "\">";	
	
	meta.push_back(str);
	return true;
}
bool Head::addMetaCharset(const std::string& charset)
{
	std::string str = "<meta ";
	str += "charset=\"";
	str += charset;
	str += "\">";	
	
	meta.push_back(str);
	return true;
}

}