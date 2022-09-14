


#include "config.h"
#include "user-permiss.hh"


namespace muposys
{

BodyUserPermission::BodyUserPermission()
{
	user_mang = false;
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
	
	print(std::cout);

	return EXIT_SUCCESS;
}

}