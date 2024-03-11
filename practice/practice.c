#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

int sum = 0;
void *adder(void *arg)
{
    for (int i = 0; i < 10; i++)
    {
        sum += i;
        printf("%d\n", sum);
    }
    return NULL;
}
int main(int argc, char const *argv[])
{
    pthread_t tid1, tid2;

    pthread_create(&tid1, NULL, adder, NULL);
    pthread_create(&tid2, NULL, adder, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    return 0;
}
