#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main()
{
    int requests[100], visited[100] = {0};
    int n, head, totalSeek = 0;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter request sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    for (int i = 0; i < n; i++)
    {
        int minDist = INT_MAX, index = -1;

        for (int j = 0; j < n; j++)
        {
            if (!visited[j])
            {
                int dist = abs(head - requests[j]);
                if (dist < minDist)
                {
                    minDist = dist;
                    index = j;
                }
            }
        }

        printf("%d ", requests[index]);
        visited[index] = 1;
        totalSeek += minDist;
        head = requests[index];
    }

    printf("\nTotal Seek Time (SSTF): %d\n", totalSeek);
    return 0;
}
