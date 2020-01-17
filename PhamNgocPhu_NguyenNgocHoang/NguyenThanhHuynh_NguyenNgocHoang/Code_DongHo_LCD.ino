//Khai báo thư viện sử dụng
#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal_I2C.h>
//Khai báo thời gian thực
RTC_DS1307 rtc;
//Địa chỉ màn hình 0x27, (16x2): 16 cột, 2 hàng 
LiquidCrystal_I2C lcd(0x27,16,2);
//Khai báo các biến để lấy giá trị thời gian
int thu, ngay, thang, nam, gio, phut, giay;
void setup() 
{
	//Giá trị tốc độ truyền thông nối tiếp 9600
	Serial.begin(9600);
	//Khởi động màn hình
	lcd.init();  
	//Bật đèn nền
	lcd.backlight();
	//Khởi tạo RTC
	if (! rtc.begin()) 
	{	
		//Thông báo lên màn hình Serial Monitor
		Serial.print("Khong tim thay RTC !");
		//Thông báo lên màn hình LCD
		lcd.print("Khong tim thay RTC!");
		while (1);
	}
	if (! rtc.isrunning()) 
	{
		Serial.print("RTC khong chay!");
		lcd.print("RTC khong chay!");
	}
	//Cách 1: Cập nhật thời gian lần đầu cho DS1307 từ máy tính
	rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
	//Cách 2: Thiết lập giờ thủ công
    //rtc.adjust(DateTime(2020, 1, 15, 8, 15, 0));
}
void loop () 
{
	//Thiết lập thời gian hiện tại
    DateTime now = rtc.now();
	//Truyền giá trị cho các biến thứ, ngày, tháng, năm
	thu = now.dayOfTheWeek();
	ngay = now.day();
	thang = now.month();
	nam = now.year();
	//Truyền giá trị cho các biến thứ, ngày, tháng, năm
	gio = now.hour();
	phut = now.minute();
	giay = now.second();
	//Hàng đầu tiên hiển thị thứ, ngày, tháng, năm
    lcd.setCursor(0, 0);
	//Hiển thị thứ trong tuần
    switch(thu)
	{
		case 0:
			lcd.print("CN,");
			break;
		case 1:
			lcd.print("Thu 2,");
			break;
		case 2:
			lcd.print("Thu 3,");
			break;
		case 3:
			lcd.print("Thu 4,");
			break;
		case 4:
			lcd.print("Thu 5,");
			break;
		case 5:
			lcd.print("Thu 6,");
			break;
		case 6:
			lcd.print("Thu 7,");
			break;			
	}
	//Hiển thị ngày
	if(ngay <= 9)	//Các điều kiện in thời gian thứ, ngày/tháng/năm
    {
		lcd.print("0");
		lcd.print(ngay);
    }
    else
		lcd.print(ngay); 
    
    lcd.print('/');	//Dấu / phân cách giữa ngày/tháng/năm
	//Hiển thị tháng
    if(thang <= 9)
    {
		lcd.print("0");
		lcd.print(thang);
    }
    else
		lcd.print(thang); 
    //Hiển thị năm
    lcd.print('/');
    if(nam <= 9)
    {
		lcd.print("0");
		lcd.print(nam);
    }
    else 
		lcd.print(nam); 
	//
	//Hàng 2 hiển thị thông tin giờ/phút/giây
	lcd.setCursor(0, 1);
	lcd.print("TIME: ");
	//Hiện thị giờ
    if(gio <= 9)	//Điều kiện hiển thị
    {
      lcd.print("0");
      lcd.print(gio);
    }
    else
     lcd.print(gio); 
    lcd.print(':');	//Dấu : phân cách giữa giờ/phút/giây
	//Hiển  thị phút
    if(phut <= 9)
    {
      lcd.print("0");
      lcd.print(phut);
    }
    else
     lcd.print(phut); 
    
    lcd.print(':');
	//Hiển  thị giây
    if(giay <= 9)	
    {
      lcd.print("0");
      lcd.print(giay);
    }
    else
     lcd.print(giay); 
    
}