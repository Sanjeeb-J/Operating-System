#include <stdio.h>
#include <stdbool.h>

#define MAX 100

struct Process
{
  int id, at, bt, rt, ct, tt, wt;
};

int queue[MAX], front = 0, rear = 0;

void enqueue(int pid)
{
  queue[rear++] = pid;
}

int dequeue()
{
  if (front == rear)
    return -1;
  return queue[front++];
}

bool isEmpty()
{
  return front == rear;
}

void rr(struct Process p[], int n, int tq)
{
  int time = 0, compeleted = 0;
  float ttt = 0, twt = 0;
  bool visited[n];

  for (int i = 0; i < n; i++)
  {
    visited[i] = false;
  }

  for (int i = 0; i < n; i++)
  {
    if (p[i].at == 0)
    {
      enqueue(i);
      visited[i] = true;
    }
  }

  while (complete < n)
  {
    if (isEmpty())
    {
      time++;
      for (int i = 0; i < n; i++)
      {
        if (p[i].at <= time && p[i].rt > 0 && !visited[i])
        {
          enqueue(i);
          visited[i] = true;
        }
      }
      continue;
    }

    int i = dequeue();

    if (p[i].rt > tq)
    {
      time += tq;
      p[i].rt -= tq;
    }
    else
    {
      time += p[i].rt;
      p[i].rt = 0;
      p[i].ct = time;
      completed++;
    }

    for (int j = 0; j < n; j++)
    {
      if (p[j].at <= time && p[j].rt > 0 && !visited[j])
      {
        enqueue(j);
        visited[j] = true;
      }
    }

    if (p[i].rt > 0)
      enqueue(i)
  }

  for (int i = 0; i < n; i++)
  {
    p[i].tt = p[i].ct - p[i].at;
    p[i].wt = p[i].tt - p[i].bt;
    ttt += p[i].tt;
    twt += p[i].wt
  }

  printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
  for (int i = 0; i < n; i++)
  {
    printf("%d\t%d\t%d\t%d\t%d\t%d\n",
           p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tt, p[i].wt);
  }

  printf("\nAverage Waiting Time: %.2f", total_wt / n);
  printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
}

int main()
{
  int n, time_quantum;
  printf("Enter number of processes: ");
  scanf("%d", &n);

  struct Process p[n];

  printf("Enter arrival time and burst time for each process:\n");
  for (int i = 0; i < n; i++)
  {
    p[i].id = i + 1;
    printf("Process %d (AT BT): ", p[i].id);
    scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);
    p[i].remaining_time = p[i].burst_time;
  }

  printf("Enter time quantum: ");
  scanf("%d", &time_quantum);

  roundRobin(p, n, time_quantum);

  return 0;
}