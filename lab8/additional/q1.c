// Write a C program to implement the deadlock detection algorithm.

#include <stdio.h>

int main()
{
    int np, nr; // Number of processes and resources
    int alloc[10][10], request[10][10], avail[10], r[10], w[10];

    printf("Enter the number of processes: ");
    scanf("%d", &np);
    printf("Enter the number of resources: ");
    scanf("%d", &nr);

    // Input total resource amounts (R1, R2, ..., Rn)
    for (int i = 0; i < nr; i++)
    {
        printf("Total amount of Resource R%d: ", i + 1);
        scanf("%d", &r[i]);
    }

    // Input request matrix
    printf("Enter the request matrix:\n");
    for (int i = 0; i < np; i++)
        for (int j = 0; j < nr; j++)
            scanf("%d", &request[i][j]);

    // Input allocation matrix
    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < np; i++)
        for (int j = 0; j < nr; j++)
            scanf("%d", &alloc[i][j]);

    // Calculate available resources
    for (int j = 0; j < nr; j++)
    {
        avail[j] = r[j];
        for (int i = 0; i < np; i++)
            avail[j] -= alloc[i][j];
    }

    // Mark processes with zero allocation
    for (int i = 0; i < np; i++)
    {
        int count = 0;
        for (int j = 0; j < nr; j++)
        {
            if (alloc[i][j] == 0)
                count++;
            else
                break;
        }
        if (count == nr)
            w[i] = 1; // Mark process as safe
    }

    // Check for deadlock
    int deadlock = 0;
    for (int i = 0; i < np; i++)
    {
        if (!w[i])
        {
            int canBeProcessed = 1;
            for (int j = 0; j < nr; j++)
            {
                if (request[i][j] > avail[j])
                {
                    canBeProcessed = 0;
                    break;
                }
            }
            if (canBeProcessed)
            {
                w[i] = 1; // Mark process as safe
                for (int j = 0; j < nr; j++)
                    avail[j] += alloc[i][j];
            }
            else
            {
                deadlock = 1;
                break;
            }
        }
    }

    if (deadlock)
        printf("\nDeadlock detected.\n");
    else
        printf("\nNo deadlock possible.\n");

    return 0;
}
