#include <stdio.h>
#include <stdlib.h>
// non-preemptive sjf

typedef struct process
{
    int process_id;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int completed;
    int completion_time;
    int turn_around_time;
} process;

void sort(process *processes, int num_processes)
{
    // sort based on arrival time
    for (int i = 0; i < num_processes; i++)
    {
        for (int j = 0; j < num_processes - i - 1; j++)
        {
            if (processes[j].arrival_time > processes[j + 1].arrival_time)
            {
                process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void non_preemptive_sjf(process *processes, int num_processes)
{
    double sumWT = 0;
    double sumTAT = 0;
    double avg_wait;
    double avg_TAT;
    int current_time = 0;
    int completed_processes = 0;

    while (completed_processes < num_processes)
    {
        int selectedProcess = -1; // initially, no process selected
        // loop through all processes and choose process which has arrived and has shortest BT
        for (int i = 0; i < num_processes; i++)
        {
            if (!processes[i].completed && processes[i].arrival_time <= current_time) // arrived process but not completed yet
            {
                if (selectedProcess == -1 || processes[i].burst_time < processes[selectedProcess].burst_time)
                {
                    selectedProcess = i;
                }
            }
        }
        // run the selected process
        if (selectedProcess != -1)
        {
            processes[selectedProcess].completion_time = current_time + processes[selectedProcess].burst_time;
            // TAT = CT - AT
            processes[selectedProcess].turn_around_time = processes[selectedProcess].completion_time - processes[selectedProcess].arrival_time;
            // WT = TAT - BT
            processes[selectedProcess].waiting_time = processes[selectedProcess].turn_around_time - processes[selectedProcess].burst_time;
            sumWT += processes[selectedProcess].waiting_time;
            sumTAT += processes[selectedProcess].turn_around_time;
            current_time = processes[selectedProcess].completion_time;
            completed_processes++;
            processes[selectedProcess].completed = 1; // process complete
        }

        else // no process arrived yet
        {
            current_time++;
        }
    }

    printf("Waiting time of each process: \n");
    for (int i = 0; i < num_processes; i++)
    {
        printf("Process %d  Waiting time: %d\n", processes[i].process_id, processes[i].waiting_time);
    }

    avg_wait = sumWT / num_processes;
    avg_TAT = sumTAT / num_processes;
    printf("Avg waiting time: %.2f\n Avg TAT: %.2f\n", avg_wait, avg_TAT);
}

int main(int argc, char const *argv[])
{
    int num_processes;
    printf("Enter number of processes: ");
    scanf("%d", &num_processes);

    process *processes = (process *)malloc(num_processes * sizeof(process));
    printf("Enter arrival time and burst time of each process: \n");
    for (int i = 0; i < num_processes; i++)
    {
        processes[i].process_id = i + 1;
        printf("Enter arrival time of process %d: ", processes[i].process_id);
        scanf("%d", &processes[i].arrival_time);
        printf("Enter burst time of process %d: ", processes[i].process_id);
        scanf("%d", &processes[i].burst_time);
    }

    // sort processes based on arrival time
    sort(processes, num_processes);

    // calculate waiting time for each process and avg waiting time
    non_preemptive_sjf(processes, num_processes);

    return 0;
}
