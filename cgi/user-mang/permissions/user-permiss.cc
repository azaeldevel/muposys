


#include "config.h"
#include "user-permiss.hh"


namespace muposys
{


BodyUserPermission::BodyUserPermission()
{
	user_mang = false;
	conn.connect(muposysdb::datconex);
	
	userlst = muposysdb::Users::select(conn,"",0);
	for(auto u : *userlst)
	{
		u->downName(conn);
		u->getPerson().downName1(conn);
		u->getPerson().downName3(conn);
	}
	
	permisslst = muposysdb::Permissions::select(conn,"",50);
	for(auto p : *permisslst)
	{
		p->downName(conn);
		p->downBrief(conn);
	}
}
BodyUserPermission::~BodyUserPermission()
{
	for(auto u : *userlst)
	{
		delete u;
	}	
	delete userlst;
	
	for(auto p : *permisslst)
	{
		delete p;
	}
	delete permisslst;
	conn.close();
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
			out << "\t\t\t<input style=\"visibility:hidden\" type=\"checkbox\" id=\"cgi\" name=\"cgi\" value=\"cgi\" checked></br>\n";
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
			out << "\t\t\t</br></br>\n";			
			std::cout << "count : " << permisslst->size() << "</br>\n";
			out << "\t\t\t<label for=\"permissions\"><b>Permisos:</b></label>\n";
			out << "\t\t\t<select name=\"permissions\" id=\"permissions\">\n";
			try
			{
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
			}
			catch(const std::exception& e)
			{
				out << "Error : " << e.what() << "\n";	
				return;
			}
			catch(...)
			{
				out << "Error : Desconocido\n";	
				return;
			}
			out << "\t\t\t</select>\n";
	
		out << "\t\t</br></br>\n";
	
		out << "\t\t<button type=\"submit\">Agregar</button>\n";

		out << "\t\t</div>\n";

	out << "\t\t</form>";
}








UserPermission::UserPermission(BodyUserPermission& b) : Application(b)
{	
	connDB.connect(muposysdb::datconex);
}
UserPermission::~UserPermission()
{
	connDB.close();	
	for(auto u : *userlst)
	{
		delete u;
	}	
	delete userlst;
}
	



int UserPermission::main(std::ostream& out)
{
	muposys::contenttype(out,"text","html");	
		
	if(not has_session())
	{
		head.redirect(0,"/login.html?failure");
		head.print(out);
		return EXIT_SUCCESS;
	}

	cgicc::form_iterator itCGI = formData.getElement("cgi"); 
	if( !itCGI->isEmpty() && itCGI != (*formData).end()) 
	{
		//out << "Running ..\n";
		bool flag;
		try
		{
			flag = methode(out);
		}
		catch(const std::exception& e)
		{
			out << "Error : " << e.what() << "\n";	
			return false;
		}
		catch(...)
		{
			out << "Error : Desconocido\n";	
			return false;
		}
		if(flag)
		{
			head.redirect(0,"/user-mang/permissions/user-permiss.cgi");
		}
		else
		{
			head.redirect(0,"/user-mang/permissions/user-permiss.cgi?failure");
		}
		head.print(out);
	}
	else 
	{		
		try
		{
			print(out);
		}
		catch(const std::exception& e)
		{
			out << "Error : " << e.what() << "\n";	
			return false;
		}
		catch(...)
		{
			out << "Error : Desconocido\n";	
			return false;
		}
	}

	return EXIT_SUCCESS;
}
bool UserPermission::methode(std::ostream& out)
{
	cgicc::form_iterator itUser = formData.getElement("user"); 
	if( !itUser->isEmpty() && itUser != (*formData).end()) 
	{
		
	}
	else 
	{
		return false;
	}
	
	cgicc::form_iterator itPermss = formData.getElement("permissions"); 
	if( !itPermss->isEmpty() && itPermss != (*formData).end()) 
	{
		
	}
	else 
	{
		return false;
	}

	//out << **itUser << " -- "  << **itPermss << "\n";
	try
	{
		std::string strsql = "name = '" + **itUser + "'";
		userlst = muposysdb::Users::select(connDB,strsql,0,'D');
		if(not userlst->size()) return false;
		if(userlst->size() != 1) return false;
		muposysdb::Users* user = userlst->front();
		if(user->downName(connDB) and user->getPerson().downName1(connDB)) 
		{
			user->getPerson().downName3(connDB);
		}
		else
		{
			return false;
		}
		
		muposysdb::User_Permission up;
		if(not up.insert(connDB,user->getPerson().getEnte().getID(),**itPermss)) return false;
		
		connDB.commit();
	}
	catch(std::exception& e)
	{
		out << "Error : " << e.what() << "</br>\n";
		return false;
	}
	
	return true;
}

}