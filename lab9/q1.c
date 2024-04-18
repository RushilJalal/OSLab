#include <stdio.h>
#include <stdlib.h>

typedef struct hole
{
    int hole_id;
    int hole_size;
} hole;

typedef struct process
{
    int process_id;
    int process_size;
    int allocated_hole;
} process;

void sort(hole holes[], int nh)
{
    for (int i = 0; i < nh; i++)
    {
        for (int j = 0; j < nh - i - 1; j++)
        {
            if (holes[j].hole_size > holes[j + 1].hole_size)
            {
                hole temp = holes[j];
                holes[j] = holes[j + 1];
                holes[j + 1] = temp;
            }
        }
    }
}

void first_fit(hole holes[], int nh, process processes[], int np)
{
    printf("First Fit: \n");
    for (int i = 0; i < np; i++)
    {
        processes[i].allocated_hole = -1;
    }

    for (int i = 0; i < np; i++)
    {
        int check = 0;
        for (int j = 0; j < nh; j++)
        {
            if (holes[j].hole_size >= processes[i].process_size)
            {
                processes[i].allocated_hole = holes[j].hole_id;
                holes[j].hole_size -= processes[i].process_size;
                check = 1;
                break;
            }
        }

        if (!check)
        {
            printf("Process %d not allocated! Not enough size\n", processes[i].process_id);
        }
    }

    printf("Allocation status: \n");
    for (int i = 0; i < np; i++)
    {
        if (processes[i].allocated_hole != -1)
            printf("Process %d, Hole %d \n", processes[i].process_id, processes[i].allocated_hole);
    }
}

void best_fit(hole holes[], int nh, process processes[], int np)
{
    printf("best fit: \n");
    sort(holes, nh);

    for (int i = 0; i < np; i++)
    {
        processes[i].allocated_hole = -1;
    }

    for (int i = 0; i < np; i++)
    {
        int best_index = -1;
        for (int j = 0; i < nh; j++)
        {
            if (processes[i].process_size <= holes[j].hole_size)
            {
                best_index = j;
            }
        }

        if (best_index == -1)
        {
            printf("Process %d could not be allocated in any hole!", processes[i].process_id);
        }
        else
        {
            processes[i].allocated_hole = holes[best_index].hole_id;
            holes[best_index].hole_size -= processes[i].process_size;
        }
    }

    printf("Allocation status: \n");
    for (int i = 0; i < np; i++)
    {
        if (processes[i].allocated_hole != -1)
            printf("Process %d, Hole %d \n", processes[i].process_id, processes[i].allocated_hole);
    }
}

int main(int argc, char const *argv[])
{
    int nh, np;
    printf("Enter number of holes: \n");
    scanf("%d", &nh);
    hole holes[nh];

    for (int i = 0; i < nh; i++)
    {
        holes[i].hole_id = i;
        printf("Enter size of hole %d: ", i);
        scanf("%d", &holes[i].hole_size);
    }

    printf("Enter number of processes: \n");
    scanf("%d", &np);
    process processes[np];

    for (int i = 0; i < np; i++)
    {
        processes[i].process_id = i;
        printf("Enter size of process %d: ", i);
        scanf("%d", &processes[i].process_size);
        processes[i].allocated_hole = -1; // Initialize allocated_hole to -1
    }

    first_fit(holes, nh, processes, np);

    sort(holes, nh);
    best_fit(holes, nh, processes, np);
    return 0;
}
