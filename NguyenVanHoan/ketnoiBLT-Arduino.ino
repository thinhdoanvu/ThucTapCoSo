#include <SoftwareSerial.h>
SoftwareSerial BLT(2, 3);
char state;
void setup() {
  // put your setup code here, to run once:
  // Cài đặt các chân bạn muốn điều khiển thành thành Ouput
  // Ở đây tôi sử dụng 9 chân 9, 13
  pinMode(9, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600); // Kết nối bluetooth module ở tốc độ 9600
  BLT.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (BLT.available()) {
    // Đọc giá trị nhận được từ bluetooth
    state = BLT.read();
    Serial.println(state);
  }
  // Thực hiện điều khiển các chân  , 12,13
  // Ở đây tôi đã quy ước sẵn các giá trị gửi và nhận dữ liệu giữa điện thoại và Arduino
  switch (state) {
    case '1':
      digitalWrite(13, HIGH);
      break;
    case '0':
      digitalWrite(13, LOW);
      break;
    case '2':
      digitalWrite(12, HIGH);
      break;
    case '3':
      digitalWrite(12, LOW);
      break;
    default:
      break;
  }


}
