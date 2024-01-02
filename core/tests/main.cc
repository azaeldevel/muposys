
#include <iostream>
#include <CUnit/Basic.h>

#ifdef MUPOSYS_CORE_V0_TDD
	#include "v0.hh"
#elif defined MUPOSYS_CORE_V1_TDD
	#include "v1.hh"
#endif


int main(int argc, char *argv[])
{
	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

#ifdef MUPOSYS_CORE_V0_TDD

	CU_pSuite pSuite_v0 = CU_add_suite("MUPOSYS - core library v0", v0_init, v0_clean);
	if (NULL == pSuite_v0)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (NULL == CU_add_test(pSuite_v0, "Library..", v0_apidb))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (NULL == CU_add_test(pSuite_v0, "Developing..", v0_develop))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
#elif defined MUPOSYS_CORE_V1_TDD

	CU_pSuite pSuite_v1 = CU_add_suite("MUPOSYS - core library v1", v1_init, v1_clean);
	if (NULL == pSuite_v1)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (NULL == CU_add_test(pSuite_v1, "Developing..", v1_develop))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (NULL == CU_add_test(pSuite_v1, "Archivo de configuracion", v1_configuration_file))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
#endif

	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
