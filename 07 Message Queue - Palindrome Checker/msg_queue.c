#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

/* Maximum string length */
#define MAX 100

/* Message structure */
struct message
{
    long type;
    char text[MAX];
};

/* Wrapper function for sending message */
void send(int msgid, struct message *msg)
{
    msgsnd(msgid, msg, sizeof(msg->text), 0);
}

/* Wrapper function for receiving message */
void receive(int msgid, struct message *msg, long type)
{
    msgrcv(msgid, msg, sizeof(msg->text), type, 0);
}

int main()
{
    key_t key;
    int msgid;
    struct message msg;
    char original[MAX], reversed[MAX];
    int i, len;

    /* Create key and message queue */
    key = ftok("prog", 60);
    msgid = msgget(key, 0666 | IPC_CREAT);

    if (fork() == 0)
    {
        /* -------- CHILD PROCESS -------- */

        /* Receive original string */
        receive(msgid, &msg, 1);
        strcpy(original, msg.text);

        /* Reverse the string */
        len = strlen(original);
        for (i = 0; i < len; i++)
            reversed[i] = original[len - i - 1];
        reversed[len] = '\0';

        /* Send reversed string back */
        msg.type = 2;
        strcpy(msg.text, reversed);
        send(msgid, &msg);
    }
    else
    {
        /* -------- PARENT PROCESS -------- */

        printf("Enter a string: ");
        scanf("%s", original);

        /* Send original string to child */
        msg.type = 1;
        strcpy(msg.text, original);
        send(msgid, &msg);

        /* Receive reversed string */
        receive(msgid, &msg, 2);
        strcpy(reversed, msg.text);

        /* Check palindrome */
        if (strcmp(original, reversed) == 0)
            printf("The string is a PALINDROME\n");
        else
            printf("The string is NOT a PALINDROME\n");

        /* Remove message queue */
        msgctl(msgid, IPC_RMID, NULL);
    }

    return 0;
}