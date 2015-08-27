#ifndef COMMON_H
#define COMMON_H

#include <time.h>
#include <sys/time.h>


void error(const int status, const char * fmt, ...);

void rand_init(const int seed);
short rand_sign();
short rand_bool();
short rand_bool_prob(const int prob);
int rand_range(const int range);
int rand_int(const int range);
int rand_signint(const int range);
float rand_float(const int range);
float rand_signfloat(const int range);

#define PLAINTIMER

#ifdef __MACH__
#define PLAINTIMER
#endif

// timer_t is already used in time_h (Linux)
typedef struct timing_t {
#ifdef PLAINTIMER
    struct timeval realbegin, realend;
#else
    struct timespec realbegin, realend;
#endif
    clock_t cpubegin, cpuend;
    //
    clock_t realtime, cputime;  // in ms
} timing_t;

void timer_start(timing_t * t);
void timer_stop(timing_t * t);


#endif
