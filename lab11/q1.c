/* Develop a menu driven program to simulate the following disk scheduling algo-
rithms: SSTF, SCAN, C-SCAN, C-LOOK.  */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to sort the requests in ascending order
void sort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
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

// Function to find the absolute difference between two numbers
int abs_diff(int a, int b)
{
    return abs(a - b);
}

// Function to find the index of the request nearest to the head
int find_nearest(int arr[], int n, int head)
{
    int min_diff = INT_MAX;
    int index = -1;
    for (int i = 0; i < n; i++)
    {
        int diff = abs_diff(arr[i], head);
        if (diff < min_diff)
        {
            min_diff = diff;
            index = i;
        }
    }
    return index;
}

// Function to simulate SSTF disk scheduling algorithm
void sstf(int arr[], int n, int head)
{
    int total_movement = 0;
    int current_head = head;
    printf("\nSSTF Sequence: ");
    for (int i = 0; i < n; i++)
    {
        int index = find_nearest(arr, n, current_head);
        printf("%d ", arr[index]);
        total_movement += abs_diff(current_head, arr[index]);
        current_head = arr[index];
        arr[index] = INT_MAX; // Mark the processed request
    }
    printf("\nTotal Head Movement: %d\n", total_movement);
}

// Function to simulate SCAN disk scheduling algorithm
void scan(int arr[], int n, int head, int size)
{
    int total_movement = 0;
    int current_head = head;
    int direction = 1; // 1 for moving right, -1 for moving left
    printf("\nSCAN Sequence: ");
    while (1)
    {
        if (direction == 1)
        {
            for (int i = 0; i < n; i++)
            {
                if (arr[i] >= current_head)
                {
                    printf("%d ", arr[i]);
                    total_movement += abs_diff(current_head, arr[i]);
                    current_head = arr[i];
                    arr[i] = INT_MAX; // Mark the processed request
                }
            }
            direction = -1;
        }
        else
        {
            for (int i = n - 1; i >= 0; i--)
            {
                if (arr[i] <= current_head && arr[i] != INT_MAX)
                {
                    printf("%d ", arr[i]);
                    total_movement += abs_diff(current_head, arr[i]);
                    current_head = arr[i];
                    arr[i] = INT_MAX; // Mark the processed request
                }
            }
            direction = 1;
        }
        // Check if there are any requests left
        int remaining_requests = 0;
        for (int i = 0; i < n; i++)
        {
            if (arr[i] != INT_MAX)
            {
                remaining_requests = 1;
                break;
            }
        }
        if (!remaining_requests)
            break;
    }
    printf("\nTotal Head Movement: %d\n", total_movement);
}

// Function to simulate C-SCAN disk scheduling algorithm
void c_scan(int arr[], int n, int head, int size)
{
    int total_movement = 0;
    int current_head = head;
    printf("\nC-SCAN Sequence: ");
    // Move right
    for (int i = 0; i < n; i++)
    {
        if (arr[i] >= current_head)
        {
            printf("%d ", arr[i]);
            total_movement += abs_diff(current_head, arr[i]);
            current_head = arr[i];
            arr[i] = INT_MAX; // Mark the processed request
        }
    }
    // Move to the beginning
    printf("%d ", size - 1);
    total_movement += abs_diff(current_head, size - 1);
    current_head = 0;
    // Move right again
    for (int i = 0; i < n; i++)
    {
        if (arr[i] != INT_MAX)
        {
            printf("%d ", arr[i]);
            total_movement += abs_diff(current_head, arr[i]);
            current_head = arr[i];
            arr[i] = INT_MAX; // Mark the processed request
        }
    }
    printf("\nTotal Head Movement: %d\n", total_movement);
}

// Function to simulate C-LOOK disk scheduling algorithm
void c_look(int arr[], int n, int head)
{
    int total_movement = 0;
    int current_head = head;
    printf("\nC-LOOK Sequence: ");
    // Move right
    for (int i = 0; i < n; i++)
    {
        if (arr[i] >= current_head)
        {
            printf("%d ", arr[i]);
            total_movement += abs_diff(current_head, arr[i]);
            current_head = arr[i];
            arr[i] = INT_MAX; // Mark the processed request
        }
    }
    // Move back to the beginning
    for (int i = 0; i < n; i++)
    {
        if (arr[i] != INT_MAX)
        {
            printf("%d ", arr[i]);
            total_movement += abs_diff(current_head, arr[i]);
            current_head = arr[i];
            arr[i] = INT_MAX; // Mark the processed request
        }
    }
    printf("\nTotal Head Movement: %d\n", total_movement);
}

int main()
{
    int initial_head_position, n;
    printf("Enter initial head position: ");
    scanf("%d", &initial_head_position);
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    int requests[n], r[n];
    printf("Enter the requests: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &requests[i]);
        r[i] = requests[i];
    }
    sort(requests, n);

    int choice;
    do
    {
        printf("\nDisk Scheduling Algorithms:\n");
        printf("1. SSTF\n");
        printf("2. SCAN\n");
        printf("3. C-SCAN\n");
        printf("4. C-LOOK\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            sstf(r, n, initial_head_position);
            break;
        case 2:
            scan(r, n, initial_head_position, n);
            break;
        case 3:
            c_scan(r, n, initial_head_position, n);
            break;
        case 4:
            c_look(r, n, initial_head_position);
            break;
        case 5:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice! Please enter a number between 1 and 5.\n");
        }

        // reinitialse r with requests
        for (int i = 0; i < n; i++)
        {
            r[i] = requests[i];
        }
    } while (choice != 5);

    return 0;
}