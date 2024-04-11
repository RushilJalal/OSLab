/* Develop a menu driven program to simulate the following disk scheduling algo- 
rithms: FCFS, LOOK. */

#include <stdio.h>
#include <stdlib.h>

// Function to simulate FCFS disk scheduling algorithm
void fcfs(int *requests, int num_requests, int head_position) {
    int total_seek_time = 0;

    for (int i = 0; i < num_requests; i++) {
        int seek_time = abs(requests[i] - head_position);
        total_seek_time += seek_time;
        head_position = requests[i];
    }

    printf("FCFS Disk Scheduling Algorithm\n");
    printf("Total Seek Time: %d\n", total_seek_time);
}

// Function to simulate LOOK disk scheduling algorithm
void look(int *requests, int num_requests, int head_position) {
    int total_seek_time = 0;
    int direction = 1; // 1 for moving towards higher track, -1 for moving towards lower track

    // Sort the requests in ascending order
    for (int i = 0; i < num_requests - 1; i++) {
        for (int j = 0; j < num_requests - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }

    // Find the index of head position in the sorted requests
    int head_index = 0;
    for (int i = 0; i < num_requests; i++) {
        if (requests[i] >= head_position) {
            head_index = i;
            break;
        }
    }

    // Move towards higher track until the last request
    for (int i = head_index; i < num_requests; i++) {
        int seek_time = abs(requests[i] - head_position);
        total_seek_time += seek_time;
        head_position = requests[i];
    }

    // Move towards lower track from the last request to the first request
    for (int i = head_index - 1; i >= 0; i--) {
        int seek_time = abs(requests[i] - head_position);
        total_seek_time += seek_time;
        head_position = requests[i];
    }

    printf("LOOK Disk Scheduling Algorithm\n");
    printf("Total Seek Time: %d\n", total_seek_time);
}

int main() {
    int num_requests;
    int head_position;

    printf("Enter the number of disk requests: ");
    scanf("%d", &num_requests);

    int *requests = (int *)malloc(num_requests * sizeof(int));

    printf("Enter the disk requests: ");
    for (int i = 0; i < num_requests; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head_position);

    int choice;
    printf("Disk Scheduling Algorithms:\n");
    printf("1. FCFS\n");
    printf("2. LOOK\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
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

    free(requests);

    return 0;
}