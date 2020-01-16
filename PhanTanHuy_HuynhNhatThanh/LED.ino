void setup() { //Các chân đàu vào
  Serial.begin(9600); 
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
 
}

void loop()     //Bật tắt đèn led
{   
  quat();
  den();
} 
 void den()
 {  
  if (Serial.available() > 0)
  {
    char data = Serial.read();
    if (data == 'a')
    {

      digitalWrite(13, HIGH); //Xử lý bật đèn
    }
    else if (data == 'b')
    {
      digitalWrite(13, LOW); //Xử lý tắt đèn
    }
  }
}
 void quat() //Bật tắt quạt
 {  
  if (Serial.available() > 0)
  {
    char data = Serial.read();
    if (data == 'c')
    {

      digitalWrite(12, HIGH);
    }
    else if (data == 'd')
    {
      digitalWrite(12, LOW);
    }
  }
}
