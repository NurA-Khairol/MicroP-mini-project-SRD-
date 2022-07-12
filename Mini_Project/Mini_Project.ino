#include <SPI.h>  // library for Serial Peripheral Interface (communicating with one or more peripheral devices quickly over short distances)
#include <Wire.h> // library that allows communication with I2C/TWI devices (by setting A4 as SDA and A5 as SCL)
#include <Adafruit_GFX.h>   // both Adafruit library is necessary library for Oled display
#include <Adafruit_SSD1306.h>

//Declaration of display resolution
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 32 

//Declaration of digital pin on Arduino
#define trigPin1 2
#define echoPin1 3 
#define buzzer 4
#define trigPin2 5
#define echoPin2 6
#define ledPin1 7
#define ledPin2 8
#define ledPin3 9
#define trigPin3 10
#define echoPin3 11

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Declaration of every variable type
long duration, LEFTSensor,BACKSensor,RIGHTSensor;
int distance, LEFTDisplay,BACKDisplay,RIGHTDisplay;

void setup() {  // set up code that will run once
  Serial.begin(9600); //begin serial communication at 9600 baud rate

  // Declaration of pin mode (either Input or Output)
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Initialize I2C addr for 128x32 display (0x3C)
  
  
  delay(1000);
  display.clearDisplay();
 
}

void loop() { //code that will run continously
  
  display.drawRect(1, 1, 126,31, WHITE); // set rectangle border on display
  SonarSensor(trigPin1, echoPin1); // refer to SonarSensor function
  String LEFTSensor = String(distance); // save data taken from fuction to a variable (and change from int to string)
  LEFTDisplay = distance; // save data taken to another variable
  SonarSensor(trigPin2, echoPin2);
  String BACKSensor = String(distance);
  BACKDisplay = distance;
  SonarSensor(trigPin3, echoPin3);
  String RIGHTSensor = String(distance);
  RIGHTDisplay = distance;

  display.display(); // initialize display
  display.clearDisplay(); // refresh out display
  DisText("Left : ", 4, 3, 1, false); // refer to function DisText
  DisText(LEFTSensor, 60, 3, 1, false);
  DisText("cm", 84, 3, 1, false);
  DisText("Back : ", 4, 11, 1, false);
  DisText(BACKSensor, 60, 11, 1, false);
  DisText("cm", 84, 11, 1, false);
  DisText("Right : ", 4, 19, 1, false);
  DisText(RIGHTSensor, 60, 19, 1, false);
  DisText("cm", 84, 19, 1, false);
  
   delay(500); // set delay of 500 microsecond before refreshing

  if((LEFTDisplay >= 10) & (LEFTDisplay <= 50)) 
  {
  digitalWrite(buzzer, HIGH); // turn on buzzer
  digitalWrite(ledPin1, HIGH); // turn on led no.1
  delay(10*(distance-5)); // set delay by calculation
  digitalWrite(buzzer, LOW); // turn off buzzer
  digitalWrite(ledPin1, LOW); // turn off led no.1
  delay(10*(distance-5));
  }

  if((BACKDisplay >= 10) & (BACKDisplay <= 50)) 
  {
  digitalWrite(buzzer, HIGH);
  digitalWrite(ledPin2, HIGH);
  delay(10*(distance-5));
  digitalWrite(buzzer, LOW);
  digitalWrite(ledPin2, LOW);
  delay(10*(distance-5));
  }

  if((RIGHTDisplay >= 10) & (RIGHTDisplay <= 50)) 
  {
  digitalWrite(buzzer, HIGH);
  digitalWrite(ledPin3, HIGH);
  delay(10*(distance-5));
  digitalWrite(buzzer, LOW);
  digitalWrite(ledPin3, LOW);
  delay(10*(distance-5));
  }
}

void DisText(String text, int x, int y,int size, boolean d) // function to simplify oled display setting
{ 

  display.setTextSize(size); // set size of text (size 1 take of 8 bit)
  display.setTextColor(WHITE); // set colour of text
  display.setCursor(x,y); // set x and y coordinate of text
  display.println(text); // print text on display
  if(d){
    display.display();
  }
  
}

void SonarSensor(int trigPin,int echoPin) // function to simplify distance measurement
{
digitalWrite(trigPin, LOW); // turn off the trigger/transmitter
delayMicroseconds(2); // for duration of two microsecond
digitalWrite(trigPin, HIGH); // turn on the transmitter
delayMicroseconds(10); // for 10 second
digitalWrite(trigPin, LOW); // turn off the transmitter
duration = pulseIn(echoPin, HIGH); // set duration as the interval of echo/receiver recieve two ulratsonic wave
distance = (duration/2) / 29.1; // calculation of ulratosonic wave interval duration to distance


}
