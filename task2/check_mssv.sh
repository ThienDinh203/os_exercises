# 2. Viết chương trình cho phép nhập vào tên và mssv. Kiểm tra
# nếu mssv đó không trùng với mình thì bắt nhập lại. In ra màn
# hình kết quả.

#!/bin/sh

echo "Nhap ten cua ban: "
read name 

echo "Nhap mssv: "
read mssv

while [ "$mssv" != "21522617" ]
do 
  echo "Your wrong!!! Try again"
  read mssv
done 

echo "$name - $mssv"
exit 0
