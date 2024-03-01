#include <stdio.h>
#include <stdlib.h>

int available[100];
int allocation[100][100];
int max[100][100];
int need[100][100];
int num_processes;
int num_resources;

int main()
{
    printf("Enter number of processes: \n");
    scanf("%d", &num_processes);
    printf("Enter number of resources: \n");
    scanf("%d", &num_resources);

    for (int i = 0; i < num_resources; i++)
    {
        printf("Number of available resources of type %d: ", i);
        scanf("%d", &available[i]);
    }

    printf("Enter allocation matrix: \n");
    for (int i = 0; i < num_processes; i++)
    {
        for (int j = 0; j < num_resources; j++)
        {
            // printf("Value of process %d and resource type %d: ", i, j);
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter max matrix: \n");
    for (int i = 0; i < num_processes; i++)
    {
        for (int j = 0; j < num_resources; j++)
        {
            // printf("Value of process %d and resource type %d: ", i, j);
            scanf("%d", &max[i][j]);
            // calc need matrix
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // display need matrix
    printf("Need matrix: \n");
    for (int i = 0; i < num_processes; i++)
    {
        for (int j = 0; j < num_resources; j++)
        {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    resource_request(need, num_processes);
}

void safety()
{
    int work[100];
    int finish[100];

    // init work = available
    for (int i = 0; i < num_processes; i++)
    {
        work[i] = available[i];
    }

    // init finish = 0 for i = 0...n-1
    for (int i = 0; i < num_processes; i++)
    {
        finish[i] = 0;
    }

    // find value of i such that:
    // finish[i]=false
    // need[i]<=work
}

void resource_request(int need[][], int num_processes)
{
    int request[num_processes];
}
