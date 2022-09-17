


#include "config.h"
#include "user-permiss.hh"


namespace muposys
{


BodyUserPermission::BodyUserPermission()
{
	user_mang = false;
	conn.connect(muposysdb::datconex);
	
	userlst = muposysdb::Users::select(conn,"",0,'D');
	for(auto u : *userlst)
	{
		if(u->downName(conn) and u->getPerson().downName1(conn)) u->getPerson().downName3(conn);
	}
	
	permisslst = muposysdb::Permissions::select(conn,"",0,'D');
	for(auto p : *permisslst)
	{
		//p->downName(conn);
		//p->downBrief(conn);
	}
}
BodyUserPermission::~BodyUserPermission()
{
	for(auto u : *userlst)
	{
		delete u;
	}	
	delete userlst;
	
	/*for(auto p : *permisslst)
	{
		delete p;
	}
	delete permisslst;*/
}
void BodyUserPermission::print(std::ostream& out)const
{
	out << "\t<div id=\"menu\">\n";		
	
		out << "\t\t<div id=\"panel\">\n";				
			out << "\t\t\t<div id=\"logout\"><a href=\"/logout.cgi\"></a></div>\n";
	
			out << "\t\t\t<div class=\"space\"></div>\n";

			out << "\t\t\t<div id=\"system\"><a href=\"/system.html\"></a></div>\n";			
		out << "\t\t</div>\n";	

		out << "\t\t<div class=\"space\"></div>\n";

	
		out << "\t\t<div id=\"options\">\n";
			
		out << "\t\t</div>\n";
	
	out << "\t</div>\n";

	out << "\t\t<form id=\"add\" class=\"modal-content animate\" action=\"user-permiss.cgi\" method=\"post\">\n";

		out << "\t\t<div class=\"container\">\n";
			out << "\t\t\t<label for=\"user\"><b>Usuario:</b></label>\n";
			out << "\t\t\t<select name=\"user\" id=\"user\">\n";
				std::string name;
				if(userlst != NULL)
				{
					//std::cout << "List <br>\n";
					for(auto u : *userlst)
					{
						//std::cout << "User<br>\n";
						out << "\t\t\t\t<option value=\"";
						out << u->getName();
						out << "\">";
						name = u->getPerson().getName1();
						if(not u->getPerson().getName3().empty()) name += " " + u->getPerson().getName3();
						out << name;
						out << "</option>\n";
					}
				}
			out << "\t\t\t</select>\n";
			
			/*out << "\t\t\t<label for=\"permissions\"><b>Permisos:</b></label>\n";
			out << "\t\t\t<select name=\"permissions\" id=\"permissions\">\n";
				if(permisslst != NULL)
				{
					for(auto p : *permisslst)
					{
						out << "\t\t\t\t<option value=\"";
						out << p->getName();
						out << "\">";
						out << p->getBrief();
						out << "</option>\n";
					}
				}
			out << "\t\t\t</select>\n";*/
	
		out << "\t\t</br></br>\n";
	
		out << "\t\t<button type=\"submit\">Agregar</button>\n";
		out << "\t\t</div>\n";

	out << "\t\t</form>";
}

UserPermission::~UserPermission()
{
}
UserPermission::UserPermission(const BodyUserPermission& b) : Application(b)
{
}
	



int UserPermission::main(std::ostream& out)
{
	muposys::contenttype(out,"text","html");	
		
	if(not session.load(conn))
	{
		head.redirect(0,"/login.html?failure");
		head.print(out);
		return EXIT_SUCCESS;
	}

	cgicc::form_iterator itCGI = formData.getElement("cgi"); 
	if( !itCGI->isEmpty() && itCGI != (*formData).end()) 
	{
		
	}
	else 
	{
		print(std::cout);
	}	

	return EXIT_SUCCESS;
}

}