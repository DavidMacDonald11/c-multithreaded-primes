#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define null NULL
#define bool char
#define true 1
#define false 0

long input(void);
void check_prime(long prime);
long *construct_divisors(long *i);
pthread_t *construct_threads(long prime, long *divisors);
void *check_divides(void *arg);
void join_threads(pthread_t *threads);
