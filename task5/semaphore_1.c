#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem1, sem2;
int sells = 0, products = 0;
void* ProcessA(void *arg) {
  while(1) {
    sem_wait(&sem1);
    sells++;
    sem_post(&sem2);
    printf("[PA] Sells = %d\n", sells);
  }
  pthread_exit(NULL);
}

void* ProcessB(void *arg) {
  while(1) {
    sem_wait(&sem2);
    products++;
    sem_post(&sem1);
    printf("[PB] Products %d\n", products);
  }
  pthread_exit(NULL);
}

int main() {
  sem_init(&sem1, 0, 0);
  sem_init(&sem2, 0, 2617);
  pthread_t th1, th2;
  pthread_create(&th1, NULL, &ProcessA, NULL);
  pthread_create(&th2, NULL, &ProcessB, NULL);
  pthread_join(th1, NULL);
  pthread_join(th2, NULL);
  return 0;
}
