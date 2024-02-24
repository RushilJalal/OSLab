#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

// finds sum from 1 to n using thread synchronisation
volatile long int a = 0;
pthread_mutex_t aLock;

void *threadFunc1(void *arg)
{
    int n = *((int *)arg);
    for (long int i = 1; i <= n / 2; i++)
    {
        pthread_mutex_lock(&aLock);
        a += i;
        printf("Thread 1: %ld\n", a);
        pthread_mutex_unlock(&aLock);
    }
}

void *threadFunc2(void *arg)
{
    int n = *((int *)arg);
    for (long int i = (n / 2) + 1; i <= n; i++)
    {
        pthread_mutex_lock(&aLock);
        a += i;
        printf(" Thread 2: %ld\n", a);
        pthread_mutex_unlock(&aLock);
    }
}

int main(int argc, char const *argv[])
{
    pthread_t one, two;
    a = 0;
    long int input;

    printf("Sum from 1 to ?: ");
    scanf("%ld", &input);

    pthread_mutex_init(&aLock, NULL);
    pthread_create(&one, NULL, &threadFunc1, &input);
    pthread_create(&two, NULL, &threadFunc2, &input);

    pthread_join(one, NULL);
    pthread_join(two, NULL);

    printf("%ld\n", a);

    pthread_mutex_destroy(&aLock);
    return 0;
}
