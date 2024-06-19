
#ifndef OCTETOS_MUPOSYS_WEB_V1_HH
#define OCTETOS_MUPOSYS_WEB_V1_HH


#include <CUnit/Basic.h>
#if defined(__linux__)

#elif defined(_WIN32) || defined(_WIN64)

#else
	#error "Plataforma desconocida"
#endif

int v1_init(void);
int v1_clean(void);
void v1_developing();


#endif
