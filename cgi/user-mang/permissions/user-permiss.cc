


#include "config.h"
#include "user-permiss.hh"


namespace muposys
{

BodyUserPermission::BodyUserPermission()
{
	user_mang = false;
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
			out << "\t\t<label for=\"user\"><b>Usuario:</b></label>\n";
			out << "\t\t<select name=\"user\" id=\"user\">\n";
					
				out << "\t\t<option value=\"";
				out << "volvo";
				out << "\">";
				out << "Volvo";
				out << "</option>\n";
	
				out << "\t\t<option value=\"";
				out << "volvo";
				out << "\">";
				out << "Volvo";
				out << "</option>\n";
		
				out << "\t\t<option value=\"";
				out << "volvo";
				out << "\">";
				out << "Volvo";
				out << "</option>\n";
	
			out << "\t\t</select>\n";

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
		cgi = true;
	}
	else 
	{
		cgi = false;
		print(std::cout);
	}
	

	return EXIT_SUCCESS;
}

}