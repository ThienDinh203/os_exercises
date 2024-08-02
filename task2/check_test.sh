# 4. Viết trình cho phép nhập vào một chuỗi. Kiểm tra chuỗi đó có tồn tại trong một file text (ví dụ test.txt) cùng thư mục hay không.

#!/bin/sh

file="./test.txt"

echo "Viet gi do nao:"
read text

if grep "$text" "$file"; then
  echo "Chuoi $text co trong $file"
fi
  
exit 0
