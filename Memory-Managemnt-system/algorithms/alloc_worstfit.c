#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n;
    if (scanf("%d", &n) != 1)
        return 0;

    int *blocks = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &blocks[i]);

    int m;
    scanf("%d", &m);

    int *proc = (int *)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++)
        scanf("%d", &proc[i]);

    int *allocation = (int *)malloc(m * sizeof(int));
    int *block_rem = (int *)malloc(n * sizeof(int));

    for (int i = 0; i < m; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++)
        block_rem[i] = blocks[i];

    for (int i = 0; i < m; i++)
    {
        int worstIdx = -1;
        for (int j = 0; j < n; j++)
        {
            if (block_rem[j] >= proc[i])
            {
                if (worstIdx == -1 || block_rem[j] > block_rem[worstIdx])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1)
        {
            allocation[i] = worstIdx;
            block_rem[worstIdx] -= proc[i];
        }
    }

    long long used = 0;

    printf("Algorithm: Worst Fit\n");
    printf("ProcessNo ProcessSize AllocatedBlock\n");

    for (int i = 0; i < m; i++)
    {
        printf("%d %d ", i + 1, proc[i]);
        if (allocation[i] != -1)
        {
            printf("%d\n", allocation[i] + 1);
            used += proc[i];
        }
        else
        {
            printf("NotAllocated\n");
        }
    }

    long long total = 0;
    for (int i = 0; i < n; i++)
        total += blocks[i];

    printf("TotalMemory:%lld\nUsedMemory:%lld\nFreeMemory:%lld\n",
           total, used, total - used);

    free(blocks);
    free(proc);
    free(allocation);
    free(block_rem);

    return 0;
}
