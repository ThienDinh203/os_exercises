// Viết chương trình mô phỏng bài toán Producer - Consumer
// như sau:
// Sử dụng kỹ thuật shared-memory để tạo một boundedbuffer có độ lớn là 10 bytes.
// Tiến trình cha đóng vai trò là Producer, tạo một số ngẫu nhiên trong khoảng [10, 20] và ghi dữ liệu vào buffer
// Tiến trình con đóng vai trò là Consumer đọc dữ liệu từ buffer, in ra màn hình và tính tổng
// Khi tổng lớn hơn 100 thì cả 2 dừng lại

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const unsigned char BUFFER_SIZE = 10;
const unsigned char COUNT_SIZE = 1;
const char *BUFFER_NAME = "BUFFFER";
const char *COUNT_NAME = "COUNT";

int fd;
unsigned char *buffer_ptr = NULL;
unsigned char *count_ptr = NULL;

int main(int argc, char *argv[])
{
  pid_t pid = fork();

  
  return 0;
}
