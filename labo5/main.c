#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main (int argc, const char *argv[])
{
	char * error;
	void * handle1;
	void * handle2;
	float (* Pi_V)(long long);
	float (* Pi_L)(long long);
	float (* ploshad_prao)(float, float);
	float (* ploshad_treo)(float, float);
	handle1 = dlopen ("./212121/libsss.so", RTLD_NOW);
	handle2 = dlopen ("./212121/libpi.so", RTLD_NOW);
	if (!handle1) {
		perror ("Handle1");
	}
	if (!handle2) {
		perror ("Handle2");
	}
	Pi_V = dlsym(handle2, "Pi_V");
	Pi_L = dlsym(handle2, "Pi_L");
	ploshad_prao = dlsym(handle1, "ploshad_prao");
	ploshad_treo = dlsym(handle1, "ploshad_treo");
	if ((error = dlerror() ) != 0) {
		printf ("error");
	}
	
	long long k = atoll(argv[1]);
	float a = atof (argv[2]);
	float b = atof (argv[3]);
	printf ("Валлиса %f \n", Pi_V(k));
	printf ("Лейбница %f \n", Pi_L(k));
	printf ("%f %f \n", a, b);
	ploshad_prao (a, b);
	ploshad_treo (a, b);
}

