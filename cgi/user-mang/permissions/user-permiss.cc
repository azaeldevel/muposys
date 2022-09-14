


#include "config.h"
#include "user-permiss.hh"


namespace muposys
{

void BodyUserPermission::options(std::ostream& out)const
{		
	out << "\t\t\t<div id=\"logout\"><a href=\"/logout.cgi\"></a></div>\n";	
}
void BodyUserPermission::print(std::ostream& out)const
{		
	
}


UserPermission::~UserPermission()
{
}
UserPermission::UserPermission(const BodyApplication& b) : Application(b)
{
}
	

int UserPermission::main(std::ostream& out)
{	
	muposys::contenttype(out,"text","html");	
		
	if(not session.load(CGI::conn))
	{
		cgicc::HTTPRedirectHeader headerRedirect("/login.html?failure");
		headerRedirect.render(out);
		return EXIT_SUCCESS;
	}
	
	print(std::cout);

	return EXIT_SUCCESS;
}
}