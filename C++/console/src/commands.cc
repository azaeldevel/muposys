
#include <string.h>
#include <iostream>

#include "commands.hh"
#include "operations-db.hh"


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
#if defined MARIADB
		octetos::db::maria::Connector conn;
#elif defined MYSQL
		octetos::db::mysql::Connector conn;
#elif defined POSTGRESQL
		octetos::db::postgresql::Connector conn;
#else
	#error "Base dedatos desconocida."
#endif
		if(!conn.connect(muposysdb::datconex))
		{
			std::cout << "fallo la conexion\n";
		}

		if(operations::addItemCatalogAdd(conn))
		{
			if(not conn.commit())
			{
				std::cout << "Fallo commit\n";
			}
			conn.close();
			return true;
		}
		return false;
	}
	else
	{
		std::cout << "'" << argv[0] << "' comando desconocido." << std::endl;
		return false;
	}

	return true;
}

}
