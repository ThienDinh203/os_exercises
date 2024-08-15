#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
  pid_t pid;  
  pid = fork();

  if(pid == 0) {
    printf("%s\n");
  }
  return 0;
}
