
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
std::ostream& meta::print  (std::ostream& out)
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
	
	return out;
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



std::ostream& Head::print (std::ostream& out)
{
	out << "<head>\n";
	for(meta& m : metas)
	{
		m.print(out);
	}
	for(const link& l : links)
	{
		l.print(out);
	}
	for(const script& s : scripts)
	{
		s.print(out);
	}
	
	if(not title.empty())
	{
		out << "\t<title>" << title << "</title>\n";
	}
	out << "</head>\n";
	
	return out;
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
void Head::addscript(const char* s)
{
	scripts.push_back(script());
	scripts.back().source(s);
}




void script::print(std::ostream& out) const
{
	out << "\t<script";
	if(not async.empty())
	{
		out << " async = \"" + async + "\"";
	}
	if(not crossorigin.empty())
	{
		out << " crossorigin =\"" + crossorigin + "\"";
	}
	if(not defer.empty())
	{
		out << " defer = \"" + defer + "\"";
	}
	if(not integrity.empty())
	{
		out << " integrity =\"" + integrity + "\" ";
	}
	if(not referrerpolicy.empty())
	{
		out << " referrerpolicy =\"" + referrerpolicy + "\"";
	}
	if(not src.empty())
	{
		out << " src = \"" + src + "\"";
	}
	if(not type.empty())
	{
		out << " type =\"" + type + "\"";
	}
	out << ">\n";
	if(not content.empty()) out << content; 
	out << "\n\t</script>\n";
	
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
	//if(is_open_DB) connDB.close();
}

/*
bool Service::add(const char* varible,const char* value)
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
}
*/
bool Service::has_session()
{
	if(get_session() > 0) return true;
	
	return false;
}
long Service::get_session()
{
	//std::cout << "Service::get_session : Step 1.0<br>\n";
	const char* host = getenv("REMOTE_ADDR");
	//std::cout << "Service::get_session : Step 1.1<br>\n";
	if(not host) return -1;	
	//std::cout << "Service::get_session : Step 1.2<br>\n";
	std::string findSesion = "client = '";
	//std::cout << "Service::get_session : Step 1.3<br>\n";
	findSesion += host;
	//std::cout << "Service::get_session : Step 1.4<br>\n";
	findSesion += "'";
	std::vector<muposysdb::Session*>* clientlst = muposysdb::Session::select(connDB,findSesion,0);
	
	//std::cout << "Service::get_session : Step 2<br>\n";
	
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
	
	//std::cout << "Service::get_session : Step 3<br>\n";
	if(clientlst != NULL)
	{
		for(auto u : *clientlst)
		{
			delete u;
		}
		delete clientlst;
	}
	
	//std::cout << "Service::get_session : Step 4<br>\n";
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
	//std::cout << "Service::register_session : " << findSesion << "<br>\n";
	std::vector<muposysdb::Variable*>* varslst = muposysdb::Variable::select(connDB,findSesion,0);
	bool flag_op,flag_main,flag_name,flag_val,flag_session;
	std::cout << "Service::register_session size : " << varslst->size() << "<br>\n";
	if(not varslst)
	{
		flag_main = variable.insert(connDB);
		flag_name = variable.upName(connDB,user_name_variable);
		flag_val = variable.upValue(connDB,s);
		flag_session = variable.upSession(connDB,session);
		flag_op = true;
	}
	else if(varslst->size() == 0)
	{
		std::cout << "Service::register_session inserting..<br>\n";
		flag_main = variable.insert(connDB);
		std::cout << "Service::register_session inserting 1<br>\n";
		flag_name = variable.upName(connDB,user_name_variable);
		std::cout << "Service::register_session inserting 2<br>\n";
		flag_val = variable.upValue(connDB,s);
		std::cout << "Service::register_session inserting 3<br>\n";
		flag_session = variable.upSession(connDB,session);
		std::cout << "Service::register_session inserting 4<br>\n";
		flag_op = true;
		std::cout << "Service::register_session updated..<br>\n";
	}
	else if(varslst->size() == 1)
	{
		std::cout << "Service::register_session updating..<br>\n";
		flag_name = true;
		flag_main = true;
		flag_val = varslst->front()->upValue(connDB,s);
		flag_session = varslst->front()->upSession(connDB,session);
		flag_op = true;
	}/*
	else
	{
		for(int i = 1; i < varslst->size(); i++)
		{
			varslst->at(i)->remove(connDB);
		}
		flag_name = true;
		flag_main = true;
		flag_val = varslst->front()->upValue(connDB,s);
		flag_session = varslst->front()->upSession(connDB,session);
		flag_op = true;
	}*/
	
	std::cout << "Service::register_session done<br>\n";
	
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
std::string Service::get_user()
{	
	//std::cout << "Service::get_user : Step 1\n<br>";
	std::string user;
	if(variable.getID() > 0)
	{
		//std::cout << "Service::get_user : Step 1.1\n<br>";
		if(variable.getValue().empty()) variable.downValue(connDB);
		return variable.getValue();
	}
	else
	{
		//std::cout << "Service::get_user : Step 1.2.1\n<br>";
		long session = get_session();
		
		//std::cout << "Service::get_user : Step 1.2.2\n<br>";
		if(session < 1) return user;
		
		//std::cout << "Service::get_user : Step 1.2.3\n<br>";
		std::string findSesion = "session = ";
		findSesion += std::to_string(session);
		findSesion += " and name = '";
		findSesion += user_name_variable;
		findSesion += "'";
		//std::cout << "SQL Service::get_user : " << findSesion << "<br>\n";
		std::vector<muposysdb::Variable*>* varslst = muposysdb::Variable::select(connDB,findSesion,0);
		//std::cout << "Service::get_user : Step 1.2.4\n<br>";
		if(not varslst)
		{
		}
		else if(varslst->size() == 1)
		{
			if(varslst->front()->downValue(connDB)) user = varslst->front()->getValue();
		}
		for(auto d : *varslst)
		{
			delete d;
		}
	}
	
	//std::cout << "Service::get_user : Step 2\n<br>";
	return user;
}
bool Service::permission(const char* p)
{
	//std::cout << "Service::permission : Step 1\n<br>";
	
	long userid = 0;
	std::string user = get_user();
	
	if(user.empty()) return false;
	
	//finding user id
	//std::cout << "Service::permission : Step 2\n<br>";
	std::string findUser = "name = '" + user + "'";
	//std::cout << "SQL where : " << findUser << "<br>\n";
	std::vector<muposysdb::User*>* userlst = muposysdb::User::select(connDB,findUser,0);
	bool flpermiss = false;
	if(not userlst)
	{
		flpermiss = false;
	}
	else if(userlst->size() != 1)
	{		
		flpermiss = false;
	}
	else if(userlst->size() == 1)
	{
		if(userlst->front()->downPerson(connDB)) 
		{
			userid = userlst->front()->getUser().getUm().getID();
			flpermiss = true;
		}
	}
	if(userlst)
	{
		for(auto u : *userlst)
		{
			delete u;
		}
		delete userlst;
	}
	if(not flpermiss) return false;
	
	//finding user id
	//std::cout << "Service::permission : Step 3\n<br>";
	std::string findPermission = "name = '";
	findPermission += p;
	findPermission += "'";
	long permss = -1;
	//std::cout << "SQL where : " << findPermission << "<br>\n";
	std::vector<muposysdb::Permission*>* permsslst = muposysdb::Permission::select(connDB,findPermission,0);
	if(not permsslst)
	{
		flpermiss = false;
	}
	else if(permsslst->size() != 1)
	{		
		flpermiss = false;
	}
	else if(permsslst->size() == 1)
	{
		permss = permsslst->front()->getPermission().getUm().getID();
		flpermiss = true;
	}
	if(permsslst)
	{
		for(auto u : *permsslst)
		{
			delete u;
		}
		delete permsslst;
	}
	if(not flpermiss) return false;
	
	//std::cout << "Service::permission : Step 4\n<br>";
	std::string findUserpermission = "user = " + std::to_string(userid) + " and permission = " +  std::to_string(permss);
	//std::cout << "SQL where : " << findUserpermission << "<br>\n";
	std::vector<muposysdb::UserPermission*>* usrpermiss = muposysdb::UserPermission::select(connDB,findUserpermission,2);
	//std::cout << "size : " << usrpermiss->size() << "<br>\n";
	//std::cout << "Query done.\n";
	//std::cout << "Service::permission : Step 3\n<br>";
	if(not usrpermiss)
	{
		flpermiss = false;
	}
	else if(usrpermiss->size() != 1)//no tine permiso o tien mas de un permiso
	{
		flpermiss = false;
	}
	else
	{
		//si hay un registro estonces es el buscado no es neceario9 comprobar los datos
		flpermiss = true;		
	}
	if(usrpermiss)
	{
		for(auto p : *usrpermiss)
		{
			delete p;
		}
		delete usrpermiss;
	}
	
	//std::cout << "permission : Step 5\n<br>";
	return flpermiss;	
}


Page::Page() : body(NULL)
{
}
Page::Page(Body& b) : body(&b)
{
}
Page::Page(Body& b,const std::string& t) : body(&b)
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
Page::~Page()
{
}

std::ostream& Page::print (std::ostream& out)
{
	head.print(out);
	out << "<html>\n";
	if(body) 
	{
		out << "<body>\n";
		body->print(out);
		out << "</body>\n";
	}
	out << "</html>\n";
	
	return out;
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
