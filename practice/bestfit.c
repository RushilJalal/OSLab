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