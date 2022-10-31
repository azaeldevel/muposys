
#include "html.hh"

namespace mps
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



const char* Service::user_name_variable = "oct.mps.web.user";
Service::Service() : is_open_DB(false)
{
}
Service::Service(const Datconnect& dat)
{
	is_open_DB = connDB.connect(dat);
}
Service::~Service()
{
	if(is_open_DB) connDB.close();
}

/*bool Service::add(const char* varible,const char* value)
{
	muposysdb::Variable var;
	bool res =  var.insert(connDB,getenv("REMOTE_ADDR"),varible,value);
	return res;
}
bool Service::add(const std::string& varible,const std::string& value)
{
	muposys::http::db::Variable var;
	bool res =  var.insert(connHttp,getenv("REMOTE_ADDR"),varible.c_str(),value.c_str());
	return res;
}*/
bool Service::has_session()
{
	if(get_session() > 0) return true;
	
	return false;
}
long Service::get_session()
{
	std::string findSesion = "client = '";
	findSesion += getenv("REMOTE_ADDR");
	findSesion += "'";
	std::vector<muposysdb::Session*>* clientlst = muposysdb::Session::select(connDB,findSesion,0);
	bool flag_op;
	long session = -1;
	if(clientlst->size() == 0)
	{
		flag_op = false;
	}
	else if(clientlst->size() > 1)
	{
		flag_op = false;
	}
	else if(clientlst->size() == 1)
	{
		flag_op = true;
		session = clientlst->front()->getID();
	}
	
	
	if(clientlst != NULL)
	{
		for(auto u : *clientlst)
		{
			delete u;
		}
		delete clientlst;
	}
	return session;
}
bool Service::register_session(const char* s)
{
	
	std::cout << "Service::register_session : Step 1<br>\n";
	
	long session = get_session();
	if(session < 1)
	{
		muposysdb::Session session;
		session.insert(connDB,getenv("REMOTE_ADDR"));
	}
	
	session = get_session();
	if(session < 1) return false;
	
	std::cout << "Service::register_session : Step 2<br>\n";
	
	std::string findSesion = "id = '";
	findSesion += std::to_string(session);
	findSesion = findSesion + "' and name = '" + user_name_variable + "'";
	std::cout << "Service::register_session : " << findSesion << "<br>\n";
	std::vector<muposysdb::Variable*>* varslst = muposysdb::Variable::select(connDB,findSesion,0);
	bool flag_op,flag_main,flag_name,flag_val,flag_session;
	muposysdb::Variable var;
	std::cout << "Service::register_session size : " << varslst->size() << "<br>\n";
	if(not varslst)
	{
		flag_main = var.insert(connDB);
		flag_name = var.upName(connDB,user_name_variable);
		flag_val = var.upValue(connDB,s);
		flag_session = var.upSession(connDB,session);
		flag_op = true;
	}
	else if(varslst->size() == 0)
	{
		std::cout << "Service::register_session updating..<br>\n";
		flag_main = var.insert(connDB);
		std::cout << "Service::register_session updating 1<br>\n";
		flag_name = var.upName(connDB,user_name_variable);
		std::cout << "Service::register_session updating 2<br>\n";
		flag_val = var.upValue(connDB,s);
		std::cout << "Service::register_session updating 3<br>\n";
		flag_session = var.upSession(connDB,session);
		std::cout << "Service::register_session updating 4<br>\n";
		flag_op = true;
		std::cout << "Service::register_session updated..<br>\n";
	}
	else if(varslst->size() == 1)
	{
		flag_name = true;
		flag_main = true;
		flag_val = varslst->front()->upValue(connDB,s);
		flag_session = varslst->front()->upSession(connDB,session);
		flag_op = true;
	}
	else
	{
		for(int i = 1; i < varslst->size(); i++)
		{
			varslst->at(i)->remove(connDB);
		}
		flag_val = varslst->front()->upValue(connDB,s);
		flag_session = varslst->front()->upSession(connDB,session);
		flag_op = true;
		flag_name = true;
		flag_main = true;
	}
	
	std::cout << "Service::register_session done\n";
	
	if(varslst != NULL)
	{
		for(auto u : *varslst)
		{
			delete u;
		}
		delete varslst;
	}
	connDB.commit();
	
	if(flag_main and flag_name and flag_val and flag_session and flag_op) return true;
	
	return false;
}
bool Service::permission(const char* p)
{
	//std::cout << "permission : Step 1\n<br>";
	//if(not has_session()) return false;
	
	//std::cout << "permission : Step 2\n<br>";
	muposysdb::Variable var;
	/*if(not var.select(connHttp,getenv("REMOTE_ADDR"),"user")) return false;*/

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

Page::Page(Body& b,const Datconnect& dat) : body(&b), Service(dat)
{

}

Page::Page(Body& b,const std::string& t,const Datconnect& dat) : body(&b), Service(dat)
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
CGI::CGI(const Datconnect& dat) : Service(dat)
{

}
CGI::~CGI()
{
}



}
