#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

sem_t semA, semB, semEF, semANS;
int x1 = 1, x2 = 2, x3 = 3, x4 = 4, x5 = 5, x6 = 6, w, v, y, z, x, ans;

void *ProcessA(void *arg) {
  w = x1 * x2;
  sem_post(&semA);
  sem_post(&semA);
  printf("w = %d\n", w);
  pthread_exit(NULL);
}

void *ProcessB(void *arg) {
  v = x3 * x4;
  sem_post(&semB);
  sem_post(&semB);
  printf("v = %d\n", v);
  pthread_exit(NULL);
}

void *ProcessC(void *arg) {
  sem_wait(&semB);
  y = v * x5;
  printf("y = %d\n", y);
  sem_post(&semEF);
  pthread_exit(NULL);
}

void *ProcessD(void *arg) {
  sem_wait(&semB);
  z = v * x6;
  printf("z = %d\n", z);
  sem_post(&semEF);
  pthread_exit(NULL);
}

void *ProcessE(void *arg) {
  sem_wait(&semA);
  sem_wait(&semEF);
  sem_wait(&semEF);
  x = w + y + z;
  printf("x = %d\n", x);
  sem_post(&semANS);
  pthread_exit(NULL);
}

void *ProcessF(void *arg) {
  sem_wait(&semA);
  sem_wait(&semEF);
  z = w * z;
  printf("z = %d\n", z);
  sem_post(&semANS);
  pthread_exit(NULL);
}

void *ProcessG(void *arg) {
  sem_wait(&semANS);
  sem_wait(&semANS);
  ans = y + z;
  printf("ans = %d\n", ans);
  pthread_exit(NULL);
}

int main() {
  sem_init(&semB, 0, 0);
  sem_init(&semEF, 0, 0);
  sem_init(&semA, 0, 0);
  sem_init(&semANS, 0, 0);

  pthread_t th1, th2, th3, th4, th5, th6, th7;
  pthread_create(&th1, NULL, &ProcessA, NULL);
  pthread_create(&th2, NULL, &ProcessB, NULL);
  pthread_create(&th3, NULL, &ProcessC, NULL);
  pthread_create(&th4, NULL, &ProcessD, NULL);
  pthread_create(&th5, NULL, &ProcessE, NULL);
  pthread_create(&th6, NULL, &ProcessF, NULL);
  pthread_create(&th7, NULL, &ProcessG, NULL);

  pthread_join(th7, NULL);
  exit(0);
  return 0;
}
