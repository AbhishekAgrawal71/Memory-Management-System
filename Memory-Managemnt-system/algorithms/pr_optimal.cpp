#include <stdio.h>
#include <stdlib.h>

// Function to find the frame that should be replaced
int findOptimalReplace(int *frames, int framesCount, int *refs, int n, int index)
{
    int farthest = -1;
    int replaceIndex = -1;

    for (int i = 0; i < framesCount; i++)
    {
        int j;
        for (j = index; j < n; j++)
        {
            if (frames[i] == refs[j])
            {
                if (j > farthest)
                {
                    farthest = j;
                    replaceIndex = i;
                }
                break;
            }
        }

        // Page not used again → replace immediately
        if (j == n)
            return i;
    }

    if (replaceIndex == -1)
        return 0;

    return replaceIndex;
}

int main()
{
    int framesCount;
    if (scanf("%d", &framesCount) != 1)
        return 0;

    int n;
    scanf("%d", &n);

    int *refs = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &refs[i]);

    int *frames = (int *)malloc(framesCount * sizeof(int));
    int framesSize = 0;

    int faults = 0;

    for (int i = 0; i < n; i++)
    {
        int page = refs[i];
        int found = 0;

        // Check if page already in frames
        for (int j = 0; j < framesSize; j++)
        {
            if (frames[j] == page)
            {
                found = 1;
                break;
            }
        }

        if (!found)
        {
            faults++;

            if (framesSize < framesCount)
            {
                frames[framesSize++] = page;
            }
            else
            {
                int idx = findOptimalReplace(frames, framesCount, refs, n, i + 1);
                frames[idx] = page;
            }
        }

        // Print current state
        printf("Step %d Frames: ", i + 1);
        for (int j = 0; j < framesSize; j++)
            printf("%d ", frames[j]);
        printf("\n");
    }

    printf("TotalPageFaults: %d\n", faults);

    free(refs);
    free(frames);

    return 0;
}
