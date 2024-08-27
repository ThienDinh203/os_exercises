// #Viết một chương trình làm bốn công việc sau theo thứ tự:
//   In ra dòng chữ: “Welcome to IT007, I am <your_Student_ID>!”
//   Thực thi file script count.sh với số lần đếm là 120
//   Trước khi count.sh đếm đến 120, bấm CTRL+C để dừng tiến trình này
//   Khi người dùng nhấn CTRL+C thì in ra dòng chữ: “count.sh has stoppped”

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>


void on_signint(signal_num) {
  printf("\ncount.sh has stopped\n");
  exit(signal_num);
}
int main(int argc, char *argv[]) {
  char *studen_id = "21522617";
  // scanf(studen_id);
  printf("Welcome to IT007, I am %s\n", studen_id);

  pid_t pid;
  pid = fork();

  if(pid == 0) {
    execlp("./count.sh", "./count.sh", "120", NULL);
  }
  else {
    // wait(NULL);
    signal(SIGINT, on_signint);
    printf("Nhan CTRL+C de dung count.sh\n");
    while(1) {
      sleep(1);
    }
  }
  return 0;
}
