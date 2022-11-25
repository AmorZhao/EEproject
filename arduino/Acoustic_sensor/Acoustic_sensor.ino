//#define Acoustic_Pin A0    // select the input pin for the potentiometer

int Acoustic_Value = 0;  // variable to store the value coming from the sensor
boolean Acoustic_flag = 0;

void setup() {
  // begin the serial monitor @ 9600 baud
  Serial.begin(9600);
  pinMode (A0, INPUT);
}

void loop() {
  // read the value from the sensor:
  Acoustic_Value = analogRead(A0);

  Serial.println(Acoustic_Value);
  Serial.write(" ");

  delay(10);
  if (Acoustic_Value >= 90.0){
    Serial.println("Rock");
    Acoustic_flag = 1;
    }

  else if(Acoustic_Value < 90.0){
    Serial.println("no");
    Acoustic_flag = 0;
  }
  }
 
