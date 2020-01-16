void setup() { // khời tạo các chân đầu vào 
  Serial.begin(9600);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
}
 
void loop() {
 onoffled();
 onoffled1(); 
 onoffquat();
 onoffquat1();
}
 
void onoffled() // Bật tắt đèn led
{
  if(Serial.available()>0) // Kiểm tra nếu nhận được tín hiệu true/ false
  { 
    char data = Serial.read(); // Đọc dữ liệu vừa nhận vào biến data
    if (data == 'a') // Xử lý bật đèn
    {     
      digitalWrite(8,HIGH);
    }
    else if(data == 'b') // Xử lý tắt đèn 
    {
      digitalWrite(8,LOW);
    }
  } 
 }
 
 void onoffquat()// Bật tắt quạt
{
  if(Serial.available()>0) // Kiểm tra nếu nhận được tín hiệu true/false
  {
    char data = Serial.read(); // Đọc dữ liệu vừa nhận vào biến data 
    if (data == 'c') // Xử lý bật quạt
    {     
      digitalWrite(10,HIGH);
    }
    else if(data == 'd') // Xử lý tắt quạt
    {
      digitalWrite(10,LOW);
    }
  } 
 }
 
void onoffled1() // Bật tắt đèn có sử dụng Rơ-le
{
  if(Serial.available()>0) // Kiểm tra nếu nhận được tín hiệu true/false
  {
    char data = Serial.read(); // Đọc dữ liệu vừa nhận vào biến data
    if (data == 'e') // Xử lý bật đèn
    {  
      digitalWrite(9,HIGH);
    }
    else if(data == 'f') // Xử lý tắt đèn
    {
      digitalWrite(9,LOW);
    }
  }  
 }
 
 void onoffquat1() // Bật tắt quạt có sử dụng Rơ-le
{
  if(Serial.available()>0) // Kiểm tra nếu nhận được tín hiệu true/false
  {
    char data = Serial.read(); // Đọc dữ liệu vừa nhận vào biến data
    if (data == 'g') // Xử lý bật quạt
    {
     
      digitalWrite(11,HIGH);
    }
    else if(data == 'h') // Xử lý tắt quạt
    {
      digitalWrite(11,LOW);
    }
  } 
 }
