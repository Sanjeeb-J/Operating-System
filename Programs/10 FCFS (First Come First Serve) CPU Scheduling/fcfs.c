#include <stdio.h>

struct Process
{
    int id, arrival_time, burst_time, completion_time, turnaround_time, waiting_time;
};

void sortByArrival(struct Process p[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].arrival_time > p[j + 1].arrival_time)
            {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

void fcfsScheduling(struct Process p[], int n)
{
    int current_time = 0;
    for (int i = 0; i < n; i++)
    {
        if (current_time < p[i].arrival_time)
        {
            current_time = p[i].arrival_time;
        }
        p[i].completion_time = current_time + p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        current_time = p[i].completion_time;
    }
}

void displayProcesses(struct Process p[], int n)
{
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    int ttt = 0, twt = 0;

    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].arrival_time, p[i].burst_time,
               p[i].completion_time, p[i].turnaround_time, p[i].waiting_time);

        ttt += p[i].turnaround_time;
        twt += p[i].waiting_time;
    }
    printf("Average turn around time: %d\nAverage waiting time: %d", ttt / n, twt / n);
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

    sortByArrival(p, n);
    fcfsScheduling(p, n);
    displayProcesses(p, n);

    return 0;
}
