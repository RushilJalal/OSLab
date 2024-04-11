// dining philosopher problem

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t forks[N];
sem_t mutex;

void *philosopher(void *arg)
{
    int id = *(int *)arg;
    int left = id;
    int right = (id + 1) % N;

    while (1)
    {
        // Thinking
        printf("Philosopher %d is thinking...\n", id);
        sleep(1);

        // Pick up forks
        sem_wait(&mutex);
        sem_wait(&forks[left]);
        sem_wait(&forks[right]);
        sem_post(&mutex);

        // Eating
        printf("Philosopher %d is eating!\n", id);
        sleep(2);

        // Put down forks
        sem_post(&forks[left]);
        sem_post(&forks[right]);
    }
}

int main()
{
    pthread_t philosophers[N];
    int ids[N];

    sem_init(&mutex, 0, 1);
    for (int i = 0; i < N; i++)
        sem_init(&forks[i], 0, 1);

    for (int i = 0; i < N; i++)
    {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(philosophers[i], NULL);

    return 0;
}
