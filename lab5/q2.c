#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

// swap 2 strings
void swapStrings(char **a, char **b)
{
    char *temp = *a;
    *a = *b;
    *b = temp;
}

// sort strings
void bubbleSortStrings(int argc, char *argv[])
{
    for (int i = 0; i < argc - 1; i++)
    {
        for (int j = 0; j < argc - i - 1; j++)
        {
            if (strcmp(argv[j], argv[j + 1]) > 0)
            {
                swapStrings(&argv[j], &argv[j + 1]);
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("Fork failed");
        return 1;
    }

    else if (pid == 0) // child
    {
        bubbleSortStrings(argc, argv);
        printf("Sorted strings in child process: \n");
        for (int i = 1; i < argc; i++)
        {
            printf("%s\n", argv[i]);
        }
    }

    else
    {
        wait(NULL);
        printf("Unsorted strings in parent process: \n");
        for (int i = 1; i < argc; i++)
        {
            printf("%s\n", argv[i]);
        }
    }
    return 0;
}

