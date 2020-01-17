//Khai báo chân của cá thiết bị
int denphongkhach = 8;
int dennhabep = 9;
int quatphongkhach = 10;
int quatnhabep = 11;
void setup() {
  Serial.begin(9600);             // Tốc độ truyền thông nối tiếp 9600 baud
  pinMode(denphongkhach,OUTPUT);  // Khai báo chân đầu ra đèn phòng khách
  pinMode(dennhabep,OUTPUT);      // Khai báo chân đầu ra đèn nhà bếp
  pinMode(quatphongkhach,OUTPUT); // Khai báo chân đầu ra quạt phòng khách
  pinMode(quatnhabep,OUTPUT);     // Khai báo chân đầu ra quạt nhà bếp
}

void loop() {
 TurnLedPK(); //Hàm điều khiển đèn nhà khách
 TurnLedNB(); //Hàm điều khiển đèn phòng bếp
 TurnFanPK(); //Hàm điều khiển đèn nhà khách
 TurnFanNB(); //Hàm điều khiển đèn phòng khách
 TurnAll();   //Hàm điều khiển bật tắt tất cả thiết bị
}
void TurnLedPK()
{
  if(Serial.available()>0) //Nếu nhận tín hiệu của Bluetooth
  { 
    char data = Serial.read(); //Thì sẽ đọc tín hiệu Bluetooth đó
    if (data == 'a')  //Nếu tín hiệu nhận được là "a"
    {
      digitalWrite(denphongkhach,HIGH); //Bật đèn
    }
    else if(data == 'b') //Nếu tín hiệu nhận được là "b"
    {
      digitalWrite(denphongkhach,LOW); //Tắt đèn
    }
  } 
 }
void TurnLedNB()
{
  if(Serial.available()>0)//Nếu nhận tín hiệu của Bluetooth
  {
    char data = Serial.read();//Thì sẽ đọc tín hiệu Bluetooth đó
    if (data == 'c') //Nếu tín hiệu nhận được là "c"
    {
     
      digitalWrite(dennhabep,HIGH);//Bật đèn
    }
    else if(data == 'd') //Nếu tín hiệu nhận được là "d"
    {
      digitalWrite(dennhabep,LOW);// Tắt đèn
    }
  }
  
 }

void TurnFanPK()
{
  if(Serial.available()>0)//Nếu nhận tín hiệu của Bluetooth
  {
    char data = Serial.read();//Thì sẽ đọc tín hiệu Bluetooth đó
    if (data == 'e') //Nếu tín hiệu nhận được là "e"
    {
     
      digitalWrite(quatphongkhach,HIGH);//Bật quạt
    }
    else if(data == 'f') //Nếu tín hiệu nhận được là "f"
    {
      digitalWrite(quatphongkhach,LOW);//Tắt quạt
    }
  }
  
 }
 void TurnFanNB()
{
  if(Serial.available()>0)//Nếu nhận tín hiệu của Bluetooth
  {
    char data = Serial.read();//Thì sẽ đọc tín hiệu Bluetooth đó
    if (data == 'g') //Nếu tín hiệu nhận được là "g"
    {
     
      digitalWrite(quatnhabep,HIGH);//Bật quạt
    }
    else if(data == 'h') //Nếu tín hiệu nhận được là "h"
    {
      digitalWrite(quatnhabep,LOW);//Tắt quạt
    }
  }
  
 }
 void TurnAll()
{
  if(Serial.available()>0)//Nếu nhận tín hiệu của Bluetooth
  { 
    char data = Serial.read();//Thì sẽ đọc tín hiệu Bluetooth đó
    if (data == 'i') //Nếu tín hiệu nhận được là "i"
    {
     
      digitalWrite(denphongkhach,HIGH);
      digitalWrite(dennhabep,HIGH);
      digitalWrite(quatphongkhach,HIGH);
      digitalWrite(quatnhabep,HIGH);
    }
    else if(data == 'j') //Nếu tín hiệu nhận được là "j"
    {
      digitalWrite(denphongkhach,LOW);
      digitalWrite(dennhabep,LOW);
      digitalWrite(quatphongkhach,LOW);
      digitalWrite(quatnhabep,LOW);
    }
  } 
 }
