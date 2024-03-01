#include <stdio.h>
#include <stdlib.h>

typedef struct Process
{
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
} Process;

int compareProcesses(Process *p1, Process *p2)
{
    if (p1->arrival_time != p2->arrival_time)
        return p1->remaining_time - p2->remaining_time;
    else
        return p1->arrival_time - p2->arrival_time;
}

void preemptiveSJF(Process processes[], int n)
{
    int currentTime = 0;
    int completedProcesses = 0;

    qsort(processes, sizeof(Process), n, compareProcesses);

    while (completedProcesses < n)
    {
        int selectedProcess = -1; // index of currently selected process for exec
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival_time < currentTime && processes[i].remaining_time > 0)
            {
                if (selectedProcess == -1 || processes[i].remaining_time < processes[selectedProcess].remaining_time)
                {
                    selectedProcess = i;
                }
            }
        }

        if (selectedProcess == -1) // no process eligible for exec
            currentTime++;
        else // execute selected process for 1 time quantum
        {
            processes[selectedProcess].remaining_time--;
            printf("Time: %d Process no: %d\n", currentTime, processes[selectedProcess].process_id);

            if (processes[selectedProcess].remaining_time == 0) // selected process fully exec
            {
                completedProcesses++;
                currentTime++;
            }
        }
    }
}

void RoundRobin(Process processes[], int n, int quantum)
{
    int currentTime = 0;
    int completedProcesses = 0;

    while(completedProcesses < n)
    {
        for(int i = 0; i < n; i++)
        {
            if(processes[i].remaining_time > 0)
            {
                
            }
        }
    }
}