#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int x = 0;
pthread_mutex_t mutex;

void *ProcessA(void *arg) {
  while (1) {
    pthread_mutex_lock(&mutex);
    x = x + 1;
    if (x == 20)
      x = 0;
    printf("A: x=%d\n", x);
    pthread_mutex_unlock(&mutex);
  }
  pthread_exit(NULL);
}
void *ProcessB(void *arg) {
  while (1) {
    pthread_mutex_lock(&mutex);
    x = x + 1;
    if (x == 20)
      x = 0;
    printf("B: x=%d\n", x);
    pthread_mutex_unlock(&mutex);
  }
  pthread_exit(NULL);
}

int main() {
  pthread_mutex_init(&mutex, NULL);
  pthread_t th1, th2;
  pthread_create(&th1, NULL, &ProcessA, NULL);
  pthread_create(&th2, NULL, &ProcessB, NULL);
  pthread_join(th1, NULL);
  pthread_join(th2, NULL);
  exit(0);
  return 0;
}
