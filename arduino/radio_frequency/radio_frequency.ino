int Htime;              //integer for storing high time
int Ltime;                //integer for storing low time
float Ttime;            // integer for storing total time of a cycle
float frequency;        //storing frequency

void setup()
{
    pinMode(8,INPUT);
    pinMode (A4, OUTPUT); 
    Serial.begin(9600);
}

void loop()
{
    digitalWrite(A4, HIGH); 
    digitalWrite(7, HIGH); 
    Serial.print("Frequency of signal: ");
    Htime=pulseIn(8,HIGH, 20000);      //read high time
    Ltime=pulseIn(8,LOW, 20000);        //read low time   
    Ttime = Htime+Ltime;
    frequency=1000000/Ttime;    //getting frequency with Ttime is in Micro seconds
    if (frequency > 200 && frequency < 300 ){
      Serial.println ("240");
    }

   else if (frequency < 200 && frequency > 100){
    Serial.println ("151");
    }

   else {
    //Serial.println ("None");
   }
    
    Serial.print(frequency);
    Serial.println(" Hz");
    delay(100);
}
