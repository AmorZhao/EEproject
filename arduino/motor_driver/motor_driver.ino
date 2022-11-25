#define left_en 8
#define right_en 9
#define left_dir 10
#define right_dir 11
int command; 

void setup() {
  pinMode(left_en,OUTPUT);
  pinMode(right_en,OUTPUT);
  pinMode(left_dir,OUTPUT);
  pinMode(right_dir,OUTPUT);
  Serial.begin(9600); 
  
}

void loop() 
{
  //a command is received
  //tested by serial command input for now
  while (Serial.available() == 0) 
  {
    // Wait for User to Input Data
  }
  command = Serial.parseInt();




  
  if ( command == 1 ) //forward
  {
      digitalWrite(left_en,HIGH); 
      digitalWrite(right_en,HIGH);
      digitalWrite(left_dir,HIGH); 
      digitalWrite(right_dir,HIGH);
      delay(100);
  }
  if ( command == 2 ) //backward
  {
      digitalWrite(left_en,HIGH); 
      digitalWrite(right_en,HIGH);
      digitalWrite(left_dir,LOW); 
      digitalWrite(right_dir,LOW);
      delay(1000); 
  }
  if ( command == 3 ) //right
  {
      digitalWrite(left_en,HIGH); 
      digitalWrite(right_en,HIGH);
      digitalWrite(left_dir,HIGH); 
      digitalWrite(right_dir,LOW);
      delay(1000); 
  }
  if ( command == 4 ) //left
  {
      digitalWrite(left_en,HIGH); 
      digitalWrite(right_en,HIGH);
      digitalWrite(left_dir,LOW); 
      digitalWrite(right_dir,HIGH);
      
  }
  else //stop
  {
    digitalWrite(left_en,LOW); 
    digitalWrite(right_en,LOW);
    delay(1000); 
  }
}
