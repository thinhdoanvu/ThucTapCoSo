void setup() 
{
  // cài đặt các chân điều khiển thành OUTPUT, sử dụng 4 chân số 7,8,9,10
  Serial.begin(9600); // Kết nối với module bluetooth ở tốc độ 9600
  pinMode(8,OUTPUT); // chân kết nối với đèn
  pinMode(9,OUTPUT);// chân kết nối với quạt
  pinMode(10,OUTPUT);// chân kết nối với đèn 2
  pinMode(11,OUTPUT);// chân kết nối với quạt 2
}

void turnled()
{
  // xuất tín hiệu khi nhận được tín hiệu từ Bluetooth: seriali.available()
  if(Serial.available()>0)
  {
    char led = Serial.read(); // đọc giá trị nhận được từ Bluetooth
    // nếu led = a thì sẽ xuất ra chân số 8 là sáng(HIGH) và chân số 10 là sáng(HIGH)
    if (led == 'a')
    {
      digitalWrite(8,HIGH);
      delay(100);
      digitalWrite(10,HIGH);
      delay(100);
    }
    // ngược lại nếu led = b thì sẽ xuất ra chân số 8 là tắt(LOW) và chân số 10 là tắt(LOW)
    else if(led == 'b')
    {
      digitalWrite(8,LOW);
      digitalWrite(10,LOW);
    }
  } 
 }
void turnfan()
{
  // xuất tín hiệu khi nhận được tín hiệu từ Bluetooth: seriali.available()
  if(Serial.available()>0)
  {
    char fan = Serial.read(); // đọc giá trị nhậc được từ Bluetooth
    // nếu fan = c thì sẽ xuất ra chân số 9, 11 là bật(HIGH
    if (fan == 'c')
    {
      digitalWrite(9,HIGH);
      delay(100);
      digitalWrite(11,HIGH);
      delay(100);
    }
    // ngược lại nếu fan = d thì sẽ xuất ra chân số 9, 11 là tắt(LOW)
    else if(fan == 'd')
    {
      digitalWrite(9,LOW);
      digitalWrite(11,LOW);
    }
  } 
 }
 void loop() 
{
 turnled(); // sử dụng bật tắt đèn
 turnfan(); // sử dụng bật tắt quạt
}


 
