#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{
    pid_t pid;
    if (argc != 3)
    {
        printf("Usage: %s <num1> <num2>\n", argv[0]);
        return 1;
    }
    pid = fork();
    if (pid < 0)
    {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0)
    {
        // Child process
        char *args[] = {"./add", argv[1], argv[2], NULL};

        printf("Child: Executing myadder using execvp()\n");
        execvp(args[0], args);

        perror("execvp failed"); // executes only if execvp fails
    }
    else
    {
        // Parent process

        printf("Parent: Child process completed\n");
    }

    return 0;
}