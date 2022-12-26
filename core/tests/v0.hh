

#ifndef MUPOSYS_CORE_TESTS_HH
#define MUPOSYS_CORE_TESTS_HH

#include <filesystem>
#include <CUnit/Basic.h>
#include <random>


#if __linux__
    #ifdef MUPOSYS_CORE_ENABLE_TDD
        #include <src/apidb.hh>
        #include <src/core.hh>
    #else
        #include <muposys/core/apidb.hh>
    #endif
#elif defined MSYS2
    #include <muposys/core/src/apidb.hh>
    #include <muposys/core/src/core.hh>
#else
	#error "Plataforma desconocida."
#endif

int v0_init(void);
int v0_clean(void);
void v0_apidb();
void v0_develop();

#endif
