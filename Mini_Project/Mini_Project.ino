#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 32 


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

long duration, LEFTSensor,BACKSensor,RIGHTSensor;
int distance, LEFTDisplay,BACKDisplay,RIGHTDisplay;
void setup() {
  Serial.begin(9600);

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
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  
  
  delay(1000);
  display.clearDisplay();
 
}

void loop() {
  
  display.drawRect(1, 1, 126,31, WHITE);
  SonarSensor(trigPin1, echoPin1);
  String LEFTSensor = String(distance);
  LEFTDisplay = distance;
  SonarSensor(trigPin2, echoPin2);
  String BACKSensor = String(distance);
  BACKDisplay = distance;
  SonarSensor(trigPin3, echoPin3);
  String RIGHTSensor = String(distance);
  RIGHTDisplay = distance;

  display.display(); 
  display.clearDisplay();
  DisText("Left : ", 4, 3, 1, false);
  DisText(LEFTSensor, 60, 3, 1, false);
  DisText("cm", 84, 3, 1, false);
  DisText("Back : ", 4, 11, 1, false);
  DisText(BACKSensor, 60, 11, 1, false);
  DisText("cm", 84, 11, 1, false);
  DisText("Right : ", 4, 19, 1, false);
  DisText(RIGHTSensor, 60, 19, 1, false);
  DisText("cm", 84, 19, 1, false);
  
   delay(500);

  if((LEFTDisplay >= 10) & (LEFTDisplay <= 70)) 
  {
  digitalWrite(buzzer, HIGH);
  digitalWrite(ledPin1, HIGH);
  delay(10*(distance-5));
  digitalWrite(buzzer, LOW);
  digitalWrite(ledPin1, LOW);
  delay(10*(distance-5));
  }

  if((BACKDisplay >= 10) & (BACKDisplay <= 70)) 
  {
  digitalWrite(buzzer, HIGH);
  digitalWrite(ledPin2, HIGH);
  delay(10*(distance-5));
  digitalWrite(buzzer, LOW);
  digitalWrite(ledPin2, LOW);
  delay(10*(distance-5));
  }

  if((RIGHTDisplay >= 10) & (RIGHTDisplay <= 70)) 
  {
  digitalWrite(buzzer, HIGH);
  digitalWrite(ledPin3, HIGH);
  delay(10*(distance-5));
  digitalWrite(buzzer, LOW);
  digitalWrite(ledPin3, LOW);
  delay(10*(distance-5));
  }
}

void DisText(String text, int x, int y,int size, boolean d) {

  display.setTextSize(size);
  display.setTextColor(WHITE);
  display.setCursor(x,y);
  display.println(text);
  if(d){
    display.display();
  }
  
  //delay(100);
}

void SonarSensor(int trigPin,int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;


}
