
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

Service::Service() : is_open_http(false),is_open_DB(false)
{
}
Service::Service(const std::filesystem::path& db) : connHttp(db),is_open_http(true),is_open_DB(false)
{
}
Service::Service(const Datconnect& dat) : is_open_DB(true)
{
	connDB.connect(dat);
}
Service::Service(const std::filesystem::path& db,const Datconnect& dat) : connHttp(db),is_open_http(true),is_open_DB(true)
{
	connDB.connect(dat);
}
Service::~Service()
{
	if(is_open_http) 
	{
		//session.remove(connHttp);
		connHttp.close();
	}
	if(is_open_DB) connDB.close();
}
bool Service::create_session()
{
	return session.addregister(connHttp);
}
bool Service::remove_session()
{
	return session.remove(connHttp);
}
bool Service::has_session()
{
	return session.load(connHttp);
}
bool Service::add(const char* varible,const char* value)
{
	muposys::http::db::Variable var;
	bool res =  var.insert(connHttp,getenv("REMOTE_ADDR"),varible,value);
	return res;
}
bool Service::add(const std::string& varible,const std::string& value)
{
	muposys::http::db::Variable var;
	bool res =  var.insert(connHttp,getenv("REMOTE_ADDR"),varible.c_str(),value.c_str());
	return res;
}
bool Service::permission(const char* p)
{
	//std::cout << "permission : Step 1\n<br>";
	if(not has_session()) return false;
	
	//std::cout << "permission : Step 2\n<br>";
	http::db::Variable var;
	if(not var.select(connHttp,getenv("REMOTE_ADDR"),"user")) return false;

	//
	if(var.getValue().empty()) return false;

	unsigned int userid = 0;
	std::string findUser = "name = '" + var.getValue() + "'";
	std::vector<muposysdb::User*>* userlst = muposysdb::User::select(connDB,findUser,0);
	if(userlst->size() == 0 or userlst->size() > 1)
	{
		for(auto u : *userlst)
		{
			delete u;
		}
		return false;
	}
	if(userlst->size() == 1)
	{
		userid = userlst->front()->getPerson().getEnte().getID();
	}
	if(userlst != NULL)
	{
		for(auto u : *userlst)
		{
			delete u;
		}
	}
	delete userlst;
	
	//std::cout << "permission : Step 3\n<br>";
	std::string findUserpermission = "user = " + std::to_string(userid) + " and permission = '" + p + "'";
	//std::cout << "SQL where : " << findUserpermission << "\n";
	std::vector<muposysdb::UserPermission*>* usrpermiss = muposysdb::UserPermission::select(connDB,findUserpermission,0);
	//std::cout << "size : " << usrpermiss->size() << "\n";
	//std::cout << "Query done.\n";
	if(usrpermiss->size() == 0 or usrpermiss->size() > 1)//no tine permiso o tien mas de un permiso
	{
		//std::cout << "permission : Step 3\n<br>";
		if(usrpermiss != NULL)
		{
			for(auto p : *usrpermiss)
			{
				delete p;
			}
		}
		delete usrpermiss;
		//std::cout << "permission : do not has\n<br>";
		return false;
	}

	//std::cout << "permission : Step 4\n<br>";
	if(usrpermiss != NULL)
	{
		for(auto p : *usrpermiss)
		{
			delete p;
		}
	}
	delete usrpermiss;
	
	//std::cout << "permission : Step 5\n<br>";
	return true;	
}
bool Service::open(const std::filesystem::path& fn)
{
	connHttp.open(fn);
	is_open_http = true;
	
	return true;
}
bool Service::register_session(const char* user)
{
	//std::cout << "register_session : 1\n<br>";
	if(not has_session())
	{
		//std::cout << "register_session : 1.2\n<br>";
		connHttp.begin();
		if(create_session())
		{
			//std::cout << "register_session : 1.2.1\n<br>";
			if(add("user",user))
			{
				//std::cout << "register_session : 1.2.1.1\n<br>";
				connHttp.commit();
				return true;
			}
			else
			{
				//std::cout << "register_session : 1.2.1.2\n<br>";
				connHttp.rollback();
				return false;
			}
		}
		else
		{
			//std::cout << "register_session : 1.2.2\n<br>";
			return false;
		}
	}
	else
	{
		//std::cout << "register_session : 1.3\n<br>";
		connHttp.begin();
		if(create_session())
		{
			//std::cout << "register_session : 1.3.1\n<br>";
			if(add("user",user))
			{
				//std::cout << "register_session : 1.3.1.1\n<br>";
				connHttp.commit();
				return true;
			}
			else
			{
				//std::cout << "register_session : 1.3.1.2\n<br>";
				connHttp.rollback();
				return false;
			}
		}
		else
		{
			//std::cout << "register_session : 1.3.2\n<br>";
			return false;
		}
	}

	//std::cout << "register_session : 2\n<br>";
	return true;
}

Page::Page() : body(NULL)
{
}


Page::Page(Body& b) : body(&b)
{
}
Page::Page(Body& b,const std::string t) : body(&b)
{
	head.title = t;
}

Page::Page(Body& b,const std::filesystem::path& db) : body(&b), Service(db)
{

}
Page::Page(Body& b,const Datconnect& dat) : body(&b), Service(dat)
{

}
Page::Page(Body& b,const std::filesystem::path& db,const Datconnect& dat) : body(&b), Service(db,dat)
{

}

Page::Page(Body& b,const std::string& t,const std::filesystem::path& db) : body(&b), Service(db)
{
	head.title = t;
}
Page::Page(Body& b,const std::string& t,const Datconnect& dat) : body(&b), Service(dat)
{
	head.title = t;
}
Page::Page(Body& b,const std::string& t,const std::filesystem::path& db,const Datconnect& dat) : body(&b), Service(db,dat)
{
	head.title = t;
}

void Page::print(std::ostream& out) const
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

CGI::CGI() 
{
}

CGI::CGI(const std::filesystem::path& db) : Service(db)
{

}
CGI::CGI(const Datconnect& dat) : Service(dat)
{

}
CGI::CGI(const std::filesystem::path& db,const Datconnect& dat) : Service(db,dat)
{

}


CGI::~CGI()
{
}



}
