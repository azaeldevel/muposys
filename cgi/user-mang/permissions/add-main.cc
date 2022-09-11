
#include <cstdlib>
#include <iostream>
#include <apidb/muposysdb.hpp>
#include "cgicc/HTTPHTMLHeader.h"


#include "../../http.hh"
#include "../../html.hh"


int main()
{	
	muposys::contenttype(std::cout,"text","html");	
	muposys::Head head;
	cgicc::Cgicc formData;   	
	std::string name, brief;
	cgicc::form_iterator itName = formData.getElement("name"); 
	if( !itName->isEmpty() && itName != (*formData).end()) 
	{
		std::cout << "name : " << **itName << "<br>"; 
		name = **itName;
	}
	else 
	{
		std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";   
		head.redirect(0,"add.html?fail");
		return EXIT_FAILURE;
	}
	
   	//std::cout << "Step 2 : \n<br>";
	
	cgicc::form_iterator itBrief = formData.getElement("brief");  
	if( !itBrief->isEmpty() && itBrief != (*formData).end()) 
	{
		std::cout << "brief : " << **itBrief << "<br>"; 
		brief = **itBrief;
	} 
	else 
	{
		std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>"; 
		head.redirect(0,"add.html?fail"); 
		head.redirect(0,"add.html?fail");  
		head.redirect(0,"add.html?fail");
		return EXIT_FAILURE; 
	}

	octetos::db::maria::Connector connmaria;
	if(not connmaria.connect(muposysdb::datconex)) std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
		
	muposysdb::Permissions permss;
	if(not permss.insert(connmaria,name,brief)) std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";

	connmaria.commit();
	connmaria.close();

	head.redirect(0,"add.html?sucesse");
	head.print(std::cout);
	
	return EXIT_SUCCESS;
}