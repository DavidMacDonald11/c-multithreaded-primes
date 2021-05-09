#include "../include/main.h"

#define THREAD_COUNT 4
bool is_prime = true;

int main(int argc, char *argv[])
{
    check_prime(input());

    return 0;
}

long input(void)
{
    long prime;

    printf("Please enter an integer that may be prime: ");
    scanf(" %ld", &prime);

    return prime;
}

void check_prime(long prime)
{
    long root = (long)sqrt((double)prime);

    for(long i = 2; i <= root && is_prime; i += 2)
    {
        long *divisors = construct_divisors(&i);
        pthread_t *threads = construct_threads(prime, divisors);
        join_threads(threads);

        free(divisors);
        free(threads);
    }

    char *result = is_prime ? "prime" : "not prime";
    printf("%d is %s.\n", prime, result);
}

long *construct_divisors(long *i)
{
    long *divisors = (long *)malloc(sizeof(long) * THREAD_COUNT);

    divisors[0] = *i;
    if(*i == 2) --(*i);

    for(int j = 1; j < THREAD_COUNT; ++j)
        divisors[j] = *i += 2;

    return divisors;
}

pthread_t *construct_threads(long prime, long *divisors)
{
    pthread_t *threads = (pthread_t *)malloc(sizeof(pthread_t) * THREAD_COUNT);

    for(int i = 0; i < THREAD_COUNT; ++i)
    {
        long *args = (long *)malloc(sizeof(long) * 2);
        args[0] = prime;
        args[1] = divisors[i];

        pthread_create(&threads[i], null, check_divides, (void *)args);
    }

    return threads;
}

void *check_divides(void *arg)
{
    long *args = (long *)arg;
    long prime = args[0];
    long divisor = args[1];

    if(prime % divisor == 0)
        is_prime = false;

    free(args);

    return null;
}

void join_threads(pthread_t *threads)
{
    for(int i = 0; i < THREAD_COUNT; ++i)
        pthread_join(threads[i], null);
}
