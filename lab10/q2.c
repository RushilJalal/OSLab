// Write a C program to simulate LRU Page Replacement. Frame allocation has to be done as
// per user input and dynamic allocation for all data structures.

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int numFrames, numPages, i, j, k, pageFaults = 0, counter = 0, leastRecentlyUsed;
    int *frames, *pages, *lastUsed;

    printf("Enter the number of frames: ");
    scanf("%d", &numFrames);

    printf("Enter the number of pages: ");
    scanf("%d", &numPages);

    frames = (int *)malloc(numFrames * sizeof(int));
    pages = (int *)malloc(numPages * sizeof(int));
    lastUsed = (int *)malloc(numFrames * sizeof(int));

    printf("Enter the page reference string: ");
    for (i = 0; i < numPages; i++)
    {
        scanf("%d", &pages[i]);
    }

    for (i = 0; i < numFrames; i++)
    {
        frames[i] = -1;
        lastUsed[i] = 0;
    }

    for (i = 0; i < numPages; i++)
    {
        int page = pages[i];
        int found = 0;

        for (j = 0; j < numFrames; j++)
        {
            if (frames[j] == page)
            {
                found = 1;
                lastUsed[j] = counter++;
                break;
            }
        }

        if (!found)
        {
            int replaceIndex = 0;
            leastRecentlyUsed = lastUsed[0];

            for (j = 1; j < numFrames; j++)
            {
                if (lastUsed[j] < leastRecentlyUsed)
                {
                    leastRecentlyUsed = lastUsed[j];
                    replaceIndex = j;
                }
            }

            frames[replaceIndex] = page;
            lastUsed[replaceIndex] = counter++;
            pageFaults++;
        }

        printf("Page reference: %d\n", page);
        printf("Frames: ");
        for (k = 0; k < numFrames; k++)
        {
            printf("%d ", frames[k]);
        }
        printf("\n\n");
    }

    printf("Total page faults: %d\n", pageFaults);

    return 0;
}