/* Develop a menu driven program to simulate the following disk scheduling
algorithms: SSTF, SCAN, C-SCAN, C-LOOK.  */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h> //used for INT_MAX

// Function to sort the requests
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

void scan(int arr[], int n, int head, int size)
{
    int total_movement = 0;
    int current_head = head;
    printf("\nSCAN Sequence: ");

    // head moves from left to right
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

    // head goes from last disk request to end of disk
    total_movement += abs_diff(size - 1, current_head);
    current_head = size - 1;

    // now head moves from right to left
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
    printf("\nTotal Head Movement: %d\n", total_movement);
}

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

    // move to the rightmost track
    printf("%d ", size - 1);
    total_movement += abs_diff(current_head, size - 1);
    current_head = size - 1;

    // Move to the beginning (leftmost track)
    printf("0 ");
    total_movement += current_head; // Add distance from last track to beginning
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
    int initial_head_position, n, size;
    printf("Enter disk size: ");
    scanf("%d", &size);
    printf("Enter initial head position: ");
    scanf("%d", &initial_head_position);
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    int requests[n], r[n];
    printf("Enter the requests: ");

    // copy the requests array into r array
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &requests[i]);
        r[i] = requests[i];
    }

    sort(requests, n);

    if (size < requests[n - 1])
        printf("size < last disk request");

    // copy the requests array into r array
    for (int i = 0; i < n; i++)
    {
        r[i] = requests[i];
    }

    printf("Sorted array: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d  ", requests[i]);
    }

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
            scan(r, n, initial_head_position, size);
            break;
        case 3:
            c_scan(r, n, initial_head_position, size);
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

        // reinitialse r with requests array
        for (int i = 0; i < n; i++)
        {
            r[i] = requests[i];
        }
    } while (choice != 5);

    return 0;
}