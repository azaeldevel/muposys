

#ifndef OCTETOS_TESTS_V0_HH
#define OCTETOS_TESTS_V0_HH

#include <CUnit/Basic.h>
#include <random>



#include "../cgi/http.hh"
#include "../cgi/http-db.hh"
#include "../apidb/muposysdb.hpp"
#include "../cgi/application.hh"

int v0_init(void);
int v0_clean(void);
void v0_develop();

#endif
