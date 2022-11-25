#define USE_WIFI_NINA         false
#define USE_WIFI101           true
#include <WiFiWebServer.h>
#include <string>
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
int command; //variable storing command in serial monitor
const int wait = 100; //delay time between motors on and off
#define left_en 8
#define right_en 9
#define left_dir 10
#define right_dir 11
const char ssid[] = "EEERover";
const char pass[] = "exhibition";
const int groupNumber = 26; // Set your group number to make the IP address constant - only do this on the EEERover network


//Webpage to return when root is requested
const char webpage1[] = \
                        "<html> <head> <title>EEERover Control</title> <style> body { background-color: #282828; } h1 { font-family: Arial, sans-serif; font-weight: bold; font-size: 28px; text-align: center; color: white; margin: 35px; } .stop { border-radius: 50%; background-color: red; color: white; height: 70px; width: 70px; box-shadow: 0 8px 16px 0 rgba(0,0,0,0.2), 0 6px 20px 0 rgba(0,0,0,0.19); border: 1px solid black; font-size: 20px; } .stop:hover { background-color: orangered; } .stop:active { transform: translateY(3px); } .container { background: #282828; height: 100vh; padding: 20px; text-align: center; }";

const char webpage2[] = \
                        ".content { position: absolute; left: 50%; top: 50%; transform: translate(-50%, -50%); p { margin: 0 0 20px; } } .button { position: relative; align-items: center; display: flex; justify-content: center; padding: 8px; } .button__arrow { background-color: transparent; height: 18px; width: 18px; } .button__arrow--up { border-left: 1px solid rgba(0, 0, 0, 0.3); border-top: 1px solid rgba(0, 0, 0, 0.3); transform: translateY(25%) rotate(45deg); } .button__arrow--right { border-right: 1px solid rgba(0, 0, 0, 0.3); border-top: 1px solid rgba(0, 0, 0, 0.3); transform: translateX(-25%) rotate(45deg); } .button__arrow--down { border-bottom: 1px solid rgba(0, 0, 0, 0.3); border-right: 1px solid rgba(0, 0, 0, 0.3); transform: translateY(-25%) rotate(45deg); } .button__arrow--left { border-bottom: 1px solid rgba(0, 0, 0, 0.3); border-left: 1px solid rgba(0, 0, 0, 0.3); transform: translateX(25%) rotate(45deg); } .textbox { border: solid white 2px; font-size: 20px; background-color: white; font-family: Arial, sans-serif; color: black; width: 300px; text-align: center; position: absolute; left: 50%; margin: -100px 0 0 -150px; border-radius: 12px; padding: 10px; top: 35%; } </style> </head>";

const char webpage3[] = \
                        "<body> <h1>EEERover Control</h1> <div class=\"textbox\"> <span id=\"state\">Awaiting scan request</span> </div> <div class=\"container\"> <div class=\"content\"> <div style=\"position: relative; left: 15px; top: 33px;\"> <button id=\"forwards\" class=\"button\" onclick=\"forwards()\"> <div class=\"button__arrow button__arrow--up\"></div> </button> </div> <div style=\"position: relative; left: 90px; top: 73px;\"> <button id=\"right\" class=\"button\" onclick=\"right()\"> <div class=\"button__arrow button__arrow--right\"></div> </button> </div> <p> <button id=\"scan\" class=\"stop\" onclick=\"brake()\">SCAN</button> </p> <div style=\"position: relative; left: 17px; top: 4px;\"> <button id=\"back\" class=\"button\" onclick=\"backwards()\"> <div class=\"button__arrow button__arrow--down\"></div> </button> </div> <div style=\"position: relative; right: 60px; bottom: 108px;\"> <button id=\"left\" class=\"button\" onclick=\"left()\"> <div class=\"button__arrow button__arrow--left\"></div> </button> </div> </div> </div> </body>";

const char webpage4[] = \
                        "<script> var xhttp = new XMLHttpRequest(); xhttp.onreadystatechange = function() {if (this.readyState == 4 && this.status == 200) {document.getElementById(\"state\").innerHTML = this.responseText;}}; function left(){xhttp.open(\"GET\", \"/left\"); xhttp.send();} function right(){xhttp.open(\"GET\", \"/right\"); xhttp.send();}";

const char webpage5[] = \
                        "function brake(){xhttp.open(\"GET\", \"/scan\"); xhttp.send();} function forwards(){xhttp.open(\"GET\", \"/forwards\"); xhttp.send();}";

const char webpage6[] = \
                        "function backwards(){xhttp.open(\"GET\", \"/backwards\"); xhttp.send();} document.addEventListener(\"keydown\", function(event) { if (event.keyCode === 87) { event.preventDefault(); document.getElementById(\"forwards\").click(); }";

const char webpage7[] = \
                        "if (event.keyCode === 83) { event.preventDefault(); document.getElementById(\"back\").click(); } if (event.keyCode === 13) { event.preventDefault(); document.getElementById(\"scan\").click(); }";


const char webpage8[] = \
                        "if (event.keyCode === 65) { event.preventDefault(); document.getElementById(\"left\").click(); } if (event.keyCode === 68) { event.preventDefault(); document.getElementById(\"right\").click(); } }); </script> </html>";


