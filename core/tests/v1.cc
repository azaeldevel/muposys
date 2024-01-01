


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
    std::cout << "\n";
    mps::Configuration config;

    std::string name = config.get_name();
    CU_ASSERT(name.compare("muposys") == 0)
    mps::Configuration::Version version;
    version = config.get_version();
    CU_ASSERT(version.major == 1)
    CU_ASSERT(version.minor == 0)
    CU_ASSERT(version.patch == 0)
    CU_ASSERT(version.prerelease.compare("alpha") == 0)
    CU_ASSERT(version.build.compare("v1") == 0)
}
