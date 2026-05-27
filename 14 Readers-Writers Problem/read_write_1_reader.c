#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define READERS 5
#define WRITERS 2
#define OPERATIONS 5

sem_t wrt, mutex;
int readcount = 0;
int dataValue = 0;

void *reader(void *arg)
{
  int id = *(int *)arg;

  for (int i = 0; i < OPERATIONS; i++)
  {
    sem_wait(&mutex);
    readcount++;
    if (readcount == 1)
      sem_wait(&wrt);
    sem_post(&mutex);

    printf("Reader %d reads value : %d\n", id, dataValue);
    sleep(1);

    sem_wait(&mutex);
    readcount--;
    if (readcount == 0)
      sem_post(&wrt);
    sem_post(&mutex);

    sleep(1);
  }

  pthread_exit(NULL);
}

void *writer(void *arg)
{
  int id = *(int *)arg;

  for (int i = 0; i < OPERATIONS; i++)
  {
    sem_wait(&wrt);

    dataValue++;
    printf("Writer %d writes value : %d\n", id, dataValue);
    sleep(2);

    sem_post(&wrt);

    sleep(1);
  }

  pthread_exit(NULL);
}

int main()
{
  pthread_t r[READERS], w[WRITERS];
  int rid[READERS], wid[WRITERS];

  sem_init(&mutex, 0, 1);
  sem_init(&wrt, 0, 1);

  for (int i = 0; i < READERS; i++)
  {
    rid[i] = i + 1;
    pthread_create(&r[i], NULL, reader, &rid[i]);
  }

  for (int i = 0; i < WRITERS; i++)
  {
    wid[i] = i + 1;
    pthread_create(&w[i], NULL, writer, &wid[i]);
  }

  for (int i = 0; i < READERS; i++)
    pthread_join(r[i], NULL);

  for (int i = 0; i < WRITERS; i++)
    pthread_join(w[i], NULL);

  sem_destroy(&mutex);
  sem_destroy(&wrt);

  return 0;
}
