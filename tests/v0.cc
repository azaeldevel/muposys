
#include <filesystem>
#include <random>

#include "v0.hh"


using namespace muposys::http::db;

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
	
	octetos::db::maria::Connector connmaria;
	bool flag = connmaria.connect(muposysdb::datconex);
	if(flag)
	{		
		CU_ASSERT(flag);
		
		//if(verbose) std::cout << "Listando los que tiene 8 con 5 registro maximo." << std::endl;
		std::vector<muposysdb::Persons*>* lst = muposysdb::Persons::select(connmaria,"name1 like 'n1-%8'");
		if(lst != NULL)
		{
		    for(auto p : *lst)
		    {
				if(p->downName1(connmaria) and p->downName3(connmaria)) 
				{
					CU_ASSERT(true);
					//std::cout << p->getName1() << " " << p->getName3() << std::endl;
				}
		    }
			for(auto p : *lst)
			{
				delete p;
			}
		}
		delete lst;


		std::vector<muposysdb::Users*>* userlst = muposysdb::Users::select(connmaria,"",0,'D');
		if(userlst != NULL)
		{
		    for(auto u : *userlst)
		    {
				if(u->getPerson().downName1(connmaria) and u->getPerson().downName3(connmaria)) 
				{
					CU_ASSERT(true);
					//std::cout << u->getPerson().getName1() << " " << u->getPerson().getName3() << std::endl;
				}
		    }
			for(auto u : *userlst)
			{
				delete u;
			}
		}
		delete lst;

		muposysdb::Permissions permss;
		int randNumber = randInt(generator);
		std::string name_perss = "permss-" + std::to_string (randNumber);
		std::string brief_perss = "biref-" + std::to_string (randNumber);
		CU_ASSERT(permss.insert(connmaria,name_perss,brief_perss));



		
		connmaria.commit();
		connmaria.close();
	}
	
	
}


void v0_develop()
{
	CU_ASSERT(true);

	std::string database_file = "http";

	CU_ASSERT(std::filesystem::exists(database_file));
	
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, 1000000);
	
	Conector conn(database_file);
	CU_ASSERT(conn.getServerConnector() != NULL);
	Session session;	
	std::string hoststr,sessionstr,timestr;
	hoststr = std::to_string(distrib(gen));
	sessionstr = std::to_string(distrib(gen));
	timestr = std::to_string(distrib(gen));
	session.insert(conn,hoststr,sessionstr,timestr);



}
