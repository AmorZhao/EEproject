#define HALL_input A4
#define RADIO_input 3
#define RADIO_output 6
#define IR_pin 2
#define Acoustic_Pin A0

int radio_Htime;              //integer for storing high time
int radio_Ltime;                //integer for storing low time
float radio_T;            // integer for storing total time of a cycle
float radio_frequency;        //storing frequency
int radio_151 = 0; 
int radio_240 = 0; 

int Htime_IR;              //integer for storing high time
int Ltime_IR;                //integer for storing low time
float Ttime_IR;            // integer for storing total time of a cycle
float frequency_IR;        //storing frequency
int IR_Thiotimoline = 0; 
int IR_Netherite = 0;

int Acoustic_Value = 0;  // variable to store the value coming from the sensor
int Acoustic_flag = 0;

void setup() 
{
  Serial.begin(9600);
  
  //magnetic
  pinMode(HALL_input, INPUT);

  //radio
  pinMode(RADIO_input,INPUT);
  pinMode(RADIO_output, OUTPUT); 

  //IR
  pinMode(IR_pin,INPUT);

  //ultrasound
  pinMode(Acoustic_Pin, INPUT); 
}

void loop()
{
  Serial.println("start"); 
  digitalWrite ( RADIO_output, LOW );  
  for (int i=0; i<10; i++)
  {
    magnetic(); 
    radio(); 
    IR_sensor (); 
    Acoustic_sensor(); 
  }
  if ( radio_151 > 7 )
  {
    Serial.println("Adamantine"); 
  }
  else if ( radio_240 > 7 )
  {
    Serial.println("Xirang"); 
  }  
  digitalWrite ( RADIO_output, HIGH );  
  radio_151 = radio_240 = 0; 
  for (int i=0; i<10; i++)
  {
    magnetic(); 
    radio();  
    IR_sensor(); 
    Acoustic_sensor(); 
  } 
  if ( radio_151 > 7 && Acoustic_flag > 12 )
  {
    Serial.println("Gaborium");  
  }
  else if ( radio_240 > 7 )
  {
    Serial.println("Lathwaite"); 
  }
  else if ( IR_Netherite > 12 && Acoustic_flag > 12 )
  {
    Serial.println("Netherite"); 
  }
  else if ( IR_Thiotimoline > 12 )
  {
    Serial.println("Thiotimoline"); 
  }
  else
  {
    Serial.println("no rock detected"); 
  }
  radio_151 = radio_240 = 0; 
  IR_Netherite = IR_Thiotimoline = Acoustic_flag = 0; 
  //delay(1000);
}

void magnetic() 
{
  //Serial.println(analogRead(HALL_input)); 
}

void radio()
{
  //Serial.print("Frequency of signal: ");
  radio_Htime=pulseIn(RADIO_input, HIGH, 20000);      //read high time
  radio_Ltime=pulseIn(RADIO_input, LOW, 20000);        //read low time   
  radio_T = radio_Htime + radio_Ltime;
  radio_frequency = 1000000/radio_T;    //getting frequency with Ttime is in Micro seconds
  if (radio_frequency > 200 && radio_frequency < 300 )
  {
    radio_240 ++; 
  }
  else if (radio_frequency < 200 && radio_frequency > 100)
  {
    radio_151 ++; 
  }    
}

void IR_sensor( )
{
    Htime_IR=pulseIn(IR_pin, HIGH, 10000);      //read high time
    Ltime_IR=pulseIn(IR_pin, LOW, 10000);        //read low time   
    Ttime_IR = Htime_IR+Ltime_IR;
    frequency_IR=1000000/Ttime_IR;    //getting frequency with Ttime is in Micro seconds
    
   if (frequency_IR > 500 && frequency_IR < 700 )
   {
      IR_Netherite ++;
   }

   else if (frequency_IR < 500 && frequency_IR > 200)
   {
      IR_Thiotimoline ++;
   }  
}

void Acoustic_sensor() 
{
  // read the value from the sensor:
  Acoustic_Value = analogRead(Acoustic_Pin);

  delay(10);
  if (Acoustic_Value >= 130.0)
  {
    Acoustic_flag ++;
  }
 }
 
