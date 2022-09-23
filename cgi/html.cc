
#include "html.hh"
#include "http.hh"

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



/*ContentType::ContentType() : content(NULL),type(NULL)
{
}
void ContentType::print(std::ostream& out) const
{
	if(content and type) out << "Content-Type: " << content << "/" << type << "\n";
}



Status::Status() : code(0),brief(NULL)
{
}
Status::Status(unsigned short c) : code(c)
{
	message();
}
//https://www.w3.org/Protocols/rfc2616/rfc2616-sec10.html
void Status::message()
{
	switch(code)
	{
		case 200: brief = "Ok";
		case 301: brief = "Mover Permanentemente";

		default: brief = "Unknow status";
	}
}
void Status::print(std::ostream& out) const
{
	if(code > 0 and brief) out << "Status : " << code << " " << brief << "\n";
}
void status(std::ostream& out,const Status& st)
{
	out << "Status : " << st.code << " " << st.brief << "\n\n";
}


void Header::redirect(const std::string& url)
{
	location = url;
	status.code = 301;
	status.message();
}
void Header::print(std::ostream& out) const
{
	contenttype.print(out);
	status.print(out);
	out << "Location : " << location << "\n";
	out << "\n";
}
void Header::print_redirect(std::ostream& out) const
{
	status.print(out);
	out << "Location : " << location << "\n";
}
	*/
void meta::print(std::ostream& out) const
{
	out << "\t<meta";
	if(not charset.empty())
	{
		out << " charset=\"" + charset + "\"";
	}
	if(not content.empty())
	{
		out << " content=\"" + content + "\"";
	}
	if(not http_equiv.empty())
	{
		out << " http-equiv=\"" + http_equiv + "\"";
	}
	if(not name.empty())
	{
		out << " name=\"" + name + "\"";
	}
	out << ">\n";
}


void link::print(std::ostream& out) const
{
	out << "\t<link";
	if(not crossorigin.empty())
	{
		out << " crossorigin = \"" + crossorigin + "\" ";
	}
	if(not href.empty())
	{
		out << " href=\"" + href + "\"";
	}
	if(not hreflang.empty())
	{
		out << " hreflang=\"" + hreflang + "\"";
	}
	if(not media.empty())
	{
		out << " media=\"" + media + "\"";
	}
	if(not referrerpolicy.empty())
	{
		out << " referrerpolicy=\"" + referrerpolicy + "\" ";
	}
	if(not rel.empty())
	{
		out << " rel=\"" + rel + "\"";
	}
	if(not sizes.empty())
	{
		out << " sizes=\"" + sizes + "\"";
	}
	if(not title.empty())
	{
		out << " title=\"" + title + "\"";
	}
	if(not type.empty())
	{
		out << " type=\"" + type + "\"";
	}
	out << ">\n";
}



void Head::print(std::ostream& out) const
{
	out << "<head>\n";
	for(const meta& m : metas)
	{
		m.print(out);
	}
	for(const link& l : links)
	{
		l.print(out);
	}
	if(not title.empty())
	{
		out << "\t<title>" << title << "</title>\n";
	}
	out << "</head>\n";
}
void Head::redirect(unsigned short time,const char* url)
{
	metas.push_back(meta());//crea uno objeto con el contructor por defualt
	metas.back().content = std::to_string(time) + "; url = '" + url + "'";
	metas.back().http_equiv = "refresh";	
}
void Head::charset(const char* cs)
{
	metas.push_back(meta());//crea uno objeto con el contructor por defualt
	metas.back().charset = cs;
}
void Head::responsive(const char* name,const char* content)
{
	metas.push_back(meta());//crea uno objeto con el contructor por defualt
	metas.back().name = name;
	metas.back().content = content;
}
void Head::css(const char* file)
{
	links.push_back(link());//crea uno objeto con el contructor por defualt
	links.back().rel = "stylesheet";
	links.back().href =  file;
}





void script::print(std::ostream& out) const
{
	out << "\t<script";
	if(not async.empty())
	{
		out << " async = \"" + async + "\" ";
	}
	if(not crossorigin.empty())
	{
		out << "crossorigin =\"" + crossorigin + "\" ";
	}
	if(not defer.empty())
	{
		out << "defer = \"" + defer + "\" ";
	}
	if(not integrity.empty())
	{
		out << "integrity =\"" + integrity + "\" ";
	}
	if(not referrerpolicy.empty())
	{
		out << "referrerpolicy =\"" + referrerpolicy + "\" ";
	}
	if(not src.empty())
	{
		out << "src = \"" + src + "\" ";
	}
	if(not type.empty())
	{
		out << "type =\"" + type + "\" ";
	}
	out << ">";
	if(not content.empty()) out << content << "<br>\n\t"; 
	out << "</script>";
	
}
void script::source(const char* s)
{
	src = s;
}



HTML::HTML() : body(NULL), conn(muposys::http::db::Conector::database_file)
{
}


HTML::HTML(Body& b) : body(&b), conn(muposys::http::db::Conector::database_file)
{
}
HTML::HTML(Body& b,const std::string t) : body(&b), conn(muposys::http::db::Conector::database_file)
{
	head.title = t;
}

void HTML::print(std::ostream& out) const
{
	out << "<html>\n";
		head.print(out);
		if(body) 
		{
			out << "<body>\n";
			body->print(out);
			out << "</body>\n";
		}
	out << "</html>\n";
}

CGI::CGI() : conn(muposys::http::db::Conector::database_file)
{
}
CGI::~CGI()
{
	conn.close();
}
bool CGI::check()
{
	return session.load(conn);
}


}