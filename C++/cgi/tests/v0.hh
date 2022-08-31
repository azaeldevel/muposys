

#ifndef OCTETOS_TESTS_V0_HH
#define OCTETOS_TESTS_V0_HH

#include <CUnit/Basic.h>
#include <random>



#include "../src/http.hh"
#include "../src/http-db.hh"
#include "../src/muposysdb.hpp"
#include "server.hh"

int v0_init(void);
int v0_clean(void);
void v0_develop();

#endif
