

#ifndef MUPOSYS_APIDB_HH
#define MUPOSYS_APIDB_HH

#include <filesystem>
#include <CUnit/Basic.h>
#include <random>


#ifdef MUPOSYS_APIDB_ENABLE_TDD
	#include "apidb.hh"
#else
	#include <muposys/apidb.hh>
#endif


int v0_init(void);
int v0_clean(void);
void v0_apidb();
void v0_develop();

#endif
