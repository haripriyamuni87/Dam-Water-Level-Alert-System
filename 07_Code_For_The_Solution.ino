#include <LiquidCrystal.h>
#include <Servo.h>

// LCD Pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Ultrasonic Sensor
const int trigPin = 9;
const int echoPin = 8;

// LEDs
const int greenLED = A0;
const int yellowLED = A1;
const int redLED = A2;

// Buzzer
const int buzzer = 6;

// Servo
Servo gateServo;

long duration;
float distance;

void setup()
{
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  pinMode(buzzer, OUTPUT);

  gateServo.attach(10);

  lcd.begin(16, 2);

  lcd.print("Dam Water");
  lcd.setCursor(0, 1);
  lcd.print("Alert System");

  delay(2000);
  lcd.clear();
}

void loop()
{
  // Trigger ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 0.0343 / 2;

  // Display distance
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Level:");
  lcd.print(distance, 1);
  lcd.print("cm");

  // SAFE
  if (distance > 50)
  {
    lcd.setCursor(0, 1);
    lcd.print("SAFE");

    digitalWrite(greenLED, HIGH);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, LOW);

    noTone(buzzer);

    gateServo.write(0);
  }

  // WARNING
  else if (distance > 30)
  {
    lcd.setCursor(0, 1);
    lcd.print("WARNING");

    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, LOW);

    tone(buzzer, 1000);
    delay(200);
    noTone(buzzer);

    gateServo.write(45);
  }

  // DANGER
  else
  {
    lcd.setCursor(0, 1);
    lcd.print("DANGER");

    digitalWrite(greenLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(redLED, HIGH);

    tone(buzzer, 2500);

    gateServo.write(90);
  }

  delay(500);
}