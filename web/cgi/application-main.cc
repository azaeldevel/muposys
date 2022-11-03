

#include "application.hh"


int main()
{	
	//mps::contenttype(std::cout,"text","html");
	//std::cout << "Step 1.\n";
	mps::BodyApplication body;
	//std::cout << "Step 2.\n";
	mps::Application app(body);
	//std::cout << "Step 3.\n";
	app.main();
	//std::cout << "Step 4.\n";
	
	return EXIT_SUCCESS;
}
