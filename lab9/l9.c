#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct hole
{
    char name[20];
    int size;
} hole;

typedef struct process
{
    char name[20];
    int size;
    char alloc[20];
    char tmname[20];
    int tmsize;
} process;

void firstfit(process processes[], int np, hole holes[], int nh)
{
    hole remholes[nh];
    for (int i = 0; i < nh; i++)
    {
        remholes[i].size = holes[i].size;
        strcpy(remholes[i].name, holes[i].name);
    }
    for (int i = 0; i < np; i++)
    {
        int check = 0;
        for (int j = 0; j < nh; j++)
        {
            if (processes[i].size <= remholes[j].size)
            {
                remholes[j].size -= processes[i].size;
                strcpy(processes[i].alloc, remholes[j].name);
                check++;
                break;
            }
        }
        if (check == 0)
        {
            printf("\nNo Large Enough Memory Available for %s\n", processes[i].name);
            strcpy(processes[i].alloc, "Unavailable");
        }
    }
    printf("\nName\tSize\tAllocation\n");
    for (int i = 0; i < np; i++)
    {
        printf("%s\t%d\t%s\n", processes[i].name, processes[i].size, processes[i].alloc);
    }

    printf("\nName\tRemainingSize\n");
    for (int i = 0; i < nh; i++)
    {
        printf("%s\t%d\n", remholes[i].name, remholes[i].size);
    }
}

void bestfit(process processes[], int np, hole holes[], int nh)
{
    hole remholes[nh];
    for (int i = 0; i < nh; i++)
    {
        remholes[i].size = holes[i].size;
        strcpy(remholes[i].name, holes[i].name);
    }
    for (int i = 0; i < np; i++)
    {
        processes[i].tmsize = 9999;
    }
    for (int i = 0; i < np; i++)
    {
        int check = 0;
        for (int j = 0; j < nh; j++)
        {
            if (processes[i].size <= remholes[j].size && remholes[j].size < processes[i].tmsize)
            {
                processes[i].tmsize = remholes[j].size;
                strcpy(processes[i].tmname, remholes[j].name);
            }
        }
        for (int j = 0; j < nh; j++)
        {
            if (strcmp(processes[i].tmname, remholes[j].name) == 0)
            {
                remholes[j].size -= processes[i].size;
                strcpy(processes[i].alloc, remholes[j].name);
                check++;
                break;
            }
        }
        if (check == 0)
        {
            printf("\nNo Large Enough Memory Available for %s\n", processes[i].name);
            strcpy(processes[i].alloc, "Unavailable");
        }
    }
    printf("\nName\tSize\tAllocation\n");
    for (int i = 0; i < np; i++)
    {
        printf("%s\t%d\t%s\n", processes[i].name, processes[i].size, processes[i].alloc);
    }

    printf("\nName\tRemainingSize\n");
    for (int i = 0; i < nh; i++)
    {
        printf("%s\t%d\n", remholes[i].name, remholes[i].size);
    }
}

void worstfit(process processes[], int np, hole holes[], int nh)
{
    hole remholes[nh];
    for (int i = 0; i < nh; i++)
    {
        remholes[i].size = holes[i].size;
        strcpy(remholes[i].name, holes[i].name);
    }
    for (int i = 0; i < np; i++)
    {
        processes[i].tmsize = 0;
    }
    for (int i = 0; i < np; i++)
    {
        int check = 0;
        for (int j = 0; j < nh; j++)
        {
            if (processes[i].size <= remholes[j].size && remholes[j].size > processes[i].tmsize)
            {
                processes[i].tmsize = remholes[j].size;
                strcpy(processes[i].tmname, remholes[j].name);
            }
        }
        for (int j = 0; j < nh; j++)
        {
            if (strcmp(processes[i].tmname, remholes[j].name) == 0)
            {
                remholes[j].size -= processes[i].size;
                strcpy(processes[i].alloc, remholes[j].name);
                check++;
                break;
            }
        }
        if (check == 0)
        {
            printf("\nNo Large Enough Memory Available for %s\n", processes[i].name);
            strcpy(processes[i].alloc, "Unavailable");
        }
    }
    printf("\nName\tSize\tAllocation\n");
    for (int i = 0; i < np; i++)
    {
        printf("%s\t%d\t%s\n", processes[i].name, processes[i].size, processes[i].alloc);
    }

    printf("\nName\tRemainingSize\n");
    for (int i = 0; i < nh; i++)
    {
        printf("%s\t%d\n", remholes[i].name, remholes[i].size);
    }
}

void main()
{
    int nh, np;

    printf("Enter number of memory locations: "); // MEMORY CREATION
    scanf("%d", &nh);
    hole holes[nh];
    for (int i = 0; i < nh; i++)
    {
        printf("Enter location id: ");
        scanf("%s", &holes[i].name);
        printf("Enter location size: ");
        scanf("%d", &holes[i].size);
    }

    printf("Enter number of processes: "); // PROCESS CREATION
    scanf("%d", &np);
    process processes[np];
    for (int i = 0; i < np; i++)
    {
        printf("Enter location name: ");
        scanf("%s", &processes[i].name);
        printf("Enter location size: ");
        scanf("%d", &processes[i].size);
    }

    printf("\n\n");
    printf("Memory: ");
    for (int i = 0; i < nh; i++)
    {
        printf("%s\t", holes[i].name);
    }
    printf("\nSize:   ");
    for (int i = 0; i < nh; i++)
    {
        printf("%d\t", holes[i].size);
    }

    printf("\n\n");
    printf("Processes: ");
    for (int i = 0; i < np; i++)
    {
        printf("%s\t", processes[i].name);
    }
    printf("\nSize:      ");
    for (int i = 0; i < np; i++)
    {
        printf("%d\t", processes[i].size);
    }
    printf("\n\nFIRST FIT\n\n");
    firstfit(processes, np, holes, nh);
    printf("\n\nBEST FIT\n\n");
    bestfit(processes, np, holes, nh);
    printf("\n\nWORST FIT\n\n");
    worstfit(processes, np, holes, nh);
}
