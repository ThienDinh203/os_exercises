#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  struct timeval start, end;
  pid_t pid;  
  gettimeofday(&start, NUL);
  pid = fork();

  if(pid == 0) {
    execl ("/bin/sh", "sh", "-c", argv[1], NULL);
  }
  else {
    wait(NULL);
    gettimeofday(&end, NULL);
    double time = ((end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec)) / (double)1000000;
    printf("Exection time: %.5f second\n", time);
  }
  return 0;
}
