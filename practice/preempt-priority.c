#include <stdio.h>
#include <stdlib.h>

typedef struct process
{
    int priority;
    int arrival_time;
    int completion_time;
    int TAT;
    int waiting_time;
    int completed;
    int remaining_time;
    int process_id;
} process;

void sortOnPriority(process *processes, int num_of_processes)
{
    for (int i = 0; i < num_of_processes; i++)
    {
        for (int j = 0; j < num_of_processes - i - 1; j++)
        {
            if (processes[j].priority > processes[j + 1].priority)
            {
                process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void preempt_priority(process *processes, int num_of_processes)
{
    int current_time = 0;
    int completed_processes = 0;
    // sort on priority
    sortOnPriority(processes, num_of_processes);

    while (completed_processes < num_of_processes)
    {
        int selectedProcess = -1;
        for (int i = 0; i < num_of_processes; i++)
        {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0)
            {
                if (selectedProcess == -1 || processes[i].priority < processes[selectedProcess].priority)
                {
                    selectedProcess = i;
                }
            }
        }

        if (selectedProcess == -1)
        {
            // no process available
            current_time++;
        }
        else // exec the selected process preemptively
        {
            printf("Time: %d Process no: %d\n", current_time, processes[selectedProcess].process_id);
            processes[selectedProcess].remaining_time--;
            current_time++;

            if (processes[selectedProcess].remaining_time == 0)
            {
                completed_processes++;
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    int num_of_processes;
    printf("Enter number of processes: ");
    scanf("%d", &num_of_processes);
    process *processes = malloc(sizeof(process) * num_of_processes);

    printf("Enter arrival time, burst time and priority: ");
    for (int i = 0; i < num_of_processes; i++)
    {
        processes[i].process_id = i + 1;
        printf("Process %d: ", processes[i].process_id);
        scanf("%d %d %d", &processes[i].arrival_time, &processes[i].remaining_time, &processes[i].priority);
    }

    preempt_priority(processes, num_of_processes);

    return 0;
}
