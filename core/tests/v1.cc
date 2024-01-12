


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
    config.create(tmpf_config);

    std::string name;
    config.get_name(name);
#ifdef OCTETOS_MUPOSYS_V1_TDD
    CU_ASSERT(name.compare("muposys(dev)") == 0)
#else
    CU_ASSERT(name.compare("muposys(dev)") == 0)
#endif // OCTETOS_MUPOSYS_V1_TDD
    mps::Configuration::Version version;
    config.get_version(version);
    CU_ASSERT(version.major == 1)
    CU_ASSERT(version.minor == 0)
    CU_ASSERT(version.patch == 0)
    CU_ASSERT(version.prerelease.compare("alpha") == 0)
    CU_ASSERT(version.build.compare("v1") == 0)

    mps::Configuration config2;
    config2.open();
#ifdef OCTETOS_MUPOSYS_V1_TDD
    CU_ASSERT(name.compare("muposys(dev)") == 0)
#else
    CU_ASSERT(name.compare("muposys(dev)") == 0)
#endif // OCTETOS_MUPOSYS_V1_TDD
    mps::Configuration::Version version2;
    config2.get_version(version2);
    CU_ASSERT(version2.major == 1)
    CU_ASSERT(version2.minor == 0)
    CU_ASSERT(version2.patch == 0)
    CU_ASSERT(version2.prerelease.compare("alpha") == 0)
    CU_ASSERT(version2.build.compare("v1") == 0)

    cave1::mmsql::Data dtm;
    config2.get_datasource(dtm);
    //CU_ASSERT(dtm.get_host() == "localhost")
    CU_ASSERT(dtm.get_user() == "develop")
    CU_ASSERT(dtm.get_password() == "123456")
    CU_ASSERT(dtm.get_database() == "muposys-dev")
}
