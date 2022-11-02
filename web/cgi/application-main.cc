

#include "application.hh"


int main()
{	
	mps::contenttype(std::cout,"text","html");
	mps::BodyApplication body;
	mps::Application app(body);
	//app.main();
	
	return EXIT_SUCCESS;
}
