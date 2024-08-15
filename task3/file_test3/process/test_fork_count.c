#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int count = 1;
  pid_t pid;
  pid = fork();
  if(pid == 0) {
    count = count + 2;
    printf("Child process, count = %d\n", count);
  }
  else {
    count = count + 3;
    printf("Parent process \n");
  }
  fork();
  count = count + 1;
  printf("Afterw second fork, count = %d\n", count);
  return 0;
}
