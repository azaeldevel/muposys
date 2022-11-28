

#ifndef OCTETOS_TESTS_V0_HH
#define OCTETOS_TESTS_V0_HH

#include <filesystem>
#include <CUnit/Basic.h>
#include <random>



#include "../cgi/http.hh"
#include "../cgi/http-db.hh"
#include "../apidb/muposysdb.hpp"
#include "../cgi/application.hh"

static std::filesystem::path database_file = "http";

int v0_init(void);
int v0_clean(void);
void v0_apidb();
void v0_httpdb();
void v0_develop();

#endif
