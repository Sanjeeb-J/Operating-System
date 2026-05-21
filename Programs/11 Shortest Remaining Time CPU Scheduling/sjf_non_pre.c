#include <stdio.h>
#include <limits.h>

struct Process
{
  int id, arrival_time, burst_time;
  int completion_time, turnaround_time, waiting_time;
};

int findNextProcess(struct Process p[], int n, int current_time, int completed[])
{
  int min_time = INT_MAX, index = -1;

  for (int i = 0; i < n; i++)
  {
    if (p[i].arrival_time <= current_time && completed[i] == 0)
    {
      if (p[i].burst_time < min_time)
      {
        min_time = p[i].burst_time;
        index = i;
      }
      else if (p[i].burst_time == min_time && p[i].arrival_time < p[index].arrival_time)
      {
        index = i;
      }
    }
  }
  return index;
}

void sjfNonPreemptive(struct Process p[], int n)
{
  int current_time = 0, completed_count = 0, completed[n];

  for (int i = 0; i < n; i++)
    completed[i] = 0;

  while (completed_count < n)
  {
    int index = findNextProcess(p, n, current_time, completed);

    if (index == -1)
    {
      current_time++;
      continue;
    }

    current_time += p[index].burst_time;

    p[index].completion_time = current_time;
    p[index].turnaround_time = p[index].completion_time - p[index].arrival_time;
    p[index].waiting_time = p[index].turnaround_time - p[index].burst_time;

    completed[index] = 1;
    completed_count++;
  }
}

void displayProcesses(struct Process p[], int n)
{
  int ttt = 0, twt = 0;

  printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
  for (int i = 0; i < n; i++)
  {
    printf("%d\t%d\t%d\t%d\t%d\t%d\n",
           p[i].id, p[i].arrival_time, p[i].burst_time,
           p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);

    ttt += p[i].turnaround_time;
    twt += p[i].waiting_time;
  }

  printf("Average turn around time: %d\n", ttt / n);
  printf("Average waiting time: %d\n", twt / n);
}

int main()
{
  int n;
  printf("Enter number of processes: ");
  scanf("%d", &n);

  struct Process p[n];

  printf("Enter arrival time and burst time for each process:\n");
  for (int i = 0; i < n; i++)
  {
    p[i].id = i + 1;
    printf("Process %d (AT BT): ", p[i].id);
    scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
  }

  sjfNonPreemptive(p, n);
  displayProcesses(p, n);

  return 0;
}
