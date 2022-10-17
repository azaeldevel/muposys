


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
	
    muposysdb::Entities ente1;
    CU_ASSERT(ente1.insert(connector));    
    muposysdb::Persons person1;
    std::string n1 = "n1-";
    n1 += std::to_string(randNumber);
    std::string country = "MEX";
    //ap += std::to_string(random);
    CU_ASSERT(person1.insert(connector,ente1,n1));
    	
    std::vector<muposysdb::Persons*>* lst = muposysdb::Persons::select(connector,"name1 like 'n1-%8'",5,'D');
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
    
    std::vector<muposysdb::Users*>* lstUsers = muposysdb::Users::select(connector,"person > 0",5,'D');
    
    std::vector<muposysdb::Permissions*>* permsslst = muposysdb::Permissions::select(connector,"",0);
    CU_ASSERT(permsslst != NULL)
  	/*
	for(auto p : *permsslst)
  	{
            if(p->downBrief(connector) and verbose)
            {
                //if(verbose)  std::cout << p->getName() << " " << p->getBrief() << std::endl;
            }
  	}
  	for(auto p : *permsslst)
  	{
            delete p;
  	}	
	*/
    delete permsslst;
	
    muposysdb::Permissions permss;
    std::string name_perss = "permss-" + std::to_string(randNumber);
    std::string brief_perss = "Prueba de muposys " + std::to_string(randNumber);
    muposysdb::Entities ente2;
    CU_ASSERT(ente2.insert(connector)); 
    CU_ASSERT(permss.insert(connector,ente2,name_perss,brief_perss));
		
    randNumber = randInt(generator);    
    muposysdb::Entities ente3;
    CU_ASSERT(ente3.insert(connector));		
    muposysdb::Persons person;
    std::string name_person = "person-" + std::to_string(randNumber);
    CU_ASSERT(person.insert(connector,ente3,name_person));
    name_person = "ap-" + std::to_string(randNumber);
    CU_ASSERT(person.upName3(connector,name_person));
    
    muposysdb::Entities ente_user;
    CU_ASSERT(ente_user.insert(connector));
    muposysdb::Users user;
    randNumber = randInt(generator);
    //std::cout << "Person : " << person.getEnte().getID() << "\n";
    std::string name_user = "user-" + std::to_string(randNumber);
    CU_ASSERT(user.insert(connector,ente_user,person,name_user));
    		
    muposysdb::Entities ente_up;
    CU_ASSERT(ente_up.insert(connector));
    muposysdb::User_Permission usr_permss;
    CU_ASSERT(usr_permss.insert(connector,ente_up,user,permss));
    
    randNumber = randInt(generator);
    muposysdb::Entities ente_catalog;
    CU_ASSERT(ente_catalog.insert(connector));
    muposysdb::Catalogs catalog1;
    std::string catalog_name = "catalog-" + std::to_string(randNumber);
    CU_ASSERT(catalog1.insert(connector,ente_catalog,catalog_name));
    
    randNumber = randInt(generator);
    muposysdb::Entities ente_cataloging;
    CU_ASSERT(ente_cataloging.insert(connector));
    muposysdb::Catalog_Items catItems1;
    std::string item_number = "item-" + std::to_string(randNumber);
    std::string item_name = "name-" + std::to_string(randNumber);
    CU_ASSERT(catItems1.insert(connector,ente_cataloging,catalog1,item_number,item_name));
    
    randNumber = randInt(generator);
    muposysdb::Entities ente_cataloging2;
    CU_ASSERT(ente_cataloging2.insert(connector));
    muposysdb::Catalog_Items catItems2;
    std::string item_number2 = "item-" + std::to_string(randNumber);
    std::string item_name2 = "name-" + std::to_string(randNumber);
    CU_ASSERT(catItems2.insert(connector,ente_cataloging2,catalog1,item_number2,item_name2));

	std::vector<muposysdb::Catalog_Items*>* lstCatItems = muposysdb::Catalog_Items::select(connector,"");
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
		
    connector.commit();
	connector.close();
		
}


void v0_develop()
{	
}
