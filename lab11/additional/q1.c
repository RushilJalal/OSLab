/* Develop a menu driven program to simulate the following disk scheduling algo-
rithms: FCFS, LOOK. */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // to use INT_MAX

void sort(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to simulate FCFS disk scheduling algorithm
void fcfs(int *requests, int num_requests, int head_position)
{
    int total_seek_time = 0;

    for (int i = 0; i < num_requests; i++)
    {
        int seek_time = abs(requests[i] - head_position);
        total_seek_time += seek_time;
        head_position = requests[i];
    }

    printf("FCFS Disk Scheduling Algorithm\n");
    printf("Total Seek Time: %d\n", total_seek_time);
}

// Function to simulate LOOK disk scheduling algorithm
void look(int *requests, int num_requests, int head_position)
{
    int total_movement = 0;
    int i;

    sort(requests, num_requests);
    printf("LOOK Disk Scheduling Algorithm\n");
    printf("LOOK Sequence: ");

    // move right and check disk requests > initial head position
    for (i = 0; i < num_requests; i++)
    {
        if (requests[i] >= head_position)
        {
            printf("%d ", requests[i]);
            total_movement += abs(requests[i] - head_position);
            head_position = requests[i];
            requests[i] = INT_MAX;
        }
    }

    i = requests[num_requests - 1];

    // move left
    while (i >= 0)
    {
        if (requests[i] < head_position && requests[i] != INT_MAX)
        {
            printf("%d ", requests[i]);
            total_movement += abs(requests[i] - head_position);
            head_position = requests[i];
            requests[i] = INT_MAX;
        }
        i--;
    }

    printf("\nTotal Seek Time: %d\n", total_movement);
}

int main()
{
    int num_requests;
    int head_position;

    printf("Enter the initial head position: ");
    scanf("%d", &head_position);

    printf("Enter the number of disk requests: ");
    scanf("%d", &num_requests);

    int r[num_requests];

    int *requests = malloc(num_requests * sizeof(int));

    printf("Enter the disk requests: ");
    for (int i = 0; i < num_requests; i++)
    {
        scanf("%d", &requests[i]);
        r[i] = requests[i];
    }

    int choice;
    do
    {
        printf("Disk Scheduling Algorithms:\n");
        printf("1. FCFS\n");
        printf("2. LOOK\n");
        printf("-1. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            fcfs(requests, num_requests, head_position);
            break;
        case 2:
            look(requests, num_requests, head_position);
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }

        // reinitialse r with requests array
        for (int i = 0; i < num_requests; i++)
        {
            r[i] = requests[i];
        }
    } while (choice != -1);

    return 0;
}