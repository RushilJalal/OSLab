// Write a C program to simulate page replacement algorithms: FIFO and optimal. Frame
// allocation has to be done as per user input and use dynamic allocation for all data structures.

#include <stdio.h>
#include <stdlib.h>

// fifo
// on inserting a page reference number
// check if it already exists in the frames, top != num_frames
// if yes, hit(no page fault)
// else, miss(page fault), replace frames[0] with this number

void fifo(int pages[], int frames[], int num_pages, int num_frames)
{
    int hit_check, top = 0, front = 0, page_faults = 0;

    for (int i = 0; i < num_pages; i++)
    {
        hit_check = 0;
        for (int j = 0; j < num_frames; j++)
        {
            if (pages[i] == frames[j])
            {
                printf("Hit %d\n", pages[i]);
                hit_check = 1;
                break;
            }
        }

        if (hit_check == 0) // miss(page fault)
        {
            page_faults++;
            // queue is not full, insert new page number at top index
            if (top != num_frames)
            {
                frames[top] = pages[i];
                top++;
            }

            // replace front queue element with the new page number
            else
            {
                frames[front] = pages[i];
                front++;
            }
        }

        // cyclic queue
        if (front == top)
        {
            front = 0;
        }

        // print intermediate page table
        printf("After inserting %d: ", pages[i]);
        for (int i = 0; i < num_frames; i++)
        {
            printf("%d  ", frames[i]);
        }
        printf("\n");
    }

    printf("Total page faults: %d\n", page_faults);

    printf("Final page table: ");
    for (int i = 0; i < num_frames; i++)
    {
        printf("%d  ", frames[i]);
    }
    printf("\n");
}


// pages are replaced which would not be used for the longest duration of time in the future. 
void optimal()
{
    
}

int main(int argc, char const *argv[])
{
    int num_frames, num_pages;
    printf("Enter number of page frames: ");
    scanf("%d", &num_frames);
    printf("Enter number of page references: ");
    scanf("%d", &num_pages);

    int *pages = malloc(num_pages * sizeof(int));
    int *frames = malloc(num_frames * sizeof(int));

    // read page reference numbers
    printf("Enter the page reference numbers: ");
    for (int i = 0; i < num_pages; i++)
    {
        scanf("%d", &pages[i]);
    }

    // init frames to -1
    for (int i = 0; i < num_frames; i++)
    {
        frames[i] = -1;
    }

    fifo(pages, frames, num_pages, num_frames);

    return 0;
}
