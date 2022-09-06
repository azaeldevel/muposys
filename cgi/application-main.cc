

#include "application.hh"


int main()
{	
	muposys::BodyApplication body;
	muposys::Application2 app(body);
	app.main();
	
	return 0;
}