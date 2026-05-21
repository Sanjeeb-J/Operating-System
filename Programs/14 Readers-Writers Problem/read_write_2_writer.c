#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define READERS 3
#define WRITERS 2
#define OPERATIONS 5

sem_t rmutex, wmutex, readtry, resource;
int readcount = 0, writecount = 0, dataValue = 0;

void *reader(void *arg)
{
  int id = *(int *)arg;

  for (int i = 0; i < OPERATIONS; i++)
  {
    sem_wait(&readtry);
    sem_wait(&rmutex);
    readcount++;
    if (readcount == 1)
      sem_wait(&resource);
    sem_post(&rmutex);
    sem_post(&readtry);

    printf("Reader %d reads value : %d\n", id, dataValue);
    sleep(1);

    sem_wait(&rmutex);
    readcount--;
    if (readcount == 0)
      sem_post(&resource);
    sem_post(&rmutex);

    sleep(1);
  }

  pthread_exit(NULL);
}

void *writer(void *arg)
{
  int id = *(int *)arg;

  for (int i = 0; i < OPERATIONS; i++)
  {
    sem_wait(&wmutex);
    writecount++;
    if (writecount == 1)
      sem_wait(&readtry);
    sem_post(&wmutex);

    sem_wait(&resource);

    dataValue++;
    printf("Writer %d writes value : %d\n", id, dataValue);
    sleep(2);

    sem_post(&resource);

    sem_wait(&wmutex);
    writecount--;
    if (writecount == 0)
      sem_post(&readtry);
    sem_post(&wmutex);
    sleep(1);
  }

  pthread_exit(NULL);
}

int main()
{
  pthread_t r[READERS], w[WRITERS];
  int rid[READERS], wid[WRITERS];

  sem_init(&rmutex, 0, 1);
  sem_init(&wmutex, 0, 1);
  sem_init(&readtry, 0, 1);
  sem_init(&resource, 0, 1);

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

  sem_destroy(&rmutex);
  sem_destroy(&wmutex);
  sem_destroy(&readtry);
  sem_destroy(&resource);

  return 0;
}
