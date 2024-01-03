


#include "v1.hh"


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
#ifdef MUPOSYS_CORE_V1_TDD
    CU_ASSERT(name.compare("muposys(dev)") == 0)
#elif
    CU_ASSERT(name.compare("muposys") == 0)
#endif // MUPOSYS_CORE_V1_TDD
    mps::Configuration::Version version;
    config.get_version(version);
    CU_ASSERT(version.major == 1)
    CU_ASSERT(version.minor == 0)
    CU_ASSERT(version.patch == 0)
    CU_ASSERT(version.prerelease.compare("alpha") == 0)
    CU_ASSERT(version.build.compare("v1") == 0)


}
