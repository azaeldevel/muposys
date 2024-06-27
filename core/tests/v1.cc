


#include "v1.hh"

#include <cave/1/mmsql.hh>


namespace cave1 = oct::cave::v1;

int v1_init(void)
{
	return 0;
}
int v1_clean(void)
{
	return 0;
}



void v1_develop()
{
    mps::Configuration config;
    cave1::mmsql::Data data = config.get_datasource();

	cave1::mmsql::Connection conn;
	try
	{
		conn.connect(data, true);
	}
	catch (const cave1::ExceptionDriver& e)
	{
		std::cout << "Exception (cave testing) : " << e.what() << "\n";
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception (cave testing) : " << e.what() << "\n";
	}
	catch (const cave1::core::exception& e)
	{
		std::cout << "Exception (cave testing) : " << e.what() << "\n";
	}
	catch (...)
	{

	}

    mps::Session session;
    std::string findSesion = "client = 'localhost' and session = 'X'";

    std::vector<mps::Session> sesionlst;
    try
    {
 		 conn.select(sesionlst,findSesion);
	}
	catch (const cave1::ExceptionDriver&)
	{

	}
	catch (...)
	{
	}
}

void v1_configuration_file()
{
    //std::cout << "MUPOSYS - TEST 1\n";
    char* tmpf_config_temp = tmpnam(NULL);
    //std::cout << "MUPOSYS - TEST 1.2\n";
    //int tmpf_hanle = mkstemp(tmpf_config_temp);
    //std::cout << "tmpf_config = " << tmpf_config_temp << "\n";
    //std::cout << "MUPOSYS - TEST 1.3\n";
    std::filesystem::path tmpf_config = tmpf_config_temp;
    //std::cout << "MUPOSYS - TEST 1.4\n";
    mps::Configuration config;
    //std::cout << "MUPOSYS - TEST 1.5\n";
    try
    {
        config.create(tmpf_config_temp);
    }
    catch(const mps::core::exception& e)
    {
        std::cout << e.what()<<"\n";
    }
    //std::cout << "MUPOSYS - TEST 1.6\n";

    //std::cout << mps::Configuration::defaul_file() << "\n";
    std::cout << " config.get_name() : " << config.get_name() << "\n";

    std::string name = config.get_name();
#ifdef OCTETOS_MUPOSYS_V1_TDD
    CU_ASSERT(name.compare("muposys(dev)") == 0)
#else
    CU_ASSERT(name.compare("muposys") == 0)
#endif // OCTETOS_MUPOSYS_V1_TDD
    mps::core::Semver version;
    version = config.get_version();
    CU_ASSERT(version.major == 1)
    CU_ASSERT(version.minor == 0)
    CU_ASSERT(version.patch == 0)
    CU_ASSERT(version.prerelease.compare("alpha") == 0)
    CU_ASSERT(version.build.compare("v1") == 0)

    //std::cout << "MUPOSYS - TEST 2\n";
    /*mps::Configuration config2;
    config2.create();
#ifdef OCTETOS_MUPOSYS_V1_TDD
    CU_ASSERT(name.compare("muposys(dev)") == 0)
#else
    CU_ASSERT(name.compare("muposys") == 0)
#endif // OCTETOS_MUPOSYS_V1_TDD
    mps::core::Semver version2;
    version2 = config2.get_version();
    CU_ASSERT(version2.major == 1)
    CU_ASSERT(version2.minor == 0)
    CU_ASSERT(version2.patch == 0)
    CU_ASSERT(version2.prerelease.compare("alpha") == 0)
    CU_ASSERT(version2.build.compare("v1") == 0)

    cave1::mmsql::Data dtm;
    dtm = config2.get_datasource();
    //CU_ASSERT(dtm.get_host() == "localhost")
    std::cout << " dtm.get_user() : " << dtm.get_user() << "\n";
    CU_ASSERT(dtm.get_user() == "develop")
    CU_ASSERT(dtm.get_password() == "123456")
#ifdef OCTETOS_MUPOSYS_V1_TDD
    CU_ASSERT(dtm.get_database() == "muposys-dev")
#else
    CU_ASSERT(dtm.get_database() == "muposys")
#endif // OCTETOS_MUPOSYS_V1_TDD

    mps::Configuration config3(mps::Configuration::default_file());
    //std::cout << config3.get_file_name() << "\n";
    cave1::mmsql::Data data = config3.get_datasource();*/

}
