#include <stdio.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int available[MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
int num_processes;
int num_resources;

int isSafe()
{
    // init finish[i] = 0, work[i] = available[i]
    // find i such that need[i] < work && finish[i] = false
    // work += allocation
    // in the end, if finish = true system in safe state

    int finish[num_processes];
    int work[num_resources];

    for (int i = 0; i < num_resources; i++)
    {
        work[i] = available[i];
    }

    for (int i = 0; i < num_processes; i++)
    {
        finish[i] = 0;
    }

    int count = 0;
    while (count < num_processes)
    {
        int found = 0;
        int i;
        for (i = 0; i < num_processes; i++)
        {
            if (finish[i] == 0)
            {
                int canAlloc = 1;
                for (int j = 0; j < num_resources; j++)
                {
                    if (need[i][j] > work[i])
                    {
                        canAlloc = 0;
                        break;
                    }
                }

                if (canAlloc)
                {
                    for (int j = 0; j < num_resources; j++)
                    {
                        work[i] = allocation[i][j];
                    }
                }
            }
        }
        if (!found)
            break;
    }
    return (count == num_processes);
}

// algo for resource request
// if request [i] < available[i] && request[i] < need[process][i]
// available[i] -= request[i];
// need[process][i] -= request[i]
// allocation[process][i] += request[i]
// check if system in safe state
// if not, rollback