void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
}

void loop() {
 turnled();
 turnfan(); 
}
void turnled()
{
  if(Serial.available()>0)
  {
    char data = Serial.read();
    if (data == 'a')
    {
     
      digitalWrite(13,HIGH);
    }
    else if(data == 'b')
    {
      digitalWrite(13,LOW);
    }
  } 
 }
void turnfan()
{
  if(Serial.available()>0)
  {
    char data = Serial.read();
    if (data == 'c')
    {
     
      digitalWrite(12,HIGH);
    }
    else if(data == 'd')
    {
      digitalWrite(12,LOW);
    }
  }
 }
 void turnmusic()
 {
  if(Serial.available()>0)
  {
    char data = Serial.read();
    if (data == '1')
    {
      digitalWrite(11,HIGH);
      }
      else if (data == '0')
      {
        digitalWrite(11,LOW);
        }
    }
  }
 
 
