#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SIZE 1024

int main()
{
    int shmid;
    char *shm;
    pid_t pid;
    int i;
    char final[300];

    /* Create shared memory */
    shmid = shmget(IPC_PRIVATE, SIZE, 0666 | IPC_CREAT);
    if (shmid < 0)
    {
        perror("shmget");
        exit(1);
    }

    /* Attach shared memory */
    shm = (char *)shmat(shmid, NULL, 0);
    if (shm == (char *)-1)
    {
        perror("shmat");
        exit(1);
    }

    /* ===== Parent reads input FIRST ===== */
    printf("Enter first string: ");
    scanf("%99s", shm);

    printf("Enter second string: ");
    scanf("%99s", shm + 100);

    printf("Enter third string: ");
    scanf("%99s", shm + 200);

    /* Create child */
    pid = fork();

    if (pid == 0)
    {
        /* ---------- CHILD PROCESS ---------- */
        char result[300];

        strcpy(result, shm);
        strcat(result, " ");
        strcat(result, shm + 100);
        strcat(result, " ");
        strcat(result, shm + 200);

        /* Send back to parent */
        strcpy(shm + 300, result);

        shmdt(shm);
        exit(0);
    }
    else
    {
        /* ---------- PARENT PROCESS ---------- */
        wait(NULL);

        strcpy(final, shm + 300);

        /* Flip case */
        for (i = 0; final[i] != '\0'; i++)
        {
            if (islower(final[i]))
                final[i] = toupper(final[i]);
            else if (isupper(final[i]))
                final[i] = tolower(final[i]);
        }

        printf("\nFinal Output: %s\n", final);

        shmdt(shm);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}
