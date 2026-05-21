#include <stdio.h>

#define MAX 10

int main()
{
  int n, m; // n = processes, m = resources
  int alloc[MAX][MAX], max[MAX][MAX], need[MAX][MAX];
  int avail[MAX], finish[MAX], safeSeq[MAX];
  int i, j, count = 0;

  printf("Enter number of processes: ");
  scanf("%d", &n);

  printf("Enter number of resource types: ");
  scanf("%d", &m);

  printf("Enter Allocation Matrix:\n");
  for (i = 0; i < n; i++)
    for (j = 0; j < m; j++)
      scanf("%d", &alloc[i][j]);

  printf("Enter Maximum Matrix:\n");
  for (i = 0; i < n; i++)
    for (j = 0; j < m; j++)
      scanf("%d", &max[i][j]);

  printf("Enter Available Resources:\n");
  for (j = 0; j < m; j++)
    scanf("%d", &avail[j]);

  // Calculate Need matrix
  for (i = 0; i < n; i++)
    for (j = 0; j < m; j++)
      need[i][j] = max[i][j] - alloc[i][j];

  for (i = 0; i < n; i++)
    finish[i] = 0;

  while (count < n)
  {
    int found = 0;
    for (i = 0; i < n; i++)
    {
      if (finish[i] == 0)
      {
        int flag = 1;
        for (j = 0; j < m; j++)
        {
          if (need[i][j] > avail[j])
          {
            flag = 0;
            break;
          }
        }
        if (flag)
        {
          safeSeq[count++] = i;
          for (j = 0; j < m; j++)
            avail[j] += alloc[i][j];
          finish[i] = 1;
          found = 1;
        }
      }
    }
    if (found == 0)
    {
      printf("System is NOT in safe state.\n");
      return 0;
    }
  }

  printf("System is in SAFE state.\nSafe sequence: ");
  for (i = 0; i < n; i++)
    printf("P%d ", safeSeq[i]);

  return 0;
}
