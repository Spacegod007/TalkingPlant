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

#define MINIMUM_MOISTURE 700
#define MAXIMUM_MOISTURE 1023

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

  Serial.println("//=\\\\=//=\\\\=//=\\\\=//=\\\\=//=\\\\=//=\\\\");
  
  delay(125);
}

void lightDemo()
{
  int lightOutput = map(analogRead(LIGHT_SENSOR), 0, 1023, 255, 0);

  printMessage("lightOutput: ", lightOutput);

  analogWrite(WHITE_LED_PIN, lightOutput);
}

void moistureDemo()
{
  int readMoisture = 1023 - analogRead(MOISURE_SENSOR);
  printMessage("read moisture: ", readMoisture);
  
  if (readMoisture >= MINIMUM_MOISTURE && readMoisture <= MAXIMUM_MOISTURE)
  {
    analogWrite(BLUE_RGB_PIN, readMoisture - MINIMUM_MOISTURE);
    analogWrite(RED_RGB_PIN, OFF);
  }
  else if (readMoisture > MAXIMUM_MOISTURE)
  {
    int writeRedPin = map(readMoisture, readMoisture - MAXIMUM_MOISTURE, 1023, 0, 255);
    analogWrite(RED_RGB_PIN, ON);
    analogWrite(BLUE_RGB_PIN, OFF);
  }
  else
  {
    int writeRedPin = map(readMoisture, 0, MINIMUM_MOISTURE, 255, 0);
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

