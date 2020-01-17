/* Khai báo các thư viện */
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
/* Thiết lập địa chỉ mặc định của màn hình là 0x27 */
#define I2C_ADDR    0x27
/* Thiết lập các chân của màn hình */
#define Rs_pin  0
#define Rw_pin  1
#define En_pin  2
#define BACKLIGHT_PIN  3
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7
#define LED_OFF 1
#define LED_ON  0
LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
/* tạo các biến char cho các thành phần ngày, tháng, thứ, giờ, phút, giây */
char ngay, thang, thu, gio, phut, giay;
/* tạo biến năm kiểu int vì năm 2020 kiểu int là hợp lí */ 
int nam;
/* hàm setup */
void setup()
 {
  lcd.begin(16,2); /* khởi động mà hình LCD 16 2 ở đây là 16
  và hai dòng */
  /* bật đèn nền cho màn hình LCD */
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(LED_ON);
  lcd.backlight();
  /* chỉnh vị trí con trỏ thụt vào 1 ô ở hàng thứ nhất */
  lcd.setCursor(1,0);
  /*Hiển thị lời chào chúng ta có thể hiện thị gì ở đây
   cũng đc
   */
  lcd.print("DONG HO DS1307");
  delay(1500); /* delay 1,5s để chúng ta có thể nhìn rõ lời chào */
  lcd.clear();
  /* bắt đầu cài giờ vào ds1307 theo thời gian thực tế theo hàm setTime
   ở trên ta nhập theo thứ tự giờ, phút, giây, thứ, ngày, tháng, năm
   */
  setTime(15,50,30,4,15,01,20);           
 }
/* ở đây ta tạo một mảng bất kì để in ra màn hình */
char buff [20];
void loop()
{
  /* khởi động đèn nền cho LCD */
 lcd.backlight();
 /* sử dụng hàm getTime để lấy thời gian từ DS1307 */ 
 getTime();
/* In ra hàng đầu tiên của LCD là hàng Giờ */
 sprintf(buff,"GIO:  %02d:%02d:%02d",gio,phut,giay);
 lcd.setCursor(0,0);
 lcd.print(buff);
 /* Dùng If else để hiển thị CN thay vì là số 1 */
 if(thu==1){
 sprintf(buff,"CN %02d/%02d/%02d",ngay,thang,nam);
 lcd.setCursor(1,1);
 lcd.print(buff);
 }
 else
 {
 sprintf(buff,"THU%2d %02d/%02d/%02d",thu,ngay,thang,nam);
 lcd.setCursor(0,1);
 lcd.print(buff);
  }
}
/* kết thúc chương trình */