WiFiWebServer server(80);

//Return the web page
void handleRoot()
{
  server.sendContent(webpage1);
  server.sendContent(webpage2);
  server.sendContent(webpage3);
  server.sendContent(webpage4);
  server.sendContent(webpage5);
  server.sendContent(webpage6);
  server.sendContent(webpage7);
  server.sendContent(webpage8);

}

void brake()
{
   digitalWrite(left_en,LOW);
   digitalWrite(right_en,LOW);
}

void right()
{
    digitalWrite(LED_BUILTIN, 0);
    digitalWrite(left_dir,HIGH);
    digitalWrite(right_dir,HIGH);
    digitalWrite(left_en,HIGH);
    digitalWrite(right_en,HIGH);
    delay(wait);
    brake();
    server.send(200, F("text/plain"), F("Awaiting scan request"));
}

//Switch LED on and acknowledge
void left()
{
  digitalWrite(left_dir,LOW);
  digitalWrite(right_dir,LOW);
  digitalWrite(left_en,HIGH);
  digitalWrite(right_en,HIGH);
  delay(wait);
  brake();
  server.send(200, F("text/plain"), F("Awaiting scan request"));
}

void forwards()
{
  digitalWrite(left_dir,HIGH);
  digitalWrite(right_dir,LOW);
  digitalWrite(left_en,HIGH);
  digitalWrite(right_en,HIGH);
  delay(wait);
  brake();
  server.send(200, F("text/plain"), F("Awaiting scan request"));
}

//Switch LED on and acknowledge
void backwards()
{
  digitalWrite(left_dir,LOW);
  digitalWrite(right_dir,HIGH);
  digitalWrite(left_en,HIGH);
  digitalWrite(right_en,HIGH);
  delay(wait);
  brake();
  server.send(200, F("text/plain"), F("Awaiting scan request"));

}

void scan()
{  
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
      server.send(200, F("text/plain"), F("Adamantine"));
    }
    else if ( radio_240 > 7 )
    {
      server.send(200, F("text/plain"), F("Xirang"));
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
      server.send(200, F("text/plain"), F("Gaborium"));
    }
    if ( radio_240 > 7 )
    {
      server.send(200, F("text/plain"), F("Lathwaite"));
    }
    if ( IR_Netherite > 12 && Acoustic_flag > 12 )
    {
      server.send(200, F("text/plain"), F("Netherite"));
    }
    if ( IR_Thiotimoline > 12 )
    {
      server.send(200, F("text/plain"), F("Thiotimoline"));
    }
    radio_151 = radio_240 = 0;
    IR_Netherite = IR_Thiotimoline = Acoustic_flag = 0;
}

//Generate a 404 response with details of the failed request
void handleNotFound()
{
  String message = F("File Not Found\n\n");
  message += F("URI: ");
  message += server.uri();
  message += F("\nMethod: ");
  message += (server.method() == HTTP_GET) ? F("GET") : F("POST");
  message += F("\nArguments: ");
  message += server.args();
  message += F("\n");
  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, F("text/plain"), message);
}

void setup()
{
  //magnetic
  pinMode(HALL_input, INPUT);

  //radio
  pinMode(RADIO_input, INPUT);
  pinMode(RADIO_output, OUTPUT);

  //IR
  pinMode(IR_pin, INPUT);

  //ultrasound
  pinMode(Acoustic_Pin, INPUT);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);

  Serial.begin(9600);
  //Wait 10s for the serial connection before proceeding
  //This ensures you can see messages from startup() on the monitor
  //Remove this for faster startup when the USB host isn't attached
  while (!Serial && millis() < 10000);
  Serial.println(F("\nStarting Web Server"));

  //Check WiFi shield is present
  if (WiFi.status() == WL_NO_SHIELD)
  {
    Serial.println(F("WiFi shield not present"));
    while (true);
  }

  //Configure the static IP address if group number is set
if (groupNumber)
  WiFi.config(IPAddress(192, 168, 0, groupNumber + 1));

  // attempt to connect to WiFi network
  Serial.print(F("Connecting to WPA SSID: "));
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED)
  {
    delay(500);
    Serial.print('.');
  }

  //Register the callbacks to respond to HTTP requests
  server.on(F("/"), handleRoot);
  server.on(F("/left"), left);
  server.on(F("/right"), right);
  server.on(F("/scan"), scan);
  server.on(F("/forwards"), forwards);
  server.on(F("/backwards"), backwards);

  server.onNotFound(handleNotFound);

  server.begin();

  Serial.print(F("HTTP server started @ "));
  Serial.println(static_cast<IPAddress>(WiFi.localIP()));
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
  radio_frequency = 1000000/radio_T;    //getting frequency with Time is in Microseconds
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
    frequency_IR=1000000/Ttime_IR;    //getting frequency with Time is in Microseconds

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
  if (Acoustic_Value >= 80.0)
  {
    Acoustic_flag ++;
  }
 }





//Call the server polling function in the main loop
void loop()
{
  server.handleClient();

}
