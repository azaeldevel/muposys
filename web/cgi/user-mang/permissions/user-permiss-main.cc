

#include "user-permiss.hh"


int main()
{	
	muposys::BodyUserPermission body;
	muposys::UserPermission app(body);
	app.main();
	
	return 0;
}