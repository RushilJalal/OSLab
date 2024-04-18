#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>

#define MAX 100
int item = 0;
sem_t pmutex, cmutex, empty, full;
int buffer[MAX];
int in = 1, out = 1;

void *produce()
{
    sem_wait(&empty);
    item++;
    sem_wait(&pmutex);
    buffer[in] = item;
    printf("Item produced");
    in = in % MAX + 1;
    sem_post(&pmutex);
    sem_post(&full);
    return 0;
}

int main(int argc, char const *argv[])
{
    int i, numThreads;
    sem_init(&pmutex, 0, 1);
    sem_init(&cmutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, MAX);

    pthread_t *prod, *con;
    numThreads = abs(atoi(argv[1]));

    prod = malloc(sizeof(pthread_t) * numThreads);
    con = malloc(sizeof(pthread_t) * numThreads);

    for (i = 0; i < numThreads; i++)
    {
        pthread_create(&prod, NULL, &produce, NULL);
    }

    for (i = 0; i < numThreads; i++)
    {
        pthread_join(&prod, NULL);
    }

    return 0;
}
