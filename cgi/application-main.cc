

#include "application.hh"


int main()
{	
	muposys::BodyApplication body;
	muposys::Application app(body);
	app.main();
	
	return 0;
}