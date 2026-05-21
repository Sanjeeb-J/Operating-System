#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        // fork failed
        printf("Fork failed\n");
    }
    else if (pid == 0)
    {
        // Child process
        printf("Child process\n");
        printf("Child PID = %d\n", getpid());
        printf("Parent PID = %d\n", getppid());
        sleep(50);
    }
    else
    {
        // Parent process
        printf("Parent process\n");
        printf("Parent PID = %d\n", getpid());
        printf("Child PID = %d\n", pid);
        sleep(50);
    }

    return 0;
}