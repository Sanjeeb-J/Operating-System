#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0)
    {
        // Child process
        printf("PCCSL407 ");
    }
    else
    {
        // Parent process waits for child
        wait(NULL);
        printf("Operating Systems Lab");
    }

    return 0;
}