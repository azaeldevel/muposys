


#include "config.h"
#include "user-permiss.hh"


namespace muposys
{



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
		cgicc::HTTPRedirectHeader headerRedirect("/login.html?failure");
		headerRedirect.render(out);
		return EXIT_SUCCESS;
	}
	
	print(std::cout);

	return EXIT_SUCCESS;
}
}