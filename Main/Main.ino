#define OFF 0
#define ON 255

int analogLightMeasuredPin = 5;
int analogMoistureMeasuredPin = 4;

int whiteLedPin = 9;

int blueRgbPin = 6;
int redRgbPin = 5;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(whiteLedPin, OUTPUT);
  pinMode(blueRgbPin, OUTPUT);
  pinMode(redRgbPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  lightDemo();
  moistureDemo();
  
  delay(250);
}

void lightDemo()
{
  int lightOutput = map(analogRead(analogLightMeasuredPin), 0, 1023, 255, 0);

  printMessage("lightOutput: ", lightOutput);

  analogWrite(whiteLedPin, lightOutput);
}

void moistureDemo()
{
  int readMoisture = map(analogRead(analogMoistureMeasuredPin), 0, 1023, -255, 255);

  printMessage("read moisture: ", readMoisture);
  
  if (readMoisture >= 0)
  {
    analogWrite(blueRgbPin, readMoisture);
    analogWrite(redRgbPin, OFF);
  }
  else
  {
    int writeRedPin = map(readMoisture, -255, -1, 255, 0);
    analogWrite(redRgbPin, writeRedPin);
    analogWrite(blueRgbPin, OFF);
  }
}

void printMessage(String message, int value)
{
  Serial.print(message);
  Serial.println(value);
}

