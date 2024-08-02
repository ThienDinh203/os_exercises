# 3. Viết chương trình cho phép nhập vào một số n. Kiểm tra nếu n < 10 thì bắt nhập lại. Tính tổng các số từ 1 đến n. In kết quả ra màn hình.

#!/bin/sh

echo "Nhap 1 so bat ky:"
read n

sum=0
i=1

while [ "$n" -lt 10 ]; do
  echo "Nhap lai so lon hon 10" 
  read n
done

while [ "$i" -le "$n" ]
do 
  sum=$((sum + i))
  i=$((i + 1))
done

echo "Tong tu 1 den n = $sum"
exit 0
