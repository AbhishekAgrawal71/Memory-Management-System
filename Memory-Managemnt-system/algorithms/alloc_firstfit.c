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
        for (int j = 0; j < n; j++)
        {
            if (block_rem[j] >= proc[i])
            {
                allocation[i] = j;
                block_rem[j] -= proc[i];
                break;
            }
        }
    }

    long long used = 0;

    printf("Algorithm: First Fit\n");
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

    printf("TotalMemory:%lld\n", total);
    printf("UsedMemory:%lld\n", used);
    printf("FreeMemory:%lld\n", total - used);

    free(blocks);
    free(proc);
    free(allocation);
    free(block_rem);

    return 0;
}
