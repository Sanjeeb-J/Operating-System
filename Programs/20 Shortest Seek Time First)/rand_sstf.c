#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

int main(int argc, char *argv[])
{

    if (argc != 4)
    {
        printf("Usage: %s<number of requests> <head position> <disk size>\n", argv[0]);
        return 1;
    }

    int requests[100], visited[100] = {0};
    int n = atoi(argv[1]);
    int head = atoi(argv[2]);
    int diskSize = atoi(argv[3]);
    int totalSeek = 0;

    srand(time(NULL));
    printf("Requests:\n");
    for (int i = 0; i < n; i++)
    {
        requests[i] = rand() % diskSize;
        printf("%d ", requests[i]);
    }

    printf("\nOrder");
    for (int i = 0; i < n; i++)
    {
        int minDist = 999999, index = -1;

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
