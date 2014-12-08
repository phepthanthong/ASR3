#ifndef TEMPS_H
#define TEMPS_H

#include <sys/time.h>
#include <time.h>

typedef union {
        unsigned long long tick;
        struct {
                unsigned low;
                unsigned high;
        };
} tick_t;

#define GET_TICK(t) \
           __asm__ volatile("rdtsc" : "=a" ((t).low), "=d" ((t).high))

/* retourne le nombre de "ticks" entre t1 et t2 */
#define TICK_DIFF(t1, t2) \
           ((t2).tick - (t1).tick)

/* retourne le nombre de ms entre t1 et t2 */
#define TIME_DIFF(t1, t2) \
        ((t2.tv_sec - t1.tv_sec) * 1000000 + (t2.tv_usec - t1.tv_usec))

#endif	/* TEMPS_H */
