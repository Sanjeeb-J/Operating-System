#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int a[100], n;
float mean, median, sd;

void *find_mean(void *arg)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += a[i];
    mean = (float)sum / n;
    pthread_exit(NULL);
}

void *find_median(void *arg)
{
    int temp;

    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i] > a[j])
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }

    if (n % 2 == 0)
        median = (a[n / 2] + a[n / 2 - 1]) / 2.0;
    else
        median = a[n / 2];

    pthread_exit(NULL);
}

void *find_sd(void *arg)
{
    float sum = 0;
    for (int i = 0; i < n; i++)
        sum += (a[i] - mean) * (a[i] - mean);

    sd = sqrt(sum / n);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t t1, t2, t3;

    n = argc - 1;
    if (n <= 0)
    {
        printf("Enter numbers as command line arguments\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
        a[i] = atoi(argv[i + 1]);

    pthread_create(&t1, NULL, find_mean, NULL);
    pthread_create(&t2, NULL, find_median, NULL);

    pthread_join(t1, NULL);

    pthread_create(&t3, NULL, find_sd, NULL);

    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("Mean = %.2f\n", mean);
    printf("Median = %.2f\n", median);
    printf("Standard Deviation = %.2f\n", sd);

    return 0;
}
