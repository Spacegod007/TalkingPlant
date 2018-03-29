#include "DHT.h"
#include <Adafruit_Sensor.h>

#define OFF 0
#define ON 255

#define LIGHT_SENSOR 5
#define MOISURE_SENSOR 4
#define TEMPERATURE_SENSOR 13
#define MOTION_PIR_SENSOR 12

#define DHTTYPE DHT22

#define WHITE_LED_PIN 9
#define BLUE_RGB_PIN 6
#define RED_RGB_PIN 5
#define GREEN_LED_PIN 8

DHT dht(TEMPERATURE_SENSOR, DHTTYPE);

void setup() {
  Serial.begin(9600);
  
  pinMode(WHITE_LED_PIN, OUTPUT);
  pinMode(BLUE_RGB_PIN, OUTPUT);
  pinMode(RED_RGB_PIN, OUTPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);

  pinMode(TEMPERATURE_SENSOR, INPUT);
  pinMode(MOTION_PIR_SENSOR, INPUT);
}

void loop() {
  lightDemo();
  moistureDemo();
  temperatureDemo();
  motionPirDemo();
  
  delay(250);
}

void lightDemo()
{
  int lightOutput = map(analogRead(LIGHT_SENSOR), 0, 1023, 255, 0);

  printMessage("lightOutput: ", lightOutput);

  analogWrite(WHITE_LED_PIN, lightOutput);
}

void moistureDemo()
{
  int readMoisture = map(analogRead(MOISURE_SENSOR), 0, 1023, -255, 255);

  printMessage("read moisture: ", readMoisture);
  
  if (readMoisture >= 0)
  {
    analogWrite(BLUE_RGB_PIN, readMoisture);
    analogWrite(RED_RGB_PIN, OFF);
  }
  else
  {
    int writeRedPin = map(readMoisture, -255, -1, 255, 0);
    analogWrite(RED_RGB_PIN, writeRedPin);
    analogWrite(BLUE_RGB_PIN, OFF);
  }
}

void temperatureDemo()
{
  printMessage("temperature: ", dht.readTemperature());
}

void motionPirDemo()
{
  if (digitalRead(MOTION_PIR_SENSOR) == 1)
  {
    digitalWrite(GREEN_LED_PIN, HIGH);
    Serial.println("motion detected!");
  }
  else
  {
    digitalWrite(GREEN_LED_PIN, LOW);
  }
}

void printMessage(String message, int value)
{
  Serial.print(message);
  Serial.println(value);
}

