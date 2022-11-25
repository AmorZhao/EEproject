int Htime;              //integer for storing high time
int Ltime;                //integer for storing low time
float Ttime;            // integer for storing total time of a cycle
float frequency;        //storing frequency

void setup()
{
    pinMode(8,INPUT);
    Serial.begin(9600);
}

void loop()
{
    Serial.print("Frequency of signal: ");
    Htime=pulseIn(8,HIGH, 10000);      //read high time
    Ltime=pulseIn(8,LOW, 10000);        //read low time   
    Ttime = Htime+Ltime;
    frequency=1000000/Ttime;    //getting frequency with Ttime is in Micro seconds
   if (frequency > 500 && frequency < 700 ){
      //Serial.println ("Netherite");
    }

   else if (frequency < 500 && frequency > 200){
    //Serial.println ("Thiotimoline");
    }

   else {
    //Serial.println ("None");
   }
    
    Serial.print(frequency);
    Serial.println(" Hz");
    delay(500);
    }
