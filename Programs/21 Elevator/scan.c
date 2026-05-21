#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
}

int main()
{
    int requests[100], n, head, diskSize, totalSeek = 0;
    int direction;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter request sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &requests[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &diskSize);

    printf("Enter direction (0 = left, 1 = right): ");
    scanf("%d", &direction);

    sort(requests, n);

    int index;
    for (index = 0; index < n; index++)
        if (head < requests[index])
            break;

    if (direction == 1)
    {
        for (int i = index; i < n; i++)
        {
            totalSeek += abs(head - requests[i]);
            head = requests[i];
        }
        totalSeek += abs(head - (diskSize - 1));
        head = diskSize - 1;

        for (int i = index - 1; i >= 0; i--)
        {
            totalSeek += abs(head - requests[i]);
            head = requests[i];
        }
    }
    else
    {
        for (int i = index - 1; i >= 0; i--)
        {
            totalSeek += abs(head - requests[i]);
            head = requests[i];
        }
        totalSeek += abs(head - 0);
        head = 0;

        for (int i = index; i < n; i++)
        {
            totalSeek += abs(head - requests[i]);
            head = requests[i];
        }
    }

    printf("Total Seek Time (SCAN): %d\n", totalSeek);
    return 0;
}
