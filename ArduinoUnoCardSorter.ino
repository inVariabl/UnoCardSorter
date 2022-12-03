// Arduino Uno Card Sorter
// Sorts Uno Cards by their color
// Written by Jacob Greene & Daniel Crooks

#include <Servo.h>
//color sensor pins
const int s0 = 2;
const int s1 = 3;
const int s2 = 4;
const int s3 = 5;
const int outPin = 6;
const int servoPin = 8;

//current color
bool red = false;
bool green = false;
bool blue = false;
bool yellow = false;

Servo servo;

void setup()
{
  //output frequency pins
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  //color pins
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  //output pin
  pinMode(outPin, INPUT);

  Serial.begin(9600); //serial monitor, for debugging

  //start color sensor 100%
  digitalWrite(s0, HIGH);
  digitalWrite(s1, HIGH);

  servo.attach(servoPin);
}

void loop()
{
  SenseColors();
  delay(500);
}

void SenseColors()
{
  //input data variables
  int redData = 0;
  int greenData = 0;
  int blueData = 0;

  // RED FILTER
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  redData = pulseIn(outPin, LOW);

  // GREEN FILTER
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  greenData = pulseIn(outPin, LOW);

  // BLUE FILTER
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  blueData = pulseIn(outPin, LOW);

  CheckColor(redData, greenData, blueData);
  PrintRawData(redData, greenData, blueData);
}

void CheckColor(int redData, int greenData, int blueData)
{
  // lower values = higher amount of color
  if (redData < greenData && redData < blueData) red = true;
  else if (greenData < redData && greenData < blueData) blue = true;
  else if (blueData < redData && blueData < greenData) blue = true;
  else yellow = true;

  printColor(red, green, blue, yellow);
  moveServo(red, green, blue, yellow);
}

void moveServo(bool red, bool green, bool blue, bool yellow)
{
  if (red) servo.write(0);
  else if (green) servo.write(90);
  else if (blue) servo.write(180);
  else if (yellow) servo.write(270);
}

void printColor(bool red, bool green, bool blue, bool yellow) {
  if (red) Serial.print("RED");
  else if (green) Serial.print("GREEN");
  else if (blue) Serial.print("BLUE");
  else if (yellow) Serial.print("YELLOW");
  Serial.println(); // newline
}


void PrintRawData(int redData, int greenData, int blueData)
{
  Serial.print("R: ");
  Serial.print(redData);

  Serial.print(" G: ");
  Serial.print(greenData);

  Serial.print(" B: ");
  Serial.print(blueData);

  Serial.print(" = ");
}
