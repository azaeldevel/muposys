


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

}

void v1_configuration_file()
{
    char* tmpf_config_temp = tmpnam(NULL);
    //int tmpf_hanle = mkstemp(tmpf_config_temp);
    //std::cout << "tmpf_config = " << tmpf_config_temp << "\n";
    std::filesystem::path tmpf_config = tmpf_config_temp;
    mps::Configuration config;
    config.create("mps-conf");

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

    mps::Configuration config2;
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
    CU_ASSERT(dtm.get_user() == "develop")
    CU_ASSERT(dtm.get_password() == "123456")
#ifdef OCTETOS_MUPOSYS_V1_TDD
    CU_ASSERT(dtm.get_database() == "muposys-dev")
#else
    CU_ASSERT(dtm.get_database() == "muposys")
#endif // OCTETOS_MUPOSYS_V1_TDD
}
