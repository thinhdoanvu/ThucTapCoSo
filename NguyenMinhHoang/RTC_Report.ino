// Date and time functions using a DS157 RTC connected via I2C and Wire lib
//A5 <--> SCL DS157
//A4 <--> SDA DS157
//RS = 7 Arduino
//E = 6 Arduino
//RW = 0 for Write Data
//D4 = 5 Arduino
//D5 = 4 Arduino
//D6 = 3 Arduino
//D7 = 2 Arduino
//khai báo chân Input của IC 74LS47
#define A 4
#define B 5
#define C 6
#define D 7
//Khai báo chân Input của IC 74LS154
#define A0 8
#define A1  9
#define A2  10
#define A3 11
// khai báo thư viện
#include <Wire.h>
#include "RTClib.h"
//Khai báo thời gian thực.
RTC_DS1307 rtc;
void setup ()
{
  //tốc độ truyền thông nối tiêp 9600 baud
  Serial.begin(9600);
  //Thiết lập các chân 0-13 là các đầu ra
  for (int i = 0; i <= 13; i++)
  {
    pinMode(i, OUTPUT);
  }
  //Khởi tạo RTC
  if (! rtc.begin())
  {
    Serial.print("Couldn't find RTC");
    while (1);
  }
  if (! rtc.isrunning())
  {
    Serial.print("RTC is NOT running!");
  }
  //cập nhật thời gian đầu tiên cho DS1307 từ PC
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));//auto update from computer time
}
// case số chuyển từ IC 74LS47 sang LED 7 đoạn
void sodonvigiay(int x)
{
  switch (x)
  {
    case 0: // hiển thị số 0 trên LED 7 đoạn
      digitalWrite(A, 0);
      digitalWrite(B, 0);
      digitalWrite(C, 0);
      digitalWrite(D, 0);
      break;
    case 1: // hiển thị số 1 trên LED 7 đoạn
      digitalWrite(A, 1);
      digitalWrite(B, 0);
      digitalWrite(C, 0);
      digitalWrite(D, 0);
      break;
    case 2: // hiển thị số 2 trên LED 7 đoạn
      digitalWrite(A, 0);
      digitalWrite(B, 1);
      digitalWrite(C, 0);
      digitalWrite(D, 0);
      break;
    case 3: // hiển thị số 3 trên LED 7 đoạn
      digitalWrite(A, 1);
      digitalWrite(B, 1);
      digitalWrite(C, 0);
      digitalWrite(D, 0);
      break;
    case 4: // hiển thị số 4 trên LED 7 đoạn
      digitalWrite(A, 0);
      digitalWrite(B, 0);
      digitalWrite(C, 1);
      digitalWrite(D, 0);
      break;
    case 5: // hiển thị số 5 trên LED 7 đoạn
      digitalWrite(A, 1);
      digitalWrite(B, 0);
      digitalWrite(C, 1);
      digitalWrite(D, 0);
      break;
    case 6: // hiển thị số 6 trên LED 7 đoạn
      digitalWrite(A, 0);
      digitalWrite(B, 1);
      digitalWrite(C, 1);
      digitalWrite(D, 0);
      break;
    case 7: // hiển thị số 7 trên LED 7 đoạn
      digitalWrite(A, 1);
      digitalWrite(B, 1);
      digitalWrite(C, 1);
      digitalWrite(D, 0);
      break;
    case 8: // hiển thị số 8 trên LED 7 đoạn
      digitalWrite(A, 0);
      digitalWrite(B, 0);
      digitalWrite(C, 0);
      digitalWrite(D, 1);
      break;
    case 9: // hiển thị số 9 trên LED 7 đoạn
      digitalWrite(A, 1);
      digitalWrite(B, 0);
      digitalWrite(C, 0);
      digitalWrite(D, 1);
      break;
    default: // hiển thị số mặc định trên LED 7 đoạn
      digitalWrite(A, 1);
      digitalWrite(B, 0);
      digitalWrite(C, 0);
      digitalWrite(D, 1);
      break;
  }
}
void loop ()
{
  //thiết lập thời gian hiện tại
  DateTime now = rtc.now();
  int nam = now.year(); //thiết lập thời gian năm 
  int namdonvi = nam%10; //thiết lập thời gian năm hàng đơn vị
  int namchucvd = nam/10 ; //thiết lập thời gian năm 
  int namchuc = namchucvd%10; //thiết lập thời gian năm hàng chục
  int thang = now.month(); //thiết lập thời gian tháng
  int thangdonvi = thang%10; //thiết lập thời gian tháng hàng đơn vị
  int thangchuc = thang/10; //thiết lập thời gian tháng hàng chục
  int ngay = now.day();//thiết lập thời gian ngày
  int ngaydonvi = ngay%10; //thiết lập thời gian ngày hàng đơn vị
  int ngaychuc = ngay/10; //thiết lập thời gian ngày hàng chục
  int gio = now.hour();  //thiết lập thời gian giời 
  int giodonvi = gio % 10; //thiết lập thời gian giời hàng đơn vị
  int giochuc = gio / 10; //thiết lập thời gian giờ hàng chục
  int phut = now.minute(); //thiết lập thời gian phút
  int phutdonvi = phut % 10; //thiết lập thời gian phút hàng đơn vị
  int phutchuc = phut / 10; //thiết lập thời gian phút hàng chục
  int giay = now.second(); //thiết lập thời gian giây
  int giaydonvi = giay % 10; //thiết lập thời gian giây hàng đơn vị 
  int giaychuc = giay / 10; //thiết lập thời gian giây hàng chục  
  // đọc các giá trị và gửi lên phần mềm
  Serial.print(phutchuc);
  Serial.print(phutdonvi);
  Serial.print(giaychuc);
  Serial.print(giaydonvi);
  //hiển thị số giây hàng đơn vị
  sodonvigiay(giaydonvi);
  digitalWrite(A0, 1);
  digitalWrite(A1, 1);
  digitalWrite(A2, 0);
  digitalWrite(A3, 1);
  delay(1);
  //hiển thị số giây hàng chục
  sodonvigiay(giaychuc);
  digitalWrite(A0, 0);
  digitalWrite(A1, 1);
  digitalWrite(A2, 0);
  digitalWrite(A3, 1);
  delay(1);
  //hiển thị số phút hàng đơn vị
  sodonvigiay(phutdonvi);
  digitalWrite(A0, 1);
  digitalWrite(A1, 0);
  digitalWrite(A2, 1);
  digitalWrite(A3, 0);
  delay(1);
  //hiển thị số phút hàng chục
  sodonvigiay(phutchuc); 
  digitalWrite(A0, 1);
  digitalWrite(A1, 1);
  digitalWrite(A2, 0);
  digitalWrite(A3, 0);
  delay(1);
  //hiển thị số giờ hàng đơn vị
  sodonvigiay(giodonvi);
  digitalWrite(A0, 1);
  digitalWrite(A1, 0);
  digitalWrite(A2, 0);
  digitalWrite(A3, 0);
  delay(1);
  //hiển thị số giờ hàng chục
  sodonvigiay(giochuc);
  digitalWrite(A0, 0);
  digitalWrite(A1, 1);
  digitalWrite(A2, 1);
  digitalWrite(A3, 0);
  delay(1);
  //hiển thị số ngày hàng đơn vị
  sodonvigiay(ngaydonvi); 
  digitalWrite(A0, 0);
  digitalWrite(A1, 0);
  digitalWrite(A2, 0);
  digitalWrite(A3, 1);
  delay(1);
  //hiển thị số hàng hàng chục
  sodonvigiay(ngaychuc); 
  digitalWrite(A0, 0);
  digitalWrite(A1, 0);
  digitalWrite(A2, 0);
  digitalWrite(A3, 0);
  delay(1);
  //hiển thị số tháng hàng đơn vị
  sodonvigiay(thangchuc);
  digitalWrite(A0, 0);
  digitalWrite(A1, 1);
  digitalWrite(A2, 0);
  digitalWrite(A3, 0);
  delay(1);
  //hiển thị số tháng hàng chục
  sodonvigiay(thangdonvi);   
  digitalWrite(A0, 1);
  digitalWrite(A1, 1);
  digitalWrite(A2, 1);
  digitalWrite(A3, 0);
  delay(1);
  //hiển thị số năm hàng đơn vị
  sodonvigiay(namdonvi);
  digitalWrite(A0, 0);
  digitalWrite(A1, 0);
  digitalWrite(A2, 1);
  digitalWrite(A3, 0);
  delay(1);
  //hiển thị số năm hàng chục
  sodonvigiay(namchuc);  
  digitalWrite(A0, 1);
  digitalWrite(A1, 0);
  digitalWrite(A2, 0);
  digitalWrite(A3, 1);
  delay(1);
}
