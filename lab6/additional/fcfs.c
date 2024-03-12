#include <stdio.h>
// fcfs

typedef struct process
{
    int process_id;
    int burst_time;
    int waiting_time;
} process;

void calculateWaitingTime(process *processes, int num_processes)
{
    processes[0].waiting_time = 0;
    for (int i = 1; i < num_processes; i++)
    {
        processes[i].waiting_time = processes[i - 1].waiting_time + processes[i - 1].burst_time;
    }
}

int main(int argc, char const *argv[])
{
    int num_processes;
    int sum = 0;
    printf("Enter number of processes\n");
    scanf("%d", &num_processes);
    process processes[num_processes];
    printf("Enter process burst times: \n");
    for (int i = 0; i < num_processes; i++)
    {
        processes[i].process_id = i;
        scanf("%d", &processes[i].burst_time);
    }

    calculateWaitingTime(processes, num_processes);

    printf("Waiting times of each process: \n");
    for (int i = 0; i < num_processes; i++)
    {
        printf("Process_id: %d  ", processes[i].process_id);
        printf("Waiting time: %d\n", processes[i].waiting_time);
    }

    for (int i = 0; i < num_processes; i++)
    {
        sum += processes[i].waiting_time;
    }

    printf("Average waiting time: %d\n", sum / num_processes);

    return 0;
}
