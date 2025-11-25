#include <stdio.h>
#include <stdlib.h>

int main()
{
    int frames;
    if (scanf("%d", &frames) != 1)
        return 0;

    int k;
    scanf("%d", &k);

    int *refs = (int *)malloc(k * sizeof(int));
    for (int i = 0; i < k; i++)
        scanf("%d", &refs[i]);

    int *cache = (int *)malloc(frames * sizeof(int)); // stores frames (LRU order)
    int cache_size = 0;

    int faults = 0;

    for (int i = 0; i < k; i++)
    {
        int page = refs[i];
        int found = -1;

        // Check if page is already in cache
        for (int j = 0; j < cache_size; j++)
        {
            if (cache[j] == page)
            {
                found = j;
                break;
            }
        }

        // If not found => page fault
        if (found == -1)
        {
            faults++;

            // If cache full, remove LRU (last element)
            if (cache_size == frames)
            {
                // shift all left by 1 (drop LRU)
                for (int j = frames - 1; j > 0; j--)
                    cache[j] = cache[j - 1];
                cache[0] = page;
            }
            else
            {
                // shift existing right to make place at front
                for (int j = cache_size; j > 0; j--)
                    cache[j] = cache[j - 1];
                cache[0] = page;
                cache_size++;
            }
        }
        else
        {
            // If found => move that page to the front (MRU)
            int temp = cache[found];
            for (int j = found; j > 0; j--)
                cache[j] = cache[j - 1];
            cache[0] = temp;
        }

        // Print frames (cache in order)
        printf("Frames: ");
        for (int j = 0; j < cache_size; j++)
            printf("%d ", cache[j]);
        printf("\n");
    }

    printf("TotalPageFaults:%d\n", faults);

    free(refs);
    free(cache);

    return 0;
}
