//Khai báo các chân của thiết bị
int quat = 8;
int quat1 = 9;
int led = 10;
int led1 = 11;

void setup() {
  //Tốc độ truyền thông nối tiếp 9600 baud
  Serial.begin(9600);
  //Thiết lập các chân đầu ra
  pinMode(quat,OUTPUT); // chân đầu ra quạt
  pinMode(quat1,OUTPUT); // chân đầu ra quạt 1
  pinMode(led,OUTPUT);   //chân đầu ra led
  pinMode(led1,OUTPUT);  //chân đầu ra led1
}

void loop() {
 dkled(); //hàm điều khiển led 
 dkled1(); //hàm điều khiển led1
 dkquat(); //hàm điều khiển quạt
 dkquat1(); //hàm điều khiển quạt 1
}
//Hàm điều khiển quạt thứ nhất
void dkquat()
{
  //Nếu nhận tín hiệu bluetooth
  if(Serial.available()>0)
  { 
    char data = Serial.read(); // thì sẽ đọc tín hiệu bluetooth đó
    if (data == 'a')           //nếu dữ liệu tín hiệu = a
    {
     
      digitalWrite(quat,HIGH); // bật đèn
    }
    else if(data == 'b')      //nếu dữ liệu tín hiệu = b
    {
      digitalWrite(quat,LOW); //tắt đèn
    }
  } 
 }
 //Hàm điều khiển quạt thứ 2
void dkquat1()
{
  if(Serial.available()>0)
  {
    char data = Serial.read();
    if (data == 'c')//nếu dữ liệu tín hiệu = c
    {
     
      digitalWrite(quat1,HIGH);
    }
    else if(data == 'd')//nếu dữ liệu tín hiệu = d
    {
      digitalWrite(quat1,LOW);
    }
  }
  
 }
//Hàm điều khiển led thứ nhất
void dkled()
{
  if(Serial.available()>0)
  {
    char data = Serial.read();
    if (data == 'e') //nếu dữ liệu tín hiệu = e
    {
     
      digitalWrite(led,HIGH);
    }
    else if(data == 'f') //nếu dữ liệu tín hiệu = f
    {
      digitalWrite(led,LOW);
    }
  }  
 }
 //Hàm điều khiển led thứ 2
 void dkled1()
{
  if(Serial.available()>0)
  {
    char data = Serial.read();
    if (data == 'h') //nếu dữ liệu tín hiệu = h
    {
     
      digitalWrite(led1,HIGH);
    }
    else if(data == 'g') //nếu dữ liệu tín hiệu = g
    {
      digitalWrite(led1,LOW);
    }
  }
  
 }


 
