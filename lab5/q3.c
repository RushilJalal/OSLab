#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void swapStrings(char **a, char **b)
{
    char *temp = *a;
    *a = *b;
    *b = temp;
}

// sort strings
void bubbleSortStrings(int n, char *arr[])
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (strcmp(arr[j], arr[j + 1]) > 0)
            {
                swapStrings(&arr[j], &arr[j + 1]);
            }
        }
    }
}

void selectionSortStrings(int n, char *arr[])
{
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (strcmp(arr[j], arr[minIndex]) < 0)
            {
                minIndex = j;
            }
        }
        if (minIndex != i)
            swapStrings(&arr[i], &arr[minIndex]);
    }
}

int main()
{
    int N;
    printf("Enter number of strings: \n");
    scanf("%d", &N);

    char *strings[N];

    printf("Enter %d strings", N);
    for (int i = 0; i < N; i++)
    {
        strings[i] = malloc(100);
        scanf("%s", strings[i]);
    }

    pid_t pid1 = fork();

    if (pid1 == 0) // child
    {
        bubbleSortStrings(N, strings);

        printf("Bubble sorted strings: \n");
        for (int i = 0; i < N; i++)
        {
            printf("%s\n", strings[i]);
            free(strings[i]);
        }
    }
    else
    {
        pid_t pid2 = fork();

        if (pid2 == 0)
        {
            selectionSortStrings(N, strings);
            printf("Selection sorted strings: \n");
            for (int i = 0; i < N; i++)
            {
                printf("%s\n", strings[i]);
            }
        }
        else
        {
            int status;
            pid_t terminated_pid = wait(&status);

            if (WIFEXITED(status))
            {
                printf("One of the child processes (PID %d) terminated.\n", terminated_pid);
            }

            for (int i = 0; i < N; i++)
            {
                free(strings[i]);
            }
        }
    }
    return 0;
}
