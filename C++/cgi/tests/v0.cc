
#include "v0.hh"

int v0_init(void)
{
	return 0;
}
int v0_clean(void)
{
	return 0;
}

using namespace muposys::http::db;

void v0_develop()
{
	CU_ASSERT(true);

	std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(1, 1000000);
	
	Conector conn(muposys::http::db::database_file);
	CU_ASSERT(conn.getServerConnector() != NULL)
	Session session;	
	std::string hoststr,sessionstr,timestr;
	hoststr = std::to_string(distrib(gen));
	sessionstr = std::to_string(distrib(gen));
	timestr = std::to_string(distrib(gen));
	session.insert(conn,hoststr,sessionstr,timestr);

	
	octetos::db::maria::Connector connmaria;
	bool flag = connmaria.connect(muposysdb::datconex);
	if(flag)
	{		
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
	}

	muposys::http::Session sessionHttp("");
	//std::cout << "mdString 2 : " << sessionHttp.getSession().getSession()  << "\n";

	muposys::server::Login login;
	login.methode();
	
}
