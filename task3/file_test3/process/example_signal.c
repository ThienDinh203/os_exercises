#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int loop_forever = 1;

void on_signint() {
  printf("\nCRT+C is pressed!\n");
  loop_forever = 0;
}

int main() {
  // loop_forever = 1;
  signal(SIGINT, on_signint);
  while(loop_forever) {
    printf("Value of loop_forever = %d\n", loop_forever);
    sleep(1);
  }
  printf("Value of loop_forever = %d\n", loop_forever);
  return 0;
}
