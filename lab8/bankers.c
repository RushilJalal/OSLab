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

// Function to check if the system is in a safe state
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
    printf("Enter the maximum resources that can be allocated to each process:\n");
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

    return 0;
}
