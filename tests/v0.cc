
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

		std::vector<muposysdb::Permissions*>* permisslst = muposysdb::Permissions::select(connmaria,"",0,'D');
		if(permisslst != NULL)
		{
		    for(auto p : *permisslst)
		    {
				if(p->downBrief(connmaria)) 
				{
					CU_ASSERT(true);
					std::cout << p->getName() << " | " << p->getBrief() << "\n";
				}
		    }
			for(auto p : *permisslst)
			{
				delete p;
			}
		}
		delete permisslst;

		
		muposysdb::Permissions permss;
		int randNumber = randInt(generator);
		std::string name_perss = "permss-" + std::to_string (randNumber);
		std::string brief_perss = "Prueba de muposys " + std::to_string (randNumber);
		CU_ASSERT(permss.insert(connmaria,name_perss,brief_perss));

		
		randNumber = randInt(generator);
		muposysdb::Entities ente;
		ente.insert(connmaria);
		
		muposysdb::Persons person;
		std::string name_person = "person-" + std::to_string(randNumber);
		CU_ASSERT(person.insert(connmaria,ente,name_person));
		name_person = "ap-" + std::to_string(randNumber);
		CU_ASSERT(person.upName3(connmaria,name_person));
		
		muposysdb::Users user;
		randNumber = randInt(generator);
		std::cout << "Person : " << person.getEnte().getID() << "\n";
		std::string name_user = "user-" + std::to_string(randNumber);
		CU_ASSERT(user.insert(connmaria,person,name_user));
		
		muposysdb::User_Permission usr_permss;
		CU_ASSERT(usr_permss.insert(connmaria,user.getPerson().getEnte().getID(),permss));
		
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
