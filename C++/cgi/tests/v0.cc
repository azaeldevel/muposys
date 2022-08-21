
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
	
	Conector conn("../../tests/database");
	CU_ASSERT(conn.getServerConnector() != NULL)
	Session session;	
	std::string hoststr,sessionstr,timestr;
	hoststr = std::to_string(distrib(gen));
	sessionstr = std::to_string(distrib(gen));
	timestr = std::to_string(distrib(gen));
	session.insert(conn,hoststr,sessionstr,timestr);

	
	
	
}
