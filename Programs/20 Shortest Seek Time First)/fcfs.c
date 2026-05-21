#include <stdio.h>
#include <stdlib.h>

int main()
{
  int requests[100];
  int n, head, totalSeek = 0;

  printf("Enter number of requests: ");
  scanf("%d", &n);

  printf("Enter request sequence: ");
  for (int i = 0; i < n; i++)
    scanf("%d", &requests[i]);

  printf("Enter initial head position: ");
  scanf("%d", &head);

  printf("Seek Sequence: ");

  for (int i = 0; i < n; i++)
  {
    printf("%d ", requests[i]);

    totalSeek += abs(head - requests[i]);
    head = requests[i];
  }

  printf("\nTotal Seek Time (FCFS): %d\n", totalSeek);

  return 0;
}