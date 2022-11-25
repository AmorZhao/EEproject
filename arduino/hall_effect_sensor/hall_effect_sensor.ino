#define Hall A2

void setup() 
{
  pinMode(Hall, INPUT);
  Serial.begin(9600);
}

void loop() 
{
  Serial.println(analogRead(Hall)); 
  delay(100); 
}
