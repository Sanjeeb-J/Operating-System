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
  int requests[100], n, head, totalSeek = 0;
  int direction;

  printf("Enter number of requests: ");
  scanf("%d", &n);

  printf("Enter request sequence: ");
  for (int i = 0; i < n; i++)
    scanf("%d", &requests[i]);

  printf("Enter initial head position: ");
  scanf("%d", &head);

  printf("Enter direction (0 = left, 1 = right): ");
  scanf("%d", &direction);

  sort(requests, n);

  int index;
  for (index = 0; index < n; index++)
    if (head < requests[index])
      break;

  if (direction == 1)
  {
    // Move right
    for (int i = index; i < n; i++)
    {
      totalSeek += abs(head - requests[i]);
      head = requests[i];
    }

    // Then move left
    for (int i = index - 1; i >= 0; i--)
    {
      totalSeek += abs(head - requests[i]);
      head = requests[i];
    }
  }
  else
  {
    // Move left
    for (int i = index - 1; i >= 0; i--)
    {
      totalSeek += abs(head - requests[i]);
      head = requests[i];
    }

    // Then move right
    for (int i = index; i < n; i++)
    {
      totalSeek += abs(head - requests[i]);
      head = requests[i];
    }
  }

  printf("Total Seek Time (LOOK): %d\n", totalSeek);

  return 0;
}