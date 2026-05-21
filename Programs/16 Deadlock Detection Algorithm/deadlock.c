#include <stdio.h>

#define MAX 10

int main()
{
    int n, m;
    int alloc[MAX][MAX], request[MAX][MAX];
    int avail[MAX], finish[MAX];
    int i, j;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Request Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &request[i][j]);

    printf("Enter Available Resources:\n");
    for (j = 0; j < m; j++)
        scanf("%d", &avail[j]);

    for (i = 0; i < n; i++)
        finish[i] = 0;

    int changed = 1;
    while (changed)
    {
        changed = 0;
        for (i = 0; i < n; i++)
        {
            if (finish[i] == 0)
            {
                int flag = 1;
                for (j = 0; j < m; j++)
                {
                    if (request[i][j] > avail[j])
                    {
                        flag = 0;
                        break;
                    }
                }
                if (flag)
                {
                    for (j = 0; j < m; j++)
                        avail[j] += alloc[i][j];
                    finish[i] = 1;
                    changed = 1;
                }
            }
        }
    }

    int deadlock = 0;
    for (i = 0; i < n; i++)
    {
        if (finish[i] == 0)
        {
            deadlock = 1;
            printf("Process P%d is deadlocked.\n", i);
        }
    }

    if (!deadlock)
        printf("No deadlock detected.\n");

    return 0;
}