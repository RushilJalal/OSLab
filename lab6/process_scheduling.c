#include <stdio.h>
#include <stdlib.h>

typedef struct Process
{
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int priority;
    int completed;
    int completion_time;
    int turn_around_time;
    int waiting_time;
} Process;

// helper function
void sort(Process *processes, int num_processes)
{
    // sort based on arrival time
    for (int i = 0; i < num_processes; i++)
    {
        for (int j = 0; j < num_processes - i - 1; j++)
        {
            if (processes[j].arrival_time > processes[j + 1].arrival_time)
            {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

// helper functions
void sortOnPriority(Process *processes, int n)
{
    // sort based on arrival time
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].priority > processes[j + 1].priority)
            {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

// helper function
void calcWait(Process processes[], int i, int currentTime, int n, double *sumWT, double *sumTAT)
{
    processes[i].completion_time = currentTime;
    // TAT = CT - AT
    processes[i].turn_around_time = processes[i].completion_time - processes[i].arrival_time;
    // WT = TAT - BT
    processes[i].waiting_time = processes[i].turn_around_time - processes[i].burst_time;
    *sumWT += processes[i].waiting_time;
    *sumTAT += processes[i].turn_around_time;
}

// helper function
void calcAvgWait(Process processes[], double sumWT, double sumTAT, int n)
{
    double avg_wait, avg_TAT;
    printf("Waiting time of each process: \n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d  Waiting time: %d\n", processes[i].process_id, processes[i].waiting_time);
    }

    avg_wait = sumWT / n;
    avg_TAT = sumTAT / n;
    printf("Avg waiting time: %.2f\nAvg TAT: %.2f\n", avg_wait, avg_TAT);
}

void preemptiveSJF(Process processes[], int n)
{
    int currentTime = 0;
    int completedProcesses = 0;
    double sumWT = 0;
    double sumTAT = 0;

    while (completedProcesses < n)
    {
        int selectedProcess = -1;
        for (int i = 0; i < n; i++) // run loop on arrived processes and get the shortest job
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
        {
            currentTime++;
        }
        else // execute selected process
        {
            processes[selectedProcess].remaining_time--;
            printf("Time: %d Process no: %d\n", currentTime, processes[selectedProcess].process_id);
            currentTime++;

            if (processes[selectedProcess].remaining_time <= 0) // selected process has no remaining time ie process completed
            {
                calcWait(processes, selectedProcess, currentTime, n, &sumWT, &sumTAT);
                completedProcesses++;
            }
        }
    }

    calcAvgWait(processes, sumWT, sumTAT, n);
}

void RoundRobin(Process processes[], int n, int quantum)
{
    int currentTime = 0;
    int completedProcesses = 0;
    double sumWT = 0;
    double sumTAT = 0;

    // sort processes according to arrival time
    sort(processes, n);

    while (completedProcesses < n)
    {
        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= currentTime && processes[i].remaining_time > 0)
            {
                printf("Time: %d  Process: %d\n", currentTime, processes[i].process_id);
                if (processes[i].remaining_time > quantum)
                {
                    currentTime += quantum;
                    processes[i].remaining_time -= quantum;
                }
                else // less that 1 time quantum RT remaining
                {
                    currentTime += processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                    completedProcesses++;
                    processes[i].completed = 1;
                    printf("Process %d completed!\n", processes[i].process_id);

                    calcWait(processes, i, currentTime, n, &sumWT, &sumTAT);
                }
            }
        }
    }
    calcAvgWait(processes, sumWT, sumTAT, n);
}

void priorityScheduling(Process processes[], int n)
{
    // non-preemptive

    int currentTime = 0;
    double sumWT = 0;
    double sumTAT = 0;

    // Sort processes based on priority (non-preemptive)
    sortOnPriority(processes, n);

    // Execute processes in order of priority
    for (int i = 0; i < n; i++)
    {
        printf("Time: %d Process no: %d\n", currentTime, processes[i].process_id);
        currentTime += processes[i].burst_time;
        calcWait(processes, i, currentTime, n, &sumWT, &sumTAT);
    }
    calcAvgWait(processes, sumWT, sumTAT, n);
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
        printf("Enter arrival time, burst time of process %d: ", i + 1);
        scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    int choice;
    while (choice != -1)
    {

        printf("\nSelect a scheduling algorithm:\n");
        printf("1. Preemptive SJF (with FCFS for equal arrival time)\n");
        printf("2. Round Robin\n");
        printf("3. Non-Preemptive Priority\n");
        printf("-1. Exit\n");
        printf("Enter your choice: ");

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
            RoundRobin(processes, n, quantum);
            break;

        case 3:
            for (int i = 0; i < n; i++)
            {
                printf("Enter the priority for process %d: ", processes[i].process_id);
                scanf("%d", &processes[i].priority);
            }
            printf("\nNon-Preemptive Priority Scheduling: \n");
            priorityScheduling(processes, n);
            break;

        case -1:
            break;

        default:
            printf("Invalid choice\n");
            break;
        }

        // reinitialise remaining time to burst times
        for (int i = 0; i < n; ++i)
        {
            processes[i].remaining_time = processes[i].burst_time;
        }
    }
    return 0;
}