

#include "server.hh"

namespace muposys::server::elements
{

template<typename Base, typename T> inline bool instanceof(const T*) 
{
   return std::is_base_of<Base, T>::value;
}





bool Window::print()
{
	return buildHTML();
}
bool Window::buildHTML()
{
	
	out << "<html>\n";	
		buildHead();	
		out << "<body>\n";	
			//out << "<div class=\"modal\">\n";
				if(instanceof<Form>(getBody()))
				{
					out << "<form class=\"modal-content animate\" action=\"/cgi/useradd\" method=\"post\">";
					getBody()->print(out);
					out << "</form>";
				}
				else
				{
					getBody()->print(out);
				}
			//out << "</div>\n";
		out << "</body>\n";	   	
	out << "</html>\n";	   	
	return true;
}
bool Window::buildHead()
{
	out << "<head>\n";
	   	
	getHead()->print(out);  
	   		   	
	out << "</head>\n";
	   	
	return true;
}
Window::~Window()
{
	
}
Window::Window(std::ostream& out,Body* body):server::elements::Html(out,body)
{
	setContentType(server::elements::ContentType::Text::html);	   
	getHead()->addMetaCharset("UTF-8");
	setBody(body);	
}









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














bool ContentType::print()
{
	ContentType* content = NULL;
	out << "Content-type:";
	switch(contenttype)
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
	
	return true;
}
void ContentType::setContentType(ContentType::Text type)
{
	contenttype = type;
}
ContentType::ContentType(std::ostream& out) : Container(out)
{
	
}









Html::Html(std::ostream& out,Body* b) : ContentType(out)
{
	body = b;
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