#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"
RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27,16,2);
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
void setup () {
 Serial.begin(9600); // Khởi động một cổng Serial với một baudrate cho trước là 9600, hay còn gọi là tốc độ truyền thông là 9600
  lcd.init();   
  lcd.backlight();
  if (! rtc.begin()) {
    lcd.print("Couldn't find RTC");
    while (1);
  }
  if (! rtc.isrunning()) {
    lcd.print("RTC is NOT running!");
  }  
    rtc.adjust(DateTime(F(_DATE_), F(_TIME_)));// tu dong cap nhat thoi gian tren may tinh
}
void loop () {
    DateTime now = rtc.now(); //Khoi tao bien gia tri thoi   
    lcd.setCursor(4, 1);
     if(now.hour()<=9) // neu gtri thoi gian nho hon 9
    {
      lcd.print("0"); //them gia tri "0" truoc do
      lcd.print(now.hour()); //sau do xuat ra man hinh LCD
    }
    else {  //gia tri thoi gian >9
     lcd.print(now.hour()); //hien thi gia tri do len man hinh
    }
    lcd.print(':'); // them ":" de hien thi gia tri tiep theo
    if(now.minute()<=9){
      lcd.print("0");
      lcd.print(now.minute());
  }
    else {
     lcd.print(now.minute()); 
    }
    lcd.print(':');
    if(now.second()<=9) {
      lcd.print("0");
      lcd.print(now.second());
    }
    else {
     lcd.print(now.second()); 
    }
    lcd.print("   ");
    lcd.setCursor(1, 0);
    lcd.print(daysOfTheWeek[now.dayOfTheWeek()]);
    lcd.print(",");
    if(now.day()<=9){
      lcd.print("0");
      lcd.print(now.day());
    }
    else {
     lcd.print(now.day()); 
    }
    lcd.print('/');
    if(now.month()<=9){
      lcd.print("0");
      lcd.print(now.month());
    }
    else {
     lcd.print(now.month()); 
    }
    lcd.print('/');
    if(now.year()<=9)
    {
      lcd.print("0");
      lcd.print(now.year());
    }
    else {
     lcd.print(now.year()); 
    }
}
