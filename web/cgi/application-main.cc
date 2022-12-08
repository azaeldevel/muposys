

#include "application.hh"

int main()
{	
	mps::GetParams params;
	//mps::contenttype(std::cout,"text","html");
	//std::cout << "Step 1.\n";
	mps::BodyApplication body(params);
	//std::cout << "Step 2.\n";
	mps::Application app(body,params);
	//std::cout << "Step 3.\n";
	app.main();
	//std::cout << "Step 4.\n";
	
	return EXIT_SUCCESS;
}
