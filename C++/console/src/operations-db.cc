
#include <iostream>


namespace muposys::operations
{

bool addItemCatalogAdd(octetos::db::maria::Connector& connector)
{
	Catalog catalog;
	
	std::cout << "Introduca el Numero: ";
	std::string number;
	std::cin >> number;

	std::cout << "Introduca el tipo: ";
	std::string type;
	std::cin >> type;

	std::cout << "Introduca una breve descripcion : ";
	std::string brief;
	std::cin >> brief;

	catalog.insert(connector,number,type,brief);

	return true;
}

} 
