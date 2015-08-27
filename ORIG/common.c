#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <sys/time.h>

#include "common.h"


void error(const int status, const char * fmt, ...) {
    va_list argp;
    va_start(argp, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, argp);
    fprintf(stderr, "\n");
    va_end(argp);
    exit(status);
}


void rand_init(const int seed) {
    srand(seed >= 0 ? (unsigned int) seed : (unsigned int) time(NULL));
}


short rand_bool() {
    return rand() < (RAND_MAX >> 1);
}


short rand_bool_prob(const int prob) {
    return rand() % 100 < prob;
}


short rand_sign() {
    return rand_bool() ? 1 : -1;
}


int rand_range(const int range) {
    return rand() % range;
}

int rand_int(const int range) {
    return rand() % range + 1;
}


int rand_signint(const int range) {
    return rand_int(range) * rand_sign();
}


float rand_float(const int range) {
    return (float) rand_int(range * 100) / 100.0;
}


float rand_signfloat(const int range) {
    return rand_float(range) * rand_sign();
}


void timer_start(timing_t * t) {
#ifdef PLAINTIMER
    gettimeofday(&t->realbegin, NULL);
#else
    clock_gettime(CLOCK_MONOTONIC, &t->realbegin);
#endif
    t->cpubegin = clock();
}


void timer_stop(timing_t * t) {
#ifdef PLAINTIMER
    gettimeofday(&t->realend, NULL);
#else
    clock_gettime(CLOCK_MONOTONIC, &t->realend);
#endif
    t->cpuend = clock();
    // calculate the difference in ms
    t->realtime = (t->realend.tv_sec - t->realbegin.tv_sec) * 1000;
#ifdef PLAINTIMER
    t->realtime += (t->realend.tv_usec - t->realbegin.tv_usec) / 1000;
#else
    t->realtime += (t->realend.tv_nsec - t->realbegin.tv_nsec) / 1000;
#endif
    t->cputime = (t->cpuend - t->cpubegin) * 1000 / CLOCKS_PER_SEC;
}
