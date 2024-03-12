#include <stdio.h>
#include <stdlib.h>

typedef struct Process
{
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int priority;
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
            if (processes[i].arrival_time <= currentTime && processes[i].remaining_time > 0)
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

    while (completedProcesses < n)
    {
        for (int i = 0; i < n; i++)
        {
            if (processes[i].remaining_time > 0)
            {
                if (processes[i].remaining_time > quantum)
                {
                    currentTime += quantum;
                    processes[i].remaining_time -= quantum;
                    printf("Time: %d  Process: %d\n", currentTime, processes[i].process_id);
                }
                else
                {
                    currentTime += processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                    printf("Time %d: Process %d\n", currentTime, processes[i].process_id);
                    completedProcesses++;
                }
            }
        }
    }
}

void priorityScheduling(Process processes[], int n)
{
    // Sort processes based on priority (non-preemptive)
    qsort(processes, n, sizeof(Process), compareProcesses);

    int currentTime = 0;

    // Execute processes in order of priority
    for (int i = 0; i < n; ++i)
    {
        currentTime += processes[i].burst_time;
        printf("Time %d: Process %d\n", currentTime, processes[i].process_id);
    }
}

int main()
{
    int n, quantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    for (int i = 0; i < n; ++i)
    {
        processes[i].process_id = i + 1;
        printf("Enter arrival time, burst time, priority for Process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
        processes[i].remaining_time = processes[i].burst_time;
    }

    printf("\nSelect a scheduling algorithm:\n");
    printf("1. Preemptive SJF (with FCFS for equal arrival time)\n");
    printf("2. Round Robin\n");
    printf("3. Non-Preemptive Priority\n");
    printf("Enter your choice: ");

    int choice;
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        printf("\nPreemptive SJF Schedule with FCFS tie-breaker:\n");
        preemptiveSJF(processes, n);
        break;
    case 2:
        printf("Enter the time quantum for Round Robin: ");
        scanf("%d", &quantum);
        printf("\nRound Robin Schedule:\n");
        roundRobin(processes, n, quantum);
        break;
    case 3:
        printf("\nNon-Preemptive Priority Schedule:\n");
        priorityScheduling(processes, n);
        break;
    default:
        printf("Invalid choice\n");
        break;
    }

    return 0;
}