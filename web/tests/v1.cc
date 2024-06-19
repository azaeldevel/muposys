

#include "v1.hh"

#include <string.h>
#include <iostream>

#if defined(__linux__)

#elif defined(_WIN32) || defined(_WIN64)

#else
	#error "Plataforma desconocida"
#endif


#include "../cgi-1/html.hh"
#include "../cgi-1/login.hh"

int v1_init(void)
{
	return 0;
}

int v1_clean(void)
{
	return 0;
}



void v1_developing()
{

    mps::Parameters params("user=root&psw=1234567");
    /*
    std::cout << params.size() << "<br>";
    for(auto const& s : params)
    {
        std::cout << s.first << " => " << s.second << "<br>";
    }
    */
    mps::Parameters::iterator user,passw;
    CU_ASSERT(params.size() == 2)
    CU_ASSERT_FALSE(params.find("user") == NULL)
    CU_ASSERT(strcmp(params.find("user"),"root") == 0)
    CU_ASSERT_FALSE(params.find("psw") == NULL)
    CU_ASSERT(strcmp(params.find("psw"),"1234567") == 0)


    mps::server::Login login;
    login.check(params);

}

