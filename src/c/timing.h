#include <stdio.h>
#include <time.h>

struct timespec tstart={0,0}, tend={0,0};
#define timing(name, func) \
    clock_gettime(CLOCK_MONOTONIC, &tstart); \
    func; \
	clock_gettime(CLOCK_MONOTONIC, &tend); \
    printf("%s took about %.5f seconds\n", #name, ((double)tend.tv_sec + 1.0e-9*tend.tv_nsec) - ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));

