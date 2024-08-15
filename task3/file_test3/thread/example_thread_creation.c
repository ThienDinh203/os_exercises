#include <stdio.h>
#include <pthread.h>

void *thread_print(void* message) {
  while(1) {
    printf("Hello, How are you\n");
  }
}

int main() {
  pthread_t idthread;
  pthread_create(
      &idthread,
      NULL,
      &thread_print,
      NULL
      );
  while (1) {
    printf("I'm fine, f*k you?\n");
  }
  return 0;
}
