
#include "add.hh"

namespace muposys::server
{

int Add::main(std::ostream& out)
{	
	muposys::contenttype(out,"text","html");
	
	out << "<html>\n";
	head.print(out);
	
	if(not has_session()) 
	{
		head.redirect(0,"/login.html?failure");
		head.print(out);
		return EXIT_FAILURE;
	}

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
		head.redirect(0,"add.html?batdata");
		head.print(out);
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
		//std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>"; 
		head.redirect(0,"add.html?batdata");
		head.print(out);
		return EXIT_FAILURE; 
	}

	octetos::db::maria::Connector connmaria;
	if(not connmaria.connect(muposysdb::datconex)) 
	{
		//std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
		head.redirect(0,"add.html?failureconection");
		head.print(out);
	}
		
	
	muposysdb::Ente enteus;;
	if(not enteus.insert(connmaria)) 
	{
		//std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
		head.redirect(0,"add.html?failuredinsert");
		head.print(out);
	}
	muposysdb::UserManagement usmang;
	if(not usmang.insert(connmaria,enteus)) 
	{
		//std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
		head.redirect(0,"add.html?failuredinsert");
		head.print(out);
	}
	muposysdb::Permission permss;
	if(not permss.insert(connmaria,usmang,name,brief)) 
	{
		//std::cout << "Fail : " << __FILE__ << ":" << __LINE__<< "<br>";
		head.redirect(0,"add.html?failuredinsert");
		head.print(out);
	}

	connmaria.commit();
	connmaria.close();

	head.redirect(0,"add.html?success");
	head.print(std::cout);
	
	out << "</html>\n";
	
	return EXIT_SUCCESS;	
}

}
