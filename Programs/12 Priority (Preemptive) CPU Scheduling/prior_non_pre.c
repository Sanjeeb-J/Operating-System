#include <stdio.h>
#include <limits.h>
struct Process
{
    int id, arrival_time, burst_time, priority;
    int waiting_time, turnaround_time, completion_time;
};

int findNextProcess(struct Process p[], int n, int current_time, int is_completed[])
{
    int min_priority = INT_MAX, index = -1;

    for (int i = 0; i < n; i++)
    {
        if (p[i].arrival_time <= current_time && is_completed[i] == 0)
        {
            if (p[i].priority < min_priority)
            {
                min_priority = p[i].priority;
                index = i;
            }
            else if (p[i].priority == min_priority && p[i].arrival_time < p[index].arrival_time)
            {
                index = i;
            }
        }
    }
    return index;
}

void priorityNonPreemptiveScheduling(struct Process p[], int n)
{
    int current_time = 0, completed = 0, is_completed[n];

    for (int i = 0; i < n; i++)
        is_completed[i] = 0;

    printf("\nExecution Order (Gantt Chart):\n");

    while (completed < n)
    {
        int idx = findNextProcess(p, n, current_time, is_completed);

        if (idx == -1)
        {
            current_time++;
            continue;
        }

        printf("Time %d -> P%d\n", current_time, p[idx].id);

        current_time += p[idx].burst_time;

        p[idx].completion_time = current_time;
        p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
        p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;

        is_completed[idx] = 1;
        completed++;
    }
}

void displayProcesses(struct Process p[], int n)
{
    float total_wt = 0, total_tat = 0;

    printf("\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\n");

    for (int i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               p[i].id, p[i].arrival_time, p[i].burst_time, p[i].priority,
               p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);

        total_wt += p[i].waiting_time;
        total_tat += p[i].turnaround_time;
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);
}

int main()
{
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    printf("Enter Arrival Time, Burst Time, and Priority for each process:\n");
    for (int i = 0; i < n; i++)
    {
        p[i].id = i + 1;
        printf("P%d: ", p[i].id);
        scanf("%d %d %d", &p[i].arrival_time, &p[i].burst_time, &p[i].priority);
    }

    priorityNonPreemptiveScheduling(p, n);

    displayProcesses(p, n);

    return 0;
}
