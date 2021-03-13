
#include <string.h>
#include <iostream>

#include "commands.hh"


namespace muposys::commands
{

bool Muposys::command(int argc, const char* argv[])
{
	if(strcmp("--help",argv[0]) == 0 or strcmp("-h",argv[0]) == 0)
	{
		std::cout << "\tSistema Software de Multi-proposito." << std::endl;
		return true;
	}
	else if(strcmp("stock",argv[0]) == 0)
	{
		return stock(argc-1,argv+1);
	}
	else
	{
		std::cout << "'" << argv[0] << "' comando desconocido." << std::endl;
		return false;
	}

	return true;
}


bool Muposys::stock(int argc, const char* argv[])
{
	if(strcmp("catalog",argv[0]) == 0)
	{
		return catalog(argc-1,argv+1);
	}
	else
	{
		std::cout << "'" << argv[0] << "' comando desconocido." << std::endl;
		return false;
	}

	return true;
}
bool Muposys::catalog(int argc, const char* argv[])
{
	if(strcmp("add",argv[0]) == 0)
	{
		return catalog(argc-1,argv+1);
	}
	else
	{
		std::cout << "'" << argv[0] << "' comando desconocido." << std::endl;
		return false;
	}

	return true;
}

}
