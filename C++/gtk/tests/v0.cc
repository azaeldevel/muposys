


#include "v0.hh"

using namespace oct::mont;

int v0_init(void)
{
	if(not std::filesystem::exists("../../tests"))
	{
		std::cout << "No esta en el directorio correcto\n";
		return 1;
	}
	
	return 0;
}

int v0_clean(void)
{
	return 0;
}

void v0_developing()
{
	
}

