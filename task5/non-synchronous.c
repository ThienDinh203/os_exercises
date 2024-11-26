#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

int a[1000], size = 0;

void *ProcessA(void *arg) {
    while (1) {
        a[size] = rand() % 100;
        size++;
        printf("\n[PUSH] Number of elements in array a: %d", size);
    }
    pthread_exit(NULL);
}

void *ProcessB(void *arg) {
    while (1) {
        if (size > 0) {
            size--;
            printf("\n[POP] Number of elements in array a: %d", size);
        } else {
            printf("\n[POP] Nothing in array a");
        }
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t th1, th2;
    pthread_create(&th1, NULL, ProcessA, NULL);
    pthread_create(&th2, NULL, ProcessB, NULL);
    pthread_join(th1, NULL);
    pthread_join(th2, NULL);
    exit(0);
    return 0;
}

