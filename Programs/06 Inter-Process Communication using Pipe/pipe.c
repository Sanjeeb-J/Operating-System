#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <sys/types.h>

int main()
{
    int fd[2];
    int a, b, c;
    int four_ac;
    int b_square;
    double result;

    printf("Enter values of a, b and c: ");
    scanf("%d %d %d", &a, &b, &c);

    // Create pipe
    if (pipe(fd) == -1)
    {
        printf("Pipe creation failed\n");
        return 1;
    }

    // Create child process
    if (fork() == 0)
    {
        // Child process: computes 4*a*c
        close(fd[0]); // Close read end

        four_ac = 4 * a * c;
        write(fd[1], &four_ac, sizeof(four_ac));

        close(fd[1]); // Close write end
    }
    else
    {
        // Parent process: computes b^2 and final expression
        close(fd[1]); // Close write end

        b_square = b * b;
        read(fd[0], &four_ac, sizeof(four_ac));

        close(fd[0]); // Close read end

        result = sqrt(b_square - four_ac);

        printf("b^2 = %d\n", b_square);
        printf("4ac = %d\n", four_ac);
        printf("Result = sqrt(b^2 - 4ac) = %.2f\n", result);
    }

    return 0;
}
