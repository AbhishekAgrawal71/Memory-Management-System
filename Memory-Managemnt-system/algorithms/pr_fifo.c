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

    int *s = (int *)malloc(frames * sizeof(int)); // stores pages
    int s_size = 0;

    int *q = (int *)malloc(frames * sizeof(int)); // FIFO queue
    int front = 0, rear = 0, q_size = 0;

    int **states = (int **)malloc(k * sizeof(int *)); // store frame states
    int *state_size = (int *)malloc(k * sizeof(int)); // size of each row

    int faults = 0;

    for (int i = 0; i < k; i++)
    {
        int page = refs[i];

        int found = 0;
        for (int j = 0; j < s_size; j++)
        {
            if (s[j] == page)
            {
                found = 1;
                break;
            }
        }

        if (!found)
        {
            faults++;

            if (s_size < frames)
            {
                s[s_size++] = page;

                q[rear] = page;
                rear = (rear + 1) % frames;
                q_size++;
            }
            else
            {
                int rem = q[front];
                front = (front + 1) % frames;
                q_size--;

                for (int j = 0; j < s_size; j++)
                {
                    if (s[j] == rem)
                    {
                        s[j] = page;
                        break;
                    }
                }

                q[rear] = page;
                rear = (rear + 1) % frames;
                q_size++;
            }
        }

        int *cur = (int *)malloc(q_size * sizeof(int));
        int idx = 0;

        int tmp_f = front;
        int count = q_size;
        while (count--)
        {
            cur[idx++] = q[tmp_f];
            tmp_f = (tmp_f + 1) % frames;
        }

        states[i] = cur;
        state_size[i] = q_size;
    }

    for (int i = 0; i < k; i++)
    {
        printf("Step %d Page %d Frames:", i + 1, refs[i]);
        for (int j = 0; j < state_size[i]; j++)
            printf("%d ", states[i][j]);
        printf("\n");
    }

    printf("TotalPageFaults:%d\n", faults);

    free(refs);
    free(s);
    free(q);
    free(state_size);
    for (int i = 0; i < k; i++)
        free(states[i]);
    free(states);

    return 0;
}
