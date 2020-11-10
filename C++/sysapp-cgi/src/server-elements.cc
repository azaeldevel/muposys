

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















ContentType* ContentType::contentType(ContentType::Text type)
{
	ContentType* content = NULL;
	out << "Content-type:";
	switch(type)
	{
		case ContentType::Text::html:
			content = new Html(out);
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
ContentType::ContentType(std::ostream& out) : Container(out)
{
	
}









void Html::setBody(Body* b)
{
	body = b;
}
bool Html::print()
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
Html::Html(std::ostream& out) : ContentType(out)
{
	body = NULL;
}
Head* Html::getHead()
{
	return &head;
}
Body* Html::getBody()
{
	return body;
}

















bool Head::addCSS(const std::string& fn)
{
	css.push_back(fn);
	
	return true;
}
bool Head::print(std::ostream& out)
{
	//titulo
	out << "<title> " << title << "</title>\n";
	
	//seccion meta
	for(const std::string& str : meta)
	{
		out << str <<"\n";
	}
	
	for(const std::string& fn : css)
	{
		out << "<link rel=\"stylesheet\" href=\"" << fn << "\">\n";
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