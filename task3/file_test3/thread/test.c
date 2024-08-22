#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

#define NUM_THREADS 2

void *thread_print(void* threadid) {
  pid_t tid = gettid();
  long ttid;
  ttid = (long)threadid;
  printf("Hello bro: I'm thread #%ld! My thread's ID: %ld\n", ttid, tid);
  sleep(100);
}

int main() {
  pthread_t threads[NUM_THREADS];
  int check;
  long tID;

  for(tID = 0; tID < NUM_THREADS; tID++) {
    printf("I'm main thread: create thread: #%ld\n", tID);
    check = pthread_create(
        &threads[tID],
        NULL,
        thread_print,
        (void*)tID
        );
    if(check != 0) {
      printf("ERROR!! I'm main thread, can't create thread #%ld\n", tID);
      exit(-1);
    }
  }
  sleep(100);
  /* Last thing main should do*/
  pthread_exit(NULL);
  return 0;
}
