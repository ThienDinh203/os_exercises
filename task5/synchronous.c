#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

sem_t empty, full;
pthread_mutex_t mutex;
int a[1000], size = 0, n;

void *ProcessA(void *arg) {
  while (1) {
    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    a[size] = rand() % 100;
    size++;
    printf("\n[PUSH] Number of elements in array a: %d", size);
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
  }
  pthread_exit(NULL);
}

void *ProcessB(void *arg) {
  while (1) {
    if (size == 0) {
      printf("\n[PCP] Nothing in array a");
      sem_wait(&empty);
    }
    pthread_mutex_lock(&mutex);
    size--;
    printf("\n[EOF] Number of elements in array a: %d", size);
    pthread_mutex_unlock(&mutex);
    sem_post(&full);
  }
  pthread_exit(NULL);
}

int main() {
  printf("\nEnter n: ");
  scanf("%d", &n);
  sem_init(&empty, 0, 0);
  sem_init(&full, 0, n);
  pthread_mutex_init(&mutex, NULL);

  pthread_t th1, th2;
  pthread_create(&th1, NULL, ProcessA, NULL);
  pthread_create(&th2, NULL, ProcessB, NULL);

  pthread_join(th1, NULL);
  pthread_join(th2, NULL);

  exit(0);
  return 0;
}
