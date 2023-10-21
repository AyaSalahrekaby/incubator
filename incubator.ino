//temp cont
// Libraries included
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Declare pins
const int DHTPIN = 2;       //pin 2 in arduino
const int fan = 11;      //pin 11 in arduino
const int heater = 9;    //pin 9 in arduino

LiquidCrystal_I2C lcd( 0x27, 16,2);
//type ox3F or 0x27
DHT dht(DHTPIN, DHT11);

//variables
int temp;
int humidity;
//...
//water
const int watersensor = 12;
const int ledwater = 13;
//sound
const int ledSound = 10;
const int Soundsensor = 3;

int soundVal = 0;
//...
//colour
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define colorsensorOut 8
int frequency = 0;
//...
//heartrate
//  Variables
int PulseSensorPurplePin = 0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0
int LED = LED_BUILTIN;   //  The on-board Arduion LED


int Signal;                // holds the incoming raw data. Signal value can range from 0-1024
int Threshold = 80;       // Determine which Signal to "count as a beat", and which to ingore.
//..

void setup() {
  // put your setup code here, to run once:
  //temp cont.
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  dht.begin();
  pinMode(fan, OUTPUT);
  pinMode(heater, OUTPUT);
  //....
  //water
   //on pin12 we have the rain sensor so this is an input
  pinMode(watersensor, INPUT);
  pinMode(ledwater, OUTPUT);
  //...
  //sound
  pinMode (ledSound, OUTPUT);
  pinMode (Soundsensor, INPUT);
//...
//colour

  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(colorsensorOut, INPUT);
  
  
  digitalWrite(S0,HIGH);
  digitalWrite(S1,HIGH);
  
 
  //...
  //heartrate
  pinMode(LED,OUTPUT);         // pin that will blink to your heartbeat!
  //...


}

void loop() {
  // put your main code here, to run repeatedly:
  //temp cont.
  delay(2000); //dht11 need 2 sec 
  temp = dht.readTemperature();
  humidity = dht.readHumidity();
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" C");
  lcd.setCursor(0,0);
  lcd.print("Temp= ");
  lcd.setCursor(6,0);
  lcd.print(temp);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Humidity= ");
  lcd.setCursor(10,1);
  lcd.print(humidity);
  lcd.print("%");
  if (temp > 36 ){
    digitalWrite(fan, HIGH);
    digitalWrite(heater, LOW);
  }
  else if(temp < 24) {
    digitalWrite(fan, LOW);
    digitalWrite(heater, HIGH);
 }
  else {
   digitalWrite(fan, LOW);
   digitalWrite(heater, LOW);
 }
  
   //delay(1000);
   //...
   //water
  if(digitalRead(watersensor) == LOW)
    {
    
    digitalWrite(ledwater, HIGH);
    }    
  else
    {
      digitalWrite(ledwater, LOW);
    }
  //...
  //sound
  soundVal = digitalRead(Soundsensor);
  if (soundVal == LOW)
  {
  digitalWrite(ledSound, HIGH);
  }
  else
  {
  digitalWrite(ledSound, LOW);
  }
  //...
  //colour
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
 
  frequency = pulseIn(colorsensorOut, LOW);
  // Serial.print("R= ");
  // Serial.print(frequency);
  // Serial.print("  ");
  delay(100);

    digitalWrite(S2,LOW);
    digitalWrite(S3,HIGH);
 
  frequency = pulseIn(colorsensorOut, LOW);
  
  // Serial.print("B= ");
  // Serial.print(frequency);
  // Serial.print("  ");
   delay(100);

   
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  
  frequency = pulseIn(colorsensorOut, LOW);
 
  // Serial.print("G= ");
  // Serial.print(frequency);
  // Serial.println("  ");
  delay(100);
  

  delay(1000);
  //...
  //heartrate
  Signal = analogRead(PulseSensorPurplePin);  // Read the PulseSensor's value.
                                              // Assign this value to the "Signal" variable.

  //  Serial.println(Signal);                    // Send the Signal value to Serial Plotter.


   if(Signal > Threshold){                          // If the signal is above "550", then "turn-on" Arduino's on-Board LED.
     digitalWrite(LED,HIGH);
   } else {
     digitalWrite(LED,LOW);                //  Else, the sigal must be below "550", so "turn-off" this LED.
   }


delay(100);


}