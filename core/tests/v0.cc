


#include "v0.hh"
#include <climits>


int v0_init(void)
{
	return 0;
}
int v0_clean(void)
{
	return 0;
}

void v0_apidb()
{
	std::random_device generator;
  	std::uniform_int_distribution<int> randInt(1,INT_MAX);
	
	mps::Connector connector;
	bool flag = connector.connect(muposysdb::datconex);
    CU_ASSERT(flag);    
		
    int randNumber = randInt(generator);
	
    muposysdb::Ente ente1;
    CU_ASSERT(ente1.insert(connector));    
    muposysdb::Person person1;
    std::string n1 = "n1-";
    n1 += std::to_string(randNumber);
    std::string country = "MEX";
    //ap += std::to_string(random);
    CU_ASSERT(person1.insert(connector,ente1,n1));
    	
    std::vector<muposysdb::Person*>* lst = muposysdb::Person::select(connector,"name1 like 'n1-%8'",5,'D');
    CU_ASSERT(lst != NULL);
   	/*
	for(auto p : *lst)
   	{
            p->downName1(connector);
            if(not p->getName1().empty() and verbose)
            {
                if(verbose)  std::cout << ""<< p->getName1() << " " << p->getName3() << std::endl;
            }
  	}
   	for(auto p : *lst)
  	{
            delete p;
   	}
	*/
    delete lst;	
    
    std::vector<muposysdb::User*>* lstUsers = muposysdb::User::select(connector,"person > 0",5,'D');
    CU_ASSERT(lstUsers != NULL)
	for(auto p : *lstUsers)
  	{
		CU_ASSERT(p->downName(connector));
		CU_ASSERT(p->downPerson(connector));
      	//std::cout << p->getName() << std::endl;
  	}
  	for(auto p : *lstUsers)
  	{
            delete p;
  	}
    delete lstUsers;
	
    std::vector<muposysdb::Permission*>* permsslst = muposysdb::Permission::select(connector,"",0);
    CU_ASSERT(permsslst != NULL)
	for(auto p : *permsslst)
  	{
		CU_ASSERT(p->downBrief(connector));
		CU_ASSERT(p->downName(connector));
  	}
  	for(auto p : *permsslst)
  	{
    	delete p;
  	}
    delete permsslst;
	
    muposysdb::Permission permss;
    std::string name_perss = "permss-" + std::to_string(randNumber);
    std::string brief_perss = "Prueba de muposys " + std::to_string(randNumber);
    muposysdb::Ente ente2;
    CU_ASSERT(ente2.insert(connector)); 
	muposysdb::UserManagement ente2_um;
    CU_ASSERT(ente2_um.insert(connector,ente2)); 
    CU_ASSERT(permss.insert(connector,ente2_um,name_perss,brief_perss));
		
    randNumber = randInt(generator);    
    muposysdb::Ente ente3;
    CU_ASSERT(ente3.insert(connector));		
    muposysdb::Person person;
    std::string name_person = "person-" + std::to_string(randNumber);
    CU_ASSERT(person.insert(connector,ente3,name_person));
    name_person = "ap-" + std::to_string(randNumber);
    CU_ASSERT(person.upName3(connector,name_person));
    
    muposysdb::Ente ente_user;
    CU_ASSERT(ente_user.insert(connector));	
	muposysdb::UserManagement usermang;
	CU_ASSERT(usermang.insert(connector,ente_user));
    muposysdb::User user;
    randNumber = randInt(generator);
    std::string name_user = "user-" + std::to_string(randNumber);
    CU_ASSERT(user.insert(connector,usermang,person,name_user));
    CU_ASSERT(user.downName(connector));
    //std::cout << "User name : " << user.getName() << "\n";
	
    		
    //muposysdb::Ente ente_up;
    //CU_ASSERT(ente_up.insert(connector));
    muposysdb::UserPermission usr_permss;
    CU_ASSERT(usr_permss.insert(connector,user,permss));
	std::vector<muposysdb::UserPermission*>* userpermsslst = muposysdb::UserPermission::select(connector,"",0);
    CU_ASSERT(userpermsslst != NULL)
	for(auto p : *userpermsslst)
  	{
		CU_ASSERT(p->downPermission(connector));
		CU_ASSERT(p->downUser(connector));
  	}
  	for(auto p : *userpermsslst)
  	{
    	delete p;
  	}
    delete userpermsslst;
    
    randNumber = randInt(generator);
    muposysdb::Ente ente_catalog;
    CU_ASSERT(ente_catalog.insert(connector));
    muposysdb::Catalog catalog1;
    std::string catalog_name = "catalog-" + std::to_string(randNumber);
    CU_ASSERT(catalog1.insert(connector,ente_catalog,catalog_name));
    
    randNumber = randInt(generator);
    muposysdb::Ente ente_cataloging;
    CU_ASSERT(ente_cataloging.insert(connector));
    muposysdb::CatalogItem  catItems1;
    std::string item_number = "item-" + std::to_string(randNumber);
    std::string item_name = "name-" + std::to_string(randNumber);
    CU_ASSERT(catItems1.insert(connector,ente_cataloging,catalog1,item_number,item_name));
    
    randNumber = randInt(generator);
    muposysdb::Ente ente_cataloging2;
    CU_ASSERT(ente_cataloging2.insert(connector));
    muposysdb::CatalogItem  catItems2;
    std::string item_number2 = "item-" + std::to_string(randNumber);
    std::string item_name2 = "name-" + std::to_string(randNumber);
    CU_ASSERT(catItems2.insert(connector,ente_cataloging2,catalog1,item_number2,item_name2));

	std::vector<muposysdb::CatalogItem *>* lstCatItems = muposysdb::CatalogItem ::select(connector,"");
    CU_ASSERT(lstCatItems != NULL);
	/*
	if(lstCatItems)
	{
		for(auto p : *lstCatItems)
	   	{
		 	if(p->downNumber(connector))
		   	{
		    	std::cout << ""<< p->getNumber() << std::endl;
		  	}
	  	}
	   	for(auto p : *lstCatItems)
	  	{
		        delete p;
	   	}
		
	}
	*/
	if(lstCatItems) delete lstCatItems;

	randNumber = randInt(generator);
    muposysdb::Ente ente_cataloging3;
    CU_ASSERT(ente_cataloging3.insert(connector));
    muposysdb::CatalogItem  catItems3;
    std::string item_number3 = "item-" + std::to_string(randNumber);
    std::string item_name3 = "name-" + std::to_string(randNumber);
    CU_ASSERT(catItems3.insert(connector,ente_cataloging3,catalog1,item_number3,item_name3));

	randNumber = randInt(generator);
    muposysdb::Ente ente_stock1;
	CU_ASSERT(ente_stock1.insert(connector));
	muposysdb::Stock stock1;
	CU_ASSERT(stock1.insert(connector,ente_stock1));	
    std::string stock1_name = "stock-" + std::to_string(randNumber);
    std::string stock1_label = "Stock " + std::to_string(randNumber);
	CU_ASSERT(stock1.upBrief(connector,stock1_name));
		
	randNumber = randInt(generator);
    muposysdb::Ente ente_stock2;
	CU_ASSERT(ente_stock2.insert(connector));
	muposysdb::Stock stock2;
	CU_ASSERT(stock2.insert(connector,ente_stock2));	
    std::string stock2_name = "stock-" + std::to_string(randNumber);
    std::string stock2_label = "Stock " + std::to_string(randNumber);
	CU_ASSERT(stock2.upBrief(connector,stock2_name));
	
	//randNumber = randInt(generator);
    //muposysdb::Ente ente_stocking1;
	//CU_ASSERT(ente_stocking1.insert(connector));
	muposysdb::Stocking stoking1;
	CU_ASSERT(stoking1.insert(connector,stock1,catItems1,3));
	
	//randNumber = randInt(generator);
    //muposysdb::Ente ente_stocking2;
	//CU_ASSERT(ente_stocking2.insert(connector));
	muposysdb::Stocking stoking2;
	CU_ASSERT(stoking2.insert(connector,stock2,catItems2,1));

	muposysdb::Version ver1(3);
	CU_ASSERT(ver1.downName(connector));
	CU_ASSERT(ver1.downMajor(connector));
	CU_ASSERT(ver1.downMinor(connector));
	CU_ASSERT(ver1.getName().compare("database") == 0);
	//std::cout << "Major : " << ver1.getMajor() << "\n";
	//std::cout << "Minor : " << ver1.getMinor() << "\n";
	CU_ASSERT(ver1.getMajor() == 0);
	CU_ASSERT(ver1.getMinor() == 2);
	
	
	//muposysdb::Progress progress1;
	//CU_ASSERT(progress1.insert(connector,stoking1,catItems2,1));
	
	
    connector.commit();
	connector.close();		
}


void v0_develop()
{	
}
