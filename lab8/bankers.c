#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int available[MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int finish[MAX_PROCESSES];
int num_processes;
int num_resources;


int isSafe()
{
    int work[MAX_RESOURCES];
    int i, j, count = 0;

    // Initialize work with available resources
    for (i = 0; i < num_resources; i++)
    {
        work[i] = available[i];
    }

    // Initialize finish array
    for (i = 0; i < num_processes; i++)
    {
        finish[i] = 0;
    }

    // Check for each process
    while (count < num_processes)
    {
        int found = 0;

        for (i = 0; i < num_processes; i++)
        {
            if (finish[i] == 0)
            {
                int canAllocate = 1;

                for (j = 0; j < num_resources; j++)
                {
                    if (need[i][j] > work[j])
                    {
                        canAllocate = 0;
                        break;
                    }
                }

                if (canAllocate)
                {
                    // Allocate resources to process i
                    for (j = 0; j < num_resources; j++)
                    {
                        work[j] += allocation[i][j];
                    }

                    // Mark process i as finished
                    finish[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }

        // If no process can be allocated resources, break the loop
        if (!found)
        {
            break;
        }
    }

    // If all processes are finished, the system is in a safe state
    return (count == num_processes);
}

void resourceRequest(int process)
{
    int request[MAX_RESOURCES];
    int i;

    printf("Enter resource request for Process %d:\n", process);
    for (i = 0; i < num_resources; i++)
    {
        printf("Resource %d: ", i);
        scanf("%d", &request[i]);
    }

    // Check if the request can be granted
    for (i = 0; i < num_resources; i++)
    {
        if (request[i] > need[process][i] || request[i] > available[i])
        {
            printf("Request cannot be granted. Exiting.\n");
            return;
        }
    }

    // Simulate allocation
    for (i = 0; i < num_resources; i++)
    {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    // Check if the system remains in a safe state
    if (isSafe())
    {
        printf("Request granted. The system is still in a safe state.\n");
    }
    else
    {
        printf("Request cannot be granted. The system would be unsafe.\n");
        // Roll back the allocation
        for (i = 0; i < num_resources; i++)
        {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
    }
}

int main()
{
    int i, j;

    // Input the number of processes and resources
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);

    // Input the maximum available resources
    printf("Enter the maximum available resources for each type:\n");
    for (i = 0; i < num_resources; i++)
    {
        printf("Resource %d: ", i);
        scanf("%d", &available[i]);
    }

    // Input the maximum resources that can be allocated to each process
    printf("Enter the maximum resources for each process:\n");
    for (i = 0; i < num_processes; i++)
    {
        printf("For Process %d:\n", i);
        for (j = 0; j < num_resources; j++)
        {
            printf("Resource %d: ", j);
            scanf("%d", &max[i][j]);
        }
    }

    // Input the resources currently allocated to each process
    printf("Enter the resources currently allocated to each process:\n");
    for (i = 0; i < num_processes; i++)
    {
        printf("For Process %d:\n", i);
        for (j = 0; j < num_resources; j++)
        {
            printf("Resource %d: ", j);
            scanf("%d", &allocation[i][j]);

            // Calculate the need matrix
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Display the need matrix
    printf("Need matrix:\n");
    for (i = 0; i < num_processes; i++)
    {
        for (j = 0; j < num_resources; j++)
        {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // Check if the system is in a safe state
    if (isSafe())
    {
        printf("The system is in a safe state.\n");
    }
    else
    {
        printf("The system is not in a safe state.\n");
    }

    int process;
    printf("Enter the process number for resource request: ");
    scanf("%d", &process);
    resourceRequest(process);

    return 0;
}
